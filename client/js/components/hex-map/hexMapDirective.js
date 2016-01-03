angular.module('hexMapDirective', [])
	.directive('hexMap', function () {
		return {
			restrict: 'E',
			scope: {
				hexCount: "=hexCount",
				size: "=",

				selectClickFn: '&'
			},
			templateNamespace: 'svg',
			templateUrl: 'js/components/hex-map/hexMap.html',
			replace: true,
			controller: function ($scope) {
				var hexLibrary = new hexLibraryConstructor();

				hexLibrary.setLayoutSize(Point($scope.size, $scope.size));
				
				var hexMap = hexLibrary.generateMap($scope.hexCount);

				var coordinateMap = [];
				hexMap.forEach(function (element) {
					coordinateMap.push(hexLibrary.hexToCoordinate(hexLibrary.flat, element));
				});

			 	var cornersSet = [];
			 	coordinateMap.forEach(function (element) {
			 		cornersSet.push(hexLibrary.setHexCorners(element));
			 	});
			 	
			 	$scope.cornersSet = cornersSet;
			},
			link: function ($scope, element, attr) {
				element.on('dragover', function (event) {
					var srcElement = d3.select(event.target);
					
					event.preventDefault();
					
					if (!srcElement.classed("hex-empty")) {
						return;
					}					

					setActiveHexToEmpty();
					
					srcElement
						.classed("hex-active", true)
						.classed("hex-empty", false);
				});

				element.on('drop', function (event) {
					var srcElement = d3.select(event.target);
					var tokenClass = event.dataTransfer.getData("tokenClass");

					if (!srcElement.classed("hex-active") || tokenClass == null) {
						return;
					}

					var dragItemId = event.dataTransfer.getData("dragItemId");
					setActiveHexToEmpty();

					if (dragItemId === "") {
						return;
					}

					srcElement
						.classed("hex-empty", false)
						.classed(tokenClass, true)
						.classed("hex-occupied", true);

					setDraggedItemFlag(dragItemId);
				});

				element.on('dragleave', function (event) {
					var srcElement = d3.select(event.target);
					
					if (!srcElement.classed("hex-active")) {
						return;
					}

					srcElement
						.classed("hex-active", false)
						.classed("hex-empty", true);			
				});

				element.on('dragenter', function () {
					event.preventDefault();
				});

				element.on('click', clickHandler);

				function setDraggedItemFlag (id) {
					event.preventDefault();
					var _item = d3.select(document.getElementById(id));

					_item
						.attr("drag-success", true);
				};

				function clickHandler (event) {
					var $srcElement = event.target;
					var _element = d3.select($srcElement);
					
					if (!_element.classed("token") 
						|| _element.classed("hex-empty")) {
						return;
					}

					event.preventDefault();
					event.stopPropagation();

					unselectElement();
					selectElement(_element);
					setupBodyEventHandler();
					
					emitSelectClickHandler($srcElement)
				};

				function emitSelectClickHandler ($element) {
					if ($scope.selectClickFn == null) {
						return;
					}

					var hexClass = $element.getAttribute("class");

					$scope.$emit('test', {hexClass: hexClass});
				};

				function selectElement (_element) {
					_element
						.classed("token-selected", true);
				};

				function unselectElement () {
					d3.select(".token-selected")
						.classed("token-selected", false);
				};

				function setupBodyEventHandler () {
					var _body = d3.select("body");

					_body
						.on("click", clickBodyHandler);
				}

				function removeBodyClickHandler () {
					var _body = d3.select("body");

					_body
						.on("click", null);
				};

				function clickBodyHandler () {
					unselectElement();
					removeBodyClickHandler();
				};

				function setActiveHexToEmpty () {
					d3.select(".hex-active")
						.classed("hex-active", false)
						.classed("hex-empty", true);
				};
			}
		};
	});