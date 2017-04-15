#version 430 core

// mesh header file ����
in vec3 position; 
in vec2 texCoord; //texture
in vec3 normal;   //lighting

out VS_OUT
{
	vec2 texCoord0;  //texture
	vec3 normal0;    //lighting

	vec3 view;
} vs_out;

uniform mat4 m_position;  //uniform �� transform�� set�Ѵ�
uniform mat4 m_perspective;	// no use


void main()
{
	gl_Position = m_position * vec4(position, 1.0);	//trnasform
	vs_out.texCoord0 = texCoord;
	vs_out.normal0 = (m_position * vec4(normal, 0.0)).xyz;	//lighting

	vs_out.view = (m_position * vec4(normal, 0.0)).xyz;
}
