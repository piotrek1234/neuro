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
				element.on('mouseover', function (event) {
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
			}
		};
	});