angular.module('tableHexDirective', [])
	.directive('tableHex', function () {
		return {
			restrict: 'E',
			scope: {
				hexSize: '='
			},
			templateNamespace: 'svg',
			templateUrl: 'js/components/table-hex/tableHex.html',
			replace: true,
			controller: function ($scope) {
				
			},
			link: function ($scope, element, attr) {
				
			}
		};
	});