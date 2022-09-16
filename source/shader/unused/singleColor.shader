#version 460 core

layout(location = 0) in vec3 p;
uniform mat4 transform;

void main() {
	gl_Position = transform * vec4(p , 1.0);
}

%

#version 460 core
out vec4 Color;
void main() {
	Color = vec4(1.0 , 0 , 0 , 0.4);
}