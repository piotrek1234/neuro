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
					
					if (!srcElement.classed("hex")) {
						return;
					}

					event.preventDefault();

					d3.select(".hex-active")
						.classed("hex-active", false);

					srcElement
						.classed("hex-active", true);			
				});

				element.on('drop', function (event) {
					var srcElement = d3.select(event.target);
					
					if (!srcElement.classed("hex")) {
						return;
					}
					//TODO dodać klasę empty
					var tokenClass = event.dataTransfer.getData("tokenClass");
					srcElement
						.classed("hex-active", false);	

					if (tokenClass == null) {
						return;
					}

					srcElement
						.classed(tokenClass, true);	

					var id = event.dataTransfer.getData("dragItemId");
					setDraggedItemFlag(id);
				});

				element.on('dragleave', function (event) {
					var srcElement = d3.select(event.target);
					
					if (!srcElement.classed("hex")) {
						return;
					}

					srcElement
						.classed("hex-active", false);			
				});


				function setDraggedItemFlag (id) {
					var $item = d3.select(document.getElementById(id));

					$item
						.attr("drag-success", true);
				};
			}
		};
	});