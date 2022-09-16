#pragma once

#define M_PI 3.14159265358979323846   // pi
#define PI M_PI
#include<cmath>

namespace gm {

	template<class T>
	T radians(T deg) {
		return deg * M_PI / 180.0;
	}

	template<class T>
	T degree(T rad) {
		return 180.0 * rad / M_PI;
	}

	template<class T, class P>
	T lerp(const T& v1, const T& v2, P v2_coff) {
		return v1 + (v2 - v1) * v2_coff;
	}

}
