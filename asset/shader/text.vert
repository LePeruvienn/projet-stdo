#version 330 core

layout(location = 0) in vec2 aVertexPosition;

uniform vec2 uCameraPosition;
uniform float uCameraZoom;
uniform float uCameraAspect;

out vec2 vUV;

void main()
{
	vUV = aVertexPosition * 0.5 + 0.5;
	vUV.y /= uCameraAspect;

	gl_Position = vec4(aVertexPosition, 0.f, 1.f);
}
