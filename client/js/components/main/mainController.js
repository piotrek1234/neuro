angular.module('mainController', [])
	.controller('mainController',
		['$scope',
		 function ($scope) {
		 	$scope.mapSize = 2;
		 	$scope.hexSize = 75;

		 	var userBoard = {
		 		width: 500,
		 		height: 300
		 	};

		 	$scope.userBoard = userBoard;

		 	$scope.$on('token:select', selectTokenHandler);
			$scope.$on('token:unselect', unselectTokenHandler);

			$scope.$on('battle:newBoard', newBoardHandler);
			$scope.$on('battle:newPlayersList', newPlayersList);

			function selectTokenHandler (event, data) {
				$scope.$broadcast('main:selectToken', data);
			};

			function unselectTokenHandler (event, data) {
				$scope.$broadcast('main:unselectToken', data);
			};

			function newBoardHandler (event, data) {
				$scope.$broadcast('hexMap:newBoard', data);
			};

			function newPlayersList (event, data) {
				console.log(data);
			};
		 }]);