#version 430 core

in vec2 texCoord0;  // texture
in vec3 normal0;    // lighting

uniform sampler2D diffuse;	// texture / uniform access by CPU wt and GPU r

void main()
{
	gl_FragColor = texture2D(diffuse, texCoord0)
		* clamp(dot(-vec3(0,0,1), normal0), 0.0, 1.0);	//lighting

}
