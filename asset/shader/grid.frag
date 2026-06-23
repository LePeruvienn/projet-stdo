#version 330 core

in vec2 vWorldPos;
out vec4 FragColor;

float gridSize = 5.f;
vec4 backgroundColor = vec4(0.1f, 0.1f, 0.1f, 1.);
vec4 lineColor = vec4(0.3f, 0.3f, 0.3f, 1.f);

void main()
{
	vec2 coord = vWorldPos / gridSize;

	vec2 grid = abs(fract(coord) - 0.5);

	vec2 fw = fwidth(coord);

	float lineX = 1.0 - smoothstep(0.0, fw.x * 1.5, grid.x);
	float lineY = 1.0 - smoothstep(0.0, fw.y * 1.5, grid.y);

	float line = max(lineX, lineY);

	FragColor = vec4(mix(backgroundColor, lineColor, line));
}
