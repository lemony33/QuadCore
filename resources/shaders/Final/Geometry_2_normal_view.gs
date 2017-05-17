#version 430 core


/* --------- Nomal Viwer : BEGIN --------- */ 

layout (triangles) in;
layout (line_strip, max_vertices = 4) out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform int i_normal_viewer;	// normal viwer ON/OFF (법선벡터 활성화 판단하는 변수)
uniform float normal_length;

uniform float explode_factor = 0.2;

/* --------- Nomal Viwer : END --------- */ 


in VS_OUT
{
	vec2 texCoord0;  //texture
	vec3 normal0;    //lighting	
	vec3 FragPos;
} gs_in[];


out GS_OUT
{
	vec2 texCoord0;  // texture
	vec3 normal0;    // lighting
	vec3 FragPos;	 // color
} gs_out;


void main()
{
	mat4 mvp = projection * view *  model;                        
	vec3 ab = gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz;     
	vec3 ac = gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz;     
	vec3 face_normal = normalize(cross(ab, ac));       
    
	vec4 tri_centroid = (gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position) / 3.0;

	vec4 explode = vec4(face_normal * explode_factor, 0.0);
	//tri_centroid += explode; // normal viewer + explode
                                                                                   
	//gl_Position = mvp * tri_centroid;
	gl_Position = mvp * (tri_centroid + explode);
	gs_out.texCoord0 = gs_in[0].texCoord0;                              
	gs_out.normal0 = gs_in[0].normal0;                                   
	gs_out.FragPos = gs_in[0].FragPos;                                     
	EmitVertex();                                                      
    
	//gl_Position = mvp * (tri_centroid + vec4(face_normal * normal_length, 0.0));                                                                           
	gl_Position = mvp * (tri_centroid + explode + vec4(face_normal * normal_length, 0.0));
	gs_out.texCoord0 = gs_in[0].texCoord0;  
	gs_out.normal0 = gs_in[0].normal0;                                   
	gs_out.FragPos = gs_in[0].FragPos;                                     
	EmitVertex();                                                      
	EndPrimitive();
	
	                                                      
	//gl_Position = mvp * gl_in[0].gl_Position;
	gl_Position = mvp * (gl_in[0].gl_Position + explode);
	gs_out.texCoord0 = gs_in[0].texCoord0;                           
	gs_out.normal0 = gs_in[0].normal0;                                   
	gs_out.FragPos = gs_in[0].FragPos;                                     
	EmitVertex();                                                      
    
	//gl_Position = mvp * (gl_in[0].gl_Position + vec4(gs_in[0].normal0 * normal_length , 0.0));                                    
	gl_Position = mvp * (gl_in[0].gl_Position + explode + vec4(gs_in[0].normal0 * normal_length , 0.0));
	gs_out.texCoord0 = gs_in[0].texCoord0;  
	gs_out.normal0 = gs_in[0].normal0;                                   
	gs_out.FragPos = gs_in[0].FragPos;                                     
	EmitVertex();                                                      
	EndPrimitive();
}