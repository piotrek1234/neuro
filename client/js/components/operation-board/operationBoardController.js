angular.module('operationBoardController', [])
	.controller('operationBoardController',
		['$scope',
		 function ($scope) {
		 	var $leftArrow = null;
		 	var $rightArrow = null;
		 	var $selectedToken = null;
		 	var $boardItem = null;
		 	var defaultCssClass = null;

		 	function setupParameters() {
		 		setMainBoardParameters();
				setBoardParameters();
				setLeftArrowParameters();
				setRightArrowParameters();
		 	};

		 	function setMainBoardParameters () {
		 		var mainBoard = {
					width: hexSize*8,
					height: hexSize*4
				};

		 		$scope.mainBoard = mainBoard;
		 	};

		 	function setBoardParameters () {
				var board = {
					x: hexSize/2,
					y: hexSize/2,
					width: hexSize*7,
					height: hexSize*2
				};

				$scope.board = board;

				setHexCenter(board);
		 	};

			function setHexCenter (board) {
				$scope.hexCenterX = board.x + board.width/2;
				$scope.hexCenterY = board.y + board.height/2;		
			};

			function setLeftArrowParameters () {
				var leftArrow = {
					x: hexSize*1,
					y: hexSize*0.75,
					width: hexSize*1.5,
					height: hexSize*1.5
				};

				$scope.leftArrow = leftArrow;
			};

			function setRightArrowParameters () {
				var rightArrow = {
					x: hexSize*5.5,
					y: hexSize*0.75,
					width: hexSize*1.5,
					height: hexSize*1.5
				};

				$scope.rightArrow = rightArrow;
			};

			function setupDOMElements () {
				$leftArrow = document.getElementById("left-arrow");
				$rightArrow = document.getElementById("right-arrow");
			};

			function setupEventHandlers () {
				$scope.$on('main:selectToken', selectTokenHandler);
				$scope.$on('main:unselectToken', unselectTokenHandler);

				$rightArrow.addEventListener("click", clickRightArrowHandler);
				$leftArrow.addEventListener("click", clickLeftArrowHandler);
			};

			function clickRightArrowHandler () {
				rotateRight($selectedToken);
				rotateRight($boardItem);
			};

			function rotateRight ($element) {
				d3.select($element)
					.transition()
					.attr("transform", "rotate(-60)")
					.duration(1000);
			};

			function clickLeftArrowHandler () {
				rotateLeft($selectedToken);
				rotateLeft($boardItem);
			};

			function rotateLeft ($element) {
				d3.select($element)
					.transition()
					.attr("transform", "rotate(60)")
					.duration(1000);
			};

			function selectTokenHandler (event, data) {
				$selectedToken = data.$token;
				$boardItem = document.getElementById("board-item");

				var cssTokenClass = d3.select($selectedToken)
					.attr("class");

				defaultCssClass = d3.select($boardItem)
					.attr("class");

				d3.select($boardItem)
					.attr("class", cssTokenClass)
					.classed("token-selected", false);
			};

			function unselectTokenHandler (event, data) {
				d3.select($boardItem)
					.attr("class", defaultCssClass);

				selectedToken = null;
			};

			var hexSize = $scope.hexSize;
 
			setupParameters();
			setupDOMElements();
			setupEventHandlers();
		 }]);
