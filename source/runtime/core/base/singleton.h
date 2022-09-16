#pragma once

template<class T>
class Singleton {
public:
	static T& get() {
		static T inst;
		return inst;
	}
	//����������Ϊ��
	virtual ~Singleton(){}

protected:
	Singleton() {}
	Singleton& operator=(const Singleton& sgt) = delete;
	Singleton(const Singleton<T>& sgt) = delete;
};