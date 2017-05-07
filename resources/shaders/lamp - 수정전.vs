
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 texCoord;
layout (location = 2) in vec3 normal;

//out vec2 texCoord0;  //texture
//out vec3 normal0;    //lighting
out vec3 LPOS;

uniform mat4 transform; 
uniform vec3 pos;


void main()

{

    gl_Position = transform * vec4(position, 1.0f);
	//texCoord0 = texCoord;
    LPOS = pos;

} 