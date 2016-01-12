angular.module('userBoardDirective', [])
	.directive('userBoard', function () {
		return {
			restrict: 'E',
			scope: {
				x: "=",
				y: "=",
				color: "=",
				sizeBase: "=",
				login: "=",
				draggable: "=",
				dropable: "=",

				click: "="
			},
			templateNamespace: 'svg',
			templateUrl: 'js/components/user-board/userBoard.html',
			replace: true,
			controller: function ($scope) {
				var hexLibrary = new hexLibraryConstructor();
				var sizeBase = $scope.sizeBase;

				$scope.player = {};
				$scope.player.name = "Tomek"

				hexLibrary.setLayoutSize(Point(sizeBase, sizeBase));
				
				var cornersSet = [];
				cornersSet.push(hexLibrary.setHexCorners(Point(sizeBase*1.5, sizeBase)));
				cornersSet.push(hexLibrary.setHexCorners(Point(sizeBase*4, sizeBase)));
				cornersSet.push(hexLibrary.setHexCorners(Point(sizeBase*6.5, sizeBase)));
				
				$scope.cornersSet = cornersSet;

				$scope.className = "board board-" + $scope.color;
			},
			link: function ($scope, element, attr) {
				$scope.$userBoard = element[0];

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

				function setPlayerToken (tokens) {
					var $hexPlace = $scope.$userBoard.querySelector(".hex");

					
				};
				
				$scope.$watch("login.name", function (newLogin, oldlogin) {
					console.log(newLogin);
					$scope.player.name = newLogin;
				});

				//TODO event zmainy tokenów
			}
		};
	});