#version 430 core

in vec2 texCoord0;  
//in vec3 normal0;

uniform sampler2D diffuse;

//out vec4 FragmentColor1;
//uniform vec4 IDcolor;

void main()
{
	gl_FragColor = texture2D(diffuse, texCoord0);
		//* clamp(dot(-vec3(0,1,0), normal0), 0.0, 1.0);

	//FragmentColor1 = IDcolor;
}
