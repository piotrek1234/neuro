function svgOperationsLibraryConstructor () {
	this.getRotateAngle = function ($element) {
		var angle = null;
		var transformAttr = d3.select($element).attr("transform");
		var rotateEnd = transformAttr.split('rotate')[1];

		var rotateArg = rotateEnd.substring(rotateEnd.indexOf('(')+1, rotateEnd.indexOf(')'));
		
		angle = parseFloat(rotateArg.split(' ')[0]);

		return angle;
	};
};