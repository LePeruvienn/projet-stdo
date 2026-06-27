#version 330 core

out vec4 fFragColor;

uniform vec4 uLineColor;

void main()
{
	fFragColor = uLineColor;
}
