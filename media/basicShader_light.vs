#version 430 core

// mesh header file 참고
in vec3 position; 
in vec2 texCoord; //texture
in vec3 normal;   //lighting

out vec2 texCoord0;  //texture
out vec3 normal0;    //lighting

uniform mat4 transform;  //uniform 에 transform을 set한다

void main()
{
	gl_Position = transform * vec4(position, 1.0); //trnasform
												   //gl_Position = vec4(position, 1.0);  // texture까지만 사용
	texCoord0 = texCoord;
	normal0 = (transform * vec4(normal, 0.0)).xyz;	   //lighting
}

