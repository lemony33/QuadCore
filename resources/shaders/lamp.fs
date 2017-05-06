#version 330 core

out vec4 color;

in vec3 LPOS;

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
uniform PointLight pointLights[LIGHTSNUM];
void main()
{

    for(int i = 0; i < LIGHTSNUM; i++)
    {
        if(round(pointLights[i].lightPos.x) == round(LPOS.x) &&
        	round(pointLights[i].lightPos.y) == round(LPOS.y) &&
        	round(pointLights[i].lightPos.z) == round(LPOS.z))
        {
            color = vec4(pointLights[i].light_diffuse, 1.0);
            return;
        }
    }
	color = vec4(1.0f, 1.0f, 1.0f, 1.0f); // Set alle 4 vector values to 1.0f

}