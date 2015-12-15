angular.module('hexTokenDirective', [])
	.directive('hexToken', function () {
		return {
			restrict: 'E',
			scope: {
				centerX: "=cx",
				centerY: "=cy"
			},
			templateNamespace: 'svg',
			templateUrl: 'js/components/hex-token/hexToken.html',
			replace: true,
			controller: function ($scope) {
				$scope.hexCorners = hexLibrary.setHexCorners({
					x: $scope.centerX,
					y: $scope.centerY
				});
			},
			link: function (scope, element, attr) {
				element.on('click', dispathClickHandler);

				function dispathClickHandler (event) {
					event.preventDefault();

					var $token = d3.select(event.target);
					
					switch (true) {
						case $token.classed("token-disactive"):
							tokenActivation($token);
							break;
					}

				};

				function tokenActivation ($token) {
					setTokenActiveClass($token);
					moveTokenToMapCenter($token);
				};

				function setTokenActiveClass ($token) {
					$token
						.classed("token-active", true);
				};

				function moveTokenToMapCenter ($token) {
					var mapWidth = getHexMapWidth();
					var mapHeigh = getHexMapHeight();

					var mapCenter = getCenterPoint(mapWidth, mapHeigh);
					var hexCorners = hexLibrary.setHexCorners(mapCenter);
					
					$token.transition()
						.duration(1500)
						.attr("points", getCornersString(hexCorners));
				};
			}
		};
	});