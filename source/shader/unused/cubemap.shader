#version 460 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;

uniform mat4 transform;
out vec3 dir;

void main() {
	vec4 p = transform * vec4(pos , 1.0);
	gl_Position = p;
	dir = pos;
}

%

#version 460 core
in vec3 dir;

uniform samplerCube texture_cubemap1;

out vec4 color;

void main() {

	color = pow(texture(texture_cubemap1 , dir) , vec4(1 / 1.2));
}