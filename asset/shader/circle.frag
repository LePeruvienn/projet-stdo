#version 330 core

in vec2 vLocalPos;
in vec4 vColor;

out vec4 fFragColor;

uniform vec4  uCircleColor;
uniform vec4  uCircleBorderColor;

uniform float uCircleRadius;
uniform float uCircleBorderThickness;

void main()
{
	float d = length(vLocalPos);
	float aa = fwidth(d);

	float borderMix = smoothstep(
			uCircleRadius - uCircleBorderThickness - aa,
			uCircleRadius - uCircleBorderThickness + aa, d);

	vec3 rgb = mix(uCircleColor.rgb, uCircleBorderColor.rgb, borderMix);

	float alpha = 1.0 - smoothstep(uCircleRadius - aa, uCircleRadius + aa, d);

	fFragColor = vec4(rgb, alpha);
}
