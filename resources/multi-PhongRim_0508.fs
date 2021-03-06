#version 430 core
//out vec4 color;

in vec2 texCoord0;  //texture
in vec3 normal0;    //lighting
in vec3 FragPos; //***********

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
vec4 CalcPointLight2(PointLight light, vec3 normal, vec3 fragPos);

vec3 CalcDirLight(vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    	//gl_FragColor = ambient + diffuse + specular + rim;

	//vec3 norm = normalize(normal0);
	//vec3 viewDir = normalize(viewPos - FragPos);
	//vec4 result = vec4(CalcDirLight(norm, viewDir), 1.0);
	vec4 result;
	for(int i = 0; i < LIGHTSNUM; i++)
		result += CalcPointLight2(pointLights[i], normal0, FragPos);
	gl_FragColor = result;

	/////////

	//vec3 norm = normalize(normal0);
	//vec3 viewDir = normalize(viewPos - FragPos);
	//vec3 result = CalcDirLight(norm, viewDir);
	//for(int i = 0; i < LIGHTSNUM; i++)
	//	result += CalcPointLight(pointLights[i], norm, FragPos, viewDir); 
	//gl_FragColor = vec4(result, 1.0);
}

////////////////////////////////////////////////////////////////////////////////////

// Calculates the color when using a point light.
vec4 CalcPointLight2(PointLight light, vec3 normal, vec3 fragPos)
{
	const float specular_power = 32.0;
	//const vec4 rim_albedo = vec4(0.5, 0.5, 0.5, 1.0);
    	//const float rim_power = 1.25;

	const vec4 rim_albedo = vec4(0.01, 0.01, 0.01, 1.0);
    	const float rim_power = 1.25;


	////////////////////

	// Interpolated vertex coordinate
    	// in view-space
    	vec3 P = vec3(fragPos);

    	// Interpolated vertex normal
    	// in view-space
    	vec3 N = normalize(normal0);

	// Transform the light vector
    	// into a direction in view space
    	vec3 L = normalize(light.lightPos - fragPos);

    	// The viewing vector points to
    	// the origin from the vertex
    	vec3 V = normalize(-P);

	// Reflect the light about the plane
    	// defined by the normal (N)
    	vec3 R = reflect(-L, N);

	

	//// Attenuation
    	float distance = length(light.lightPos - fragPos);
    	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	///////////////////

	///////////////////


	vec4 ambient = vec4(light.light_ambient * vec3(texture(texture_diffuse, texCoord0)), 1.0);

    	// Compute the diffuse contribution
    	vec4 diffuse = max(0.0, dot(N, L)) * vec4(light.light_diffuse,1.0) * texture2D(texture_diffuse, texCoord0);

	// Traditional Phong specular contribution
    	// ( no Blinn-Phong optimisation )
	vec4 specular = pow( max(0.0, dot(R, V)), specular_power ) * vec4(light.light_specular,1.0);
	
	// Artificial rim colour contributes
    	// when normal is at a grazing angle to the view
    	vec4 rim = pow( smoothstep(0.0, 1.0, 1.0 - dot(N, V)), rim_power/5.0) * rim_albedo;

	
    	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	//rim *= attenuation;

	return (ambient + diffuse + specular + rim );
}

// Calculates the color when using a directional light.
vec3 CalcDirLight(vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(lightPos - FragPos);
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);//material.shininess);
    // Combine results
    vec3 ambient = light_ambient * vec3(texture(texture_diffuse, texCoord0));
    vec3 diffuse = light_diffuse * diff * vec3(texture(texture_diffuse, texCoord0));
    vec3 specular = light_specular * spec  * vec3(texture(texture_diffuse, texCoord0));// * vec3(texture(material.specular, texCoord0));
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

