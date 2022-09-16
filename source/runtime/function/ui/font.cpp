#include"font.h"


const char* CodeName(CodeType t)
{
	switch (t)
	{
	case 1:
		return "gb2312";
		break;
	case 2:
		return "gbk";
		break;
	case 3:
		return "gb18030";
		break;
	case 4:
		return "utf-8";
		break;
	case 5:
		return "UCS-2BE";
		break;
	case 6:
		return "ASCII";
		break;
	default:break;
		//__debugbreak();
	}
}

void Font::init(const string& fontpath)
{
	fontSize = 24;
	sha_str = "#version 460 core\n"
		"layout(location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>\n"
		"out vec2 TexCoords;\n"
		"uniform mat4 proj;\n"
		"uniform mat3 model;"
		"uniform float pri;\n"
		"void main()\n"
		"{\n"
		"float prio = pri;"
		"if(prio>1024)prio = 1024+log(prio);"
		"prio = prio/(100+prio)*prio/1024;"
		"\tgl_Position = proj*vec4((model*vec3(vertex.xy, 1.0)).xy,prio,1.0);\n"
		"\tTexCoords = vertex.zw;\n"
		"}\n"
		"%\n"
		"#version 460 core\n"
		"in vec2 TexCoords;\n"
		"out vec4 color;\n"
		"uniform sampler2D text;\n"
		"uniform vec4 textColor;\n"
		"void main()\n"
		"{\n"
		"float val = texture(text, TexCoords).r; "
		"color = vec4(textColor.rgb, val*textColor.a);\n"
		"}\n";
	//"\tvec4 sampled = vec4(1.0, 1.0, texture(text, TexCoords).r );\n"
	//;*sampled

	initOBJ();
	fontPath = fontpath;
	initLib(fontPath);
	coder.start(gb2312, Unicode);
	setColor({ 255,0,0 });
}


void Font::initOBJ()
{
	shader.parseFromString(sha_str.c_str());
	proj = ortho(0.0f, win_w, 0.0f, win_h);//省略时n=-1,f=1
	shader.setMat4("proj", proj);
	shader.setMat3("model", mat3(1.0f));
	model = mat3(1.0);

	evtor.windowreshape() = ([=](int x, int y)->bool {
		proj = ortho(0.0f, win_w, 0.0f, win_h);
		shader.setMat4("proj", proj);
		return false;
		});

	VAO.bind();
	VBO.setData(4 * 4 * 6, NULL, GL_DYNAMIC_DRAW);
	VBO.setAttribPointer(0, 4, 4 * 4, 0);//索引，点数，空间，偏移
}

void Font::loadAsc()//只加载Asc码
{
	VAO.bind();
	for (GLubyte c = 0; c < 128; c++)
	{
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			excep(WERROR_FILE_LOAD, "Wrong when load Glyph: " + char(c));
			continue;
		}
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,
			face->glyph->bitmap.width, face->glyph->bitmap.rows,
			0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		texChar character = {
			texture,
			gm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			gm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		fonts.insert(pair<long, texChar>(c, character));
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Font::loadFont()//加载整个字体，不推荐
{
	VAO.bind();
	for (long c = 0; c < 63355; c++)
	{
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			excep(WERROR_FILE_LOAD, "Wrong when load Glyph: " + itos(c));
			continue;
		}
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,
			face->glyph->bitmap.width, face->glyph->bitmap.rows,
			0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		texChar character = {
			texture,
			gm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			gm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		fonts.insert(pair<long, texChar>(c, character));
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Font::loadString(const string& s)//加载一个字符串用于显示
{
	VAO.bind();
	for (int i = 0; i < s.size();)
	{
		Char ch = coder.encodeChar(s.c_str() + i);
		long code = ch.longCode(); i += ch.len;
		if (FT_Load_Char(face, code, FT_LOAD_RENDER))
		{
			excep(WERROR_FILE_LOAD, "Wrong when load Glyph: " + itos(code));
			continue;
		}
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,
			face->glyph->bitmap.width, face->glyph->bitmap.rows,
			0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		texChar character = {
			texture,
			gm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			gm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		fonts.insert(pair<long, texChar>(code, character));
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}

texChar Font::loadCode(long code)//加载一个字符
{
	VAO.bind();
	if (FT_Load_Char(face, code, FT_LOAD_RENDER))
	{
		excep(WERROR_FILE_LOAD, "Wrong when load Glyph: " + itos(code));
	}
	if (code == '\t')face->glyph->advance.x *= 2.88;
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,
		face->glyph->bitmap.width, face->glyph->bitmap.rows,
		0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	texChar character = {
		texture,
		gm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
		gm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
		face->glyph->advance.x
	};
	fonts.insert(pair<long, texChar>(code, character));
	glBindTexture(GL_TEXTURE_2D, 0);
	return character;
}

void Font::renderLiveText()
{
	VAO.bind();
	glActiveTexture(GL_TEXTURE0);
	shader.setMat4("proj", proj);
	shader.setMat3("model", model);
	for (int j = 0; j < renderlist.size(); j++)
	{
		float x = renderlist[j].x; float y = renderlist[j].y;
		const string& s = renderlist[j].str;
		const Color& coo = renderlist[j].co;
		shader.setVec4("textColor", coo.vec4());
		shader.setFloat("pri", renderlist[j].prior);
		float padding = renderlist[j].padding;
		for (int i = 0; i < s.size();)
		{
			Char c = coder.encodeChar(s.c_str() + i);
			long code = c.longCode(); i += c.len;
			switch (code)
			{
			case 10:
				y -= fontSize + 10; x = 50; continue;
				break;
			case 9:
				x += fontSize * 2; continue;
				break;
			default:
				break;
			}
			auto it = fonts.find(code);
			texChar ch;
			if (it == fonts.end())
				ch = loadCode(code);
			else ch = it->second;
			GLfloat xpos = x + ch.bearing.x * scale;
			GLfloat ypos = y - (ch.size.y - ch.bearing.y) * scale;
			GLfloat w = ch.size.x * scale;
			GLfloat h = ch.size.y * scale;
			GLfloat vertices[6][4] = {
				{ xpos,     ypos + h,   0.0, 0.0 },
				{ xpos,     ypos,       0.0, 1.0},
				{ xpos + w, ypos,       1.0, 1.0 },
				{ xpos,     ypos + h,   0.0, 0.0 },
				{ xpos + w, ypos,       1.0, 1.0 },
				{ xpos + w, ypos + h,   1.0, 0.0 }
			};
			glBindTexture(GL_TEXTURE_2D, ch.texid);
			VBO.setSubData(sizeof(vertices), 0, vertices);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			x += (ch.advance >> 6) * scale + padding;
			/*if (x + 20 >= win_w)
				x = 50 , y -= fontSize + 10;*/
		}
	}
	renderlist.resize(0);
	useDefalut();
}

float Font::testWidth(const string& s)
{//测试一个字符串被渲染出来的宽度
	float ret = 0;
	for (int i = 0; i < s.length();)
	{
		Char c = coder.encodeChar(s.c_str() + i);
		long code = c.longCode(); i += c.len;
		auto it = fonts.find(code);
		texChar ch = (it == fonts.end()) ? loadCode(code) : it->second;
		ret += (ch.advance >> 6) * scale;
	}
	return ret;
}

float Font::testCharW(const char* cc)
{
	Char c = coder.encodeChar(cc);
	long code = c.longCode();
	auto it = fonts.find(code);
	texChar ch = (it == fonts.end()) ? loadCode(code) : it->second;
	return (ch.advance * 1.0 / 64) * scale;
}