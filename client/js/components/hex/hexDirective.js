angular.module('hexDirective', [])
	.directive('hex', function () {
		return {
			restrict: 'E',
			scope: {
				id: '=',

				corners: '=',
				color: '=',
				draggable: '=',
				dropable: '=',

				centerX: '=',
				centerY: '=',
				size: '='
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
					$scope.className += 'token token-' + colorClass;
				};

				function setDefaultHexClass () {
					$scope.className += 'hex-empty';
				};

				function setDraggableAttribute (draggable) {
					draggable = draggable || false;

					if (draggable === "true" || draggable === true) {
						$scope.className += ' draggable';
					}
				};

				function setCornersFromCenterPoint (x, y) {
					var hexLibrary = new hexLibraryConstructor();
					var center = new Point(x, y);

					hexLibrary.setLayoutSize(Point($scope.size, $scope.size));
					
					var corners = hexLibrary.setHexCorners(center);
					return corners;
				};

				setColorClass($scope.color);
				setDraggableAttribute($scope.draggable);
 				
				if (!!$scope.centerX || !!$scope.centerY) {
					$scope.corners = setCornersFromCenterPoint($scope.centerX, $scope.centerY);
				}
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

				var _selectedElement = null;
				var $startElement = null;
				var startElementClass = null;

				var correctionX = null;
				var correctionY = null;

				var startPoint = null;
				var endPoint = null;

				function dragstartHandler (event) {  
					var $srcElement = event.target;
					var _src = d3.select($srcElement);

					if (!_src.classed("token")) {
						return;
					}

					var center = new Point(-100, -100);
					var corners = hexLibrary.setHexCorners(center);

					var srcClass = _src.attr("class");

					$startElement = $srcElement;
					startElementClass = _src.attr("class");
					_src
						.attr("class", "hex-empty");

					var $svg = document.getElementsByTagName('svg')[0];
					var svgBoundingRect = $svg.getBoundingClientRect();

					correctionX = -svgBoundingRect.left;
					correctionY = -svgBoundingRect.top;
					startPoint = new Point(event.pageX+correctionX, event.pageY+correctionY);
					var canvas = d3.select($svg);
					
					_selectedElement = canvas
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

					var patt = new RegExp("token-");

					classArray.some(function (element) {
						return patt.test(element) ? ((result = "token " + element), true) : false;
					});
					
					return result;
				};

				function dragHandler (event) {
					var $srcElement = event.target;
					var _src = d3.select($srcElement);
					var center = Point(event.pageX+correctionX+60, event.pageY+correctionY+60);
					var corners = hexLibrary.setHexCorners(center);
					
					if (_selectedElement == null) {
						return;
					}

					_selectedElement
						.attr("points", getCornersString(corners));

					if (event.pageX !== 0 && event.pageY !== 0) {
						endPoint = center;
					}
				};

				function dragendHandler (event) {
					if (_selectedElement == null) {
						return;
					} else if (!(_selectedElement.attr("drag-success") === "true" || _selectedElement.attr("drag-success") === true)) {
						returnToStartingPosition(_selectedElement);
					} else {
						removeSelectedElement();	
					}
				};

				function removeSelectedElement () {
					_selectedElement.remove();
					_selectedElement = null;
					startElement = null;
				};

				function returnToStartingPosition ($element) {
					var $srcElement = event.target;
					var corners = hexLibrary.setHexCorners(endPoint);
					
					_selectedElement
						.attr("points", getCornersString(corners));

					corners = hexLibrary.setHexCorners(startPoint);
					
					_selectedElement.transition()
						.attr("points", getCornersString(corners))
						.duration(1000)
						.each("end", afterTransitionCallback);
				};

				function afterTransitionCallback () {
					removeSelectedElement();
					
					d3.select($startElement)
						.attr("class", startElementClass); 

					$startElement = null;
					startElementClass = null;
				};
			}
		};
	});
