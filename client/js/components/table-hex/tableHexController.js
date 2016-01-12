angular.module('tableHexController', [])
	.controller('tableHexController',
		['$scope',
		 function ($scope) {
		 	subscribeOnPlayerList(getPlayerList);

		 	function getPlayerList (players) {
		 		var array = [];
		 		var currentPlayer = sessionStorage.playerName;

		 		for (singlePlayer in players) {
		 			if (currentPlayer !== singlePlayer)
		 				array.push({ name: singlePlayer });
		 		}

		 		$scope.$broadcast('tableHex:players', array);
		 		$scope.$broadcast('tableHex:currentPlayer', { name: currentPlayer })
		 	};
		 }]);