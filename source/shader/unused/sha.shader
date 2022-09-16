#version 460 core
layout (location=0) in vec3  position;
layout(location = 1) in vec2 intexcord;

out vec2 texcord;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
void main()
{
	gl_Position=  proj *view * model * vec4(position,1.0);
	texcord = intexcord;
}

%

#version 460 core
in vec2 texcord;

out vec4 color;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {

	color = vec4(1.0,0,0,1.0)*mix(texture(texture1, texcord)*2,texture(texture2,texcord)*2,0.5);

}