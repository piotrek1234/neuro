function svgOperationsLibraryConstructor () {
	this.getRotateAngle = function ($element) {
		var angle = null;
		var transformAttr = d3.select($element).attr("transform");
		var rotateEnd = transformAttr.split('rotate')[1];

		var rotateArg = rotateEnd.substring(rotateEnd.indexOf('(')+1, rotateEnd.indexOf(')'));
		
		angle = parseFloat(rotateArg.split(' ')[0]);

		return angle;
	};

	this.getTransformParameters = function (parametersString) {
        var parameters = null;

        var translateRe = /translate\(-?[^a-zA-Z|)]+\)/;
        var rotateRe = /rotate\(-?[^a-zA-Z|)]+\)/;

        var translate = translateRe.exec(parametersString);
        var rotate = rotateRe.exec(parametersString);

        parameters = {
            translate: translate ? translate[0] : null,
            rotate: rotate ? rotate[0] : null
        };
        
        return parameters;
    };

    this.getRotateParmaters = function (parametersString) {
    	var parameters = null;

    	var re = /-?[1-9.]+/;
    	var rotateParms = re.exec(parametersString);


    	parameters = {
    		angle: rotateParms ? rotateParms[0] : 0,
    		x: rotateParms ? rotateParms[1] : 0,
    		y: rotateParms ? rotateParms[2] : 0
    	};

    	return parameters;
    };
};