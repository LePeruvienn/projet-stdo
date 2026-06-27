#version 330 core
layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec2 aInstancePosition;

uniform vec2  uCameraPosition;
uniform float uCameraZoom;
uniform float uCameraAspect;

out vec2 vUV;

const float glyphWidth  = 11.0;
const float atlasWidth  = 1045.0;

int charId = 2;

void main()
{
	float u0 = (float(charId) * glyphWidth) / atlasWidth;
	float u1 = u0 + glyphWidth / atlasWidth;

	vec2 local = aVertexPosition * 0.5 + 0.5;
	vUV = vec2(
		mix(u0, u1, local.x),
		local.y
	);

	vec2 pos = (aVertexPosition + aInstancePosition - uCameraPosition) / uCameraZoom;
	pos.y *= uCameraAspect;
	gl_Position = vec4(pos, 0.0, 1.0);
}
