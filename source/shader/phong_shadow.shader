#version 460 core

layout(location = 0) in vec3 p;
layout(location = 1) in vec3 norm;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec3 Tan;
layout(location = 4) in vec3 Bitan;
layout(location = 5) in ivec4 id;
layout(location = 6) in vec4 weights;

out vec3 pos;
out vec3 normal;
out vec3 opos;
out vec2 TexCoords;
out mat3 TBN;

uniform mat4 curs[65];
uniform mat4 transform;
uniform mat4 model;
uniform bool anim_enable;

void main() {

	if (!anim_enable)
		gl_Position = transform * vec4(p, 1.0);
	else
	{
		mat4 cur = curs[id[0]] * weights[0] + curs[id[1]] * weights[1] + curs[id[2]] * weights[2] + curs[id[3]] * weights[3];
		normal = vec3(cur * vec4(norm, 0.0));
		gl_Position = transform * cur * vec4(p, 1.0);
	}
	//normal = norm;
	pos = vec3(model * vec4(p, 1.0));
	opos = p;
	TexCoords = texCoord;
	mat3 normMat = mat3(transpose(inverse(model)));
	normal = normMat * norm;
	vec3 T = normalize(normMat * Tan);
	vec3 N = normalize(normal);
	vec3 B = cross(N, T);
	TBN = mat3(T, B, N);
};

%

#version 460 core
in vec3 pos;
in vec3 normal;
in vec3 opos;
in vec2 TexCoords;
in mat3 TBN;

uniform vec4 objectColor;
uniform bool texture_enable;
uniform bool shadow_enable;
uniform vec3 lightColor;
uniform vec3 viewPos;

uniform int state;
uniform int coord_type;
uniform mat4 ltTrans;

#define RENDER_LIGHT	0
#define RENDER_MESH		1
#define RENDER_LIST		2
#define RENDER_SKY		3
#define RENDER_NORMAL	4
#define RENDER_DEPTH	5

#define texture_none				 0 
#define texture_diffuse				 1 
#define texture_specular			 2 
#define texture_ambient				 3 
#define texture_emmisive			 4 
#define texture_height				 5 
#define texture_normal				 6 
#define texture_shiness				 7 
#define texture_opacity				 8 
#define texture_displaces			 9 
#define texture_lightmap			 10
#define texture_reflect				 11
#define texture_base_color			 12
#define texture_normal_camera		 13
#define texture_emission_color		 14
#define texture_metalness			 15
#define texture_diffuse_roughness	 16
#define texture_abient_occlusion	 17
#define texture_unknown				 18
#define texture_cubemap				 10
#define texture_buffer				 19

#define SPOTLIGHT     0
#define POINTLIGHT    1
#define PARALLELLIGHT 2

#define TEXTURE_COORD 0
#define SPHERE_COORD  1
#define CUBIC_COORD   2

uniform sampler2D shadow;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;
uniform sampler2D texture_height1;
uniform sampler2D texture_height2;
uniform sampler2D texture_normal1;
uniform sampler2D texture_normal2;
uniform samplerCube texture_cubemap1;
uniform samplerCube texture_cubemap2;
uniform int text_num[20];

struct Light
{
	int type; float theta; float shiness;
	vec3 pos; vec3 color; vec3 dir; vec3 dv;
};
uniform int light_num;
uniform Light lts[10];

const float pi = acos(-1);

vec2 coord() {
	if (coord_type == TEXTURE_COORD)return TexCoords;
	else if (coord_type == CUBIC_COORD)return vec2(opos.x, opos.z);
	else if (coord_type == SPHERE_COORD) {
		float phi = acos(-opos.y);
		float theta = acos(opos.z / sqrt(1 - opos.y * opos.y));
		if (opos.x < 0)theta = 2 * pi - theta;
		return vec2(theta / (2 * pi), (2 * phi - pi) / 2 / pi + 0.5);
	}
}

vec3 tex_height;
vec4 color_dif;
vec4 color_spec;

void sampleColor() {

	if (texture_enable)
	{
		if (text_num[texture_diffuse] == 0)color_dif = vec4(0.1, 0.1, 0.1, 1.0);
		else if (text_num[texture_diffuse] > 0) {
			color_dif = texture(texture_diffuse1, coord());
			if (text_num[texture_diffuse] > 1)
			{
				color_dif += texture(texture_diffuse2, coord());
			}
		}
		float spec = 0.1; if (text_num[texture_diffuse] == 0)spec = 0.1;
		if (text_num[texture_specular] == 0)color_spec = vec4(vec3(spec), 1.0);
		else if (text_num[texture_specular] > 0) {
			color_spec = texture(texture_specular1, coord());
			if (text_num[texture_specular] > 1)
			{
				color_spec += texture(texture_specular2, coord());
			}
		}
	}
	else
	{
		color_dif = objectColor;
		color_spec = objectColor;
	}

	if (text_num[texture_height] > 0) {
		vec3 normm = vec3(texture(texture_height1, coord()));
		normm = TBN * (normalize(normm) * 2.0 - 1.0);
		tex_height = normm;
	}
	else tex_height = normal;
	//color_dif = vec4(pow(color_dif, vec4(2.2)));
	//color_spec = vec4(pow(color_spec, vec4(2.2)));
}


float damp(int i) {
	float len = length(lts[i].pos - pos);
	return 1.0 / (lts[i].dv.x + lts[i].dv.y * len + lts[i].dv.z * len * len);
}

float shadow_cof() {
	if (!shadow_enable)return 1.0;
	vec4 lpos = ltTrans * vec4(pos, 1.0);
	lpos = vec4(lpos.xyz / lpos.w, 1.0);
	lpos = vec4(lpos.xyz * 0.5 + vec3(0.5), 1.0);

	float ldep = texture(shadow, lpos.xy).r;
	float tdep = lpos.z;
	float cof = 1.0;
	if (tdep > ldep + 0.0005)
		cof = 0.5;
	return cof;
}



vec4 calcuLight(int i) {

	vec3 norm = normalize(tex_height.rgb);
	vec4 color = vec4(lts[i].color, 1.0);
	float shine = lts[i].shiness;
	float sha_cof = shadow_cof();

	if (lts[i].type == POINTLIGHT) {
		vec3 lightDir = normalize(lts[i].pos - pos);
		vec3 viewv = normalize(viewPos - pos);
		float dc = max(dot(lightDir, norm), 0.0);//diffuse coefficient
		float sc = pow(max(dot(normalize(lightDir + viewv), norm), 0.0), 128);//specular coefficient
		return (color_dif * color * (dc)+color_spec * sc) * damp(i) * shine * sha_cof;
	}
	else if (lts[i].type == SPOTLIGHT) {
		vec3 dirPos = normalize(pos - lts[i].pos);
		vec3 dir = normalize(lts[i].dir);
		float co = acos(dot(dirPos, dir));

		float coff = max((lts[i].theta - co) / lts[i].theta, 0.0);
		vec3 lightDir = normalize(lts[i].pos - pos);
		vec3 viewv = normalize(viewPos - pos);
		float dc = max(dot(lightDir, norm), 0.0);//diffuse coefficient
		float sc = 0.2 * pow(max(dot(normalize(lightDir + viewv), norm), 0.0), 1024);//specular coefficient
		return (color_dif * color * (dc + 0.35) + color_spec * sc) * damp(i) * shine * coff * sha_cof;
	}
	else if (lts[i].type == PARALLELLIGHT) {
		vec3 lightDir = normalize(-lts[i].dir);
		vec3 viewv = normalize(viewPos - pos);
		float dc = max(dot(lightDir, norm), 0.0);//diffuse coefficient
		float sc = pow(max(dot(normalize(lightDir + viewv), norm), 0.0), 128);//specular coefficient
		return (color_dif * color * (dc + 0.35) + color_spec * sc) * shine * sha_cof;
	}
}

out vec4 color;

float near = 2;
float far = 2000.0;

float zbefore(float ndc) {
	return -near * far / ((far - near) * ndc - far);
}


void main() {

	sampleColor();
	if (state == RENDER_MESH) {
		vec4 co = vec4(0.0);
		for (int i = 0; i < light_num; ++i) {
			co += calcuLight(i);
		}
		//color = vec4(co.rgb, 1.0);
		color = vec4(sqrt(co.rgb) * 0.9, color_dif.a) * 0.5 + color_dif * 0.5;
		//color = pow(color, vec4(0.45));
	}
	if (state == RENDER_LIGHT)
		color = vec4(lightColor, 1.0);
	else if (state == RENDER_SKY)
		color = pow(texture(texture_cubemap1, pos), vec4(1 / 2.0));
	else if (state == RENDER_NORMAL)
		color = vec4(normalize(tex_height.rgb), 1.0);
	else if (state == RENDER_DEPTH) {
		float zb = zbefore(gl_FragCoord.z) / 300;
		color = vec4(vec3(zb / (0.19 + zb)), 1.0);
	}

};