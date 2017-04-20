
#version 330 core

in vec3 normal0;
in vec2 texCoord0;
in vec3 Position;

out vec4 color;



uniform vec3 lightPos;
uniform vec3 viewPos;
//uniform vec3 lightColor;
uniform vec3 light_ambient;
uniform vec3 light_diffuse;
uniform vec3 light_specular;
uniform vec3 objectColor;
//uniform sampler2D texture_diffuse;
uniform samplerCube skybox;



void main()

{             

    vec3 I = normalize(Position - viewPos);

    vec3 R = reflect(I, normalize(normal0));

    color = texture(skybox, R);

}