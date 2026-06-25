#version 330 core

layout(location = 0) in vec2 aVertexPosition;

out vec2 vUV;

void main()
{
	vUV = aVertexPosition;
	gl_Position = vec4(aVertexPosition, 0.f, 1.f);
}
