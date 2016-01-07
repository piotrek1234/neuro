angular.module('popupDirective', [])
	.directive('popup', function () {
		return {
			restrict: 'E',
			scope: {
				centerX: "=cx",
				centerY: "=cy"
			},
			templateNamespace: 'svg',
			templateUrl: 'js/components/popup/popup.html',
			replace: true,
			controller: function ($scope) {
				debugger;
			},
			link: function ($scope, $element, attr) {
				
			}
		};
	});