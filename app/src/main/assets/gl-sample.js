function createStar(count = 5, inner = 0.20, outer = 0.75, phase = 0.0) {
  const scount = count * 2;
  const vertices = new Float32Array(scount * 2);
  for (let index = 0; index < scount; index++) {
    const a = ((index / scount) * Math.PI * 2);
    if (index % 2 === 0) {
      vertices[(index * 2) + 0] = Math.cos(a + phase) * outer;
      vertices[(index * 2) + 1] = Math.sin(a + phase) * outer;
    } else {
      vertices[(index * 2) + 0] = Math.cos(a + phase) * inner;
      vertices[(index * 2) + 1] = Math.sin(a + phase) * inner;
    }
  }
  return vertices;
}

function createPolygon(count = 72, radius = 0.75, phase = 0.0) {
  const vertices = new Float32Array(count * 2);
  for (let index = 0; index < count; index++) {
    const a = ((index / count) * Math.PI * 2);
    vertices[(index * 2) + 0] = Math.cos(a + phase) * radius;
    vertices[(index * 2) + 1] = Math.sin(a + phase) * radius;
  }
  return vertices;
}

const vertexShader = gl.createShader(gl.VERTEX_SHADER);
console.log("create Shader");
gl.shaderSource(vertexShader, `
precision mediump float;

attribute vec2 position;

void main(void) {
  gl_Position = vec4(position.x, position.y, 0.0, 1.0);
}`);
console.log("build Shader Source");
gl.compileShader(vertexShader);
console.log("compile Shader");

const vertexStatus = gl.getShaderParameter(vertexShader, gl.COMPILE_STATUS);
console.log("Shader Status");

const fragmentShader = gl.createShader(gl.FRAGMENT_SHADER);
console.log("create fragment");
gl.shaderSource(fragmentShader, `
precision highp float;

void main(void) {
  gl_FragColor = vec4(0.0,0.0,0.0,1.0);
}`);
console.log("build fragment source");
gl.compileShader(fragmentShader);
console.log("compile Fragment");

const fragmentStatus = gl.getShaderParameter(fragmentShader, gl.COMPILE_STATUS);
console.log("get Shader Param");

const program = gl.createProgram();
console.log("create program");
gl.attachShader(program, vertexShader);
console.log("attach Shader");
gl.attachShader(program, fragmentShader);
console.log("attach Fragment");
gl.linkProgram(program);
console.log("link program");

const linked = gl.getProgramParameter(program, gl.LINK_STATUS);
console.log("get Program Param");

const COUNT = 6;

const buffer = gl.createBuffer();
console.log("create Buffer");
gl.bindBuffer(gl.ARRAY_BUFFER, buffer);
console.log("bind Buffer");

const polygon = createPolygon(COUNT, 0.15);
gl.bufferData(gl.ARRAY_BUFFER, polygon, gl.STATIC_DRAW);
console.log("fill buffer data");

const attribPosition = gl.getAttribLocation(program, "position");
console.log("get location");
gl.vertexAttribPointer(attribPosition, 2, gl.FLOAT, false, 0, 0);
console.log("fill Pointer");
gl.enableVertexAttribArray(attribPosition);
console.log("enable Array");

gl.useProgram(program);
console.log("use program");

gl.clearColor(0.0,255.0,0.0,1.0);
gl.clear(gl.COLOR_BUFFER_BIT);
console.log("fill Data");


gl.lineWidth(5);
console.log("set line width");

gl.drawArrays(gl.LINE_LOOP, 0, COUNT);
console.log("draw");