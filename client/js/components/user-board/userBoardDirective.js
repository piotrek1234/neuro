angular.module('userBoardDirective', [])
	.directive('userBoard', function () {
		return {
			restrict: 'E',
			scope: {
				x: "=",
				y: "=",
				color: "=",
				sizeBase: "=",
				login: "=",
				draggable: "=",
				dopable: "="
			},
			templateNamespace: 'svg',
			templateUrl: 'js/components/user-board/userBoard.html',
			replace: true,
			controller: function ($scope) {
				var hexLibrary = new hexLibraryConstructor();
				var sizeBase = $scope.sizeBase;

				hexLibrary.setLayoutSize(Point(sizeBase, sizeBase));
				
				var cornersSet = [];
				cornersSet.push(hexLibrary.setHexCorners(Point(sizeBase*1.5, sizeBase)));
				cornersSet.push(hexLibrary.setHexCorners(Point(sizeBase*4, sizeBase)));
				cornersSet.push(hexLibrary.setHexCorners(Point(sizeBase*6.5, sizeBase)));
				
				$scope.cornersSet = cornersSet;

				$scope.className = $scope.color + "-token";
			},
			link: function ($scope, $element, attr) {
				
			}
		};
	});