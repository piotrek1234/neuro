angular.module('hexDirective', [])
	.directive('hex', function () {
		return {
			restrict: 'E',
			scope: {
				corners: '=',
				color: '=',
				draggable: '='
			},
			templateNamespace: 'svg',
			templateUrl: 'js/components/hex/hex.html',
			replace: true,
			controller: function ($scope) {
				$scope.className = '';

				function setColorClass (className) {
					switch (className) {
						case 'green':
						case 'yellow':
						case 'blue':
						case 'red':
							setColorTokenClass(className);
							break;
						default:
							setDefaultHexClass();
					} 
				};

				function setColorTokenClass (colorClass) {
					$scope.className += colorClass + '-token';
				};

				function setDefaultHexClass () {
					$scope.className += 'hex';
				};

				function setDraggableAttribute (draggable) {
					draggable = draggable || false;

					if (draggable === "true" || draggable === true) {
						$scope.className += ' draggable';
					}
				};

				setColorClass($scope.color);
				setDraggableAttribute($scope.draggable);
			}
		};
	});
