#version 430 core

uniform mat3 m_position;
uniform mat3 m_perspective;

in vec3 position; 
in vec3 normal;   

out VS_OUT
{
	vec3 normal;
	vec3 view;
} vs_out;

void main()
{
	vec3 pos_vs = m_position * position;

    vs_out.normal = mat3(m_position) * normal;
    vs_out.view = pos_vs.xyz;

    gl_Position = m_perspective * pos_vs;
}