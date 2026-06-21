#version 330 core

in vec2 vLocalPos;
in vec4 vColor;

out vec4 fFragColor;

vec4 fillColor = vec4(1.f, 0.f, 0.f, 1.f);
vec4 borderColor = vec4(0.f, 1.f, 0.f, 1.f);

float radius = 1.0;
float thickness = 0.1f;

void main()
{
	float d = length(vLocalPos);
	float aa = fwidth(d);

	float borderMix = smoothstep(radius - thickness - aa, radius - thickness + aa, d);
	vec3 rgb = mix(fillColor.rgb, borderColor.rgb, borderMix);

	float alpha = 1.0 - smoothstep(radius - aa, radius + aa, d);

	fFragColor = vec4(rgb, alpha);
}
