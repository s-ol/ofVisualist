#version 130

in vec2 texCoordVarying;
uniform sampler2DRect tex0;

uniform vec4 colors[8];
uniform float offset;
uniform float colMix;
uniform float lumMix;
uniform float lumOff;
uniform float lumTLo;
uniform float lumTHi;

out vec4 outputColor;

vec3 L = vec3(0.2125, 0.7154, 0.0721);

void main() {
  vec3 sample = texture(tex0, texCoordVarying).rgb;
  float lum = (dot(L, sample) - lumTLo) / lumTHi;
  int index = int(lum * 8 + offset) % 8;
  vec3 recol = colors[index].rgb;

  float alpha = float(index)/8.0 + lumOff;

  outputColor = vec4(mix(sample, recol, colMix), mix(1.0, alpha, lumMix));
}
