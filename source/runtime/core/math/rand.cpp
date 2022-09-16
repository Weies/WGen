#include"rand.h"

#define abs(x) ((x)<0?(-(x)):x)

namespace gm {
	ll seed = 155454417;
	ll out = 544189413;
	ll MAX_RAND = 32367;


	int Rand()
	{
		seed = seed % (out + 7) + out % 107252;
		out = out % seed + seed % 12451472;
		return (out % seed) % MAX_RAND;
	}

	void Srand(int i)
	{
		seed = i; out = i + 115477;
		out = Rand() + 44781545; seed = Rand() + 1279123147;
	}

	int Rand(int start, int end)
	{
		if (end - start < 1)return -1;
		seed = seed % (out + 7) + seed % 107247 + out % 107252;
		out = out % seed + seed % 12451472;
		return start + (out % seed + seed * 12147ll + 51894984147487ll) % (end - start);
	}
	float Randf(float start, float end)
	{
		if (end < start)return -1.0f;
		seed = seed % (out + 7) + seed % 9107178247 + out % 599777107252;
		out = out % seed + seed % 31124514472;
		return start + abs(
			((out % seed) * 7478845157ll + seed * 4712414147ll)
			% 71716145418484987ll * double(end - start)
		)
			/ 71716145418484987ll;
	}

}
