#version 330 core

#define NR_POINT_LIGHTS 1
#define NR_SPOT_LIGHTS 1

struct Material
{
	float shininess;
	sampler2D textureDiffuse0;
	sampler2D textureSpecular0;
	vec3 diffuseColor;
	vec3 specularColor;
};

struct DirLight
{
	vec3 dir;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight
{
    vec3 pos;
    
    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight
{
	vec3 pos;
	vec3 dir;
	float innerCutOff;
	float outerCutOff;

	float constant;
    float linear;
    float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 FragPos;
in vec2 TexCoord;
in vec3 Normal;

out vec4 color;

uniform bool hasTexture;
uniform vec2 screenRes;
uniform vec3 viewPos;
uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLights[NR_SPOT_LIGHTS];

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
	vec3 normal = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);

	// Directional lighting
	vec3 result = calcDirLight(dirLight, normal, viewDir);

	// Point lights
	for (int i = 0; i < NR_POINT_LIGHTS; i++)
		result += calcPointLight(pointLights[i], normal, FragPos, viewDir);

	// Spot light
	//for (int k = 0; k < NR_SPOT_LIGHTS; k++)
		//result += calcSpotLight(spotLights[k], normal, FragPos, viewDir);

	color = vec4(result, 1.0f);
}

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.dir);

	// Diffuse shading
	float diff = max(dot(normal, lightDir), 0.0f);

	// Specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	if (hasTexture) {
		ambient  = light.ambient  * vec3(texture(material.textureDiffuse0, TexCoord));
		diffuse  = light.diffuse  * diff * vec3(texture(material.textureDiffuse0, TexCoord));
		specular = light.specular * spec * vec3(texture(material.textureSpecular0, TexCoord));
	} else {
		ambient  = light.ambient  * material.diffuseColor;
		diffuse  = light.diffuse  * diff * material.diffuseColor;
		specular = light.specular * spec * material.specularColor;
	}

	return ambient + diffuse + specular;
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.pos - FragPos);

	// Diffuse shading
	float diff = max(dot(normal, lightDir), 0.0f);

	// Specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);

	// Attenuation
	float distance = length(light.pos - fragPos);
	float attenuation = 1.0f / (light.constant
							  + light.linear * distance
							  + light.quadratic * (distance * distance));

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	if (hasTexture) {
		ambient  = light.ambient  * vec3(texture(material.textureDiffuse0, TexCoord));
		diffuse  = light.diffuse  * diff * vec3(texture(material.textureDiffuse0, TexCoord));
		specular = light.specular * spec * vec3(texture(material.textureSpecular0, TexCoord));
	} else {
		ambient  = light.ambient  * material.diffuseColor;
		diffuse  = light.diffuse  * diff * material.diffuseColor;
		specular = light.specular * spec * material.specularColor;
	}

	ambient  *= attenuation;
	diffuse  *= attenuation;
	specular *= attenuation;

	return ambient + diffuse + specular;
}

vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.pos - fragPos);

	// Diffuse shading
	float diff = max(dot(normal, lightDir), 0.0f);

	// Specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);

	// Attenuation
	float distance = length(light.pos - fragPos);
	float attenuation = 1.0f / (light.constant
							  + light.linear * distance
							  + light.quadratic * (distance * distance));

	// Spotlight intensity
	float theta = dot(lightDir, normalize(-light.dir));
	float epsilon = light.innerCutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	if (hasTexture) {
		ambient  = light.ambient  * vec3(texture(material.textureDiffuse0, TexCoord));
		diffuse  = light.diffuse  * diff * vec3(texture(material.textureDiffuse0, TexCoord));
		specular = light.specular * spec * vec3(texture(material.textureSpecular0, TexCoord));
	} else {
		ambient  = light.ambient  * material.diffuseColor;
		diffuse  = light.diffuse  * diff * material.diffuseColor;
		specular = light.specular * spec * material.specularColor;
	}

	ambient  *= attenuation * intensity;
	diffuse  *= attenuation * intensity;
	specular *= attenuation * intensity;

	return ambient + diffuse + specular;
}
