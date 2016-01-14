angular.module('hexMapDirective', [])
	.directive('hexMap', function () {
		return {
			restrict: 'E',
			scope: {
				hexCount: "=hexCount",
				hexMap: "=",

				size: "="
			},
			templateNamespace: 'svg',
			templateUrl: 'js/components/hex-map/hexMap.html',
			replace: true,
			controller: function ($scope) {
				var hexLibrary = new hexLibraryConstructor();

				hexLibrary.setLayoutSize(Point($scope.size, $scope.size));
				
				var hexMap = hexLibrary.generateMap($scope.hexCount);
				$scope.hexMap = hexMap;

				var coordinateMap = [];
				hexMap.forEach(function (element) {
					coordinateMap.push(hexLibrary.hexToCoordinate(hexLibrary.flat, element));
				});

			 	var cornersSet = [];
			 	coordinateMap.forEach(function (element) {
			 		cornersSet.push(hexLibrary.setHexCorners(element));
			 	});
			 	
			 	$scope.cornersSet = cornersSet;
			},
			link: function ($scope, element, attr) {
				$scope.$hexMap = element[0];

				element.on('dragover', dragoverHandler);
				element.on('drop', dropHandler);
				element.on('dragleave', dragleaveHandler);

				element.on('dragenter', function () {
					event.preventDefault();
				});

				function dragoverHandler (event) {
					var srcElement = d3.select(event.target);
					
					event.preventDefault();
					
					if (!srcElement.classed("hex-empty")) {
						return;
					}					

					setActiveHexToEmpty();
					
					srcElement
						.classed("hex-active", true)
						.classed("hex-empty", false);
				};

				function dropHandler (event) {
					var _srcElement = d3.select(event.target);
					var tokenClass = event.dataTransfer.getData("tokenClass");					

					if (!_srcElement.classed("hex-active") || tokenClass == null) {
						return;
					}

					var dragItemId = event.dataTransfer.getData("dragItemId");
					setActiveHexToEmpty();

					if (dragItemId === "") {
						return;
					}

					var tokenId = event.dataTransfer.getData("tokenId");
					var rotateCount = event.dataTransfer.getData("rotateCount");
					var transform = getTransferDataFromSrc(rotateCount, _srcElement);
					
					var coordinate = {
						r: _srcElement.attr("r"),
						q: _srcElement.attr("q")
					};

					_srcElement
						.classed("hex-empty", false)
						.classed(tokenClass, true)
						.classed("hex-occupied", true);

					_srcElement
						.attr("fill", "url(#" + tokenId + ")")
						.attr("transform", transform);

					setDraggedItemFlag(dragItemId);
					sendPutToken(tokenId, coordinate, rotateCount);
				};

				function sendPutToken (id, coordinate, rotateCount) {
					var msg = {
						id: id,
						coordinate: coordinate,
						rotateCount: rotateCount
					};
					
					$scope.$emit("hexMap:putToken", msg);
				};

				function getTransferDataFromSrc (rotateCount, _hex) {
					var hexLibrary = new hexLibraryConstructor();					
					var center = hexLibrary.getHexCenter(_hex.attr("points"));
					var rotateAngle = rotateCount*60;
					if (rotateAngle === 0) {
						return "";
					} else {
						return "rotate(" + rotateAngle + ", " + center.x + ", " + center.y + ")";
					}
				};

				function dragleaveHandler (event) {
					var srcElement = d3.select(event.target);
					
					if (!srcElement.classed("hex-active")) {
						return;
					}

					srcElement
						.classed("hex-active", false)
						.classed("hex-empty", true);
				};

				function setDraggedItemFlag (id) {
					event.preventDefault();
					var _item = d3.select(document.getElementById(id));

					_item
						.attr("drag-success", true);
				};

				function setActiveHexToEmpty () {
					d3.select(".hex-active")
						.classed("hex-active", false)
						.classed("hex-empty", true);
				};
			}
		};
	});