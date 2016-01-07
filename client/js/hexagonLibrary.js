function hexLibraryConstructor () {
    this.getHexSize = function () {
        return this.flat.size;
    };

    this.setLayoutSize = function (size) {
        var origin = Point(size.x * 4, size.y * 4 + 20);
        
        this.flat = this.Layout(this.layout_flat, size, origin);
    };

    this.setHexCorners = function (center) {
        var corners = [];
        var center = Point(center.x, center.y);
        for (var i = 0; i < 6; i++)
        {
            var offset = this.hexCornerOffset(i);
            corners.push(Point(center.x + offset.x, center.y + offset.y));
        }

        return corners;
    };

    this.hexCornerOffset = function (corner) {
        var size = this.flat.size;
        var angle = 2.0 * Math.PI * corner / 6;
        return Point(size.x * Math.cos(angle), size.y * Math.sin(angle));
    };

    this.generateMap = function (mapRadius) {
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

    this.Orientation = function (f0, f1, f2, f3, b0, b1, b2, b3, start_angle) {
        return {f0: f0, f1: f1, f2: f2, f3: f3, b0: b0, b1: b1, b2: b2, b3: b3, start_angle: start_angle};
    };

    this.Layout = function (orientation, size, origin) {
        return {orientation: orientation, size: size, origin: origin};
    };

    this.hexToCoordinate = function (layout, h) {
        var M = layout.orientation;
        var size = layout.size;
        var origin = layout.origin;
        var x = (M.f0 * h.q + M.f1 * h.r) * size.x;
        var y = (M.f2 * h.q + M.f3 * h.r) * size.y;
        return Point(x + origin.x, y + origin.y);
    };
    
    this.getHexCenter = function (cornersString) {
        var center = null;

        var pointsArray = this.convertCornersStringToArray(cornersString);
        
        var firstCorner = pointsArray[0];
        var fourthCorner = pointsArray[3];
        
        center = new Point((firstCorner.x + fourthCorner.x)/2, (firstCorner.y + fourthCorner.y)/2);
        
        return center;
    };

    this.convertCornersStringToArray = function (cornersString) {
        var pointsArray = [];
        var cornersStringArray = cornersString.split('\n');

        removeWhitespacesFromStringArray(cornersStringArray);
        
        cornersStringArray.forEach(function (element) {
            var elementArray = element.split(',');
            pointsArray.push({
                x: parseInt(elementArray[0]),
                y: parseInt(elementArray[1])
            });
         });

        return pointsArray;
    };

    function removeWhitespacesFromStringArray (stringArray) {
        stringArray.forEach( function (element, index) {
            stringArray[index] = element.replace(/\s/g,'');
        });  
    };

    this.layout_flat = this.Orientation(3.0 / 2.0, 0.0, Math.sqrt(3.0) / 2.0, Math.sqrt(3.0), 2.0 / 3.0, 0.0, -1.0 / 3.0, Math.sqrt(3.0) / 3.0, 0.0);
    this.flat = this.Layout(this.layout_flat, Point(70, 70), Point(280, 300));
};



function Point (x, y) {
    return {x: x, y: y};
};

function Hex (q, r, s) {
    return {q: q, r: r, s: s};
};

function getCornersString (corners) {
    var result = "";

    corners.forEach(function (corner) {
        result += corner.x + ", " + corner.y + "\n";
    });

    return result;
};

function getCenterPoint (width, height) {
    return new Point(width/2, height/2);
};

function getHexMapWidth () {
    var $hexMap = document.querySelector(".hex-map");

    var widthString = d3.select($hexMap).attr("width");

    return parseInt(widthString);
};

function getHexMapHeight () {
    var $hexMap = document.querySelector(".hex-map");

    var heightString = d3.select($hexMap).attr("height");

    return parseInt(heightString);
};

function convertPointsStringToArray (pointsString) {
    var result = [];

    pointsString = pointsString.replace(/,/g, '');
    var pointsArray = pointsString.split(' ');
    
    //TODO dorobic funkcje która przyporządkowuje koordynaty x i y

    pointsArray.forEach(function (element, index) {
        if (index%2) {

        } else {

        }
    });

    return result;
};