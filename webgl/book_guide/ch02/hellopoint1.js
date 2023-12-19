// hellopoint1.js
// vertext shader program
var VSHADER_SOURCE = 
  'void main() {\n' + 
  '  gl_Position = vec4(0.0, 0.0, 0.0, 1.0);\n' + // coordinates
  '  gl_PointSize = 10.0;\n' +                     // set the point size
  '}\n';
console.info(VSHADER_SOURCE);
// fragment shader program
var FSHADER_SOURCE = 
  'void main() {\n' +
  '    gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n' + // set the color
  '}\n';

function main() {
	var canvas = document.getElementById('webgl');

	var gl = canvas.getContext('webgl');
	if (!gl) {
		console.error('Failed to get the rendering context for WebGL');
		return;
	}

	// initialize the shaders
	if 

	// specify the color
	gl.clearColor(0.0, 1.0, 0.0, .3);

	// clear the canvas
	gl.clear(gl.COLOR_BUFFER_BIT);
}
