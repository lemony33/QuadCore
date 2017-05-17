#version 430 core


in GS_OUT
{
	vec2 texCoord0;  //texture
	vec3 normal0;    //lighting
	vec3 FragPos;
} fs_in;


//dirLight
uniform vec3 lightPos;
uniform vec3 light_ambient;
uniform vec3 light_diffuse;
uniform vec3 light_specular;

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

uniform vec3 viewPos;
uniform sampler2D texture_diffuse;
uniform PointLight pointLights[LIGHTSNUM];

// Function prototypes
vec3 CalcDirLight(vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
	vec3 norm = normalize(fs_in.normal0);
	vec3 viewDir = normalize(viewPos - fs_in.FragPos);
	vec3 result = CalcDirLight(norm, viewDir);
	for(int i = 0; i < LIGHTSNUM; i++)
		result += CalcPointLight(pointLights[i], norm, fs_in.FragPos, viewDir); 
	gl_FragColor = vec4(result, 1.0);
	
}

////////////////////////////////////////////////////////////////////////////////////

// Calculates the color when using a directional light.
vec3 CalcDirLight(vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);//material.shininess);
    // Combine results
    vec3 ambient = light_ambient * vec3(texture(texture_diffuse, fs_in.texCoord0));
    vec3 diffuse = light_diffuse * diff * vec3(texture(texture_diffuse, fs_in.texCoord0));
    vec3 specular = light_specular * spec  * vec3(texture(texture_diffuse, fs_in.texCoord0));// * vec3(texture(material.specular, fs_in.texCoord0));
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
    vec3 ambient = light.light_ambient * vec3(texture(texture_diffuse, fs_in.texCoord0));
    vec3 diffuse = light.light_diffuse * diff * vec3(texture(texture_diffuse, fs_in.texCoord0));
    //vec3 specular = light.light_specular * spec * vec3(texture(material.specular, fs_in.texCoord0));
	vec3 specular = spec * light.light_specular * vec3(texture(texture_diffuse, fs_in.texCoord0));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

