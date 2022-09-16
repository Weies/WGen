#pragma once
#include"ft2build.h"
#include"iconv.h"
#include"core/log/debuger.h"
enum CodeType {
	gb2312 = 1, gbk = 2, gb18030 = 3, utf8 = 4, Unicode = 5, AscII = 6
};

const char* CodeName(CodeType t);

class Char {//文字字符
public:
	inline Char() {}
	inline Char(const char* c, int len) {
		init(c, len);
	}
	inline void init(const char* c, int length)
	{
		len = length;
		for (int i = 0; i < len; i++)
			str[i] = c[i];
	}
	inline long longCode()
	{
		if (len == 1)
		{
			return str[0];
		}
		else {
			unsigned char cha = str[0];
			unsigned long ret = 0;
			ret += cha;
			ret <<= 8;
			cha = str[1];
			ret += cha;
			return ret;
		}
	}
	size_t len;
	char str[4] = {};
};

class Encoder {
public:

	inline bool start(CodeType source, CodeType target)
	{
		src = source; tgt = target;
		ASSERT(handle = iconv_open(CodeName(target), CodeName(source)));
		return handle;
	}
	inline void end() {
		iconv_close(handle);
	}

	inline Char encodeChar(const char* c)
	{
		Char ret; char* p = ret.str;
		if (src == Unicode || *c < 0)
		{
			ret.init(c, 2);
			iconv(handle, &p, &ret.len, &p, &ret.len);
			ret.len = 2;
			return ret;
		}
		else
		{
			ret.init(c, 1);
			return ret;
		}
	}

	inline string encode(const string& s)
	{
		int i = 0; Char ch; string ret;
		while (i < s.size())
		{
			ch = encodeChar(s.c_str() + i);
			i += ch.len;
			ret += ch.str;
		}
		return ret;
	}

	static bool isCharset(const string& s, CodeType tp) {
		iconv_t cd = iconv_open("UTF-8", CodeName(tp));
		if (cd == 0)debug("error happened when open handle for convert charset");
		size_t inlen = s.size(); char* inbuf = (char*)s.c_str();
		memset(outbuf, 0, 4096); char* p = outbuf; size_t outlen = 4096;
		if (iconv(cd, &inbuf, &inlen, &p, &outlen) == -1)return false;
		return true;
	}

	static string getGBK(const string& s) {
		//先检查字符串是否是GBK编码
		iconv_t cd = iconv_open("gb2312", "gb2312"); if (cd == 0)return "error";
		size_t inlen = s.size(); char* inbuf = (char*)s.c_str();
		memset(outbuf, 0, 4096); char* p = outbuf; size_t outlen = 4096;
		if (iconv(cd, &inbuf, &inlen, &p, &outlen) == -1)
			memset(outbuf, 0, 4096), p = outbuf, outlen = 4096, inbuf = (char*)s.c_str(), inlen = s.size();
		else { iconv_close(cd); return s; }
		iconv_close(cd);

		cd = iconv_open("gb2312//IGNORE", "utf-8"); if (cd == 0)return "error";
		if (iconv(cd, &inbuf, &inlen, &p, &outlen) == -1)
			memset(outbuf, 0, 4096), p = outbuf, outlen = 4096, inbuf = (char*)s.c_str(), inlen = s.size();
		else { iconv_close(cd); return outbuf; }
		iconv_close(cd);

		cd = iconv_open("gb2312//IGNORE", "UCS-2BE"); if (cd == 0)return "error";
		if (iconv(cd, &inbuf, &inlen, &p, &outlen) != -1) { iconv_close(cd); return outbuf; }
		iconv_close(cd);
		return s;
	}
	static string getUTF8(const string& s) {
		//先检查字符串是否是UTF-8编码
		iconv_t cd = iconv_open("utf-8", "utf-8"); if (cd == 0)return "error";
		size_t inlen = s.size(); char* inbuf = (char*)s.c_str();
		memset(outbuf, 0, 4096); char* p = outbuf; size_t outlen = 4096;
		if (iconv(cd, &inbuf, &inlen, &p, &outlen) == -1)
			memset(outbuf, 0, 4096), p = outbuf, outlen = 4096, inbuf = (char*)s.c_str(), inlen = s.size();
		else { iconv_close(cd); return s; }
		iconv_close(cd);

		cd = iconv_open("utf-8//IGNORE", "gb2312"); if (cd == 0)return "error";
		if (iconv(cd, &inbuf, &inlen, &p, &outlen) == -1)
			memset(outbuf, 0, 4096), p = outbuf, outlen = 4096, inbuf = (char*)s.c_str(), inlen = s.size();
		else { iconv_close(cd); return outbuf; }
		iconv_close(cd);

		cd = iconv_open("utf-8//IGNORE", "UCS-2BE"); if (cd == 0)return "error";
		if (iconv(cd, &inbuf, &inlen, &p, &outlen) != -1) { iconv_close(cd); return outbuf; }
		iconv_close(cd);
		return s;
	}

	static string gbkUtf8(const string& strGbk)// 传入的strGbk是GBK编码 
	{
		return code_convert("gb2312//IGNORE", "utf-8", strGbk);//IGNORE
	}

	static string utf8Gbk(const string& strUtf8)
	{
		return code_convert("utf-8//IGNORE", "gb2312", strUtf8);//IGNORE
	}

	static string gbkUnicode(const string& strGbk)
	{
		//UCS-2BE代表Unicode大端模式
		return code_convert("gb2312//IGNORE", "UCS-2BE", strGbk);//IGNORE
	}

	static string unicodeGbk(const string& strGbk)// 传入的strGbk是GBK编码 
	{
		return code_convert("UCS-2BE//IGNORE", "gb2312", strGbk);//IGNORE
	}
	static string convert(CodeType from, CodeType to, const string& toBeTranform) {
		return code_convert(CodeName(from), CodeName(to), toBeTranform);
	}

private:
	static char outbuf[4096];
	CodeType src;
	CodeType tgt;
	iconv_t handle;
	static string code_convert(const char* from_charset, const char* to_charset, const string& sourceStr) //sourceStr是源编码字符串
	{
		iconv_t cd = iconv_open(to_charset, from_charset);//获取转换句柄，void*类型
		if (cd == 0)return "";
		size_t inlen = sourceStr.size(); char* inbuf = (char*)sourceStr.c_str();
		char outbuf[3000] = {}; char* p = outbuf; size_t outlen = 3000;
		if (iconv(cd, &inbuf, &inlen, &p, &outlen) == -1)
			return "error";
		iconv_close(cd);
		//iconv
		return outbuf;
	}
};