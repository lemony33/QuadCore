#version 430 core

out vec4 color;
layout (location = 100) uniform vec4 lineColor;

void main()
{
	//color = color;
	color = lineColor;
}
