#pragma once
#include"../base/global_values.h"
#include<functional>
#include<unordered_map>
using namespace globals;
#define timer timor.push

inline double updateTime() {
	double time = ::clock();
	frameTime = time - clockTime;
	gameTime += frameTime;
	clockTime = ::clock();
	return gameTime;
}

struct TimerEvent;
using te = TimerEvent;
// 时间函数返回true表示执行完成，将被移除执行队列


using timefun = function<bool(TimerEvent&)>;
using timefunc = function<void()>;
using timef = function<bool()>;

struct TimerEvent {
	TimerEvent() :bgTime(0), func(0) {}
	TimerEvent(double delay, const timef& fun) :delay(delay), bgTime(delay + updateTime()) {
		func = [fun](TimerEvent& e)->bool {return fun(); };
	}
	TimerEvent(double delay, const timefun& fun) :delay(delay), bgTime(delay + updateTime()), func(fun) {}
	TimerEvent(double delay, const timefunc& fun) :delay(delay), bgTime(delay + updateTime()) {
		func = [fun](TimerEvent& e)->bool {fun(); return true; };
	}

	void setDelay(double delay) {
		this->delay = delay;
		bgTime = delay + updateTime();
	}

	bool exec() {
		return func(*this);
	}

	double  delay;
	double	bgTime;
	timefun	func;
};


// 游戏时间管理类
class Timor {
public:
	int								hands = 1;
	unordered_map<int, TimerEvent>	te;
	vector<int>						remove;

	void exec() {
		for (auto& y : te) {
			if (y.second.bgTime > gameTime)continue;
			if (y.second.exec())remove.push_back(y.first);
			else y.second.bgTime = y.second.bgTime + y.second.delay;
		}
		for (auto& y : remove) {
			te.erase(y);
		}
		remove.resize(0);
	}

	int push(const TimerEvent& e) {
		te.insert({ hands,e });
		return hands++;
	}
	int push(double delay, function<bool(TimerEvent&)> fun) {
		te.insert({ hands,TimerEvent(delay,fun) });
		return hands++;
	}
	int push(int delay, function<void()> fun) {
		te.insert({ hands,TimerEvent((double)delay,fun) });
		return hands++;
	}
	int push(double delay, function<bool()> fun) {
		te.insert({ hands,TimerEvent(delay,fun) });
		return hands++;
	}

	TimerEvent& query(int timerHandle) {
		if (te.find(timerHandle) != te.end())
			return te[timerHandle];
	}
	bool stop(int timerHandle) {
		remove.push_back(timerHandle);
		return te.find(timerHandle) != te.end();
	}
	bool delay(int timerHandle, double delay_time) {
		auto it = te.find(timerHandle);
		if (it == te.end())return false;
		it->second.bgTime += delay_time;
	}
	void updateTime() {
		::updateTime();
	}


	//map<int, TimerEvent> te;
};

___global(Timor, timor);
#define timor _get_timor()

//class Timer {
//public:
//	Timer() {}
//	Timer(int dely, function<void(void)> fun)
//	{
//		delay = dely;
//		func = fun;
//		start();
//	}
//
//	void stop()
//	{
//		run = false;
//	}
//	static void startTimer(int dely, function<void(void)> fun)
//	{
//		thread td([=]() {
//			while (timerAble)
//			{
//				this_thread::sleep_for(chrono::milliseconds(dely));
//				fun();
//			}
//			});
//		td.detach();
//	}
//	void once()
//	{
//		if (timerAble)
//		{
//			thread td([=]() {
//				this_thread::sleep_for(chrono::milliseconds(delay));
//				func();
//				});
//			td.detach();
//		}
//	}
//	static void singleTimer(int dely, function<void(void)> fun)
//	{
//		if (timerAble)
//		{
//			thread td([=]() {
//				this_thread::sleep_for(chrono::milliseconds(dely));
//				fun();
//				});
//			td.detach();
//		}
//	}
//	bool run = false;
//	int delay = 100;
//	function<void(void)> func = 0;
//private:
//	void start()
//	{
//		run = true;
//		thread td([=]() {
//			while (run && timerAble)
//			{
//				this_thread::sleep_for(chrono::milliseconds(delay));
//				func();
//			}
//			});
//		td.detach();
//	}
//};
