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
					{ name: "" },
					{ name: "" },
					{ name: "" },
					{ name: "" }
				];

				$scope.$on('tableHex:players', setPlayers);
				$scope.$on('tableHex:currentPlayer', setCurrentPlayer);

				function setPlayers (event, players) {
					$scope.players = players;
					$scope.$apply();
				};

				function setCurrentPlayer (event, currentPlayer) {
					debugger;
					$scope.currentPlayer = currentPlayer;
					$scope.$apply();
				};
			},
			link: function ($scope, element, attr) {
				$scope.hexTable = element[0];
			}
		};
	});