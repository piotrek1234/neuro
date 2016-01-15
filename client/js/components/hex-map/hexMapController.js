angular.module('hexMapController', [])
	.controller('hexMapController',
		['$scope',
		 function ($scope) {
			$scope.$on("hexMap:putToken", putTokenHandler);

			subscribeOnTokenAdd(addTokenHandler);

			function putTokenHandler (event, data) {
				var msg = {
					q: parseInt(data.q),
					r: parseInt(data.r),
					id: parseInt(data.id),
					angle: parseInt(data.angle)
				}

				socketServer.putToken(data);
				// console.log(data);
			};

			function addTokenHandler (data) {
				// console.log(data);
			};

		 }]);