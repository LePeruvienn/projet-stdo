#version 330 core

layout(location = 0) in vec2 aVertexPosition;

out vec2 vWorldPos;

uniform vec2 uCameraPosition;
uniform float uCameraZoom;
uniform float uCameraAspect;

void main()
{
	vec2 pos = (aVertexPosition - uCameraPosition) / uCameraZoom;
	pos.y *= uCameraAspect;

	vWorldPos = pos;

	gl_Position = vec4(aVertexPosition, 0.0, 1.0);
}
