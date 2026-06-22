#version 330 core

in vec2 vWorldPos;
out vec4 fFragColor;

uniform vec2 uCameraPosition;
uniform float uCameraZoom;

vec4 backgroundColor = vec4(1.0, 1.0, 1.0, 1.0);
vec4 lineColor = vec4(0.0, 0.0, 0.0, 1.0);

float gridSize = 2.0;
float lineWidth = 0.1;

void main()
{
	fFragColor = backgroundColor;
}
