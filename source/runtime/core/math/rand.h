#pragma once

using llong = long long;

namespace gm {
	int Rand();

	void Srand(int i);

	// ����[start,end)֮�������
	int Rand(int start, int end);

	float Randf(float start, float end);


	inline float Randf()//�õ�[-1,1]֮��ĸ�����
	{
		return Randf(-1.0f, 1.0f);
	}
}

