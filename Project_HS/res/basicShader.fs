#version 430 core

varying vec2 texCoord0;
varying vec3 normal0;

uniform sampler2D diffuse;

out vec4 color;

void main()
{
	color = texture2D(diffuse, texCoord0)
		* clamp(dot(-vec3(0.0f, 0.0f, 1.0f), normal0), 0.0f, 1.0f);
}

