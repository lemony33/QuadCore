#version 430 core


/* --------- Object Explode : BEGIN --------- */ 

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;


uniform float explode_factor = 0.2;

/* --------- Object Explode : END --------- */ 


//in VS_OUT
in TES_OUT
{
	vec2 texCoord0;  //texture
	vec3 normal0;    //lighting	
	vec3 FragPos;
} gs_in[];


out GS_OUT
{
	vec2 texCoord0;  //texture
	vec3 normal0;    //lighting
	vec3 FragPos;
} gs_out;


void main()
{
	for (int i = 0; i < gl_in.length(); i++)
	{
		vec3 ab = gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz;
		vec3 ac = gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz;
		vec3 face_normal = -normalize(cross(ab, ac));
		gl_Position = gl_in[i].gl_Position + vec4(face_normal * explode_factor, 0.0);
		gs_out.texCoord0 = gs_in[i].texCoord0;
		gs_out.normal0 = gs_in[i].normal0;
		gs_out.FragPos = gs_in[i].FragPos;
		EmitVertex();
	}
	EndPrimitive();
}