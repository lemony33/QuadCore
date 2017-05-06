#version 430 core
//out vec4 color;

in vec2 texCoord0;  //texture
in vec3 normal0;    //lighting
in vec3 FragPos; //***********
in vec3 LPOS; // 이 쉐이더의 메인

//dirLight : 원래는 유니티에 DirectLight같은 Default 빛 정보들
uniform vec3 lightPos;
uniform vec3 light_ambient;
uniform vec3 light_diffuse;
uniform vec3 light_specular;

// 추가적인 빛들의 정보 구조체
struct PointLight{
	vec3 lightPos;
	vec3 light_ambient;
	vec3 light_diffuse;
	vec3 light_specular;
	float constant;
    float linear;
    float quadratic;
};

#define LIGHTSNUM 5

uniform vec3 viewPos;
uniform sampler2D texture_diffuse;
uniform PointLight pointLights[LIGHTSNUM];

// Function prototypes
vec3 CalcDirLight(vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
	if(LPOS.x == 0 && LPOS.z == 0) // 이 쉐이더가 태양꺼일때
		gl_FragColor = vec4(vec3(texture(texture_diffuse, texCoord0)) * 2.0 , 1.0);
	else
	{
		vec3 norm = normalize(normal0);
		vec3 viewDir = normalize(viewPos - FragPos);
		vec3 result = CalcDirLight(norm, viewDir);
		for(int i = 0; i < LIGHTSNUM; i++)
			result += CalcPointLight(pointLights[i], norm, FragPos, viewDir); 
		gl_FragColor = vec4(result, 1.0);
	}
}

////////////////////////////////////////////////////////////////////////////////////

// Calculates the color when using a directional light.
vec3 CalcDirLight(vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(pointLights[0].lightPos - FragPos);
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);//material.shininess);
    // Combine results
    vec3 ambient = pointLights[0].light_ambient * vec3(texture(texture_diffuse, texCoord0));
    vec3 diffuse = pointLights[0].light_diffuse * diff * vec3(texture(texture_diffuse, texCoord0));
    vec3 specular = pointLights[0].light_specular * spec  * vec3(texture(texture_diffuse, texCoord0));// * vec3(texture(material.specular, texCoord0));
    return (ambient + diffuse + specular);
}


// Calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.lightPos - fragPos);
    //// Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    //// Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);//material.shininess);
    //// Attenuation
    float distance = length(light.lightPos - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    //// Combine results
    vec3 ambient = light.light_ambient * vec3(texture(texture_diffuse, texCoord0));
    vec3 diffuse = light.light_diffuse * diff * vec3(texture(texture_diffuse, texCoord0));
    //vec3 specular = light.light_specular * spec * vec3(texture(material.specular, texCoord0));
	vec3 specular = spec * light.light_specular * vec3(texture(texture_diffuse, texCoord0));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

