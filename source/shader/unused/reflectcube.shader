#version 460 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
uniform mat4 transform;
uniform mat4 model;
out vec3 p;
out vec3 norm;
void main() {
	gl_Position = transform * vec4(pos , 1.0);
	p = vec3(model * vec4(pos , 1.0));
	norm = normal;
}

%

#version 460 core
in vec3 p;
in vec3 norm;

uniform samplerCube texture_cubemap1;
uniform vec3 viewPos;
uniform float rr;

out vec4 color;

void main() {
	vec3 v = normalize(p - viewPos);
	//vec3 r = refract(v , normalize(norm) , rr);
	vec3 r = reflect(v , normalize(norm));
	color = texture(texture_cubemap1 , r);
}