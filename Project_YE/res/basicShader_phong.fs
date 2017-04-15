#version 430 core

in VS_OUT
{
	vec2 texCoord0;	// textrue
	vec3 normal0;	// lighting

	vec3 view;
} fs_in;

uniform sampler2D diffuse;

uniform samplerCube tex_cubemap;

out vec4 color;

void main()
{
//	gl_FragColor = texture2D(diffuse, fs_in.texCoord0)
//		* clamp(dot(-vec3(0,0,1), fs_in.normal0), 0.0, 1.0);	//lighting

	vec3 r = reflect(fs_in.view, normalize(fs_in.normal0));
//	color = texture2D(diffuse, fs_in.texCoord0)
//		* vec4(0.95, 0.80, 0.45, 1.0);	// gold
//	color = texture(tex_cubemap, r)
//		* vec4(0.95, 0.80, 0.45, 1.0);	// gold

	color = texture2D(diffuse, fs_in.texCoord0) * vec4(0.95, 0.80, 0.45, 1.0);
}
