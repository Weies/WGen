#version 460 core

layout(location = 0)in vec3 p;

uniform mat4 pv_mat;
uniform mat4 model;

void main() {
	gl_Position = pv_mat * model * vec4(p , 1.0);
}


%


#version 460 core

void main() {

}