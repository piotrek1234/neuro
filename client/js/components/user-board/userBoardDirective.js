angular.module('userBoardDirective', [])
	.directive('userBoard', function () {
		return {
			restrict: 'E',
			scope: {
				x: "=",
				y: "=",
				sizeBase: "="
			},
			templateNamespace: 'svg',
			templateUrl: 'js/components/user-board/userBoard.html',
			replace: true,
			controller: function ($scope) {
				
			}
		};
	});