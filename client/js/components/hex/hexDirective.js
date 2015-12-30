angular.module('hexDirective', [])
	.directive('hex', function () {
		return {
			restrict: 'E',
			scope: {
				corners: '=',
				color: '=',
				draggable: '=',
				dropable: '='
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
			},
			link: function ($scope, $element, attr) {
				var hexLibrary = new hexLibraryConstructor();
				var isDragable = ($scope.draggable === true || $scope.draggable === 'true') ? true : false;
				var isDropable = ($scope.dropable === true || $scope.dropable === 'true') ? true : false;

				if (isDragable) {
					$element.on('dragstart', dragstartHandler);
				 	$element.on('drag', dragHandler);
				 	$element.on('dragend', dragendHandler);
				}

				if (isDropable) {
					// $element.on('dragover', function () { console.log("dragover") });
				 	$element.on('drop', dropHandler);
				}

				var selectedElement = null;

				var correctionX = null;
				var correctionY = null;

				function dragstartHandler (event) {
					var $srcElement = event.target;
					var center = Point(-100, -100);
					var corners = hexLibrary.setHexCorners(center);

					var $svg = document.getElementsByTagName('svg')[0];
					var svgBoundingRect = $svg.getBoundingClientRect();

					correctionX = -svgBoundingRect.left;
					correctionY = -svgBoundingRect.top;

					var canvas = d3.select($svg);
					
					selectedElement = canvas
						.append("polygon")
					 	.attr("points", getCornersString(corners));
				};

				function dragHandler (event) {
					var $srcElement = event.target;
					var center = Point(event.pageX+correctionX, event.pageY+correctionY);
					var corners = hexLibrary.setHexCorners(center);
					
					selectedElement
						.attr("points", getCornersString(corners));
				};

				function dragendHandler (event) {
					selectedElement.remove();
					selectedElement = null;
				};

				function dropHandler (event) {
					console.log("dropHandler");
				};
			}
		};
	});
