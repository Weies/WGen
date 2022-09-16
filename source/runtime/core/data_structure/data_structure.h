#pragma once
#include"../log/exception.h"


template<class T , int capacity>
class Array {
public:
	Array() {
		_size = 0;
		//arr = new T[capacity];
	}
	void push_back(const T& a) {
		arr[_size] = a;
		++_size;
		if (_size > capacity)excep(WERROR_BAD_POINTER , "Array over flow;");
	}
	void pop_back() {
		--_size;
	}
	T& back() {
		return arr[_size - 1];
	}
	T& last() {
		return arr[_size++];
	}
	const T& back()const {
		return arr[_size - 1];
	}
	const T& operator[](int i)const {
		return arr[i];
	}
	T& operator[](int i)
	{
		return arr[i];
	}
	void resize(uint new_size) {
		if (new_size > capacity)excep(WERROR_ARGUMENT , "Index out of range;");
		_size = new_size;
	}
	size_t size() const {
		return _size;
	}
	void swap(Array<T , capacity>& otr) {
		std::swap(_size , otr._size);
		T tp[capacity]; const int sz = sizeof(T) * capacity;
		memcpy(tp, arr, sz);
		memcpy(arr, otr.arr, sz);
		memcpy(otr.arr, tp, sz);
		//std::swap(arr , otr.arr);
	}
private:
	int _size;//T* arr;
	T arr[capacity];
};