angular.module('popupController', [])
	.controller('popupController',
		['$scope',
		 function ($scope) {
		 	$scope.$on("popup:rendered", startHandler);
		 	$scope.$on("popup:selectPlayer", selectPlayerHandler);
		 	$scope.$on("popup:playerReady", playerReadyHandler);

		 	subscribeOnPlayerList(getPlayerList);

		 	function startHandler (event) {
		 		console.log("popupController#startHandler");
		 		sendPlayerListToPopup([]);
		 		socketServer.getPlayers();
		 	};

		 	function selectPlayerHandler (event, data) {
		 		console.log("popupController#selectPlayerHandler "
		 			+ " login: " + data.login + " color: " + data.color);
		 	};

		 	function playerReadyHandler (event, data) {
		 		console.log("popupController#playerReadyHandler "
		 			+ " login: " + data.login + " color: " + data.color);
		 	};

		 	function closePopupEvent () {
		 		$scope.$broadcast("popup:close");
		 	};

		 	function sendPlayerListToPopup (playerList) {
		 		$scope.$broadcast("popup:playerList", playerList);	
		 	};

		 	function getPlayerList (data) {
		 		var playerList = parsePlayerList(data);

		 		sendPlayerListToPopup(playerList);
		 	};

		 	function parsePlayerList (input) {
		 		var result = [];

		 		for (element in input) {

		 			var player = {
		 				login: "",
		 				isCurrentPlayer: false,
		 				isReady: false
		 			};

		 			player.login = element;
		 			player.isReady = input[element].ready;

		 			if (player.login === sessionStorage.playerName) {
		 				player.isCurrentPlayer = true;
		 			}

		 			result.push(player);
		 		}

		 		return result;
		 	};
		 }]);