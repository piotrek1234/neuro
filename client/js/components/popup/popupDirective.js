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
					var actualPlayer = getActualPlayer(players);
					
					if (!actualPlayer) {
						setButtonsNoActual(players);
					} else if (actualPlayer.isReady) {
						setButtonsActualReady(players);
					} else {
						setButtonsActual(players);
					}
				};

				function setButtonsActualReady (players) {
					var colors = ["red", "green", "blue", "yellow"];
					var $buttons = $scope.$buttons;

					[].forEach.call($buttons, function ($button, index) {
						var player = players[index];
						var colorIndex = null;

						if (!player) {
							$button.setAttribute('class', 'button player-button-disabled');
							colorIndex = 0;
							$button.text = 'wolny - ' + colors[colorIndex];
						} else {
							var text = player.isReady ? ' (r) ' : '';
							$button.setAttribute('class', 'button player-button-disabled');
							$button.text = player.login + text + player.color;
							colorIndex = colors.indexOf(player.color);
						}
						
						colors.splice(colorIndex, 1);
					});
				};

				function setButtonsActual (players) {
					var colors = ["red", "green", "blue", "yellow"];
					var $buttons = $scope.$buttons;

					[].forEach.call($buttons, function ($button, index) {
						var player = players[index];
						var colorIndex = null;
						
						if (!player) {
							$button.setAttribute('class', 'button player-button-disabled');
							colorIndex = 0;
							$button.text = 'wolny - ' + colors[colorIndex];
						} else if (player.isActual) {
							$button.setAttribute('class', 'button player-button-' + player.color);
							$button.text = 'GRAJ!';
							$button.setAttribute("play", "true");
							colorIndex = colors.indexOf(player.color);
						} else {
							var text = player.isReady ? ' (r) ' : '';
							$button.setAttribute('class', 'button player-button-disabled');
							$button.text = player.login + text + ' - ' + player.color;
							colorIndex = colors.indexOf(player.color);
						}

						colors.splice(colorIndex, 1);
					});
				};

				function setButtonsNoActual (players) {
					var colors = ["red", "green", "blue", "yellow"];
					var $buttons = $scope.$buttons;

					[].forEach.call($buttons, function ($button, index) {
						var player = players[index];
						var colorIndex = null;

						if (!player) {
							$button.setAttribute('class', 'button player-button-disabled');
							colorIndex = 0;
							$button.text = 'wolny - ' + colors[colorIndex];
						} else {
							var text = player.isReady ? ' (r) ' : '';
							$button.setAttribute('class', 'button player-button-disabled');
							$button.text = player.login + text + player.color;
							colorIndex = colors.indexOf(player.color);
						}

						colors.splice(colorIndex, 1);
					});
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