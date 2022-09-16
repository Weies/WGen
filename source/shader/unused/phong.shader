#version 460 core
layout(location = 0) in vec3 p;
layout(location = 1) in vec3 norm;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec3 Tan;
layout(location = 4) in vec3 Bitan;

out vec3 pos;
out vec3 normal;
out vec3 opos;
uniform mat4 transform;
uniform mat4 model;
void main() {
	gl_Position = transform * vec4(p , 1.0);
	normal = mat3(transpose(inverse(model))) * norm;
	//normal = norm;
	pos = vec3(model * vec4(p , 1.0));
	opos = p;
};

%

#version 460 core
in vec3 pos;
in vec3 normal;
in vec3 opos;

uniform vec4 objectColor;
uniform bool texture_enable;
uniform vec3 lightColor;
uniform vec3 viewPos;
uniform sampler2D text;
uniform sampler2D text2;
uniform int state;
uniform int coord_type;

#define RENDER_LIGHT 0
#define RENDER_MESH  1
#define RENDER_LIST  2
#define RENDER_SKY   3

#define SPOTLIGHT     0
#define POINTLIGHT    1
#define PARALLELLIGHT 2

#define SPHERE_COORD 0
#define CUBIC_COORD   1


struct Light
{
	int type; float theta; float shiness;
	vec3 pos; vec3 color; vec3 dir; vec3 dv;
};
uniform int light_num;
uniform Light lts[10];

const float pi = acos(-1);

vec2 sphere_coord() {
	float phi = acos(-opos.y);
	float theta = acos(opos.z / sqrt(1 - opos.y * opos.y));
	if (opos.x < 0)theta = 2 * pi - theta;
	return vec2(theta / (2 * pi) , (3 * phi - pi) / 2 / pi);
}

vec2 coord() {
	if (coord_type == SPHERE_COORD)
	{
		float phi = acos(-opos.y);
		float theta = acos(opos.z / sqrt(1 - opos.y * opos.y));
		if (opos.x < 0)theta = 2 * pi - theta;
		return vec2(theta / (2 * pi) , (3 * phi - pi) / 2 / pi);
	}
	return vec2(opos.x , opos.z);
}


vec3 calcuLight(int i) {
	vec3 norm = normalize(normal);
	vec3 color = lts[i].color;
	float shine = lts[i].shiness;

	vec4 objColor;
	if (texture_enable)
		objColor = texture(text , coord());
	else objColor = objectColor;

	if (lts[i].type == POINTLIGHT) {
		vec3 lightDir = normalize(lts[i].pos - pos);
		vec3 viewv = normalize(viewPos - pos);
		float dc = max(dot(lightDir , norm) , 0.0);//diffuse coefficient
		float sc = 0.8 * pow(max(dot(normalize(lightDir + viewv) , norm) , 0.0) , 128);//specular coefficient
		return (vec3(objColor) * color * dc + color * sc) * damp(i) * shine;
	}
	if (lts[i].type == SPOTLIGHT) {
		vec3 dirPos = normalize(pos - lts[i].pos);
		vec3 dir = normalize(lts[i].dir);
		float co = acos(dot(dirPos , dir));
		//if (co > lts[i].theta) return vec3(0.01 , 0.01 , 0.01);

		float coff = max((lts[i].theta - co) / lts[i].theta , 0.0);
		vec3 lightDir = normalize(lts[i].pos - pos);
		vec3 viewv = normalize(viewPos - pos);
		float dc = max(dot(lightDir , norm) , 0.0);//diffuse coefficient
		float sc = 0.2 * pow(max(dot(normalize(lightDir + viewv) , norm) , 0.0) , 1024);//specular coefficient
		return (vec3(objColor) * color * dc + color * sc) * damp(i) * shine * coff;
		//return (vec3(objColor) * color * dc) * damp(i) * shine * coff;
	}

	if (lts[i].type == PARALLELLIGHT) {
		vec3 lightDir = normalize(-lts[i].dir);
		vec3 viewv = normalize(viewPos - pos);
		float dc = max(dot(lightDir , norm) , 0.0);//diffuse coefficient
		float sc = pow(max(dot(normalize(lightDir + viewv) , norm) , 0.0) , 128);//specular coefficient
		return vec3(objColor) * color * dc * shine + color * sc * shine;
	}
}

out vec4 color;

float near = 20;
float far = 8000.0;

float LinearizeDepth(float depth)
{
	float z = depth * 2.0 - 1.0; // back to NDC 
	return (2.0 * near * far) / (far + near - z * (far - near));
}
float zbefore(float ndc) {
	return -near * far / ((far - near) * ndc - far);
}
float s(float x) {
	return 1 / (1 + exp(10 - 15 * x));
}

void main() {

	if (state == RENDER_LIGHT) {
		color = vec4(lightColor , 1.0); return;
	}
	else
	{
		vec3 co = vec3(0.0);
		for (int i = 0; i < light_num; ++i) {
			co += calcuLight(i);
		}
		//float depth = LinearizeDepth(gl_FragCoord.z); // 为了演示除以 far
		color = vec4(co , objectColor.a);
		//color = objectColor;
		//color = vec4(vec3(zbefore(gl_FragCoord.z)) , 1.0);
		//color = vec4(abs(normalize(normal)) , 1.0);
	}

};