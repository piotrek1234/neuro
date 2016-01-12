angular.module('tableHexController', [])
	.controller('tableHexController',
		['$scope',
		 function ($scope) {
		 	$scope.isGameStarted = false;

		 	subscribeOnPlayerList(playerListChangeHandler);

		 	function playerListChangeHandler (players) {
		 		getPlayersList(players);
		 	};

		 	function getPlayersList (players) {
		 		var array = [];
		 		var currentPlayer = {
		 			name: sessionStorage.playerName,
		 			color: null
		 		};

		 		for (singlePlayer in players) {
		 			if (currentPlayer.name !== singlePlayer) {
		 				array.push({ 
		 					name: singlePlayer,
		 					color: decodeColor(players[singlePlayer].color)
		 				});
		 			} else {
		 				currentPlayer.color = decodeColor(players[singlePlayer].color);
		 			}
		 		}

		 		// uzupełnianie pustych stanowisk
		 		for (var i=array.length; i<3; i++) {
		 			array.push({
		 				name: "",
		 				color: ""
		 			})
		 		}

		 		// aby gracz z sesji był ostatni w tablicy
		 		array.push(currentPlayer);

		 		$scope.$broadcast('tableHex:players', array);
		 	};

		 	function decodeColor (colorId) {
		 		var result = "";

		 		switch (colorId) {
		 			case 1:
			 			result = "blue";
			 			break;
		 		
		 			case 2:
			 			result = "red";
			 			break;

		 			case 3:
			 			result = "yellow";
			 			break;

		 			case 4:
			 			result = "green";
			 			break;
		 		}

		 		return result;
		 	};

		 }]);