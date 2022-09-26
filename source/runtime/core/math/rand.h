#pragma once

using llong = long long;

namespace gm {
	int Rand();

	void Srand(int i);

	// 生成[start,end)之间的整数
	int Rand(int start, int end);

	float Randf(float start, float end);


	inline float Randf()//得到[-1,1]之间的浮点数
	{
		return Randf(-1.0f, 1.0f);
	}
}

