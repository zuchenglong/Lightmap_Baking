#version 330 core

struct Material
{
    vec3 diffuse;
    vec3 ambient;
    vec3 specular;
    float specularIntensity;
};

struct DirectionLight
{
    vec3 direction;
    vec3 color;
    float intensity;
};

in vec3 Normal;
in vec3 worldPos;
in vec2 TexCoords;

out vec4 FragColor;

uniform vec3 camPos;

uniform Material material;
uniform DirectionLight directionLight;

vec3 CalcDirectionLight()
{
    vec3 normal = normalize(Normal);

    vec3 lightDir = normalize(directionLight.direction);
    vec3 viewDir = normalize(worldPos - camPos);
    vec3 reflectDir = reflect(lightDir, normal);

    float diffuse = max(dot(normal,lightDir), 0);
    float specular = max(dot(viewDir, reflectDir), 0);

    vec3 diffuseColor = (directionLight.color + material.diffuse) * diffuse;
    vec3 specularColor = (directionLight.color + material.specular) * pow(specular, material.specularIntensity);
    vec3 ambientColor = material.ambient;

    return diffuseColor + specularColor + ambientColor;
}

void main(){
    vec3 outValue = vec3(0, 0, 0);
    outValue +=CalcDirectionLight();

    vec3 normal = normalize(Normal);

    vec3 lightDir = normalize(directionLight.direction);
    vec3 viewDir = normalize(worldPos - camPos);
    vec3 reflectDir = reflect(lightDir, normal);

    float diffuse = max(dot(normal,lightDir), 0);
    float specular = max(dot(viewDir, reflectDir), 0);

    vec3 diffuseColor = (directionLight.color + material.diffuse) * diffuse;
    vec3 specularColor = (directionLight.color + material.specular) * specular;
    vec3 ambientColor = material.ambient;

    FragColor = vec4(vec3(outValue), 1);

}