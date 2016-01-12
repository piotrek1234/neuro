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
					{ name: "", color: "" },
					{ name: "", color: "" },
					{ name: "", color: "" },
					{ name: "", color: "" }
				];

				$scope.$on('tableHex:players', setPlayers);

				function setPlayers (event, players) {
					players.forEach(function (singlePlayer, index) {
						$scope.players[index].name = singlePlayer.name;
						$scope.players[index].color = singlePlayer.color;
					});

					$scope.$apply();
				};
			},
			link: function ($scope, element, attr) {
				$scope.hexTable = element[0];
			}
		};
	});