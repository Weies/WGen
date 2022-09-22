#version 460 core
in vec3 p;
in vec3 norm;
in vec2 texcoord;

out vec3 pos;
out vec3 normal;
out vec2 texCoord;

uniform mat4 transform;
uniform mat4 model;

void main() {
	gl_Position = transform * vec4(p, 1.0);
	pos = vec3(model * vec4(p, 1.0));
	normal = norm;
	texCoord = texcoord;
}

%

#version 460 core
in vec3 pos;
in vec3 normal;
in vec2 texCoord;

uniform sampler2D tex_base_color;
uniform vec4 base_color;

out vec4 color;
void main() {
	//color = base_color + texture(tex_base_color, texCoord);
	color = vec4(1.0, 0, 0, 1.0);
}