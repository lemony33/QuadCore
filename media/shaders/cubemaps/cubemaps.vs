
#version 330 core


layout (location = 0) in vec3 position;	// position
layout (location = 1) in vec2 texCoord;	// texture
layout (location = 2) in vec3 normal;	// lighting


//out vec3 Normal;
out vec3 Position;

out vec2 texCoord0;  //texture
out vec3 normal0;    //lighting

out vec3 FragPos;


uniform mat4 transform;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;



void main()

{

    gl_Position = projection * view * model * vec4(position, 1.0f);

    normal0 = mat3(transpose(inverse(model))) * normal;
	texCoord0 = texCoord;
    Position = vec3(model * vec4(position, 1.0f));

}  

/*
{

    gl_Position = projection * view * model * vec4(position, 1.0f);

    normal0 = mat3(transpose(inverse(model))) * normal;
	texCoord0 = texCoord;
    Position = vec3(model * vec4(position, 1.0f));

}  
*/