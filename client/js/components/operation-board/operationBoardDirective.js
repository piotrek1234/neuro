angular.module('operationBoardDirective', [])
	.directive('operationBoard', function () {
		return {
			restrict: 'E',
			scope: {
				hexSize: '='
			},
			templateNamespace: 'svg',
			templateUrl: 'js/components/operation-board/operationBoard.html',
			replace: true,
			controller: function ($scope) {
			 	function setupParameters() {
			 		setMainBoardParameters();
					setBoardParameters();
					setLeftArrowParameters();
					setRightArrowParameters();
					setActionButtonParameters();
					setDropButtonParameters();
			 	};

			 	function setMainBoardParameters () {
			 		var mainBoard = {
						width: hexSize*8,
						height: hexSize*4
					};

			 		$scope.mainBoard = mainBoard;
			 	};

			 	function setBoardParameters () {
					var board = {
						x: hexSize/2,
						y: hexSize/2,
						width: hexSize*7,
						height: hexSize*2
					};

					$scope.board = board;

					setHexCenter(board);
			 	};

				function setHexCenter (board) {
					$scope.hexCenterX = board.x + board.width/2;
					$scope.hexCenterY = board.y + board.height/2;		
				};

				function setLeftArrowParameters () {
					var leftArrow = {
						x: hexSize*1,
						y: hexSize*0.75,
						width: 112,
						height: 50
					};

					$scope.leftArrow = leftArrow;
				};

				function setRightArrowParameters () {
					var rightArrow = {
						x: hexSize*1,
						y: hexSize*1.6,
						width: 112,
						height: 50
					};

					$scope.rightArrow = rightArrow;
				};

				function setActionButtonParameters () {
					var actionButton = {
						x: hexSize*5.5,
						y: hexSize*0.75,
						width: 112,
						height: 50
					};

					$scope.actionButton = actionButton;
				};

				function setDropButtonParameters () {
					var dropButton = {
						x: hexSize*5.5,
						y: hexSize*1.6,
						width: 112,
						height: 50
					};

					$scope.dropButton = dropButton;
				};

				var hexSize = $scope.hexSize;
	 
				setupParameters();
			},
			link: function ($scope, element, attr) {
				$scope.$board = element[0];
				$scope.defaultCssClass = null;

				$scope.$buttons = $scope.$board.querySelectorAll(".board-button");
				$scope.$actionButton = null;
				$scope.$removeTokenButton = null;
				$scope.$rotationButtons = [];

				$scope.action = null;

				$scope.$on('operationBoard:selectToken', selectTokenHandler);
				$scope.$on('operationBoard:unselectToken', unselectTokenHandler);

				$scope.$on('operationBoard:actionButton', actitonButtonActivationHandler);
				$scope.$on('operationBoard:rotationButtons', rotationButtonsActivationHandler);

				function setupDOMElements () {
					$scope.$leftArrow = document.getElementById("left-arrow");
					$scope.$rightArrow = document.getElementById("right-arrow");
				};

				function setupEventHandlers () {
					$scope.$rightArrow.addEventListener("click", clickRightArrowHandler.bind(this));
					$scope.$leftArrow.addEventListener("click", clickLeftArrowHandler.bind(this));

					$scope.$removeTokenButton.addEventListener("click", clickRemoveTokenHandler.bind(this));
					$scope.$actionButton.addEventListener("click", clickActionButtonHandler.bind(this));
				};

				function clickRightArrowHandler (event) {
					event.stopPropagation();

					if (checkButtonIsDisabled(event.target))
						return;

					rotateRight($scope.$selectedToken);
					rotateRight($scope.$boardItem);
				};

				function clickLeftArrowHandler (event) {
					event.stopPropagation();

					if (checkButtonIsDisabled(event.target))
						return;

					rotateLeft($scope.$selectedToken);
					rotateLeft($scope.$boardItem);
				};

				function clickRemoveTokenHandler (event) {
					if (checkButtonIsDisabled(event.target)) {						
						return;
					}

					removeToken($scope.$selectedToken);
				};

				function clickActionButtonHandler (event) {
					if (checkButtonIsDisabled(event.target)) {						
						return;
					}

					var tokenId = d3.select($scope.$selectedToken).attr("token-id");


					switch ($scope.action) {
						case "move":
						$scope.$emit('action:move', { tokenId: tokenId });
						break;


						case "push":
						$scope.$emit('action:push', { tokenId: tokenId });
						break;

						case "battle":
						$scope.$emit('operationBoard:battle', { tokenId: tokenId });
						break;
					}
				};

				function removeToken ($token) {
					var _token = d3.select($token);
					var tokenId = _token.attr("token-id");					

					$scope.$emit('operationBoard:removeToken', { tokenId: tokenId });
				};

				function rotateRight ($element) {
					rotate($element, -60);
				};

				function rotateLeft ($element) {
					rotate($element, 60);
				};

				function rotate($element, angle) {
					var hexLibrary = new hexLibraryConstructor();
					var corners = d3.select($element).attr("points");
					var center = hexLibrary.getHexCenter(corners);

					var svgOperations = new svgOperationsLibraryConstructor();
					var angleCurrent = svgOperations.getRotateAngle($element);

					angle += angleCurrent;
					disableRotationButtons();
					
					d3.select($element)
						.transition()
						.attr("transform", "rotate(" + angle + " " + center.x + " " + center.y + ")")
					.duration(1000)
					.each("end", activeRotationButtons);
				};

				function selectTokenHandler (event, data) {
					var svgOperations = new svgOperationsLibraryConstructor();
					var hexLibrary = new hexLibraryConstructor();

					$scope.$selectedToken = data.$token;
					$scope.$boardItem = document.querySelector("polygon[ng-moving=true]");

					var cssTokenClass = d3.select($scope.$selectedToken)
						.attr("class");

					var fillAtribute = d3.select($scope.$selectedToken)
						.attr("fill");

					$scope.defaultCssClass = d3.select($scope.$boardItem)
						.attr("class");

					var rotateAngle = svgOperations.getRotateAngle(data.$token);
					var center = hexLibrary.getHexCenter($scope.$boardItem.getAttribute("points"));

					d3.select($scope.$boardItem)
						.attr("class", cssTokenClass)
						.attr("fill", fillAtribute)
						.attr("transform", "rotate(" + rotateAngle + ", " + center.x + ", " + center.y + ")")
						.classed("token-selected", false);

					if (data.isPutable) {
						rotationButtonsActivationHandler();
					} else {
						actitonButtonActivationHandler();
						$scope.action = d3.select($scope.$selectedToken)
											.attr("action");
					}

					setButtonBackground($scope.$removeTokenButton, "board-button-background");
				};

				function unselectTokenHandler (event, data) {
					d3.select($scope.$boardItem)
						.attr("class", $scope.defaultCssClass)
						.attr("fill", null)
						.attr("transform", "rotate(0)");

					deactiveAllButtons();

					$scope.$selectedToken = null;
					$scope.$boardItem = null;
					$scope.action = null;
				};

				function setButtonBackground ($button, buttonClass) {
					var buttonId = d3.select($button).attr("id");
					var $buttonBackground = document.getElementById(buttonId + "-background");

					$buttonBackground.setAttribute("class", buttonClass);
				};

				function checkButtonIsDisabled ($button) {
					var buttonId = d3.select($button).attr("id");
					var _buttonBackground = d3.select("#" + buttonId + "-background");

					return _buttonBackground.classed("board-button-background-disabled");
				};

				function actitonButtonActivationHandler () {
					disableRotationButtons();
					setButtonBackground($scope.$actionButton, "board-button-background");
				};

				function rotationButtonsActivationHandler () {
					activeRotationButtons();
					setButtonBackground($scope.$actionButton, "board-button-background-disabled");
				};

				function activeRemoveTokenHandler (event) {
					setButtonBackground($scope.$removeTokenButton, "board-button-background");
				};

				function deactiveAllButtons () {
					disableRotationButtons();
					setButtonBackground($scope.$actionButton, "board-button-background-disabled");
					setButtonBackground($scope.$removeTokenButton, "board-button-background-disabled");
				};

				function disableRotationButtons () {
					$scope.$rotationButtons.forEach(function ($button) {
						setButtonBackground($button, "board-button-background-disabled");
					});
				};

				function activeRotationButtons () {
					$scope.$rotationButtons.forEach(function ($button) {
						setButtonBackground($button, "board-button-background");
					});
				};

				[].forEach.call($scope.$buttons, function ($button) {
					$button.addEventListener('mouseenter', function (event) {
						var $srcElement = event.target;
						if (checkButtonIsDisabled($srcElement)) 
							return;

						setButtonBackground($srcElement, "board-button-background-active");
					});

					$button.addEventListener('mouseleave', function (event) {
						var $srcElement = event.target;
						if (checkButtonIsDisabled($srcElement))
							return;

						setButtonBackground($srcElement, "board-button-background");
					});	

					var _button = d3.select($button);

					if (_button.classed('rotation-button')) {
						$scope.$rotationButtons.push($button);
						
					} else if (_button.classed('action-button')) {
						$scope.$actionButton = $button;
					} else {
						$scope.$removeTokenButton = $button;
					}

					setButtonBackground($button, "board-button-background-disabled");
				});
				
				setupDOMElements();
				setupEventHandlers();
			}
		};
	});