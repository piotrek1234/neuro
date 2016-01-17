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
						$scope.players[index].tokensCount = singlePlayer.tokensCount;

						$scope.players[index].tokens = singlePlayer.tokens;
					});

					$scope.$apply();
				};
			},
			link: function ($scope, element, attr) {
				$scope.$hexTable = element[0];

				$scope.$endTurnButton = $scope.$hexTable.querySelector(".button-end-turn");
				$scope.$endTurnButtonBack = $scope.$hexTable.querySelector(".end-turn-background-disabled")

				$scope.$on('userBoard:enable', setButtonEnabled);
				$scope.$on('userBoard:disable', setButtonDisabled);

				function setButtonEnabled () {
					d3.select($scope.$endTurnButtonBack)
						.classed("end-turn-background", true)
						.classed("end-turn-background-active", false)
						.classed("end-turn-background-disabled", false);
				};

				function setButtonDisabled () {
					d3.select($scope.$endTurnButtonBack)
						.classed("end-turn-background", false)
						.classed("end-turn-background-active", false)
						.classed("end-turn-background-disabled", true);
				};

				$scope.$endTurnButton.addEventListener('mouseenter', function (event) {
					var _srcElement = d3.select(event.target);
					if (_srcElement.classed("end-turn-background-disabled"))
						return;

					d3.select($scope.$endTurnButtonBack)
						.classed("end-turn-background", false)
						.classed("end-turn-background-active", true);
				});

				$scope.$endTurnButton.addEventListener('mouseleave', function (event) {
					var _srcElement = d3.select(event.target);

					if (_srcElement.classed("end-turn-background-disabled"))
						return;

					d3.select($scope.$endTurnButtonBack)
						.classed("end-turn-background", true)
						.classed("end-turn-background-active", false);
				});

				$scope.$endTurnButton.addEventListener('click', function (event) {
					var _srcElement = d3.select(event.target);

					if (_srcElement.classed("end-turn-background-disabled"))
						return;

					$scope.$emit("tableHex:endTurn");
				});
			}
		};
	});