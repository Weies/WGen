#version 460 core

layout(location = 0) in vec2 p;
layout(location = 1) in vec2 texcoords;

out vec2 texcoord;
void main() {

	gl_Position = vec4(p , 0.6 , 1.0);
	texcoord = texcoords;
}

%

#version 460 core
in vec2 texcoord;

uniform sampler2D tex1;
uniform sampler2D tex2;

float contrast = 5.0f;

float sigmoid(float val) {
	return 1 / (1 + exp(contrast - 2 * contrast * val));
}

vec3 sigmoid(vec3 v) {
	return vec3(sigmoid(v.x) , sigmoid(v.y) , sigmoid(v.z));
}

out vec4 co;

void main() {
	co = vec4(vec3(texture(tex1 , texcoord) - texture(tex2 , texcoord)) , 1.0);
	//co = vec4(1.0 , 0 , 0 , 1.0);
}
