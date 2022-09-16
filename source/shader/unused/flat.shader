#version 460 core
layout(location = 0) in vec3 p;
layout(location = 1) in vec3 norm;
out vec3 poss;
uniform mat4 transform;

void main() {
	gl_Position = transform * vec4(p , 1.0);
	poss = p;
};

%

#version 460 core
in vec3 poss;

uniform vec3 normal;
uniform mat4 model;
uniform vec4 objectColor;
uniform bool texture_enable;
uniform vec3 lightColor;
uniform vec3 viewPos;
uniform sampler2D text;
uniform int state;

#define RENDER_LIGHT 0
#define RENDER_MESH  1
#define RENDER_LIST  2

#define SPOTLIGHT     0
#define POINTLIGHT    1
#define PARALLELLIGHT 2

struct Light
{
	int type;
	vec3 pos;
	vec3 color;
	vec3 dir;
	vec3 dv;
	float theta;
	float shiness;
};
uniform int light_num;
uniform Light lts[10];


vec3 calcuLight(int i) {
	vec3 norm = normalize(vec3(transpose(inverse(model)) * vec4(normal , 1.0)));
	vec3 color = lts[i].color;
	float shine = lts[i].shiness;
	vec3 pos = vec3(model * vec4(poss , 1.0));

	if (lts[i].type == POINTLIGHT) {
		vec3 lightDir = normalize(lts[i].pos - pos);
		vec3 viewv = normalize(viewPos - pos);
		float dc = max(dot(lightDir , norm) , 0.0);//diffuse coefficient
		float sc = 0.8 * pow(max(dot(normalize(lightDir + viewv) , norm) , 0.0) , 128);//specular coefficient
		float len = length(lts[i].pos - pos);
		float damp = 1.0 / (lts[i].dv.x + lts[i].dv.y * len + lts[i].dv.z * len * len);
		return vec3(objectColor) * color * dc * damp * shine + color * sc * damp * shine;
	}
	if (lts[i].type == SPOTLIGHT) {
		vec3 dirPos = normalize(pos - lts[i].pos);
		vec3 dir = normalize(lts[i].dir);
		float cosv = dot(dirPos , dir);
		if (cosv < cos(lts[i].theta)) {
			return vec3(0.01 , 0.01 , 0.01);
		}
		float coff = (lts[i].theta - acos(cosv)) / lts[i].theta;
		float len = length(lts[i].pos - pos);
		float damp = 1.0 / (lts[i].dv.x + lts[i].dv.y * len + lts[i].dv.z * len * len);
		vec3 lightDir = normalize(lts[i].pos - pos);
		vec3 viewv = normalize(viewPos - pos);
		float dc = max(dot(lightDir , norm) , 0.0);//diffuse coefficient
		float sc = pow(max(dot(normalize(lightDir + viewv) , norm) , 0.0) , 128);//specular coefficient
		return (vec3(objectColor) * color * dc + color * sc) * damp * shine * coff;
	}

	if (lts[i].type == PARALLELLIGHT) {
		vec3 lightDir = normalize(-lts[i].dir);
		vec3 viewv = normalize(viewPos - pos);
		float dc = max(dot(lightDir , norm) , 0.0);//diffuse coefficient
		float sc = pow(max(dot(normalize(lightDir + viewv) , norm) , 0.0) , 128);//specular coefficient
		return vec3(objectColor) * color * dc * shine + color * sc * shine;
	}
}

out vec4 color;

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
		//color = vec4(abs(calcuLight(4)) , 1.0);
		color = vec4(co + vec3(0.2) , objectColor.a);
	}
};