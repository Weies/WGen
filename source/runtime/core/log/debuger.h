#pragma once

#include"../base/basis.h"
#include"../base/singleton.h"
#include<string>
#define WIN32_LEAN_AND_MEAN
#include<windows.h>
#undef max
#undef min
#include<sstream>
#include<string>

inline std::wstring wstr(const string& s) {
	std::wstring o; o.reserve(s.size() + 1);
	for (int i = 0; i < s.size(); ++i) {
		o.push_back(s[i]);
	}
	return o;
}

class StringConventer {
public:
	ostringstream o; string r;

	template<class T>
	StringConventer& operator<<(const T& s) {
		o << s;
		return *this;
	}
	/*template<class T>
	StringConventer& operator<<(T s) {
		o << s;
		return *this;
	}*/
	string str() {
		r = o.str();
		o.str("");
		return r;
	}
};
extern StringConventer sc;


class Debuger :public Singleton<Debuger> {
private:
	Debuger() {}
	friend class Singleton<Debuger>;
	friend Debuger& endl(Debuger& d);
	ostringstream o;
public:

	template<class T>
	Debuger& operator()(T s)
	{
		o << s << "\n";
		if (qFlush)flush();
		return*this;
	}

	template<class T>
	Debuger& operator<<(const T& s)
	{
		o << s;
		return *this;
	}

	Debuger& operator<<(Debuger& (__cdecl* const func)(Debuger& d))
	{
		func(*this);
		return *this;
	}

	template<class T>
	Debuger& operator>>(T s)
	{
		o << s;
		return *this;
	}

	//debug("I love {},but {}", "China", vec3(7, 2, 9));
	template<typename T, typename... types>
	Debuger& operator()(const char* format, const T& arg, const types&... alias) {
		while (true) {
			while (*format != '{') {
				if (*format == '\0')return *this;
				o.put(*format); ++format;
			}
			if (*(format + 1) == '}') {
				o << arg;
				operator()(format + 2, alias...);
				return *this;
			}
			else o << '{';
		}
		return *this;
	}
	template<typename T>
	Debuger& operator()(const char* format, const T& arg) {
		while (true) {
			while (*format != '{') {
				if (*format == '\0') {
					if (qFlush)flush();
					return *this;
				}
				o.put(*format); ++format;
			}
			if (*(format + 1) == '}') {
				o << arg;
				format += 2;
				o << format;o << "\n";
				if (qFlush)flush();
				return *this;
			}
			else o << '{';
		}
	}

	Debuger& operator()() {
		o << "\n";
		if (qFlush)flush();
		return*this;
	};

	void debugall(const string& s);
	template<class T>
	void debugseq(const T& v) {
		auto i = v.begin(); auto j = v.end();
		while (i != j) {
			o << *i++ << ", ";
		}
	}
	void debugbyte(const string& s);
	void debugbit(void* ptr, int size) {
		if (size > 63)size = 64;
		llong num = *(llong*)ptr;
		for (int i = size - 1; i > -1; --i) {
			o << int((num & (1ll << i)) != 0);
		}
	}

	void debughex(const string& s);
	void flush() {
		OutputDebugStringA(o.str().c_str());
		o.str("");
	}
	bool qFlush = true;
};

#define debug Singleton<Debuger>::get()

inline Debuger& __cdecl endl(Debuger& de) {
	de.o << '\n';
	if (de.qFlush)de.flush();
	return de;
}

//#define GLCall(x)		clearError();x;ASSERT(glCheckError_(#x,__FILE__,__LINE__));
//#define glCheckError()	glCheckError_("",__FILE__, __LINE__) 
//inline void clearError()
//{
//	while (glGetError());
//}

//GLenum glCheckError_(const char* fun, const char* file, int line);
//
//void glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, void* userParam);
//
