#version 330 core

out vec4 color;

in vec2 texCoord0;  //texture
in vec3 normal0;    //lighting
in vec3 FragPos; //***********
in vec3 LPOS; // 이 쉐이더의 메인

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
void main()
{

    for(int i = 0; i < LIGHTSNUM; i++)
    {
        if(round(pointLights[i].lightPos.x) == round(LPOS.x) &&
        	round(pointLights[i].lightPos.y) == round(LPOS.y) &&
        	round(pointLights[i].lightPos.z) == round(LPOS.z))
        {
            color = vec4((pointLights[i].light_ambient + pointLights[i].light_diffuse + pointLights[i].light_specular) * 0.3 * vec3(texture(texture_diffuse, texCoord0)), 1.0);
            return;
        }
    }
	color = vec4(1.0f, 1.0f, 1.0f, 1.0f); // Set alle 4 vector values to 1.0f

}