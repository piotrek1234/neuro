angular.module('popupController', [])
	.controller('popupController',
		['$scope',
		 function ($scope) {
		 	$scope.$on("popup:rendered", startHandler);
		 	$scope.$on("popup:selectPlayer", selectPlayerHandler);

		 	function startHandler (event) {
		 		console.log("popupController#startHandler");

		 		closePopupEvent();
		 	};

		 	function selectPlayerHandler (event, data) {
		 		console.log("popupController#selectPlayerHandler "
		 			+ " login: " + data.login + " color: " + data.color);
		 	};

		 	function closePopupEvent () {
		 		$scope.$broadcast("popup:close");
		 	};
		 }]);