#pragma once

template<class T>
class Singleton {
public:
	static T& get() {
		static T inst;
		return inst;
	}
	//做父类析构为虚
	virtual ~Singleton(){}

protected:
	Singleton() {}
	Singleton& operator=(const Singleton& sgt) = delete;
	Singleton(const Singleton<T>& sgt) = delete;
};