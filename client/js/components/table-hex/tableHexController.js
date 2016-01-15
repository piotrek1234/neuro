angular.module('tableHexController', [])
	.controller('tableHexController',
		['$scope',
		 function ($scope) {
		 	$scope.isGameStarted = false;

		 	$scope.players = [];

		 	subscribeOnPlayerList(playerListChangeHandler);
		 	subscribeOnTurn(playerTurnChangeHandler);

		 	function playerListChangeHandler (players) {
		 		getPlayersList(players);
		 	};

		 	function getPlayersList (players) {
		 		playersSetDefaultValue();

		 		var currentPlayerName = sessionStorage.playerName;
		 		var index = 0;
		 		
		 		for (singlePlayer in players) {
		 			if (currentPlayerName !== singlePlayer) {
		 				$scope.players[index].name = singlePlayer;
		 				$scope.players[index].color = decodeColor(players[singlePlayer].color);
		 				index++;
		 			} else {
		 				//ostatni element to gracz aktualny
		 				$scope.players[$scope.players.length-1].name = singlePlayer;
		 				$scope.players[$scope.players.length-1].color = decodeColor(players[singlePlayer].color);
		 			}
		 		}		 		

		 		$scope.$broadcast('tableHex:players', $scope.players);
		 	};

		 	function playersSetDefaultValue () {
				$scope.players = [
			 		{ name: "", color: "", turn: false, tokens: [] },
			 		{ name: "", color: "", turn: false, tokens: [] },
			 		{ name: "", color: "", turn: false, tokens: [] },
			 		{ name: "", color: "", turn: false, tokens: [] }
			 	];
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

		 	function playerTurnChangeHandler (login, tokens, tokensCount) {
		 		$scope.players.forEach(function (player) {
		 			if (player.name === login) {
		 				player.turn = true;
		 				player.tokens = tokens;
		 			} else {
		 				player.turn = false;
		 			}
		 		});

		 		$scope.$broadcast('tableHex:players', $scope.players);
		 	};

		 	playersSetDefaultValue();

		 }]);