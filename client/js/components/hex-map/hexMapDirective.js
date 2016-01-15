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
				$scope.$on('hexMap:setSingleToken', setSingleToken);
				$scope.$on('hexMap:setAllMap', setAllTokens);

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
					var $srcElement = event.target;

					if (!_srcElement.classed("hex-active")) {
						return;
					}

					var dragItemId = event.dataTransfer.getData("dragItemId");
					setActiveHexToEmpty();

					if (dragItemId === "") {
						return;
					}

					var tokenId = event.dataTransfer.getData("tokenId");
					var tokenUrl = event.dataTransfer.getData("tokenUrl");
					var rotateCount = event.dataTransfer.getData("rotateCount");
					var transform = getTransferDataFromSrc(rotateCount, _srcElement);
					
					var coordinate = {
						r: _srcElement.attr("r"),
						q: _srcElement.attr("q")
					};

					var tokenParams = {
						tokenId: tokenId,
						tokenUrl: tokenUrl,
						transform: transform
					};

					setOccupateTokenAttr($srcElement, tokenParams);

					setDraggedItemFlag(dragItemId);
					sendPutToken(tokenId, coordinate, rotateCount);
				};

				function sendPutToken (id, coordinate, rotateCount) {
					var msg = {
						id: id,
						q: coordinate.q,
						r: coordinate.r,
						angle: rotateCount
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

				function setAllTokens (event, tokens) {
					tokens.forEach(function (singleToken) {
						setSingleToken(singleToken);
					});
				};

				function setSingleToken (event, token) {
					var $token = $scope.$hexMap.querySelector("[q='" + token.q + "'][r='" + token.r + "']");

					var tokenParams = {
						tokenId: token.id,
						tokenUrl: token.name,
						transform: getTransferDataFromSrc(token.angle, d3.select($token))
					};
					
					setOccupateTokenAttr($token, tokenParams);
				};

				function setOccupateTokenAttr ($token, params) {
					var _token = d3.select($token);

					_token
						.classed("hex-empty", false)
						.classed("hex-occupied", true);

					_token
						.attr("token-id", params.tokenId)
						.attr("fill", "url(#" + params.tokenUrl + ")")
						.attr("transform", params.transform);
				};

				function setEmptyTokenAttr ($token, params) {
					var _token = d3.select($token);

					_token
						.classed("hex-empty", true)
						.classed("hex-occupied", false);

					_token
						.attr("token-id", params.tokenId)
						.attr("fill", "url(#" + params.tokenUrl + ")")
						.attr("transform", params.transform);
				};
			}
		};
	});