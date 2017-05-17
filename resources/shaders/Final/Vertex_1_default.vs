#version 430 core


// mesh header file ����
layout (location = 0) in vec3 position;	// position
layout (location = 1) in vec2 texCoord;	// texture
layout (location = 2) in vec3 normal;	// lighting


out VS_OUT
{
	vec2 texCoord0;  //texture
	vec3 normal0;    //lighting	
	vec3 FragPos;
} vs_out;


//uniform mat4 transform;		// mvp�� �ѹ��� ����ϴ� ����, ������������� ������� ����
uniform mat4 model;				// model matrix (��ü)
uniform mat4 view;				// view matrix (ī�޶�)
uniform mat4 projection;		// projection matrix (�翵)

uniform int i_normal_viewer;	// normal viwer ON/OFF (�������� Ȱ��ȭ �Ǵ��ϴ� ����)


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

