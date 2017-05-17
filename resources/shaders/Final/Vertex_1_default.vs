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


//uniform mat4 transform;		// mvp를 한번에 계산하는 변수, 현재버전에서는 사용하지 않음
uniform mat4 model;				// model matrix (물체)
uniform mat4 view;				// view matrix (카메라)
uniform mat4 projection;		// projection matrix (사영)

uniform int i_normal_viewer;	// normal viwer ON/OFF (법선벡터 활성화 판단하는 변수)


void main()
{

	if ( i_normal_viewer == 0 )
	{
		//gl_Position = transform * vec4(position, 1.0);	//trnasform
		gl_Position = projection * view *  model * vec4(position, 1.0f);	
	}
	if ( i_normal_viewer == 1 )
	{
		gl_Position = vec4(position, 1.0);
	}
	

	// OUT TO FRAGMENT SHADER
	vs_out.texCoord0 = texCoord;
	vs_out.normal0 = mat3(transpose(inverse(model))) * normal;
	vs_out.FragPos = vec3(model * vec4(position, 1.0f));

}

/*
	// Exploder
	gl_Position = proj_matrix * mv_matrix * position;	
	vs_out.FragPos = position * 2.0 + vec3(0.5, 0.5, 0.5);	
	vs_out.normal0 = normalize(mat3(mv_matrix) * normal); 

	// Normal Viewer
	gl_Position = position;										
	vs_out.FragPos = position * 2.0 + vec3(0.5, 0.5, 0.5);	
	vs_out.normal0 = normalize(normal);  


	if (i_normal_viewer==1)
	{
		vs_out.texCoord0 = texCoord;
		vs_out.normal0 = normalize(normal);
		vs_out.FragPos = position * 2.0 + vec3(0.5, 0.5, 0.5);
	}
	else
	{
		vs_out.texCoord0 = texCoord;
		vs_out.normal0 = mat3(transpose(inverse(model))) * normal;
		vs_out.FragPos = vec3(model * vec4(position, 1.0f));
	}
*/

