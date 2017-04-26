#version 430 core

in vec2 TextureCoords;
in vec4 color;

layout (location = 0) out vec4 FragmentColor0;
layout(location = 1) out vec4 FragmentColor1;

uniform vec4 IDcolor;

void main()
{
	FragmentColor0 = color;
	FragmentColor1 = IDcolor;
}
