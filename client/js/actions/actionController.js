angular.module('actionController', [])
	.controller('actionController',
		['$scope',
		 function ($scope) {
		 	subscribeOnGetMoves(getMovePlaces);

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
		 		console.log("tutut");
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
		 		var userColor = getColorPrefix(sessionStorage.playerColor);

		 		var urlId = svgLibrary.getFillUrlId($token);
		 		var urlIdPrefix = urlId.split('_')[0];

		 		return (userColor === urlIdPrefix);
		 	};



		 	function hexMapClickHandler (event) {
		 		var _eventSrc = d3.select(event.target);

		 		if (_eventSrc.classed("token-to-move")) {
		 			
		 			unselectAllUserTokens("token-to-move");
		 			$scope.$userHexs = [];

		 			$scope.srcTokenCoordinate = {
		 				q: _eventSrc.attr('q'),
		 				r: _eventSrc.attr('r')
		 			};

		 			socketServer.getMoves(
		 				$scope.srcTokenCoordinate.q,
		 				$scope.srcTokenCoordinate.r
		 			);

		 		} else if (_eventSrc.classed("hex-move-destination")) {
		 			// wysłanie do serwera eventu pusha		 			
		 			$scope.destTokenCoordinate = {
		 				q: _eventSrc.attr('q'),
		 				r: _eventSrc.attr('r')
		 			};

		 			sendMoveTokenMsg();

		 			unselectAllUserTokens("hex-move-destination");
		 			$scope.$userHexs = [];
		 			$scope.$broadcast('userBoard:enable');
		 			//$scope.$hexMap.removeEventListener("click", hexMapClickHandler);
		 		}
		 	};

		 	function sendMoveTokenMsg () {
		 		console.log("actionController#sendPushTokenMsg");

		 		socketServer.moveToken(
		 			$scope.tokenId,
		 			$scope.srcTokenCoordinate.q,
		 			$scope.srcTokenCoordinate.r,
		 			$scope.destTokenCoordinate.q,
		 			$scope.destTokenCoordinate.r
		 		);
		 	};

		 	function getMovePlaces (hexs) {
		 		// TODO - reakcja na pusta tablice
		 		
		 		[].forEach.call($scope.$hexs, function ($singleHex) {
		 			var _singleHex = d3.select($singleHex);
		 			var hexCoordinate = {
		 				q: _singleHex.attr('q'),
		 				r: _singleHex.attr('r')
		 			};

		 			if (checkCoordinate(hexCoordinate, hexs)) {
			 			$scope.$userHexs.push($singleHex);
		 			}
		 		});

		 		selectAllUserTokens("hex-move-destination");
		 	};


		 	function checkCoordinate (coordinates, hexs) {
		 		var result = false;

		 		hexs.forEach(function (singleHex) {
		 			if (singleHex.q == coordinates.q 
		 				&& singleHex.r == coordinates.r) {
		 				result = true;
		 				return;
		 			}
		 		});

		 		return result;
		 	};
		 }]);