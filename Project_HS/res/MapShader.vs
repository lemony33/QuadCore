#version 430 core

in vec3 position;
in vec2 texCoord;

out vec2 texCoord0;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(position, 1.0f);
	texCoord0 = texCoord;
}
