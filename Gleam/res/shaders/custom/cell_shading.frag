#version 330 core

out vec4 fragColor;

in vec2 texCoord;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gColorSpec;

uniform vec3 cameraFront;
uniform vec3 shadowColor;

struct PointLight {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
	float radius;
};
#define NUM_POINT_LIGHTS 32
uniform PointLight pointLights[NUM_POINT_LIGHTS];

struct DirectionalLight {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
#define NUM_DIRECTIONAL_LIGHTS 32
uniform DirectionalLight directionalLights[NUM_DIRECTIONAL_LIGHTS];

uniform vec3 viewPos;

uniform int numPointLights;
uniform int numDirectionalLights;
uniform int numSpotLights;

vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuse, float specular) {
	
	vec3 Ambient = light.ambient * diffuse;
	
	float distance = length(light.position - fragPos);
	if (distance < light.radius) {
		vec3 lightDir = normalize(light.position - fragPos);

		// diffuse lighting
		float diff = max(dot(normal, lightDir), 0.0);
		
		// specular lighting
		// Blinn-Phong
		vec3 halfwayDir = normalize(lightDir + viewDir);
		float spec = pow(max(dot(normal, halfwayDir), 0.0), 16);

		float attenuation = 1.0 / (1.0 + light.linear * distance + light.quadratic * distance * distance);
		
		vec3 Diffuse = light.diffuse * diff * diffuse;
		vec3 Specular = light.specular * spec * specular;
		
		return Ambient + (Diffuse + Specular) * attenuation;
	}
	
	return Ambient;
}

vec3 calculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir, vec3 diffuse, float specular) {
	
	vec3 lightDir = normalize(-light.direction);
	
	// diffuse lighting
	float diff = max(dot(normal, lightDir), 0.0);
	
	// specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);

	vec3 Ambient = light.ambient * diffuse;
	vec3 Diffuse = light.diffuse * diff * diffuse;
	vec3 Specular = light.specular * spec * specular;

	return (Ambient + Diffuse + Specular);
}

void main() {

	vec3 fragPos = texture(gPosition, texCoord).rgb;
	vec3 normal = texture(gNormal, texCoord).rgb;
	vec3 diffuse = texture(gColorSpec, texCoord).rgb;
	float specular = texture(gColorSpec, texCoord).a;
	
	vec3 lighting = diffuse * 0.1;
	vec3 viewDir = normalize(viewPos - fragPos);
	
	vec3 directional = vec3(0, 0, 0);
	for (int i = 0; i < numDirectionalLights; i++) {
		directional += calculateDirectionalLight(directionalLights[i], normal, viewDir, diffuse, specular);
	}
	
	vec3 point = vec3(0, 0, 0);
	for (int i = 0; i < numPointLights; i++) {
		point += calculatePointLight(pointLights[i], normal, fragPos, viewDir, diffuse, specular);
	}

	float dotResult = dot(-normalize(cameraFront), normalize(normal));
	
	vec3 result = dotResult * (lighting + (directional + point));
	if (dotResult < 0.6) {
		result = shadowColor;
	}
	
	fragColor = vec4(result, 1.0);
} 