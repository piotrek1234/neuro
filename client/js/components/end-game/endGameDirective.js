angular.module('endGameDirective', [])
	.directive('endGame', function () {
		return {
			restrict: 'E',
			scope: {
				
			},
			templateUrl: 'js/components/end-game/endGame.html',
			replace: true,
			controller: function ($scope) {
				
			},
			link: function ($scope, element, attr) {
				$scope.$popup = element[0];
				$scope.$winner = $scope.$popup.querySelector(".winner");

				$scope.$on("endGamePopup:open", openPopupHandler);
				$scope.$on("endGamePopup:close", closePopupHandler);

				function openPopupHandler (event, data) {
					console.log(data);
					d3.select($scope.$popup)
						.classed("popup-active", true)
						.classed("popup-disabled", false);

					$scope.$winner.innerHTML = data.winner;
				};

				function closePopupHandler (event, data) {
					d3.select($scope.$popup)
						.classed("popup-active", false)
						.classed("popup-disabled", true);
				};
			}
		};
	});