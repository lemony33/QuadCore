#version 430 core

in vec3 position; 
in vec2 texCoord;
in vec3 normal;
in vec4 ray;

out vec2 texCoord0;
out vec3 normal0;
out vec4 color0;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(position, 1.0);
	texCoord0 = texCoord;
}
