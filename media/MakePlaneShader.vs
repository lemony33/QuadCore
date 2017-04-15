#version 430 core

attribute vec3 position;
attribute vec2 texCoord;
varying vec2 texCoords;

void main()
{
	gl_Position = vec4(position, 1.0f);
	texCoords = texCoord;
}

