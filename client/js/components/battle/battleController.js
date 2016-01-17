angular.module('battleController', [])
	.controller('battleController',
		['$scope',
		 function ($scope) {			
			subscribeOnAfterBattle(endBattleHandler);

			function startBattleHandler () {

			};

			function endBattleHandler (board, players) {
				// wysłać event do map o nowym rozkładzie tokenów
				$scope.$emit('battle:newBoard', { board: board });
				// wysłać event do user-board o stanie graczy
				$scope.$emit('battle:newPlayersList', { players: players });

				$scope.$broadcast('battlePopup:open');
				setTimeout(function ($scope) { 
					$scope.$broadcast('battlePopup:close');
				}, 3000, $scope);
			};
		 }]);