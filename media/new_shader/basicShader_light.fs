#version 430 core
out vec4 color;

in vec2 texCoord0;  //texture
in vec3 normal0;    //lighting

in vec3 FragPos; //***********

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;


uniform sampler2D diffuse;

void main()
{
	//gl_FragColor = texture2D(diffuse, texCoord0)
	//	* clamp(dot(-vec3(0,1,0), normal0), 0.0, 1.0);	//lighting

	//gl_FragColor = texture2D(diffuse, texCoord0) //Texture
	//gl_FragColor = texture2D(diffuse, vec2(0.3, 0.8)); //Texture
	//gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);	//Color

	// Ambient
    	float ambientStrength = 0.1f;
    	vec3 ambient = ambientStrength * lightColor;
    
	// Diffuse
	vec3 norm = normalize(normal0);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;
    
	// Specular
	float specularStrength = 0.5f;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;
    
	vec3 result = (ambient + diffuse + specular) * objectColor;
	color = vec4(result, 1.0f);
}

