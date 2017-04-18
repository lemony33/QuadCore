#version 430 core

in vec2 texCoord0;
in vec3 normal0;
out vec4 color;
uniform sampler2D diffuse;

void main()
{
	color = 
	texture2D(diffuse, texCoord0) * 
	clamp(dot(-vec3(0.0f, 0.0f, 1.0f), normal0), 0.0f, 1.0f);
}
