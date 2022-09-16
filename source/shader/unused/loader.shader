#version 460 core

layout(location = 0) in vec3 p;
layout(location = 1) in vec3 norm;
layout(location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 pos;
out vec3 normal;
out vec3 opos;

uniform mat4 transform;
uniform mat4 model;

void main() {
	gl_Position = transform * vec4(p , 1.0);
	normal = mat3(transpose(inverse(model))) * norm;
	pos = vec3(model * vec4(p , 1.0));
	opos = p;
	TexCoords = aTexCoords;
};

%

#version 460 core

in vec2 TexCoords;
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

uniform sampler2D shadow;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;
uniform sampler2D texture_height1;
uniform sampler2D texture_height2;
uniform sampler2D texture_normal1;
uniform sampler2D texture_normal2;
uniform ivec4 text_num;

#define RENDER_LIGHT 0
#define RENDER_MESH  1
#define RENDER_LIST  2
#define RENDER_SKY   3

#define SPOTLIGHT     0
#define POINTLIGHT    1
#define PARALLELLIGHT 2

#define SPHERE_COORD  0
#define CUBIC_COORD   1

out vec4 color;

struct Light
{
	int type; float theta; float shiness;
	vec3 pos; vec3 color; vec3 dir; vec3 dv;
};

uniform int light_num;
uniform Light lts[10];

const float pi = acos(-1);

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

vec4 color_dif; vec4 color_spec;

void sampleColor() {
	color_dif = 0.5 * (texture(texture_diffuse1 , TexCoords) + texture(texture_diffuse2 , TexCoords));
	color_dif = vec4(pow(color_dif.rgb , vec3(1 / 2.2)) , color_dif.a);

	color_spec = 0.5 * (texture(texture_specular1 , TexCoords) + texture(texture_specular2 , TexCoords));
	color_spec = vec4(pow(color_spec.rgb , vec3(1 / 2.2)) , color_spec.a);
}

float damp(int i) {
	float len = length(lts[i].pos - pos);
	//return 1.0 / ( len * len);
	return 1.0 / (lts[i].dv.x + lts[i].dv.y * len + lts[i].dv.z * len * len);
}

vec4 calcuLight(int i) {

	vec3 norm = normalize(normal);
	vec4 color = vec4(lts[i].color , 1.0);
	float shine = lts[i].shiness;

	if (lts[i].type == POINTLIGHT) {
		vec3 lightDir = normalize(lts[i].pos - pos);
		vec3 viewv = normalize(viewPos - pos);
		float dc = max(dot(lightDir , norm) , 0.0);//diffuse coefficient
		float sc = 0.8 * pow(max(dot(normalize(lightDir + viewv) , norm) , 0.0) , 128);//specular coefficient
		return (color_dif * color * dc + color_spec * color * sc) * damp(i) * shine;
	}
	if (lts[i].type == SPOTLIGHT) {
		vec3 dirPos = normalize(pos - lts[i].pos);
		vec3 dir = normalize(lts[i].dir);
		float cosv = dot(dirPos , dir);
		if (cosv < cos(lts[i].theta)) {
			return vec4(0.01 , 0.01 , 0.01 , 1.0);
		}
		float coff = (lts[i].theta - acos(cosv)) / lts[i].theta;
		float len = length(lts[i].pos - pos);
		float damp = 1.0 / (lts[i].dv.x + lts[i].dv.y * len + lts[i].dv.z * len * len);
		vec3 lightDir = normalize(lts[i].pos - pos);
		vec3 viewv = normalize(viewPos - pos);
		float dc = max(dot(lightDir , norm) , 0.0);//diffuse coefficient
		float sc = pow(max(dot(normalize(lightDir + viewv) , norm) , 0.0) , 128);//specular coefficient
		return (color_dif * color * dc + color_spec * color * sc) * damp(i) * shine * coff;
	}

	if (lts[i].type == PARALLELLIGHT) {
		vec3 lightDir = normalize(-lts[i].dir);
		vec3 viewv = normalize(viewPos - pos);
		float dc = max(dot(lightDir , norm) , 0.0);//diffuse coefficient
		float sc = pow(max(dot(normalize(lightDir + viewv) , norm) , 0.0) , 128);//specular coefficient
		return (color_dif * color * dc + color_spec * color * sc) * shine;;
	}
}

void main()
{
	if (state == RENDER_LIGHT) {
		color = vec4(lightColor , 1.0); return;
	}
	color = vec4(0.0f); sampleColor();
	//color_dif = objectColor; color_spec = objectColor;
	for (int i = 0; i < light_num; ++i) {
		color += calcuLight(i);
	}
	//color = color_dif + color_spec;
	color.a = 1.0;
}
