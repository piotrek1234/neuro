angular.module('popupController', [])
	.controller('popupController',
		['$scope',
		 function ($scope) {
		 	$scope.$on("popup:rendered", startHandler);
		 	$scope.$on("popup:selectPlayer", selectPlayerHandler);
		 	$scope.$on("popup:playerReady", playerReadyHandler);

		 	function startHandler (event) {
		 		console.log("popupController#startHandler");

		 		//closePopupEvent();
		 		var playerList = [];
		 		playerList.push({
		 			login: 'Gracz1',
		 			color: 'green',
		 			isActual: true,
		 			isReady: false
		 		});

		 		playerList.push({
		 			login: 'Gracz2',
		 			color: 'red',
		 			isActual: false,
		 			isReady: true
		 		});

		 		sendPlayerList(playerList);
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

		 	function sendPlayerList (playerList) {
		 		$scope.$broadcast("popup:playerList", playerList);	
		 	};
		 }]);