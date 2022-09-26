#pragma once
#include<vector>
#include<string>
#include<unordered_map>
//ע�ⲻҪinclude GL.h
//#include<gl/GL.h>
#include<GLEW/glew.h>
#include<GLFW/glfw3native.h>
#include<GLFW/glfw3.h>


#define ef else if 
#define el else
#define cast(type,p) ((type)p)
#define bitTest(bit ,i) ((bit & (1 << i)) != 0)
#define bitSet(bit , i , val) {if (val)bit = bit | (1 << i);else bit = bit & (~(1 << i));}
#define ASSERT(x,y)		if(!(x)){debug<<y<<endl;__debugbreak();};
#define ASSERT(x)		if(!(x))__debugbreak();
#define assert(x,y)		if(!(x)){debug<<y<<endl;__debugbreak();};
#define assert(x)		if(!(x))__debugbreak();

using llong = long long;
using ullong = unsigned long long;
using ulong = unsigned long;
using uint = unsigned int;
using us = unsigned int;
using std::string;
using std::ostringstream;
using std::vector;
using uid = size_t;
using uchar = unsigned char;
//template<class T, class P>
//using unordered_map = unordered_map<T, P>;

//using winptr = GLFWwindow*;

inline string itos(int i) {
	return std::to_string(i);
}
inline string ftos(float s) {
	return std::to_string(s);
}
inline vector<string> split(const string& s, char delma) {
	int last = 0; vector<string> ret;
	for (int i = 0; i < s.size(); ++i) {
		if (delma == s[i]) {
			ret.push_back(string(s.begin() + last, s.begin() + i));
			last = i + 1;
		}
	}
	ret.push_back(string(s.begin() + last, s.end()));
	return ret;
}

inline string fileName(const string& filePath) {
	size_t pos = filePath.find_last_of('\\');
	if (pos != string::npos) {
		return filePath.substr(pos + 1);
	}
	pos = filePath.find_last_of('/');
	if (pos != string::npos) {
		return filePath.substr(pos + 1);
	}
	return "BAD";
}
