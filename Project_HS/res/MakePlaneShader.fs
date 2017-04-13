#version 430 core

varying vec2 texCoords;
uniform sampler2D diffuse;
out vec4 color;

void main()
{
	color = texture2D(diffuse, texCoords);
}

