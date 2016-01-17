angular.module('tableHexController', [])
	.controller('tableHexController',
		['$scope',
		 function ($scope) {
		 	$scope.isGameStarted = false;

		 	$scope.players = [];

		 	$scope.$on("tableHex:endTurn", endTurnHandler);
		 	$scope.$on("tableHex:newPlayersList", newPlayersListHandler);

		 	subscribeOnPlayerList(playerListChangeHandler);
		 	subscribeOnTurn(playerTurnChangeHandler);

		 	function playerListChangeHandler (players) {
		 		getPlayersList(players);
		 	};

		 	function newPlayersListHandler (event, data) {
		 		getPlayersList(data.players);
		 	};

		 	function getPlayersList (players) {
		 		playersSetDefaultValue();

		 		var currentPlayerName = sessionStorage.playerName;
		 		var index = 0;
		 		
		 		for (singlePlayer in players) {
		 			if (currentPlayerName !== singlePlayer) {
		 				$scope.players[index].name = singlePlayer;
		 				$scope.players[index].color = decodeColor(players[singlePlayer].color);
		 				$scope.players[index].life = players[singlePlayer].life;
		 				index++;
		 			} else {
		 				//ostatni element to gracz aktualny
		 				$scope.players[$scope.players.length-1].name = singlePlayer;
		 				$scope.players[$scope.players.length-1].color = decodeColor(players[singlePlayer].color);
		 				$scope.players[$scope.players.length-1].life = players[singlePlayer].life;
		 			}
		 		}		 		

		 		$scope.$broadcast('tableHex:players', $scope.players);
		 	};

		 	function playersSetDefaultValue () {
				$scope.players = [
			 		{ name: "", color: "", turn: false, tokens: [], toknesCount: 0, life: 0 },
			 		{ name: "", color: "", turn: false, tokens: [], toknesCount: 0, life: 0 },
			 		{ name: "", color: "", turn: false, tokens: [], toknesCount: 0, life: 0 },
			 		{ name: "", color: "", turn: false, tokens: [], toknesCount: 0, life: 0 }
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
		 				player.tokensCount = tokensCount;
		 				player.turn = true;
		 				player.tokens = tokens;
		 			} else {
		 				player.turn = false;
		 			}
		 		});

		 		$scope.$broadcast('tableHex:players', $scope.players);

		 		if (login === sessionStorage.playerName) {
		 			$scope.$broadcast('userBoard:enable');
		 		} else {
		 			$scope.$broadcast('userBoard:disable');
		 		}
		 	};

		 	function endTurnHandler (event, data) {
		 		if (sessionStorage.playerName === sessionStorage.currentTurn) {
		 			socketServer.endTurn();
		 		}
		 	};

		 	playersSetDefaultValue();

		 }]);