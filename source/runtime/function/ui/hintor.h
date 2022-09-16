#pragma once
#include"font.h"
#include"painter.h"

class Hintor {
public:
	struct hinttext {
		float x, y;
		double time;
		string s;
	};
	unordered_map<int, hinttext>	hints;
	vector<int>						eras;
	int								handle = 0;

	bool erase(int hand) {
		eras.push_back(hand);
		return hints.find(hand) != hints.end();
	}
	int push(float x, float y, const string& str, double time = -1) {
		if (time > 0)time += gameTime;
		hints.insert({ ++handle, { x, y,time, str } });
		return handle;
	}

	void renderHint() {
		for (auto& x : hints) {
			auto& y = x.second;
			if (y.time > gameTime || y.time < 0)
				drawString(y.x, y.y, y.s);
			else eras.push_back(x.first);
		}
		for (auto& y : eras) {
			hints.erase(y);
		}
		eras.resize(0);
	}


};

___global(Hintor, hintor);
#define hintor _get_hintor()
inline int addHint(float x, float y, const string& str, double time = -1) {
	return hintor.push(x, y, str, time);
}