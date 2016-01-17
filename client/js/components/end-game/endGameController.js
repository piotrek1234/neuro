angular.module('endGameController', [])
	.controller('endGameController',
		['$scope',
		 function ($scope) {			
			subscribeOnGameEnd(endGameHandler);

			function endGameHandler (winner) {
				console.log(winner);
				$scope.$broadcast("endGamePopup:open", { winner: winner });
			};
		 }]);