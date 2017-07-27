#version 120
#extension GL_EXT_gpu_shader4 : enable

uniform vec4 colors[8];
uniform float offset;
uniform float colMix;
uniform float lumMix;
uniform float lumOff;
uniform float lumTLo;
uniform float lumTHi;
uniform int stepMode;

uniform sampler2DRect tex0;
varying vec2 texCoordVarying;

vec3 L = vec3(0.2125, 0.7154, 0.0721);

void main() {
	vec3 sample = texture2DRect(tex0, texCoordVarying).rgb;
	float lum = (dot(L, sample) - lumTLo) / lumTHi;
	int index = int(lum * 8 + offset) % 8;
	if (stepMode == 1)
		int(lum * 8 + floor(offset)/10) % 8;
	vec3 recol = colors[index].rgb;

	float alpha = float(index)/8.0 + lumOff;

	gl_FragColor = vec4(mix(sample, recol, colMix), mix(1.0, alpha, lumMix));
}