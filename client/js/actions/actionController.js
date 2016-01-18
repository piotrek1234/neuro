angular.module('actionController', [])
	.controller('actionController',
		['$scope',
		 function ($scope) {
		 	$scope.$on('action:move', moveActionHandler);
		 	$scope.$on('action:push', pushActionHandler);

		 	$scope.$hexMap = null;
		 	$scope.$hexs = null;

		 	$scope.tokenId = null;

		 	$scope.srcTokenCoordinate = null;
		 	$scope.destTokenCoordinate = null;

		 	function pushActionHandler (event, data) {
		 		$scope.$hexMap = document.body.querySelector(".hex-map");
		 		$scope.$hexs = $scope.$hexMap.querySelectorAll(".hex");

		 		$scope.tokenId = data.tokenId;

		 		//blokowanie interfejsu
		 		$scope.$broadcast('userBoard:disable');

		 		console.log('actionController#pushActionHandler');
		 	};

		 	function moveActionHandler (event, data) {
		 		$scope.$hexMap = document.body.querySelector(".hex-map");
		 		$scope.$hexs = $scope.$hexMap.querySelectorAll(".hex");

		 		$scope.tokenId = data.tokenId;

		 		//blokowanie interfejsu
		 		$scope.$broadcast('userBoard:disable');

		 		getAllUserTokens();
		 		selectAllUserTokens("token-to-move");
		 		setHexMapClickListener();
		 	};

		 	function setHexMapClickListener () {
		 		$scope.$hexMap.addEventListener('click', hexMapClickHandler);
		 	};

		 	function getAllUserTokens () {
		 		$scope.$userHexs = [];
		 		//uwaga na blokadę gdy brak tokenów usera

		 		[].forEach.call($scope.$hexs, function ($hex) {
		 			if (!checkIsEmptyHex($hex) 
		 					&& checkIsUserToken($hex)) {
		 				$scope.$userHexs.push($hex);
		 			}
		 		});
		 	};

		 	function selectAllUserTokens (className) {
		 		[].forEach.call($scope.$userHexs, function ($hex) {
		 			d3.select($hex)
		 				.classed(className, true);
		 		});
		 	};

		 	function unselectAllUserTokens (className) {
		 		[].forEach.call($scope.$userHexs, function ($hex) {
		 			d3.select($hex)
		 				.classed(className, false);
		 		});
		 	};

		 	function checkIsEmptyHex ($hex) {
		 		return d3.select($hex)
		 					.classed("hex-empty");
		 	};

		 	function checkIsUserToken ($token) {
		 		var svgLibrary = new svgOperationsLibraryConstructor();
		 		var userColor = decodeColor(sessionStorage.playerColor);

		 		var urlId = svgLibrary.getFillUrlId($token);
		 		var urlIdPrefix = urlId.split('_')[0];

		 		return (userColor.slice(0, 2) === urlIdPrefix);
		 	};

		 	function hexMapClickHandler (event) {
		 		var _eventSrc = d3.select(event.target);

		 		if (_eventSrc.classed("token-to-move")) {
		 			unselectAllUserTokens("token-to-move");
		 			$scope.srcTokenCoordinate = {
		 				q: _eventSrc.attr('q'),
		 				r: _eventSrc.attr('r')
		 			};

		 		} else if (_eventSrc.classed("hex-move-destination")) {
		 			// wysłanie do serwera eventu pusha
		 			$scope.$hexMap.removeEventListener("click", hexMapClickHandler);
		 		}
		 	};



		 }]);