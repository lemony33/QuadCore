#version 430 core


// mesh header file 참고
layout (location = 0) in vec3 position;	// position
layout (location = 1) in vec2 texCoord;	// texture
layout (location = 2) in vec3 normal;	// lighting


out VS_OUT
{
	vec2 texCoord0;  //texture
	vec3 normal0;    //lighting	
	vec3 FragPos;
} vs_out;


uniform mat4 transform;  //uniform 에 transform을 set한다
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
//	gl_Position = transform * vec4(position, 1.0);	//trnasform
	gl_Position = projection * view *  model * vec4(position, 1.0f);


	// OUT TO FRAGMENT SHADER
	vs_out.texCoord0 = texCoord;
	vs_out.normal0 = mat3(transpose(inverse(model))) * normal;
	vs_out.FragPos = vec3(model * vec4(position, 1.0f));
}

