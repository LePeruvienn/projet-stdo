#version 330 core

layout(location = 0) in vec2 aVertexPosition;

out vec2 vWorldPos;

uniform vec2 uCameraPosition;
uniform float uCameraZoom;
uniform float uCameraAspect;

void main()
{
	vec2 worldPos;

	// calcul tricky pour éviter un défilement pas "naturelle"
	worldPos.x = aVertexPosition.x * uCameraZoom + uCameraPosition.x;
	worldPos.y = (aVertexPosition.y / uCameraAspect) * uCameraZoom + uCameraPosition.y;

	vWorldPos = worldPos;

	gl_Position = vec4(aVertexPosition, 0.0, 1.0);
}
