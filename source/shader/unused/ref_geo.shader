#version 460 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
uniform mat4 transform;
uniform mat4 model;
out VS_OUT{
	out vec3 pp;
	out vec3 normm;
} vs_out;

void main() {
	gl_Position = transform * vec4(pos , 1.0);
	vs_out.pp = vec3(model * vec4(pos , 1.0));
	vs_out.normm = normal;
}

%

#version 460 core
in vec3 p;
in vec3 norm;

uniform samplerCube cube;
uniform vec3 viewPos;
uniform float rr;

out vec4 color;

void main() {
	vec3 v = normalize(p - viewPos);
	vec3 r = refract(v , normalize(norm) , rr);
	color = texture(cube , r);
}


%

#version 460 core
layout(triangles) in;
layout(line_strip , max_vertices = 3) out;

in VS_OUT{
	vec3 pp;
	vec3 normm;
} gs_in[];

out vec3 p;
out vec3 norm;

uniform float time;

vec4 explode(vec4 position , vec3 normal) {
	float magnitude = 10.0;
	vec3 direction = normal * ((sin(time) + 1.0) / 2.0) * magnitude;
	return position + vec4(direction , 0.0);
}

vec3 GetNormal() {
	vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
	vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
	return normalize(cross(a , b));
}

void main() {

	vec3 normal = GetNormal();
	vec4 aver = (gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position) * 0.3334;

	gl_Position = aver;
	p = gs_in[0].pp; norm = gs_in[0].normm;
	EmitVertex();

	gl_Position = aver + vec4(normal , 0.0)*0.1;
	p = gs_in[1].pp; norm = gs_in[1].normm;
	EmitVertex();


	/*gl_Position = explode(gl_in[0].gl_Position , normal);
	p = gs_in[0].pp; norm = gs_in[0].normm;
	EmitVertex();

	gl_Position = explode(gl_in[1].gl_Position , normal);
	p = gs_in[1].pp; norm = gs_in[1].normm;
	EmitVertex();

	gl_Position = explode(gl_in[2].gl_Position , normal);
	p = gs_in[2].pp; norm = gs_in[2].normm;
	EmitVertex();*/

	EndPrimitive();
}
