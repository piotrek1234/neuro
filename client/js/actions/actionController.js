angular.module('actionController', [])
	.controller('actionController',
		['$scope',
		 function ($scope) {
		 	subscribeOnGetMoves(getMovePlaces);
		 	subscribeOnGetPushes(getPushPlaces);

		 	$scope.$on('action:move', moveActionHandler);
		 	$scope.$on('action:push', pushActionHandler);

		 	$scope.$hexMap = null;
		 	$scope.$hexs = null;

		 	$scope.action = null;
		 	$scope.tokenId = null;

		 	$scope.srcTokenCoordinate = null;
		 	$scope.destTokenCoordinate = null;

		 	function pushActionHandler (event, data) {
		 		$scope.$hexMap = document.body.querySelector(".hex-map");
		 		$scope.$hexs = $scope.$hexMap.querySelectorAll(".hex");

		 		$scope.tokenId = data.tokenId;
		 		$scope.action = "push";

		 		//blokowanie interfejsu
		 		$scope.$broadcast('userBoard:disable');

		 		getAllUserTokens();
		 		selectAllUserTokens("token-to-move");
		 		setHexMapClickListener();
		 	};

		 	function moveActionHandler (event, data) {
		 		$scope.$hexMap = document.body.querySelector(".hex-map");
		 		$scope.$hexs = $scope.$hexMap.querySelectorAll(".hex");

		 		$scope.tokenId = data.tokenId;
				$scope.action = "move";		 		

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

		 	function sendActionMessage () {
		 		if ($scope.action === "move") {
		 			socketServer.getMoves(
		 				$scope.srcTokenCoordinate.q,
		 				$scope.srcTokenCoordinate.r
		 			);
		 		} else if ($scope.action === "push") {
		 			socketServer.getPushes(
		 				$scope.srcTokenCoordinate.q,
		 				$scope.srcTokenCoordinate.r
		 			);
		 		}
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

		 			sendActionMessage();
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
		 		} else if (_eventSrc.classed("token-opponent")) {
		 			$scope.destTokenCoordinate = {
		 				q: _eventSrc.attr('q'),
		 				r: _eventSrc.attr('r')
		 			};

		 			sendPushTokenMsg();

		 			unselectAllUserTokens("token-opponent");
		 			$scope.$userHexs = [];
		 			$scope.$broadcast('userBoard:enable');
		 		}
		 	};

		 	function sendMoveTokenMsg () {
		 		socketServer.moveToken(
		 			$scope.tokenId,
		 			$scope.srcTokenCoordinate.q,
		 			$scope.srcTokenCoordinate.r,
		 			$scope.destTokenCoordinate.q,
		 			$scope.destTokenCoordinate.r
		 		);
		 	};

		 	function sendPushTokenMsg () {
		 		socketServer.pushToken(
		 			$scope.tokenId,
		 			$scope.srcTokenCoordinate.q,
		 			$scope.srcTokenCoordinate.r,
		 			$scope.destTokenCoordinate.q,
		 			$scope.destTokenCoordinate.r
		 		);
		 	};

		 	function getMovePlaces (hexs) {
		 		if (hexs.length === 0)
		 			undoAction();

		 		selectHexs(hexs);
		 		selectAllUserTokens("hex-move-destination");
		 	};

		 	function getPushPlaces (hexs) {
		 		if (hexs.length === 0)
		 			undoAction();

		 		selectHexs(hexs);
		 		selectAllUserTokens("token-opponent");
		 	};

		 	function undoAction () {
		 		unselectAllUserTokens("token-to-move");
		 		$scope.$userHexs = [];
		 		$scope.$broadcast('userBoard:enable');
		 	};

		 	function selectHexs (hexs) {
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