#version 430 core

in vec2 texCoord0;
uniform sampler2D diffuse;

layout (location = 3) out vec4 Fragment_color1;

uniform vec4 IDcolor;

void main()
{
	gl_FragColor = texture2D(diffuse, texCoord0);
	Fragment_color1 = IDcolor;	
}
