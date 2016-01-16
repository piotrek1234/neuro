angular.module('operationBoardController', [])
	.controller('operationBoardController',
		['$scope',
		 function ($scope) {
		 	//TODO przenieść do kontrolera
				$scope.$on('main:selectToken', selectTokenHandler);
				$scope.$on('main:unselectToken', unselectTokenHandler);

				function selectTokenHandler (event, data) {
					var tokenType = data.$token.getAttribute("token-type");
					var isPutable = (tokenType === "putable");

					$scope.$broadcast('operationBoard:selectToken', {
						$token: data.$token,
						isPutable: isPutable
					});
				};

				function unselectTokenHandler (event, data) {
					$scope.$broadcast('operationBoard:unselectToken', data);
				};
		 }]);
