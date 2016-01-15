angular.module('hexMapController', [])
	.controller('hexMapController',
		['$scope',
		 function ($scope) {
			$scope.$on("hexMap:putToken", putTokenHandler);

			subscribeOnTokenAdd(addTokenHandler);
			subscribeOnAddFailed(addTokenFaildHandler);

			function putTokenHandler (event, data) {
				var msg = {
					q: parseInt(data.q),
					r: parseInt(data.r),
					id: parseInt(data.id),
					angle: parseInt(data.angle)
				}

				socketServer.putToken(msg);
			};

			function addTokenHandler (data) {
				console.log(data);
				if (data.color !== sessionStorage.playerColor) {
					$scope.$broadcast("hexMap:setSingleToken", data);
				}	
			};

			function addTokenFaildHandler (event, data) {
				console.log("addTokenFaildHandler");
				// strzał po aktualny stan planszy
				// odświerzenie starego stanu planszy
			};

		 }]);