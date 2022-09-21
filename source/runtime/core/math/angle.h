#pragma once

namespace gm
{
	template<class T>
	T radians(T deg) {
		return deg * M_PI / 180.0;
	}

	template<class T>
	T degree(T rad) {
		return 180.0 * rad / M_PI;
	}

	template<class T>class TAngle {
	public:
		T value;
		TAngle() = default;
		TAngle(T value) :value(value) {}

		virtual T deg() { return value; };
		virtual T rad() { return value; };
		virtual T degree() { return deg(); };
		virtual T radian() { return rad(); }
		operator T& () { return value; }
	};

	template<class T>class TRadian;

	template<class T>
	class TDegree : public TAngle<T>
	{
	public:
		TDegree() = default;
		TDegree(T degree) :TAngle<T>(degree) {}
		TDegree(TRadian<T> radian) : TAngle<T>(radian.deg()) {}
		T deg()override { return TAngle<T>::value; };
		T rad()override { return PI / (T)180 * TAngle<T>::value; }
	};


	template<class T>
	class TRadian :public TAngle<T> {
	public:
		TRadian() = default;
		TRadian(T radians) :TAngle<T>(radians) {}
		TRadian(TDegree<T> degree) :TAngle<T>(degree.rad()) {}
		T deg()override { return (T)180 / PI * TAngle<T>::value; };
		T rad()override { return TAngle<T>::value; };
	};

	using Angle = TAngle<float>;
	using Radian = TRadian<float>;
	using Degree = TDegree<float>;
}

