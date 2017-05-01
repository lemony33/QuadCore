
#version 330 core

in vec3 normal0;
in vec2 texCoord0;
in vec3 FragPos;

out vec4 color;



uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 light_ambient;
uniform vec3 light_diffuse;
uniform vec3 light_specular;
uniform vec3 objectColor;

uniform samplerCube texture_diffuse;
uniform samplerCube skybox;



void main()
{             
	float ratio = 1.00 / 1.52;
    vec3 I = normalize(FragPos - viewPos);

    //vec3 R = reflect(I, normalize(normal0));
	vec3 R = refract(I, normalize(normal0), ratio);

    color = texture(skybox, R);

}