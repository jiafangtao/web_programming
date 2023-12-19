// utils.js

function initShaders(gl, vssrc, fssrc) {
	// 1. create shader objects
	var vshader = gl.createShader(gl.VERTEX_SHADER);
	if (!vshader) {
		console.error("Failed to create vertex shader");
		return false;
	}

	var fshader = gl.createShader(gl.FRAGMENT_SHADER);
	if (!fshader) {
		console.error("Failed to create fragment shader");
		return false;
	}

	// 2. store shader programs in shader objects
	gl.shaderSource(vshader, vssrc);
	gl.shaderSource(fshader, fssrc);

	// 3. compile shader objects
	gl.compileShader(vshader);
	gl.compileShader(fshader);

	//TODO: check compilation errors if any
	var success = gl.getShaderParameter(vshader, gl.COMPILE_STATUS);
	if (!success) {
		console.error("Compilation error was found");
		const error = gl.getShaderInfoLog(vshader);
		console.error(error);
		return false;
	}

	// 4. create a program object
	var program = gl.createProgram();

	// 5. attach shader objects to the program object
	gl.attachShader(program, vshader);
	gl.attachShader(program, fshader);

	// 6. link the program object
	//    During linking, various constraints of the WebGL system are checked.
	gl.linkProgram(program);
	// Check if linking succeeded or not.
	success = gl.getProgramParameters(program, gl.LINK_STATUS);
	if (!success) {
		console.error("Linking failed.");
		const error = gl.getProgramInfoLog(program);
		console.error(error);
		return false;
	}

	// 7. tell webgl system the program to be used
	gl.useProgram(program);
	// keep it for further reference.
	gl.program = program;
}
