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
				$scope.$popup = element[0];
				$scope.$buttons = $scope.$popup.querySelectorAll(".button");

				element.on("click", clickHandler);
				$scope.$on("popup:close", closePopupHandler);
				$scope.$on("popup:playerList", setPlayerList);

				var validationBox = null;

				function clickHandler (event) {
					var $srcElement = event.target;

					if (checkIsButton($srcElement) 
						&& checkIsEnable($srcElement)) {

						if (!validateInputName()) {
							return;
						}

						if (checkIsReady($srcElement)) {
							sendSetPlayerReady($srcElement);
						} else {
							sendSetPlayerEvent($srcElement);
							setPopupDisabled();
						}
					}
				};

				function checkIsReady ($element) {
					return !!$element.getAttribute("play");
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
					var color = getPlayerColor($element);
					var login = getPlayerLogin();

					$scope.$emit('popup:selectPlayer', {login: login, color: color});
				};

				function sendSetPlayerReady ($element) {
					var color = getPlayerColor($element);
					var login = getPlayerLogin();

					$scope.$emit('popup:playerReady', {login: login, color: color});
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

				function closePopupHandler (event, data) {
					var $popup = $scope.$popup;
					var $overlay = document.querySelector(".overlay");

					$popup.parentElement.removeChild($popup);
					$overlay.style.visibility = "hidden";
				};

				function setPopupDisabled () {
					var $popup = $scope.$popup;
					var $buttons = $scope.$buttons;
					var $login = $popup.querySelector('input');

					[].forEach.call($buttons, function ($item) {
						$item.setAttribute('class', 'button player-button-disabled');
					});
 
					$login.disabled = true;
				};

				function setPlayerList (event, players) {
					for (var i=players.length; i<4; i++) {
						players.push({});
					}


					players.forEach(setSinglePlayerButton);
				};

				function setSinglePlayerButton (player, index) {
					var $button = $scope.$buttons[index];
					
					switch (true) {
						case checkIsPlayer(player):
						$button.setAttribute('class', 'button player-button-blue');
						$button.text = "wolny";
						break;

						case checkIsCurrentPlayer(player) && !checkIsReady(player):
						$button.setAttribute('class', 'button player-button-red');
						$button.text = player.login;
						break;

						case !checkIsReady(player):
						$button.setAttribute('class', 'button player-button-yellow');
						$button.text = player.login;
						break;

						default:
						$button.setAttribute('class', 'button player-button-green');
						$button.text = player.login;
					}
				} 

				function checkIsReady (player) {
					return player.isReady;
				};

				function checkIsCurrentPlayer (player) {
					return player.isCurrentPlayer;
				};

				function checkIsPlayer (player) {
					return Object.keys(player).length === 0;
				};

				function getActualPlayer (players) {
					var actualPlayer = null;

					players.forEach(function (player) {
						if (player.isActual) {
							actualPlayer = player;
						}
					});

					return actualPlayer;
				};
				
				$scope.$emit("popup:rendered");
			}
		};
	});