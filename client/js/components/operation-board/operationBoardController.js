angular.module('operationBoardController', [])
	.controller('operationBoardController',
		['$scope',
		 function ($scope) {
			var hexSize = $scope.hexSize;

			var mainBoard = {
				width: hexSize*8,
				height: hexSize*4
			};

			var board = {
				x: hexSize/2,
				y: hexSize/2,
				width: hexSize*7,
				height: hexSize*2
			};

			$scope.mainBoard = mainBoard;
			$scope.board = board;

			$scope.hexCenterX = board.x + board.width/2;
			$scope.hexCenterY = board.y + board.height/2;

			var leftArrow = {
				x: hexSize*1,
				y: hexSize*0.75,
				width: hexSize*1.5,
				height: hexSize*1.5
			};

			var rightArrow = {
				x: hexSize*5.5,
				y: hexSize*0.75,
				width: hexSize*1.5,
				height: hexSize*1.5
			};

			$scope.leftArrow = leftArrow;
			$scope.rightArrow = rightArrow;
		 }]);
