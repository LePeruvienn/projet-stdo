#version 330 core

uniform sampler2D uTexture;
// MARCHE PAS !!!!
uniform vec4 uTextColor;

in vec2 vUV;
out vec4 fFragColor;

void main()
{
	vec4 textureColor = texture(uTexture, vUV);

	fFragColor = textureColor + uTextColor;
}
