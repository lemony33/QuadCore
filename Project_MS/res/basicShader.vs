#version 430 core

// mesh header file 참고
attribute vec3 position; 
attribute vec2 texCoord; //texture
attribute vec3 normal;   //lighting

varying vec2 texCoord0;  //texture
varying vec3 normal0;    //lighting

uniform mat4 transform;  //uniform 에 transform을 set한다

void main()
{
	gl_Position = transform * vec4(position, 1.0); //trnasform
												   //gl_Position = vec4(position, 1.0);  // texture까지만 사용
	texCoord0 = texCoord;
	normal0 = (transform * vec4(normal, 0.0)).xyz;	   //lighting
}
