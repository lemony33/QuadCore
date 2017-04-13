#version 430 core

uniform float Scale;

in  vec4 v_color;
out vec4 f_color;

void main()
{
	//f_color = vec4(1.0, 0.0, 0.0, 1.0);
	f_color = v_color * Scale;
};