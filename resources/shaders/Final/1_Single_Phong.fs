#version 430 core
//out vec4 color;

in vec2 texCoord0;  //texture
in vec3 normal0;    //lighting

in vec3 FragPos; //***********

uniform vec3 lightPos;
uniform vec3 viewPos;
//uniform vec3 lightColor;
uniform vec3 light_ambient;
uniform vec3 light_diffuse;
uniform vec3 light_specular;

uniform vec3 objectColor;


uniform sampler2D texture_diffuse;


struct PointLight{
	vec3 lightPos;
	vec3 light_ambient;
	vec3 light_diffuse;
	vec3 light_specular;
	float constant;
    float linear;
    float quadratic;
};

#define LIGHTSNUM 4

uniform PointLight pointLights[LIGHTSNUM];

void main()
{
	const vec3 fixed_lightPos = vec3(2.0, 2.0, 2.0);
	//gl_FragColor = texture2D(diffuse, texCoord0) //Texture
	//gl_FragColor = texture2D(diffuse, vec2(0.3, 0.8)); //Texture
	//gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);	//Color

	// Ambient
    	float ambientStrength = 0.3f;
    	vec3 ambient = ambientStrength * light_ambient;
    
	// Diffuse
	vec3 norm = normalize(normal0);
	//vec3 lightDir = normalize(lightPos - FragPos);
	//vec3 lightDir = normalize(fixed_lightPos - FragPos);
	vec3 lightDir = normalize(pointLights[3].lightPos- FragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * 1.5f * light_diffuse;
    
	// Specular
	float specularStrength = 0.9f;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * light_specular * 10;
    
	vec3 result = (ambient + diffuse + specular);
	//color = vec4(result, 1.0f);

	//////

	lightDir = normalize(fixed_lightPos - FragPos);
	diff = max(dot(norm, lightDir), 0.0);
	diffuse = diff * 1.5f * light_diffuse;
	viewDir = normalize(viewPos - FragPos);
	reflectDir = reflect(-lightDir, norm);
	spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	specular = specularStrength * spec * light_specular * 10;
	result += (ambient + diffuse + specular);
	//////

	gl_FragColor = texture2D(texture_diffuse, texCoord0)
		/* clamp(dot(-vec3(0,1,0), normal0), 0.0, 1.0) */* vec4(result, 1.0f);	//lighting
}

