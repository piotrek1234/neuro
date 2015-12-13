angular.module('hexMapDirective', [])
	.directive('hexMap', function () {
		return {
			restrict: 'E',
			scope: {
				hexCount: "=hexCount",
				width: "=",
				height: "=",
				size: "="
			},
			templateNamespace: 'svg',
			templateUrl: 'js/components/hex-map/hexMap.html',
			controller: function ($scope) {
				setLayoutSize(Point($scope.size, $scope.size));
				debugger;
				var hexMap = generateMap($scope.hexCount);

				var coordinateMap = [];
				hexMap.forEach(function (element) {
					coordinateMap.push(hexToCoordinate(flat, element));
				});

			 	var cornersSet = [];
			 	coordinateMap.forEach(function (element) {
			 		cornersSet.push(setHexCorners(element));
			 	});
			 	
			 	$scope.cornersSet = cornersSet;
			}
		};
	});