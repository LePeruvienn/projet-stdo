#version 330 core

layout(location = 0) in vec2 aVertexPosition;
layout(location = 2) in vec2 aInstanceLineP1;
layout(location = 3) in vec2 aInstanceLineP2;

uniform vec2 uCameraPosition;
uniform float uCameraZoom;
uniform float uCameraAspect;

out vec4 vColor;

float thickness = 0.05f;
vec4 lineColor = vec4(0.3f, 0.2f, 2.f, 1.f);

void main()
{
	vec2 p = mix(aInstanceLineP1, aInstanceLineP2, aVertexPosition.x * 0.5f + 0.5f);

	vec2 dir = normalize(aInstanceLineP2 - aInstanceLineP1);
	vec2 perp = vec2(-dir.y, dir.x);

	p += perp * aVertexPosition.y * thickness;

	vec2 pos = (p - uCameraPosition) / uCameraZoom;
	pos.y *= uCameraAspect;

	gl_Position = vec4(pos, 0.f, 1.f);

	vColor = lineColor;
}
