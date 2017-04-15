#version 430 core

varying vec2 texCoord0;
varying vec3 normal0;
uniform sampler2D diffuse;
out vec4 color;

void main()
{48l65h
	color = texture2D(diffuse, texCoord0);
}

