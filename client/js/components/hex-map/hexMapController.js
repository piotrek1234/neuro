angular.module('hexMapController', [])
	.controller('hexMapController',
		['$scope',
		 function ($scope) {
			$scope.$on("hexMap:putToken", putTokenHandler);
			$scope.$on("hexMap:newBoard" , getNewBoardHandler)

			subscribeOnTokenAdd(addTokenHandler);
			subscribeOnAddFailed(addTokenFaildHandler);

			subscribeOnGetBoard(getBoardHandler);

			function putTokenHandler (event, data) {
				var msg = {
					q: parseInt(data.q),
					r: parseInt(data.r),
					id: parseInt(data.id),
					angle: (-1)*parseInt(data.angle)
				}
				console.log("hexMapController#putTokenHandler");
				console.log(msg);
				socketServer.putToken(msg);
			};

			function addTokenHandler (data) {
				data.angle *= -1;
				console.log(data);
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
				console.log("hexMapController#getBoardHandler");
				console.log(tokens);
				tokens.forEach(function (singleToken) {
					var params = {
						q: singleToken.q,
						r: singleToken.r,
						angle: (-1)*singleToken.token.angle,
						name: singleToken.token.name,
						id: singleToken.token.id
					};

					msg.push(params);
				});

				$scope.$broadcast("hexMap:setAllMap", msg);
			};

			function getNewBoardHandler (event, data) {
				getBoardHandler(data.board);
			};
		 }]);