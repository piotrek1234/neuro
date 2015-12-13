angular.module('hexMapDirective', [])
	.directive('hexMap', function () {
		return {
			restrict: 'E',
			scope: {
				size: "=",
				width: "=",
				height: "="
			},
			templateNamespace: 'svg',
			templateUrl: 'js/components/hex-map/hexMap.html',
			controller: function ($scope) {
				var hexMap = generateMap($scope.size);

				var coordinateMap = [];
				hexMap.forEach(function (element) {
					coordinateMap.push(hexToCoordinate(flat, element));
				});

			 	var cornersSet = [];
			 	coordinateMap.forEach(function (element) {
			 		cornersSet.push(setHexCorners(element));
			 	});
			 	debugger;
			 	$scope.cornersSet = cornersSet;
			}
		};
	});