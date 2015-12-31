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
					$scope.className += 'tokenClass-' + colorClass;
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

				var selectedElement = null;

				var correctionX = null;
				var correctionY = null;

				var startPoint = null;
				var endPoint = null;

				function dragstartHandler (event) {  
					var $srcElement = event.target;
					var src = d3.select($srcElement);

					;
					var center = new Point(-100, -100);
					var corners = hexLibrary.setHexCorners(center);

					var srcClass = src.attr("class");

					src
						.attr("class", "hex");

					var $svg = document.getElementsByTagName('svg')[0];
					var svgBoundingRect = $svg.getBoundingClientRect();

					correctionX = -svgBoundingRect.left;
					correctionY = -svgBoundingRect.top;
					startPoint = new Point(event.pageX+correctionX, event.pageY+correctionY);
					var canvas = d3.select($svg);
					
					selectedElement = canvas
						.append("polygon")
						.attr("id", "dragged-item")
						.attr("class", srcClass)
					 	.attr("points", getCornersString(corners));

					var tokenClass = getTokenClass(srcClass);

					event.dataTransfer.setData('tokenClass', tokenClass);
					event.dataTransfer.setData('dragItemId', "dragged-item");
				};

				function getTokenClass (inputClass) {
					var result = null;
					var classArray = inputClass.split(" ");

					var patt = new RegExp("tokenClass");

					classArray.some(function (element) {
						return patt.test(element) ? ((result = element), true) : false;
					});
					
					return result;
				};

				function dragHandler (event) {
					console.log("dragHandler# pageX: " + event.pageX + ", pageY: " +event.pageY);
					var $srcElement = event.target;
					var center = Point(event.pageX+correctionX+60, event.pageY+correctionY+60);
					var corners = hexLibrary.setHexCorners(center);
					
					selectedElement
						.attr("points", getCornersString(corners));

					if (event.pageX !== 0 && event.pageY !== 0) {
						endPoint = center;
					}
				};

				function dragendHandler (event) {
					if (!(selectedElement.attr("drag-success") === "true" || selectedElement.attr("drag-success") === true)) {
						returnToStartingPosition(selectedElement);
					} else {
						removeSelectedElement();	
					}
				};

				function removeSelectedElement () {
					selectedElement.remove();
					selectedElement = null;
				};

				function returnToStartingPosition ($element) {
					console.log("returnToStartingPosition# pageX: " + endPoint.x + ", pageY: " +endPoint.y);
					var $srcElement = event.target;
					var corners = hexLibrary.setHexCorners(endPoint);
					
					selectedElement
						.attr("points", getCornersString(corners));

					corners = hexLibrary.setHexCorners(startPoint);
					
					selectedElement.transition()
						.attr("points", getCornersString(corners))
						.duration(1000)
						.each("end", removeSelectedElement);
				};
			}
		};
	});
