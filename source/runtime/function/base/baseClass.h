#pragma once
#include"core/log/debuger.h"
#include"core/math/math_include.h"
using namespace gm;


class Line {
public:
	Line() {}

	Line(int x , int y , int a , int b)
	{
		p1.x = x; p1.y = y;
		p2.x = a; p2.y = b;
		if (x || y || a || b)need = true;
	}
	bool need = false;
	point<float> p1;
	point<float> p2;
};

struct CameraBlock {
	mat4 mPVTransform;
	vec3 mCameraPosition;
};
