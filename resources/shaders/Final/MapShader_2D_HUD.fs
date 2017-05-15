#version 430 core

out vec4 color;
uniform vec4 lineColor;

void main()
{
	//color = color;
	color = lineColor;
}
