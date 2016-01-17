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
				$scope.$validation = document.querySelector(".validation");

				element.on("click", clickHandler);
				$scope.$on("popup:close", closePopupHandler);
				$scope.$on("popup:playerList", setPlayerList);

				$scope.$on("popup:joinedSucess", joinedSucessHandler);
				$scope.$on("popup:joinedError", joinedErrorHandler);

				function joinedSucessHandler (event, data) {
					var $login = $scope.$popup.querySelector('input');

					$login.disabled = true;
				};

				function joinedErrorHandler (event, data) {
					var $validation = $scope.$validation;

					$validation.textContent = data.reason;
				};

				function clickHandler (event) {
					var $srcElement = event.target;

					if (checkIsButton($srcElement) 
						&& checkIsEnable($srcElement)) {

						if (!validateInputName()) {
							return;
						}

						if (checkIsReadyFromButton($srcElement)) {
							sendSetPlayerReady($srcElement);
						} else {
							sendSetPlayer($srcElement);
						}

						setPopupDisabled();
					}
				};

				function checkIsReadyFromButton ($element) {
					return d3.select($element)
								.classed("button player-button-red");
				};

				function checkIsButton ($element) {
					return d3.select($element)
								.classed("button");
				};

				function checkIsEnable ($element) {
					return !d3.select($element)
								.classed("player-button-disabled") 
							&& !d3.select($element)
								.classed("player-button-yellow")
							&& !d3.select($element)
								.classed("player-button-green");
				};

				function sendSetPlayer ($element) {
					var login = getPlayerLogin();

					$scope.$emit('popup:selectPlayer', {login: login});
				};

				function sendSetPlayerReady ($element) {
					var login = getPlayerLogin();

					$scope.$emit('popup:playerReady', {login: login});
				};

				function getPlayerLogin () {
					var $login = document.getElementById("login-input");

					return $login.value;
				}

				function validateInputName () {
					var result = null;

					var $validationBox = $scope.$validation;
					var login = getPlayerLogin();

					if (login != null && login != "") {
						$validationBox.textContent = "";

						result = true;
					} else {
						$validationBox.textContent = "Niepoprawny login";

						result = false;
					}
					
					return result;
				};

				function closePopupHandler (event, data) {
					var $popup = $scope.$popup;
					var $overlay = document.getElementById("main-overlay");

					$popup.parentElement.removeChild($popup);
					$overlay.style.visibility = "hidden";
				};

				function setPopupDisabled () {
					var $popup = $scope.$popup;
					var $buttons = $scope.$buttons;
					var $login = $popup.querySelector('input');

					[].forEach.call($buttons, function ($item) {
						$item.setAttribute('class', 'button player-button-yellow');
					});
 
					$login.disabled = true;
				};

				function setPlayerList (event, players) {
					var isCurrentPlayer = false;

					players.forEach(function (element) {
						if (element.isCurrentPlayer) 
							isCurrentPlayer = true;
					});
					
					for (var i=players.length; i<4; i++) {
						players.push({noPlayer: true, hasCurrent: isCurrentPlayer});
					}

					players.forEach(setSinglePlayerButton);
				};

				function setSinglePlayerButton (player, index) {
					var $button = $scope.$buttons[index];
					
					switch (true) {
						case checkIsNoPlayer(player) && !checkHasCurrentPlayer(player):
						$button.setAttribute('class', 'button player-button-blue');
						$button.text = "wolny";
						break;

						case checkIsNoPlayer(player):
						$button.setAttribute('class', 'button player-button-yellow');
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

				function checkHasCurrentPlayer (player) {
					return !!player.hasCurrent;
				};

				function checkIsNoPlayer (player) {
					return !!player.noPlayer;
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