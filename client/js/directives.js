angular.module('myDirectives', [])
	.directive('hexMap', function () {
		return {
			restrict: 'E',
			scope: {
				size: "="
			},
			templateUrl: 'views/templates/hex.html',
			controller: function ($scope) {
				function setHexCorners (center) {
			 		var corners = [];
				    var center = Point(center.x, center.y);
				    for (var i = 0; i < 6; i++)
				    {
				        var offset = hex_corner_offset(i);
				        corners.push(Point(center.x + offset.x, center.y + offset.y));
				    }

				    return corners;
			 	};

				function hex_corner_offset(corner)
				{
				    var size = flat.size;
				    var angle = 2.0 * Math.PI * corner / 6;
				    return Point(size.x * Math.cos(angle), size.y * Math.sin(angle));
				};

				function generateMap (mapRadius) {
			 		var map = [];

					for (var q = -mapRadius; q <= mapRadius; q++) {
					    var r1 = Math.max(-mapRadius, -q - mapRadius);
					    var r2 = Math.min(mapRadius, -q + mapRadius);
					    for (var r = r1; r <= r2; r++) {
					        map.push(Hex(q, r, -q-r));
						}
					}

					return map;
				};

				function Orientation(f0, f1, f2, f3, b0, b1, b2, b3, start_angle) {
				    return {f0: f0, f1: f1, f2: f2, f3: f3, b0: b0, b1: b1, b2: b2, b3: b3, start_angle: start_angle};
				}

				var layout_flat = Orientation(3.0 / 2.0, 0.0, Math.sqrt(3.0) / 2.0, Math.sqrt(3.0), 2.0 / 3.0, 0.0, -1.0 / 3.0, Math.sqrt(3.0) / 3.0, 0.0);
				var flat = Layout(layout_flat, Point(40, 40), Point(200, 200));
				
				function Layout(orientation, size, origin) {
				    return {orientation: orientation, size: size, origin: origin};
				}

				function hexToCoordinate (layout, h) {
				    var M = layout.orientation;
				    var size = layout.size;
				    var origin = layout.origin;
				    var x = (M.f0 * h.q + M.f1 * h.r) * size.x;
				    var y = (M.f2 * h.q + M.f3 * h.r) * size.y;
				    return Point(x + origin.x, y + origin.y);
				};

				function Point(x, y) {
				    return {x: x, y: y};
				};

				function Hex(q, r, s) {
					return {q: q, r: r, s: s};
				};

				var hexMap = generateMap($scope.size);

				var coordinateMap = [];
				hexMap.forEach(function (element) {
					coordinateMap.push(hexToCoordinate(flat, element));
				});

			 	var cornersSet = [];
			 	coordinateMap.forEach(function (element) {
			 		cornersSet.push(setHexCorners(element));
			 	});

			 	$scope.cornersSet = cornersSet;
				//$scope.corners = setHexCorners(setHexCorners(element));
			}
		};
	});