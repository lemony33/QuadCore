#version 430 core

// mesh header file 참고
layout (location = 0) in vec3 position;	// position
layout (location = 1) in vec2 texCoord;	// texture
layout (location = 2) in vec3 normal;	// lighting

out vec2 texCoord0;  //texture
out vec3 normal0;    //lighting

out vec3 FragPos;

uniform mat4 transform;  //uniform 에 transform을 set한다
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

layout (location = 100) uniform mat4 MVP;


void main()
{
////	gl_Position = transform * vec4(position, 1.0);	//trnasform
//	gl_Position = projection * view *  model * vec4(position, 1.0f);

	gl_Position = MVP * vec4(position, 1.0f);


	// OUT TO FRAGMENT SHADER
	texCoord0 = texCoord;
////	normal0 = (transform * vec4(normal, 0.0)).xyz;	//lighting

	FragPos = vec3(model * vec4(position, 1.0f));
	normal0 = mat3(transpose(inverse(model))) * normal;

}

