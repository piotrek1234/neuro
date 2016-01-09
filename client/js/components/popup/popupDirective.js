angular.module('popupDirective', [])
	.directive('popup', function () {
		return {
			restrict: 'E',
			scope: {
			
			},
			templateUrl: 'js/components/popup/popup.html',
			replace: true,
			controller: function ($scope) {
				
			},
			link: function ($scope, element, attr) {
				element.on('click', clickHandler);
				var validationBox = "totot";

				function clickHandler (event) {
					var $srcElement = event.target;

					if (checkIsButton($srcElement) 
						&& checkIsEnable($srcElement)) {

						sendSetPlayerEvent($srcElement);
					}
				};

				function checkIsButton ($element) {
					return d3.select($element)
								.classed("button");
				};

				function checkIsEnable ($element) {
					return !d3.select($element)
								.classed("player-button-disabled");
				};

				function sendSetPlayerEvent ($element) {
					if (!validateInputName()) {
						return;
					}
					
					var color = getPlayerColor($element);
					var login = getPlayerLogin();

					$scope.$emit('popup:selectPlayer', {login: login, color: color});
				};

				function getPlayerColor ($element) {
					var result = null;
					var buttonClass = $element.classList[1];
					
					switch (buttonClass) {
						case "player-button-red":
						result = "red";
						break;

						case "player-button-green":
						result = "green";
						break;

						case "player-button-yellow":
						result = "yellow";
						break;

						case "player-button-blue":
						result = "blue";
						break;
					}

					return result;
				};

				function getPlayerLogin () {
					var $login = document.getElementById("login-input");

					return $login.value;
				}

				function validateInputName () {
					var result = null;

					var $validationBox = document.querySelector(".validation");
					var login = getPlayerLogin();

					if (login != null && login != "") {
						$validationBox.style.visibility = "hidden";

						result = true;
					} else {
						$validationBox.style.visibility = "visible";

						result = false;
					}
					
					return result;
				};
			}
		};
	});