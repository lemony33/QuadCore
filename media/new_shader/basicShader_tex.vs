#version 430 core

// mesh header file ����
layout (location = 0) in vec3 position;	// position
layout (location = 1) in vec2 texCoord;	// texture
//layout (location = 2) in vec3 normal;	// lighting

out vec2 texCoord0;  // texture
//varying vec3 normal0;    // lighting

uniform mat4 transform;  // uniform �� transform�� set�Ѵ�

void main()
{
	gl_Position = transform * vec4(position, 1.0); // trnasform
		 //gl_Position = vec4(position, 1.0);  // 1. shader ù��°

	texCoord0 = texCoord;
	//normal0 = (transform * vec4(normal, 0.0)).xyz;	   //lighting
}
