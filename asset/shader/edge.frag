#version 330 core

out vec4 fFragColor;

uniform vec4 uEdgeColor;

void main()
{
	fFragColor = uEdgeColor;
}
