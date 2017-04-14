#version 430 core

attribute vec3 position;
attribute vec2 texCoord;

varying vec2 texCoord0;
varying vec3 normal0;

void main()
{
	gl_Position = vec4(position, 1.0f);
	texCoord0 = texCoord;
}

