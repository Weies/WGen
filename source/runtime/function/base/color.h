#pragma once
#include"core/math/math_include.h"
using namespace gm;

class Color {
public:
	Color() {}
	Color(float rr, float gg, float bb, float aa = 1) {
		r = rr / 255; g = gg / 255; b = bb / 255;  a = aa;
	}
	Color(const vec3& v) {
		r = v.x; g = v.y; b = v.z; a = 1.0;
	}
	Color(const vec4& v) {
		r = v.x; g = v.y; b = v.z; a = v.w;
	}
	Color(float gray) {
		r = g = b = gray / 255; a = 1.0;
	}
	void set(float rr, float gg, float bb, float aa = 1) {
		r = rr / 255; g = gg / 255; b = bb / 255;  a = aa;
	}
	void set(float gray) {
		r = g = b = gray / 255; a = 1.0;
	}
	Color setAlpha(float a) {
		Color co = *this; co.a = a;
		return co;
	}
	static Color normalColor(float rr, float gg, float bb, float aa = 1)
	{
		Color co;
		co.r = rr;
		co.g = gg;
		co.b = bb;
		co.a = aa;
		return co;
	}
	static Color getRandColor()
	{
		return normalColor(Randf(0, 2), Randf(0, 2), Randf(0, 2));
	}
	static Color getRandColor(int seed) {
		Srand(seed);
		return normalColor(Randf(0, 2), Randf(0, 2), Randf(0, 2));
	}
	string toString() const
	{
		ostringstream o;
		o << "r=" << r << ",g=" << g << ",b=" << b << ",a=" << a << endl;
		return o.str();
	}
	void setRandColor()
	{
		r = Rand() % 255 / 255.0;
		g = Rand() % 255 / 255.0;
		b = Rand() % 255 / 255.0;
	}

	void operator=(Color co)
	{
		r = co.r; b = co.b;
		g = co.g; a = co.a;
	}
	gm::vec3 vec3() const {
		return gm::vec3(r, g, b);
	}
	gm::vec4 vec4() const {
		return gm::vec4(r, g, b, a);
	}

	float r; float g; float b; float a = 1.0f;
};

