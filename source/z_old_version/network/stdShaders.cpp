#include"stdShaders.h"

//����2D��ͼ�ķǹ�����ɫ��
const char* shader_2d = {
	"#version 460 core\n"
	"layout(location = 0) in vec2  pos;\n"
	"uniform mat3 transform;//�任����\n"
	"uniform mat4 proj;//����ͶӰ����\n"
	"uniform float prior;"
	"void main()\n"
	"{\n"
	"	float prio = prior;"
	"	if(prior>1024)prio = 1024+log(prior);"
	"	prio = prio/(100+prio)*prio/1024;"
	"	gl_Position =proj* vec4((transform*vec3(pos,1.0)).xy,prio,1.0);\n"
	"}\n"
	"%\n"
	"#version 460 core\n"
	"out vec4 co;\n"
	"uniform vec4 color;\n"
	"void main() {\n"
	"\tco = color;\n"
	"}\n"
};

//����3D��ͼ�ķǹ�����ɫ��
const char* shader_3d = {
	"#version 460 core\n"
	"layout(location = 0) in vec3 pos;"
	"uniform mat4 transform;"
	"uniform mat4 model;"
	"uniform vec3 normal;"
	"out vec3 norm;"
	"out vec3 pp;"
	"void main(){"
	"	gl_Position = transform*vec4(pos,1.0);"
	"	if(normal.x>-100) {"
	"		norm = normalize(transpose(inverse(mat3(model)))*normal);"
	"		pp = vec3(model*vec4(pos,1.0));"
	"	}"
	"	else norm= normal;"
	"}"
	"  %  "
	"#version 460 core\n"
	"uniform vec4 color;"
	"uniform vec3 viewPos;"
	"in vec3 pp;"
	"in vec3 norm;"
	"out vec4 co;"
	"void main(){"
	"	float diff=1.0;float spec=0.0;"
	"	if(norm.x>-50){"
	"		vec3 viewDir=normalize(viewPos-pp);"
	"		diff=max(dot(norm,viewDir),0.0);"
	"		spec=diff*diff;spec *= spec*spec;spec*=spec*spec;spec*= spec*spec;"
	"	}"
	"	co = vec4(color.rgb*((diff+spec)/2.0+0.5),color.a);"
	"}"
};

//ƽ����ɫ�Ĺ�����ɫ��
const char* shader_flat = {
"#version 460 core\n								  "
"layout(location = 0) in vec3  pos;			          "
"layout(location = 1) in vec3  norm_V;			      "
"uniform mat4 transform;	"
"out vec3 poss;"
"void main()										  "
"{													  "
"	gl_Position = transform*vec4(pos, 1.0);"
"	poss = pos;"
"}							"
"   %						"
"#version 460 core\n	    "
"in vec3  poss;		"
"out vec4 color;"
"uniform vec3 normal;       "
"uniform mat4 model;		"
"uniform vec3 lightPos;"	//��Դλ��
"uniform vec3 lightColor;"	//��Դ��ɫ
"uniform vec4 objectColor;"	//������ɫ
"uniform vec3 viewPos;"		//���λ��
"uniform bool light_rendering;"
"uniform bool texture_enable;"
"uniform vec3 dampVec;"
"void main() {"
"	if(light_rendering)color = vec4(lightColor,1.0);"
"	else{"
"		vec3 Pos=vec3(model*vec4(poss,1.0));"
"		vec3 norm = normalize(transpose(inverse(mat3(model)))*normal);"
"		norm = vec3(norm.x,abs(norm.y),norm.z);"
"		vec3 lightDir= normalize(lightPos-Pos);"//���߷���Ϊ��Դλ��-���壨�㣩��λ��
"		vec3 viewDir=normalize(viewPos-Pos);"//�۲췽��=�۲�λ��-����λ��
"		float diff=(max(dot(norm,lightDir),0.0)*5.0+1.0)/4.0;"//������ǿ��Ϊ���ߵ�˹��߷���
"		float spec=pow(max(dot(norm,normalize(viewDir+lightDir)),0.0),256)*0.6;"//���淴��ǿ��Ϊ�����������64�η�
"		color = vec4(diff*vec3(objectColor)*lightColor+spec*lightColor,objectColor.a);"
"	}"
"}"

};
//"uniform sampler2D text;"
//"	vec3 texture_pos = normalize(pos)*3.5+vec3(3.8,4.2,1.0);"
//"	vec3 outColor = texture(text,texture_pos.xy).xyz;"

const char* shader_Phong = {
	"#version 460 core\n"
	"layout (location = 0) in vec3 p;"
	"layout (location = 1) in vec3 norm;"
	"out vec3 pos;"
	"out vec3 normal;"
	"out vec3 opos;"
	"uniform mat4 transform;"
	"uniform mat4 model;"
	"void main(){"
	"	gl_Position = transform * vec4(p,1.0);"
	"	normal = normalize(transpose(inverse(mat3(model))) * norm);"
	"	pos = vec3(model * vec4(p,1.0));"
	"	opos = p;"
	"};"
	"     "
	"%"
	"   "
	"#version 460 core\n"
	"in vec3 pos;"
	"in vec3 normal;"
	"in vec3 opos;"
	"uniform vec4 objectColor;"
	"uniform bool light_rendering;"
	"uniform bool texture_enable;"
	"uniform vec3 viewPos;"
	"uniform vec3 lightPos;"
	"uniform sampler2D text;"
	"uniform vec3 lightColor;"
	"uniform vec3 dampVec;"
	"struct light"
	"{"
	"}"
	"out vec4 color;"
	"void main(){"
	"	if(light_rendering)color = vec4(lightColor,1.0);"
	"	else {"
	"		vec3 norm = normal ;"
	"		vec3 lightDir = normalize(lightPos - pos);"
	"		vec3 viewv = normalize(viewPos - pos);"
	"		float dc = max(dot(lightDir,norm),0.0);"//diffuse coefficient
	"		float sc = pow(max(dot(normalize(lightDir+viewv),norm),0.0),128);"//specular coefficient
	"		vec4 objColor;"
	"		if(texture_enable){"
	"			float pi = acos(-1);"
	"			float rd = acos(opos.z/sqrt(1-opos.y*opos.y));"
	"			if(opos.x<0) rd+=2*(pi - rd);"
	"			vec2 text_pos = vec2(rd/(2*pi),1 - acos(opos.y)/pi);"
	"			objColor= texture(text,text_pos);"
	"		}"
	"		else objColor = objectColor;"
	"		float len = length(lightPos - pos);"
	"		float damp = 1.0/(dampVec.x+dampVec.y*len + dampVec.z*len*len);"
	"		color = vec4(vec3(objColor) * lightColor * dc * damp + lightColor * sc * damp+vec3(0.2),objectColor.a);\n"
	"	}"
	"}; "
};
const char* shader_Gouraud = {
	"#version 460 core\n"
	"layout (location = 0) in vec3 p;"
	"layout (location = 1) in vec3 normal;"
	"uniform mat4 model;"
	"uniform vec4 objectColor;"
	"uniform mat4 transform;"
	"uniform vec3 viewPos;"
	"uniform vec3 lightPos;"
	"uniform vec3 lightColor;"
	"uniform bool light_rendering;"
	"uniform bool texture_enable;"
	"uniform vec3 dampVec;"
	"out vec4 color;"
	"void main(){"
	"	gl_Position = transform * vec4(p,1.0);"
	"	if(light_rendering)color = vec4(lightColor,1.0);"
	"	else {"
	"	vec3 viewDir = normalize(viewPos - p);"
	"	vec3 lightDir = normalize(lightPos - p);"
	"   vec3 norm = normalize(transpose(inverse(mat3(model))) * normal);"
	"	float diff = max(dot(norm,lightDir),0.0f);"
	"	float spec = pow(max(dot(normalize(viewDir+lightDir),norm),0.0f),64);"
	"	color = vec4(diff * vec3(objectColor) +lightColor*vec3(objectColor)*spec +vec3(0.2),objectColor.a);"
	"	}"
	"};"
	"     "
	"%"
	"   "
	"#version 460 core\n"
	"in vec4 color;"
	"out vec4 Color;"
	"void main(){"
	"	Color = color;"
	"}; "
};