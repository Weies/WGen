#pragma once
#include<fstream>
#include"core/math/math_include.h"
#include"../base/image.h"
#include"../base/render_base.h"
#include"../base/global_values.h"
#include"../render/texture.h"

using namespace globals;
using std::fstream;

class Shader {
public:
	Shader() {}
	Shader(const string& fontPath , bool geo = false) {
		parseShader(fontPath , geo);
		use();
	}
	void setMat4(const string& uniName , const mat4& mat)const
	{
		use();
		glUniformMatrix4fv(glGetUniformLocation(id , uniName.c_str()) , 1 , GL_FALSE , value_ptr(mat));
	}
	void setMat3(const string& uniName , const mat3& mat) const
	{
		use();
		glUniformMatrix3fv(glGetUniformLocation(id , uniName.c_str()) , 1 , GL_FALSE , value_ptr(mat));
	}
	void setVec2(const string& uniName , const vec2& vec) const
	{
		use();
		glUniform2f(glGetUniformLocation(id , uniName.c_str()) , vec.x , vec.y);
	}
	void setVec2(const string& uniName , int x , int y) const
	{
		use();
		glUniform2f(glGetUniformLocation(id , uniName.c_str()) , x , y);
	}
	void setVec3(const string& uniName , int x , int y , int z) const
	{
		use();
		glUniform3f(glGetUniformLocation(id , uniName.c_str()) , x , y , z);
	}
	void setVec3(const string& uniName , const vec3& v) const
	{
		use();
		glUniform3f(glGetUniformLocation(id , uniName.c_str()) , v.x , v.y , v.z);
	}
	void setVec4(const string& uniName , const vec4& vec) const
	{
		use();
		glUniform4f(glGetUniformLocation(id , uniName.c_str()) , vec.x , vec.y , vec.z , vec.w);
	}
	void setFloat(const string& uniName , float val) const
	{
		use();
		glUniform1f(glGetUniformLocation(id , uniName.c_str()) , val);
	}
	void setInt(const string& uniName , int val) const
	{
		use();
		glUniform1i(glGetUniformLocation(id , uniName.c_str()) , val);
	}
	void setDouble(const string& uniName , double val) const
	{
		use();
		glUniform1d(glGetUniformLocation(id , uniName.c_str()) , val);
	}

	void setMat4(int loc , const mat4& mat) const
	{
		use();
		glUniformMatrix4fv(loc , 1 , GL_FALSE , value_ptr(mat));
	}
	void setMat3(int loc , const mat3& mat) const
	{
		use();
		glUniformMatrix3fv(loc , 1 , GL_FALSE , value_ptr(mat));
	}
	void setVec2(int loc , const vec2& vec) const
	{
		use();
		glUniform2f(loc , vec.x , vec.y);
	}
	void setVec2(int loc , int x , int y) const
	{
		use();
		glUniform2f(loc , x , y);
	}
	void setVec3(int loc , int x , int y , int z) const
	{
		use();
		glUniform3f(loc , x , y , z);
	}
	void setVec3(int loc , const vec3& v) const
	{
		use();
		glUniform3f(loc , v.x , v.y , v.z);
	}
	void setVec4(int loc , const vec4& vec) const
	{
		use();
		glUniform4f(loc , vec.x , vec.y , vec.z , vec.w);
	}
	void setFloat(int loc , float val) const
	{
		use();
		glUniform1f(loc , val);
	}
	void setInt(int loc , int val) const
	{
		use();
		glUniform1i(loc , val);
	}
	void setDouble(int loc , double val) const
	{
		use();
		glUniform1d(loc , val);
	}

	void use() const
	{
		if (cur_id != id)
			glUseProgram(id) , cur_id = id;//使用着色器程序
	}
	void disuse() const
	{
		glUseProgram(defaultShader);
	}

	void parseFromString(const string& shader_string , bool geo = false)
	{
		string ver = shader_string;
		if (geo == false) {
			string fras = ver.substr(ver.find("%") + 2);
			ver = string(ver.begin() , ver.begin() + ver.find("%"));
			id = createShader(ver , fras);
		}
		else
		{
			string fras(ver.begin() + ver.find('%') + 2 , ver.begin() + ver.rfind('%'));
			string geo(ver.begin() + ver.rfind('%') + 2 , ver.begin() + ver.size());
			ver = string(ver.begin() , ver.begin() + ver.find('%'));
			id = createShader(ver , fras , geo);
		}
		use();
	}

	void parseShader(const string& filepath , bool geo = false)
	{
		fstream f(filepath);
		std::istreambuf_iterator<char> beg(f) , end;
		string ver(beg , end);
		if (ver == "")excep(WERROR_FILE_LOAD , "Wrong when load shader file: " + filepath);
		if (geo == false) {
			string fras = ver.substr(ver.find('%') + 2);
			ver = string(ver.begin() , ver.begin() + ver.find('%'));
			id = createShader(ver , fras);
		}
		else
		{
			string fras(ver.begin() + ver.find('%') + 2 , ver.begin() + ver.rfind('%'));
			string geo(ver.begin() + ver.rfind('%') + 2 , ver.begin() + ver.size());
			ver = string(ver.begin() , ver.begin() + ver.find('%'));
			id = createShader(ver , fras , geo);
		}
		f.close();
		use();
	}
	unsigned int id = 0;
private:
	static int cur_id;
	unsigned int compileShader(const unsigned int& type , const string& s)
	{
		unsigned int id = glCreateShader(type);
		const char* src = s.c_str();
		glShaderSource(id , 1 , &src , nullptr);
		glCompileShader(id);
		int ret;
		glGetShaderiv(id , GL_COMPILE_STATUS , &ret);
		if (ret == GL_FALSE)
		{
			int len;
			glGetShaderiv(id , GL_INFO_LOG_LENGTH , &len);
			GLsizei size; char* buf = new char[len];
			glGetShaderInfoLog(id , 1000 , &size , buf);
			debug(string("Wrong when compile ") +
				  ((type == GL_VERTEX_SHADER)?"Vertex shader":(type == GL_FRAGMENT_SHADER)
				   ?"Fragment shader":"Geometry shader")
				  + string("\n") + buf);
			delete[] buf;
			glDeleteShader(id);
			return -1;
		}
		return id;
	}
	unsigned int createShader(const string& ver , const string& fras , const string& geo = "")
	{
		unsigned int pro = glCreateProgram();
		unsigned int vertexShader = compileShader(GL_VERTEX_SHADER , ver);
		unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER , fras);
		uint gs = -1;
		glAttachShader(pro , vertexShader);
		glAttachShader(pro , fragmentShader);
		if (geo != "") {
			gs = compileShader(GL_GEOMETRY_SHADER , geo);
			glAttachShader(pro , gs);
		}
		glLinkProgram(pro);
		glValidateProgram(pro);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		if (gs != -1)glDeleteShader(gs);
		return pro;
	}
};

class Picture {
public:
	Picture() {
		vao.bind();
	}
	Picture(const string& path)
	{
		img.load(path);
		vao.bind();
		w = 400 , h = 400;
		static float dat[] =
		{
		0,0,0,0,
		w,h,1,1,
		0,h,0,1,

		0,0,0,0,
		w,h,1,1,
		w,0,1,0
		};
		data = dat;
		vbo.setData(24 * 4 , data);
		vbo.setAttribPointer(0 , 2 , 16 , 0);
		vbo.setAttribPointer(1 , 2 , 16 , (void*)8);
		const char* sha =
			"#version 460 core\n								  "
			"layout(location = 0) in vec2  position;			  "
			"layout(location = 1) in vec2 intexcord;			  "//"uniform mat4 proj;                          "
			"uniform float prior;"
			"uniform mat4 proj;								      "
			"out vec2 texcord;									  "
			"void main()										  "
			"{													  "
			"	gl_Position =proj*vec4(position,prior, 1.0);"
			"	texcord = intexcord;	 "
			"}							 "
			"							 "
			"%							 "
			"#version 460 core\n		 "
			"in vec2 texcord;			 "
			"							 "
			"out vec4 color;			 "
			"uniform sampler2D texture; "
			"void main() {"
			"	color = texture(texture, texcord);"
			"}";

		shader.parseFromString(sha);
		//glTexture
		tex.setData(img);
		w = img.w; h = img.h;
		tex.bindToShader(shader.id , "texture");
		proj = gm::ortho(0.0f , win_w , 0.0f , win_h);
		proj[2][2] = -1.0 / 1025;
		shader.setMat4("proj" , proj);
		shader.setFloat("prior" , 0.0);
		//shapFuncs.push_back([=](int x , int y) {
		//	proj = gm::ortho(0.0f , win_w , 0.0f , win_h);
		//	proj[2][2] = -1.0 / 1025;
		//	shader.setMat4("proj" , proj);
		//});
	}
	void draw()
	{
		vao.bind();
		vbo.bind();
		tex.bind();
		shader.setFloat("prior" , prior);
		glDrawArrays(GL_TRIANGLES , 0 , 6);
		shader.disuse();
	}
	void setPriorty(float pri)
	{
		prior = pri / 1025;
	}
	void reset()
	{
		prior = -0.5;
	}
	float prior = -0.5;
	Image img; float w; float h;
	VAOBuffer vao; VBOBuffer vbo;
	Texture tex; mat4 proj;
	Shader shader; float* data;
};
