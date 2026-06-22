#version 330 core

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec2 aInstancePosition;

uniform vec2 uCameraPosition;
uniform float uCameraZoom;
uniform float uCameraAspect;

uniform vec3 uModelPosition;
uniform vec3 uModelScale;
uniform vec3 uModelColor;

out vec4 vColor;
out vec2 vLocalPos;

void main()
{
	vLocalPos = aVertexPosition;
	vColor = vec4(1.0f, 0.f, 0.f, 1.0f);

	vec2 pos = (aVertexPosition - aInstancePosition - uCameraPosition) / uCameraZoom;
	pos.y *= uCameraAspect;

	gl_Position = vec4(pos, 0.0f, 1.0f);
}
