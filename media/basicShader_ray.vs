#version 430 core

in vec3 position; 
in vec2 texCoord; 
//in vec3 normal;


out vec2 texCoord0;
//out vec3 normal0; 

uniform mat4 transform; 

void main()
{
	gl_Position = transform * vec4(position, 1.0);
	texCoord0 = texCoord;
	//normal0 = (transform * vec4(normal, 0.0)).xyz;
}

