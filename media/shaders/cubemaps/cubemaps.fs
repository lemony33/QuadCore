
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

uniform sampler2D texture_diffuse;
uniform samplerCube skybox;



void main()

{
    float ambientStrength = 0.1f;
    //vec3 ambient = ambientStrength * light_ambient;
	vec3 texcolor = texture(texture_diffuse, texCoord0).rgb;
    vec3 ambient = ambientStrength * texcolor;

	// Diffuse
	vec3 norm = normalize(normal0);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(lightDir, norm), 0.0);
	vec3 diffuse = diff * texcolor;//* 1.5f * light_diffuse;
    
	// Specular
	float specularStrength = 0.9f;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * light_specular * 10;
    
	vec3 result = (ambient + diffuse + specular);

	float ratio = 1.00 / 1.52;
    vec3 I = normalize(FragPos - viewPos);

    //vec3 R = reflect(-I, normalize(normal0));

	vec3 R = refract(I, normalize(normal0), ratio);
	gl_FragColor = texture(skybox, R) // texture(texture_diffuse, texCoord0)
		 //* clamp(dot(-vec3(0,1,0), normal0), 0.0, 1.0)
		 * vec4(result, 1.0f);	//lighting
	
	
}
/*
{             
	float ratio = 3.00 / 4.00; //1.00 / 1.52;
    vec3 I = normalize(FragPos - viewPos);

    //vec3 R = reflect(I, normalize(normal0));
	vec3 R = refract(I, normalize(normal0), ratio);

    color = texture(skybox, -R);

}
*/