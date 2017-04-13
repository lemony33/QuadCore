#version 430 core

varying vec2 texCoord0;  // texture
varying vec3 normal0;    // lighting

uniform sampler2D diffuse;	// texture / uniform access by CPU wt and GPU r

void main()
{
	gl_FragColor = texture2D(diffuse, texCoord0)
	* clamp(dot(-vec3(0,0,1), normal0), 0.0, 1.0);	//lighting

	//gl_FragColor = texture2D(diffuse, texCoord0) //Texture
	//gl_FragColor = texture2D(diffuse, vec2(0.3, 0.8)); // 2. Texture

	//gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);	// 1. shader ù��° : color ���� ���ذ���.
}
