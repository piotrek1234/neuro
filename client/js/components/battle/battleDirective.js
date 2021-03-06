angular.module('battleDirective', [])
	.directive('battle', function () {
		return {
			restrict: 'E',
			scope: {
				
			},
			templateUrl: 'js/components/battle/battle.html',
			replace: true,
			controller: function ($scope) {
				
			},
			link: function ($scope, element, attr) {
				$scope.$popup = element[0];

				$scope.$on("battlePopup:open", openPopupHandler);
				$scope.$on("battlePopup:close", closePopupHandler);

				function openPopupHandler (event, data) {
					d3.select($scope.$popup)
						.classed("popup-active", true)
						.classed("popup-disabled", false);
				};

				function closePopupHandler (event, data) {
					d3.select($scope.$popup)
						.classed("popup-active", false)
						.classed("popup-disabled", true);
				};
			}
		};
	});