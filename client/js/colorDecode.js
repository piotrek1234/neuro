function decodeColor (colorId) {
	var result = "";

	colorId = parseInt(colorId);

	switch (colorId) {
		case 1:
			result = "blue";
			break;
	
		case 2:
			result = "red";
			break;

		case 3:
			result = "yellow";
			break;

		case 4:
			result = "green";
			break;
	}

	return result;
};

function getColorPrefix (colorId) {
	var result = "";

	colorId = parseInt(colorId);

	switch (colorId) {
		case 1:
			result = "bl";
			break;
	
		case 2:
			result = "rd";
			break;

		case 3:
			result = "yl";
			break;

		case 4:
			result = "gr";
			break;
	}

	return result;
};