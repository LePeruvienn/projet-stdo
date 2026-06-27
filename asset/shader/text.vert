#version 330 core

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec2 aInstancePosition;
layout(location = 4) in int aInstanceCharId;

uniform vec2  uCameraPosition;
uniform float uCameraZoom;
uniform float uCameraAspect;

uniform float uTextSize;

out vec2 vUV;

int charsPerRow = 10;
int charsPerCol = 10;

void main()
{
	float col = float(aInstanceCharId % charsPerRow);
	float row = float(aInstanceCharId / charsPerRow);

	float u0 = col / float(charsPerRow);
	float u1 = u0 + 1.0 / float(charsPerRow);

	float v0 = row / float(charsPerCol);
	float v1 = v0 + 1.0 / float(charsPerCol);

	vec2 local = aVertexPosition * 0.5 + 0.5;

	vUV = vec2(
		mix(u0, u1, local.x),
		mix(v0, v1, local.y)
	);

	vec2 pos = ((aVertexPosition * uTextSize) + aInstancePosition - uCameraPosition) / uCameraZoom;
	pos.y *= uCameraAspect;
	gl_Position = vec4(pos, 0.0, 1.0);
}
