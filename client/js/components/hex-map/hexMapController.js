angular.module('hexMapController', [])
	.controller('hexMapController',
		['$scope',
		 function ($scope) {
			$scope.$on("hexMap:putToken", putTokenHandler);

			subscribeOnTokenAdd(addTokenHandler);
			subscribeOnAddFailed(addTokenFaildHandler);

			subscribeOnGetBoard(getBoardHandler);

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
				if (data.color !== sessionStorage.playerColor) {
					$scope.$broadcast("hexMap:setSingleToken", data);
				}	
			};

			function addTokenFaildHandler (event, data) {
				// miejsce na wyswietlenie popup'u niepowodzenia
				socketServer.getBoard();
			};

			function getBoardHandler (tokens) {
				var msg = [];

				tokens.forEach(function (singleToken) {
					var params = {
						q: singleToken.q,
						r: singleToken.r,
						angle: singleToken.token.angle,
						name: singleToken.token.name,
						id: singleToken.token.id
					};

					msg.push(params);
				});

				$scope.$broadcast("hexMap:setAllMap");
			};

		 }]);