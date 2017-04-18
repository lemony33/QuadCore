#version 430 core

out vec4 color;
uniform sampler2D diffuse;
layout (location = 100) uniform vec4 lineColor;

void main()
{
	//color = color;
	color = lineColor;
}
