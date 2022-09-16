#version 460 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 transform;

void main()
{
	TexCoords = aTexCoords;
	gl_Position = transform * vec4(aPos , 1.0);
}

%

#version 460 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_diffuse4;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;
uniform sampler2D texture_specular3;
uniform sampler2D texture_specular4;

void main()
{
	FragColor = texture(texture_diffuse1 , TexCoords) + texture(texture_specular1 , TexCoords)
		+ texture(texture_diffuse2 , TexCoords) + texture(texture_specular2 , TexCoords);
}

