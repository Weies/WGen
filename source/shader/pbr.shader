#version 460 core
layout(location = 0)in vec3 p;
layout(location = 1)in vec3 norm;
layout(location = 2)in vec2 texcoord;

uniform mat4 transform;
uniform mat4 model;

out vec3 pos;
out vec3 normal;
out vec2 texCoord;


void main() {

	gl_Position = transform * vec4(p, 1.0);
	pos = vec3(model * vec4(p, 1.0));
	normal = mat3(transpose(inverse(model))) * norm;
	texCoord = texcoord;

}


%


#version 460 core
in vec3 pos;
in vec3 normal;
in vec2 texCoord;

uniform vec3 camPos;
uniform vec3 lightPos[4];
uniform vec3 lightColor[4];

uniform float ao;
uniform sampler2D albedo_t;
uniform sampler2D metallic_t;
uniform sampler2D roughness_t;
uniform sampler2D normal_t;
uniform sampler2D tex;

out vec4 color;

const float PI = 3.1415926;

vec3 getNormalFromMap()
{
	vec3 tangentNormal = texture(normal_t, texCoord).xyz * 2.0 - 1.0;

	vec3 Q1 = dFdx(pos);
	vec3 Q2 = dFdy(pos);
	vec2 st1 = dFdx(texCoord);
	vec2 st2 = dFdy(texCoord);

	vec3 N = normalize(normal);
	vec3 T = normalize(Q1 * st2.t - Q2 * st1.t);
	vec3 B = -normalize(cross(N, T));
	mat3 TBN = mat3(T, B, N);

	return normalize(TBN * tangentNormal);
}

vec3 FresnelSchlick(float cosTheta, vec3 F0) {
	return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
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

	return sqrt(ggx1 * ggx2);
}
vec3 filmic(vec3 x) {
	const float A = 0.22;
	const float B = 0.30;
	const float C = 0.10;
	const float D = 0.20;
	const float E = 0.01;
	const float F = 0.30;
	return (x * (A * x + C * B) + D * E) / (x * (A * x + B) + D * F) - E / F;//
}

void main() {
	//vec3 N = normalize(normal);
	vec3 N = getNormalFromMap();
	vec3 V = normalize(camPos - pos);
	vec3 Lo = vec3(0.0);
	vec3 albedo = vec3(texture(albedo_t, texCoord));
	albedo = pow(albedo, vec3(2.2));
	float metallic = texture(metallic_t, texCoord).r;
	float roughness = texture(roughness_t, texCoord).r;
	vec3 F0 = vec3(0.08);
	F0 = mix(F0, albedo, metallic);

	for (int i = 0; i < 4; ++i) {
		vec3 L = normalize(lightPos[i] - pos);
		vec3 H = normalize(V + L);
		float distance = length(lightPos[i] - pos);
		float attenuation = 1.0 / (distance * distance);
		vec3 radiance = lightColor[i] * attenuation;

		vec3 F = FresnelSchlick(max(dot(L, N), 0), F0);
		float D = DistributionGGX(N, H, roughness);
		float G = GeometrySmith(N, V, L, roughness);

		float denom = 4 * dot(N, V) * dot(N, L) + 0.00001;
		vec3 specular = D * F * G / denom;
		vec3 KS = F; vec3 KD = vec3(1.0) - KS;
		//KD *= 1.0 - metallic;
		float NdotL = max(dot(N, L), 0.0);
		Lo += (KD * albedo / PI + specular) * radiance * NdotL;// 
	}

	vec3 ambient = vec3(0.8) * albedo * ao;
	vec3 co = ambient + Lo;
	co = filmic(co);
	co = pow(co, vec3(0.45));
	color = vec4(Lo, 1.0);
	//color = vec4(albedo, 1.0);
}