angular.module('hexMapDirective', [])
	.directive('hexMap', function () {
		return {
			restrict: 'E',
			scope: {
				hexCount: "=hexCount",
				size: "="
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
			link: function (scope, element, attr) {
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
					var $item = d3.select(document.getElementById(id));

					$item
						.attr("drag-success", true);
				};

				function clickHandler (event) {
					var $srcElement = event.target;

					selectElement($srcElement);
				};

				function selectElement ($element) {
					var _elemenet = d3.select($element);

					debugger;
				};

				function setActiveHexToEmpty () {
					d3.select(".hex-active")
						.classed("hex-active", false)
						.classed("hex-empty", true);
				};
			}
		};
	});