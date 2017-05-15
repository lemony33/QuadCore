#version 430 core

in vec3 position;
uniform mat4 transform;

layout (location = 100) uniform mat4 MVP;


void main()
{
	//gl_Position = transform * vec4(position, 1.0f);
	gl_Position = MVP * vec4(position, 1.0f);
}
