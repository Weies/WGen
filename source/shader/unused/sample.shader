#version 460 core
layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 tex;

out vec2 texcoord;
void main() {
	gl_Position = vec4(pos , 0.0 , 1.0);
	texcoord = tex;
}

%

#version 460 core
in vec2 texcoord;

uniform sampler2D text;
out vec4 color;

const float offsetx = 1.0 / 800.0;
const float offsety = 1.0 / 600.0;

const vec2 offsets[9] = vec2[](
	vec2(-offsetx , offsety) , // 左上
	vec2(0.0f , offsety) , // 正上
	vec2(offsetx , offsety) , // 右上
	vec2(-offsetx , 0.0f) ,   // 左
	vec2(0.0f , 0.0f) ,   // 中
	vec2(offsetx , 0.0f) ,   // 右
	vec2(-offsetx , -offsety) , // 左下
	vec2(0.0f , -offsety) , // 正下
	vec2(offsetx , -offsety)  // 右下
	);

const float kernelo[9] = float[](
	0 , 0 , 1 ,
	0 , 0 , 1 ,
	0 , 0 , 1
	);

const float kernel[9] = float[](
	-1 , -1 , -1 ,
	-1 , 8 , -1 ,
	-1 , -1 , -1
	);
const float kernelb[9] = float[](
	2 , 2 , 2 ,
	2 , 2 , 2 ,
	2 , 2 , 2
	);

const float kernelc[9] = float[](
	8 , 8 , 8 ,
	8 , 0 , 8 ,
	8 , 8 , 8
	);

const float kerneld[9] = float[](
	-8 , -8 , -8 ,
	-8 , 80 , -8 ,
	-8 , -8 , -8
	);

uniform float contrast;

float sigmoid(float val) {
	return 1 / (1 + exp(contrast - 2 * contrast * val));
}


void main()
{
	/*vec3 sampleTex[9];
	for (int i = 0; i < 9; i++)
	{
		sampleTex[i] = vec3(texture(text , texcoord.xy + offsets[i]));
	}
	vec3 col = vec3(0.0);
	for (int i = 0; i < 9; i++)
		col += sampleTex[i] * kernel[i];
	color = vec4(col , 1.0);*/

	vec3 co = vec3(texture(text , texcoord.xy));
	//co.x = sigmoid(co.x); co.y = sigmoid(co.y); co.z = sigmoid(co.z);
	//co.x = sqrt(co.x); co.y = sqrt(co.y); co.z = sqrt(co.z);
	//color = vec4(pow(co , vec3(1 / 2.2)) , 1.0);
	//color = vec4(pow(co , vec3(2.2)) , 1.0);
	color = vec4(co , 1.0);
	//color = vec4(1.0);
	//vec4 co = texture(text , texcoord);
	//float aver = (co.r + co.g + co.b) / 3;
	////float aver = 0.2126 * co.r + 0.7152 * co.g + 0.0722 * co.b;
	//color = vec4(aver , aver , aver , 1.0);

	//color = vec4(vec3(texture(text , texcoord)) , 1.0);
}