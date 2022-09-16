#version 460 core
layout(location = 0)in vec3 p;
layout(location = 1)in vec3 norm;
layout(location = 2)in vec2 tex;

uniform mat4 transform;
uniform mat4 model;

out vec3 pos;
out vec3 normal;
out vec2 texCoord;


void main() {

	gl_Position = transform * vec4(p, 1.0);
	pos = vec3(model * vec4(p, 1.0));
	normal = mat3(transpose(inverse(model))) * norm;
	texCoord = tex;

}


%


#version 460 core
in vec3 pos;
in vec3 normal;
in vec2 texCoord;

uniform vec3 camPos;
uniform vec3 albedo;
uniform float metallic;
uniform float roughness;
uniform float ao;
uniform vec3 lightPos[4];
uniform vec3 lightColor[4];

out vec4 color;

const float PI = 3.1415926;


vec3 FresnelSchlick(float cosTheta, vec3 F0) {
	return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

float DistributionGGX(vec3 N, vec3 H, float roughness) {
	float a = roughness * roughness;
	a = a * a;
	float NdotH = max(dot(N, H), 0.0);
	float NdotH2 = NdotH * NdotH;
	float denom = (NdotH2 * (a - 1.0) + 1.0);
	denom = PI * denom * denom;
	return a / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness) {
	float r = roughness + 1.0;
	float k = (r * r) / 8.0;
	return NdotV / (NdotV * (1 - k) + k);
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness) {
	float NdotV = max(dot(N, V), 0.0);
	float NdotL = max(dot(N, L), 0.0);
	float ggx2 = GeometrySchlickGGX(NdotV, roughness);
	float ggx1 = GeometrySchlickGGX(NdotL, roughness);

	return ggx1 * ggx2;
}


void main() {
	vec3 N = normalize(normal);
	vec3 V = normalize(camPos - pos);
	vec3 Lo = vec3(0.0);

	for (int i = 0; i < 4; ++i) {
		vec3 L = normalize(lightPos[i] - pos);
		vec3 H = normalize(V + L);
		float distance = length(lightPos[i] - pos);
		float attenuation = 1.0 / (distance * distance);
		vec3 radiance = lightColor[i] * attenuation;
		vec3 F0 = vec3(0.04);
		F0 = mix(F0, albedo, metallic);

		vec3 F = FresnelSchlick(dot(L, N), F0);
		float D = DistributionGGX(N, H, roughness);
		float G = GeometrySmith(N, V, L, roughness);

		float denom = 4 * dot(N, V) * dot(N, L) + 0.00001;
		vec3 specular = D * F * G / denom;

		vec3 KS = F; vec3 KD = vec3(1.0) - KS;
		KD *= 1.0 - metallic;
		float NdotL = max(dot(N, L), 0.0);
		Lo += (KD * albedo / PI + specular) * radiance * NdotL;

	}

	color = vec4(Lo, 1.0);
	/*vec3 ambient = vec3(0.03) * albedo * ao;
	vec3 co = ambient + Lo;
	co = co / (vec3(1.0) + co);
	co = pow(co, vec3(0.45));
	color = vec4(co, 1.0);*/
}