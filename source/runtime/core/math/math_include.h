#pragma once
#include"matrix_operation.h"
#include"mat_generate.h"
#include"rand.h"

namespace gm {

	//使用弧度
	inline vec3 eulerDir(float pitch, float yaw) {
		return vec3(sin(yaw) * cos(pitch), sin(pitch), cos(yaw) * cos(pitch));
	}

	inline vec2 PitchYaw(const vec3& v) {
		return vec2(asin(v.y), atan2(v.x, v.z));
	}
	// v需要已经normalize
	inline qua dirvQua(const vec3& v) {
		vec2 t = PitchYaw(v);
		return qua(vec3(1, 0, 0), -t.x) * qua(vec3(0, 1, 0), t.y);
	}

}
