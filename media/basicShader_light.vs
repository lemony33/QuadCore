#version 430 core

// mesh header file ����
in vec3 position; 
in vec2 texCoord; //texture
in vec3 normal;   //lighting

out vec2 texCoord0;  //texture
out vec3 normal0;    //lighting

uniform mat4 transform;  //uniform �� transform�� set�Ѵ�

void main()
{
	gl_Position = transform * vec4(position, 1.0); //trnasform
												   //gl_Position = vec4(position, 1.0);  // texture������ ���
	texCoord0 = texCoord;
	normal0 = (transform * vec4(normal, 0.0)).xyz;	   //lighting
}

