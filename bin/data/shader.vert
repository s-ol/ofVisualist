#version 130

in vec4 position;
in vec2 texcoord;
uniform mat4 modelViewProjectionMatrix;

out vec2 texCoordVarying;

void main() {
  texCoordVarying = texcoord;
  gl_Position = modelViewProjectionMatrix * position;
}
