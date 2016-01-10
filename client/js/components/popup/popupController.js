angular.module('popupController', [])
	.controller('popupController',
		['$scope',
		 function ($scope) {
		 	$scope.$on("popup:rendered", startHandler);
		 	$scope.$on("popup:selectPlayer", joinPlayerHandler);
		 	$scope.$on("popup:playerReady", playerReadyHandler);

		 	subscribeOnPlayerList(getPlayerList);
		 	subscribeOnJoinState(getJoinState);
		 	subscribeOnGameState(getGameState);

		 	function startHandler (event) {
		 		sendPlayerListToPopup([]);
		 		socketServer.getPlayers();
		 	};

		 	function joinPlayerHandler (event, data) {
		 		socketServer.join(data.login);
		 	};

		 	function getJoinState (joined, reason) {
		 		if (joined) {
		 			$scope.$broadcast("popup:joinedSucess", { reason: reason });
		 		} else {
		 			$scope.$broadcast("popup:joinedError",  { reason: reason });
		 		}
		 	};

		 	function playerReadyHandler (event, data) {
		 		socketServer.setReady(true);
		 	};

		 	function closePopupEvent () {
		 		$scope.$broadcast("popup:close");
		 	};

		 	function sendPlayerListToPopup (playerList) {
		 		$scope.$broadcast("popup:playerList", playerList);	
		 	};

		 	function getPlayerList (data, reason) {
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

		 	function getGameState (state) {
		 		if (checkIfGameStarted(state)) {

		 			closePopupEvent();
		 		}
		 	};

		 	function checkIfGameStarted (state) {
		 		return (state === 1);
		 	};

		 }]);