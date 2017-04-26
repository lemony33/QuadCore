#version 430 core

out vec4 color;
layout (location = 100) uniform vec4 lineColor;

out vec4 FragmentColor1;
uniform vec4 IDcolor;

void main()
{
	//color = color;
	color = lineColor;
	FragmentColor1 = IDcolor;
}
