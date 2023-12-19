// hellocanvas.js
function main() {
	var canvas = document.getElementById('webgl');

	var gl = canvas.getContext('webgl');
	if (!gl) {
		console.error('Failed to get the rendering context for WebGL');
		return;
	}

	// specify the color
	gl.clearColor(0.0, 1.0, 0.0, .3);

	// clear the canvas
	gl.clear(gl.COLOR_BUFFER_BIT);
}
