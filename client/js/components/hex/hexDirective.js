angular.module('hexDirective', [])
	.directive('hex', function () {
		return {
			restrict: 'E',
			scope: {
				corners: "="
			},
			templateNamespace: 'svg',
			templateUrl: 'js/components/hex/hex.html',
			replace: true,
			controller: function ($scope) {
				
			},
			link: function (scope, element, attr) {
				element.on('mouseenter', function (event) {
					event.preventDefault();

					var srcElement = d3.select(event.srcElement);
					srcElement.classed('hex-active', true);
				});

				element.on('mouseleave', function (event) {
					event.preventDefault();

					var srcElement = d3.select(event.srcElement);
					srcElement.classed('hex-active', false);
				});
			}
		};
	});
