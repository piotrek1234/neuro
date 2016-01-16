angular.module('userBoardDirective', [])
	.directive('userBoard', function () {
		return {
			restrict: 'E',
			scope: {
				x: "=",
				y: "=",
				color: "=",
				sizeBase: "=",
				player: "=",
				draggable: "=",
				dropable: "=",
				isUser: "=",

				click: "="
			},
			templateNamespace: 'svg',
			templateUrl: 'js/components/user-board/userBoard.html',
			replace: true,
			controller: function ($scope) {
				var hexLibrary = new hexLibraryConstructor();
				var sizeBase = $scope.sizeBase;

				hexLibrary.setLayoutSize(Point(sizeBase, sizeBase));
				
				var cornersSet = [];
				cornersSet.push(hexLibrary.setHexCorners(Point(sizeBase*1.5, sizeBase)));
				cornersSet.push(hexLibrary.setHexCorners(Point(sizeBase*4, sizeBase)));
				cornersSet.push(hexLibrary.setHexCorners(Point(sizeBase*6.5, sizeBase)));
				
				$scope.cornersSet = cornersSet;

				$scope.loginClassName = "board";
				$scope.boardClassName = "board-empty";
			},
			link: function ($scope, element, attr) {
				$scope.$userBoard = element[0];
				$scope.$overlay = $scope.$userBoard.querySelector(".user-overlay");

				if ($scope.isUser) {
					$scope.$on("userBoard:disable", userBoardDisableHandler);
				}	$scope.$on("userBoard:enable", userBoardEnableHandler);
					
				function userBoardDisableHandler () {
					$scope.$overlay.style.display = "block";
				};

				function userBoardEnableHandler () {
					$scope.$overlay.style.display = "none";
				};

				if (!!$scope.click) {
					element.on('click', clickHandler);
				}

				function clickHandler (event) {
					var $srcElement = event.target;
					var _element = d3.select($srcElement);
					
					if (!_element.classed("token") 
						|| _element.classed("hex-empty")) {
						return;
					}
					
					event.preventDefault();
					event.stopPropagation();

					unselectElement();
					selectElement($srcElement);
					setupBodyEventHandler();
				};

				function selectElement ($element) {
					var _element = d3.select($element);

					_element
						.classed("token-selected", true);

					emitSelectClickHandler($element);
				};

				function unselectElement () {
					d3.select(".token-selected")
						.classed("token-selected", false);

					emitUnselectClickHandler();
				};

				function setupBodyEventHandler () {
					var _body = d3.select("body");

					_body
						.on("click", clickBodyHandler);
				}

				function removeBodyClickHandler () {
					var _body = d3.select("body");

					_body
						.on("click", null);
				};

				function clickBodyHandler () {
					unselectElement();
					removeBodyClickHandler();
				};

				function emitSelectClickHandler ($element) {
					$scope.$emit('token:select', {$token: $element});
				};

				function emitUnselectClickHandler () {
					$scope.$emit('token:unselect', {});
				};

				$scope.$watch("player.color", function (newColor) {
					$scope.loginClassName = "board board-" + newColor;
				});

				$scope.$watch("player.turn", function (newTurn) {
					if (newTurn) {
						$scope.boardClassName = "board-active";
					} else {
						$scope.boardClassName = "board-empty";
					}
				});

				$scope.$watch("player.tokens", function (newTokens) {
					var $tokens = $scope.$userBoard.querySelectorAll("polygon");

					[].forEach.call($tokens, function ($singleToken, index) {
						if (newTokens[index]) {
							d3.select($singleToken)
								.classed("hex-empty", false)
								.classed("token", true);

							$singleToken.setAttribute("token-type", newTokens[index].type);
							$singleToken.setAttribute("token-id", newTokens[index].id);
							$singleToken.setAttribute("fill", "url(#" + newTokens[index].name + ")");
						} else {
							d3.select($singleToken)
								.classed("hex-empty", true)
								.classed("token", false);
							$singleToken.removeAttribute("fill");
						}
					});
				});
			}
		};
	});