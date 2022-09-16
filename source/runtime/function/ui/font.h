#pragma once
#include"../render/shader.h"
#include"../event/events.h"
#include"../base/encoder.h"
#include FT_FREETYPE_H

#define drawString font.pushString
#define rdrawString font.rpushString

#define cdrawString(x,y,str) font.pushString(x-font.testWidth(str)/2,y + font.fontSize/(2+0.3),str)
#define cvdrawString(x,y,str) font.pushString(x,y + font.fontSize/(2+0.3),str)
#define chdrawString(x ,y,str) font.pushString(x - font.testWidth(str) / 2 , y, str)
#define rcdrawString(x,y,str) font.rpushString(x-font.testWidth(str)/2,y + font.fontSize/(2+0.3),str)
#define rcvdrawString(x,y,str) font.rpushString(x,y + font.fontSize/(2+0.3),str)
#define rchdrawString(x ,y,str) font.rpushString(x - font.testWidth(str) / 2 , y, str)

using namespace std;
using namespace events;

struct texChar {//纹理字符
	GLuint texid;	//纹理号
	ivec2 size;		//宽高向量
	ivec2 bearing;	//方位
	GLuint advance;	//增长，注意是1/64
};

class String {//字符串对象
public:
	String() {}
	String(float xx, float yy, const string& s, const Color& c, float pri, float padding = 0) :str(s), co(c) {
		x = xx; y = yy; prior = pri; this->padding = padding;
	}
	float width;
	float x; float y; float padding = 0;
	string str; Color co; float prior;
};

class Font {
public:
	void initLib(const string& fontPath)
	{
		if (FT_Init_FreeType(&ft))excep(WERROR_INITIALIZE, "Wrong when init freetype");
		if (FT_New_Face(ft, fontPath.c_str(), 0, &face))excep(WERROR_FILE_LOAD, "Wrong when load font");
		fontSize = 20;
		FT_Set_Pixel_Sizes(face, 0, fontSize);
		coder.start(gb2312, Unicode);
	}
	void freeLib()
	{
		FT_Done_Face(face);
		FT_Done_FreeType(ft);
	}


	void pushString(float x, float y, const string& s, float padding = 0)
	{
		if (LEFT_UP)
			renderlist.push_back(String(x, win_h - y, s, co, curPriority + 1024, padding));
		else renderlist.push_back(String(x, win_h - y, s, co, curPriority + 1024, padding));
	}
	void rpushString(float x, float y, const string& s, float padding = 0)
	{
		if (LEFT_UP)
			renderlist.push_back(String(x + origin_x, win_h - origin_y - y, s, co, curPriority + 1024, padding));
		else renderlist.push_back(String(x + origin_x, win_h - origin_y - y, s, co, curPriority + 1024, padding));
	}
	texChar& operator[](long c)
	{
		return fonts[c];
	}
	void rotate(float deg) {
		//model = gm::rotate(model , deg , );
	}
	void setFont(const string& fontpath)
	{
		fontPath = fontpath;
		freeLib();
		initLib(fontpath);
		fonts.clear();
	}
	void setColor(const Color& color)
	{
		co = color;
	}
	void setColor(float r, float g, float b, float a = 1)
	{
		co = Color(r, g, b, a);
	}
	void setSize(int pix)
	{
		fontSize = pix;
		FT_Set_Pixel_Sizes(face, 0, fontSize);
	}
	void setScale(float times)
	{
		scale = times;
	}
	void setPriority(float pri)
	{
		curPriority = pri;
	}
	void reset()
	{
		prior = 2.0f;
	}

	Font() {};
	void init(const string& fontpath);
	void initOBJ();
	void loadAsc();//只加载Asc码
	void loadFont();//加载整个字体，不推荐
	void loadString(const string& s);//加载一个字符串用于显示
	texChar loadCode(long code);//加载一个字符
	//渲染未加载的文字使用liveText，会自动加载没有的字符
	void renderLiveText();
	float testWidth(const string& s);//测试一个字符串被渲染出来的宽度
	float testCharW(const char* cc);
	void setModel(const mat3& m) {
		model = m;
	}
	void lock() {
		while (_lock);
		_lock = true;
	}
	void unlock() {
		_lock = false;
	}
	bool _lock = false;
	mat3 model;
	mat4 proj;
	float prior = 2.0f;
	int fontSize; bool added = false;
	map<long, texChar> fonts;
	Shader shader; float scale = 1.0;
	Color co; VAOBuffer VAO;
	VBOBuffer VBO; string sha_str;
	Encoder coder; string fontPath;
	FT_Library ft; FT_Face face;
	vector<String> renderlist;//字体渲染列表
private:

};

___global(Font, font);
#define font _get_font()


