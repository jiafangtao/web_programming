function initWebGL(canvas) {
    var gl;
    try {
        gl = canvas.getContext("experimental-webgl");
    } catch(e) {
        var msg = "Error creating WebGL context: " + e.toString();
        alert(msg);
        throw Error(msg);
    }

    return gl;
}

function initViewport(gl, canvas) {
    gl.viewport(0, 0, canvas.width, canvas.height);
}

function createSquare(gl) {
    var vertexBuffer;
    vertexBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
    
    var verts = [
        .5, .5, 0.0,
        -.5, .5, 0.0,
        .5, -.5, 0.0,
        -.5, -.5, 0.0
    ];

    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(verts), gl.STATIC_DRAW);
    var square = { buffer: vertextBuffer, vertSize: 3, nVerts: 4,
        primtype: gl.TRIANGLE_STRIP};

    return square;
}

function initMatrices() {
    modelViewMatrix = new Float32Array(
        [1, 0, 0, 0,
         0, 1, 0, 0,
         0, 0, 1, 0,
         0, 0, -3.333, 1]
    );

    projectionMatrix = new Float32Array(
        [2.41421, 0, 0, 0,
         0, 2.41421, 0, 0,
         0, 0, -1.002002, -1,
         0, 0, -0.2002002, 0]);
}

var vertexShaderSource = 
    "    attribute vec3 vertexPos;\n" +
    "    uniform mat4 modelViewMatrix;\n" +
    "    uniform mat4 projectionMatrix;\n" +
    "    void main(void) {\n" +
    "        gl_Position = projectionMatrix * modelViewMatrix * \n" + 
    "                vec4(vertexPos, 1.0);\n" +
    "    }\n";

var fragmentShaderSource =
    "    void main(void) {\n" +
    "        gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);\n" +
    "    }\n";


function draw(gl, obj) {
    gl.clearColor(0.0, 0.0, 0.0, 1.0);
    gl.clear(gl.COLOR_BUFFER_BIT);

    gl.bindBuffer(gl.ARRAY_BUFFER, obj.buffer);

    gl.useProgram(shaderProgram);

    gl.vertexAttributePointer(shaderVertexPositionAttibute, obj.vertSize, gl.FLOAT, false, 0, 0);
    gl.uniformMatrix4fv(shaderProjectionMatrixUniform, false, projectionMatrix);
    gl.uniformMatrix4fv(shaderModelViewMatrixUniform, false, modelViewMatrix);

    gl.drawArrays(obj.primtype, 0, obj.nVerts);
}

