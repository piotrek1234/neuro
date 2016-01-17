angular.module('tableHexDirective', [])
	.directive('tableHex', function ($timeout) {
		return {
			restrict: 'E',
			scope: {
				hexSize: '='
			},
			templateNamespace: 'svg',
			templateUrl: 'js/components/table-hex/tableHex.html',
			replace: true,
			controller: function ($scope) {
				$scope.players = [
					{ name: "", color: "", turn: false, tokens: [], tokensCount: 0, life: 0 },
					{ name: "", color: "", turn: false, tokens: [], tokensCount: 0, life: 0 },
					{ name: "", color: "", turn: false, tokens: [], tokensCount: 0, life: 0 },
					{ name: "", color: "", turn: false, tokens: [], tokensCount: 0, life: 0 }
				];

				$scope.$on('tableHex:players', setPlayers);

				function setPlayers (event, players) {
					players.forEach(function (singlePlayer, index) {
						$scope.players[index].name = singlePlayer.name;
						$scope.players[index].color = singlePlayer.color;
						$scope.players[index].turn = singlePlayer.turn;
						$scope.players[index].life = singlePlayer.life;

						$scope.players[index].tokens = singlePlayer.tokens;
					});

					$scope.$apply();
				};
			},
			link: function ($scope, element, attr) {
				$scope.$hexTable = element[0];

				$scope.$endTurnButton = $scope.$hexTable.querySelector(".button-end-turn");

				$scope.$endTurnButton.addEventListener('click', function (event) {
					$scope.$emit("tableHex:endTurn");
				});
			}
		};
	});