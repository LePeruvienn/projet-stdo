#version 330 core

in vec2 vWorldPos;
out vec4 FragColor;

uniform float uGridSize;
uniform vec4 uGridBgColor;
uniform vec4 uGridLineColor;

void main()
{
	vec2 coord = vWorldPos / uGridSize;

	vec2 grid = abs(fract(coord) - 0.5);

	vec2 fw = fwidth(coord);

	float lineX = 1.0 - smoothstep(0.0, fw.x * 1.5, grid.x);
	float lineY = 1.0 - smoothstep(0.0, fw.y * 1.5, grid.y);

	float line = max(lineX, lineY);

	FragColor = vec4(mix(uGridBgColor, uGridLineColor, line));
}
