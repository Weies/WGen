#pragma once

#define M_PI 3.14159265358979323846   // pi
#define PI M_PI
#define M_E 2.718281828459045235360	//e
#include<cmath>

namespace gm {

	template<class T, class P>
	T lerp(const T& v1, const T& v2, P v2_coff) {
		return v1 + (v2 - v1) * v2_coff;
	}

}
