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

				$rightArrow.addEventListener("click", clickRightArrowHandler.bind(this));
				$leftArrow.addEventListener("click", clickLeftArrowHandler.bind(this));
			};

			function clickRightArrowHandler (event) {
				event.stopPropagation();

				rotateRight($selectedToken);
				rotateRight($boardItem);
			};

			function clickLeftArrowHandler (event) {
				event.stopPropagation();

				rotateLeft($selectedToken);
				rotateLeft($boardItem);
			};

			function rotateRight ($element) {
				rotate($element, -60);
			};

			function rotateLeft ($element) {
				rotate($element, 60);
			};

			function rotate($element, angle) {
				var hexLibrary = new hexLibraryConstructor();
				var corners = d3.select($element).attr("points");
				var center = hexLibrary.getHexCenter(corners);

				var svgOperations = new svgOperationsLibraryConstructor();
				var angleCurrent = svgOperations.getRotateAngle($element);

				angle += angleCurrent;

				d3.select($element)
					.transition()
					.attr("transform", "rotate(" + angle + " " + center.x + " " + center.y + ")")
				.duration(1000);
			};

			function selectTokenHandler (event, data) {
				$selectedToken = data.$token;
				$boardItem = document.querySelector("polygon[ng-moving=true]");
				
				var cssTokenClass = d3.select($selectedToken)
					.attr("class");

				var fillAtribute = d3.select($selectedToken)
					.attr("fill");

				defaultCssClass = d3.select($boardItem)
					.attr("class");

				d3.select($boardItem)
					.attr("class", cssTokenClass)
					.attr("fill", fillAtribute)
					.classed("token-selected", false);
			};

			function unselectTokenHandler (event, data) {
				d3.select($boardItem)
					.attr("class", defaultCssClass)
					.attr("fill", null);

				$selectedToken = null;
				$boardItem = null;
			};

			var hexSize = $scope.hexSize;
 
			setupParameters();
			setupDOMElements();
			setupEventHandlers();
		 }]);
