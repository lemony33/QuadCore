#version 430 core

in vec2 texCoord0;  //texture
in vec3 normal0;    //lighting

uniform sampler2D diffuse;

void main()
{
	gl_FragColor = texture2D(diffuse, texCoord0)
		* clamp(dot(-vec3(0,1,0), normal0), 0.0, 1.0);	//lighting

	//gl_FragColor = texture2D(diffuse, texCoord0) //Texture
	//gl_FragColor = texture2D(diffuse, vec2(0.3, 0.8)); //Texture
	//gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);	//Color
}

