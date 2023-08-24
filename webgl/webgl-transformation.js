var VSHADER_SOURCE = 
  'attribute vec4 a_Position;\n' +
  'void main() {\n' +
  '  gl_Position = a_Position;\n' +
  '}\n';

var FSHADER_SOURCE = 
  'void main() {\n' + 
  ' gl_FragColor = vec4(1.0, 1.0, 0, .8);\n' +
  '}\n';

function main() {
  const canvas = document.querySelector("#glcanvas");
  const gl = canvas.getContext("webgl");

  if (gl === null) {
    alert(
      "Unable to initialize WebGL. Your browser or machine may not support it."
    );
    return;
  }

  // Set clear color to black, fully opaque
  gl.clearColor(0.0, 0.0, 0.0, 1.0);
  // Clear the color buffer with specified clear color
  gl.clear(gl.COLOR_BUFFER_BIT);


  if (!initShaders(gl, VSHADER_SOURCE, FSHADER_SOURCE)) {
    alert("Failed to initialize shaders. end of the world");
    return;
  }

  // set position of vertex
  var n = initVertexBuffers(gl);

  gl.drawArrays(gl.TRIANGLES, 0, n);
}

function initVertexBuffers(gl) {
  var vertices = new Float32Array({
    0.0, 0.5, -0.5, -0.5, 0.5, -0.5
  });

  var n = 3;

  // create buffers
  var vertextBuffer = gl.createBuffer();
  if (!vertextBuffer) {
    alert("Failed to create buffer, oops!");
    return -1;
  }

  gl.bindBuffer(gl.ARRAY_BUFFER, vertextBuffer);
  gl.bufferData(gl.ARRAY_BUFFER, vertices, gl.STATIC_DRAW);

  var a_Position = gl.getAttribLocation(gl.program, 'a_Position');

  gl.vertexAttribPointer(a_Position, 2, gl.FLOAT, false, 0, 0);

  // connect var with its buffer object
  gl.enableVertexAttribArray(a_Position);
  
  return n;
}
