#pragma once
#include"../log/debuger.h"
#include"math_defs.h"
#include"rand.h"
#include"angle.h"

namespace gm {

	template<class T>
	class vector3;
	template<class T>
	class vector2;
	template<class T>
	class vector4;

	template<class T>
	using point = vector3<T>;
	using point2 = vector2<float>;
	using point3 = vector3<float>;

	//内部向量，为ZXY坐标系
	template<class T>
	class vector2 {
	public:
		vector2() {
			x = y = 0;
		}
		vector2(T val) {
			x = y = val;
		}
		vector2(T x, T y) {
			this->x = x; this->y = y;
		}
		vector2(const T* const arr) {
			x = arr[0]; y = arr[1];
		}
		bool operator==(const vector2<T>& v)const {
			return x == v.x && y == v.y;
		}
		//权重化,和为1
		vector2<T> weightlize() {
			T s = x + y;;
			return vector2<T>(x / s, y / s);
		}
		//标准化，单位向量，平方和为1
		vector2<T> normalize() {
			T sqt = sqrt(x * x + y * y);
			return vector2<T>(x / sqt, y / sqt);
		}
		string str()const {
			sc << x << ", " << y;
			return sc.str();
		}

		void set(T val) {
			this->x = val; this->y = val;
		}
		void set(T x, T y) {
			this->x = x; this->y = y;
		}
		void set(const T* const arr) {
			x = arr[0]; y = arr[1];
		}
		T sum()const {
			return x + y;
		}
		T max() {
			return ::max(x, y);
		}
		T min() {
			return::min(x, y);
		}
		T aver() {
			return (x + y) / (T)2;
		}

		T len() const
		{
			return sqrt(x * x + y * y);
		}
		T& operator[](int i) {
			return (&x)[i];
		}
		const T& operator[](int i) const {
			return (&x)[i];
		}
		vector2<T> vct() const {
			return vector2<T>(x, y);
		}
		vector2<T> vec() const {
			return vector2<T>(x, y);
		}
		//绕（0，0）逆时针旋转
		void rot(float deg) {
			double a = radians(deg);
			float tx = x * cos(a) - y * sin(a);
			y = x * sin(a) + y * cos(a);
			x = tx;
		}
		T square_sum()const {
			return x * x + y * y;
		}

		void rand() {
			x = Randf();
			y = Randf();
		}
		void rand(T start, T end) {
			x = Randf(start, end);
			y = Randf(start, end);
		}

		bool operator<(vector2<T>& o) const
		{
			return x < o.x&& y < o.y;
		}

		//向量之间的运算
		vector2<T> operator+(const vector2<T>& p) const
		{
			return vector2(x + p.x, y + p.y);
		}
		vector2<T> operator-(const vector2<T>& p) const
		{
			return vector2(x - p.x, y - p.y);
		}
		vector2<T> operator*(const vector2<T>& p) const
		{
			return vector2(x * p.x, y * p.y);
		}
		vector2<T> operator/(const vector2<T>& p) const
		{
			return vector2(x / p.x, y / p.y);
		}
		vector2<T>& operator+=(const vector2<T>& p)
		{
			x += p.x; y += p.y;
			return *this;
		}
		vector2<T>& operator-=(const vector2<T>& p)
		{
			x -= p.x; y -= p.y;
			return *this;
		}
		vector2<T>& operator*=(const vector2<T>& p)
		{
			x *= p.x; y *= p.y;
			return *this;
		}
		vector2<T>& operator/=(const vector2<T>& p)
		{
			x /= p.x; y /= p.y;
			return *this;
		}

		//向量与标量的运算
		vector2<T> operator+(T t) const
		{
			return vector2<T>(t + x, t + y);
		}
		vector2<T> operator-(T t) const
		{
			return vector2<T>(x - t, t * -t);
		}
		vector2<T> operator*(T t) const
		{
			return vector2<T>(t * x, t * y);
		}
		vector2<T> operator/(T t) const
		{
			return vector2<T>(t / x, t / y);
		}
		vector2<T>& operator+=(T t)
		{
			x = t + x; y = t + y;
			return *this;
		}
		vector2<T>& operator-=(T t)
		{
			x = x - t; y = y - t;
			return *this;
		}
		vector2<T>& operator*=(T t)
		{
			x = t * x; y = t * y;
			return *this;
		}
		vector2<T>& operator/=(T t)
		{
			x = x / t; y = y / t;
			return *this;
		}
		vector2<T> operator-() const
		{
			return vector2<T>(-x, -y);
		}
		T x, y;
	};

	template<class T>
	inline vector2<T> operator+(T t, const vector2<T>& v)
	{
		return vector2<T>(t + v.x, t + v.y);
	}
	template<class T>
	inline vector2<T> operator-(T t, const vector2<T>& v)
	{
		return vector2<T>(t - v.x, t - v.y);
	}
	template<class T>
	inline vector2<T> operator*(T t, const vector2<T>& v)
	{
		return vector2<T>(t * v.x, t * v.y);
	}
	template<class T>
	inline vector2<T> operator/(T t, const vector2<T>& v)
	{
		return vector2<T>(t / v.x, t / v.y);
	}

	template<class T>
	class vector3 {
	public:
		vector3() {
			x = y = z = 0;
		}
		vector3(T val) {
			x = y = z = val;
		}
		vector3(T x, T y, T z) {
			this->x = x; this->y = y; this->z = z;
		}
		vector3(const vector2<T>& v, T z) {
			this->x = v.x; this->y = v.y; this->z = z;
		}

		vector3(const T* const arr) {
			this->x = arr[0]; this->y = arr[1]; this->z = arr[2];
		}

		vector3(const vector4<T>& v) {
			this->x = v.x; this->y = v.y; this->z = v.z;
		}

		bool operator==(const vector3<T>& v)const {
			return x == v.x && y == v.y && z == v.z;
		}

		void rand() {
			x = Randf();
			y = Randf();
			z = Randf();
		}
		void rand(T start, T end) {
			x = Randf(start, end);
			y = Randf(start, end);
			z = Randf(start, end);
		}

		//权重化,和为1
		vector3<T> weightlize() const {
			T s = 1 / (x + y + z);
			return vector3<T>(x * s, y * s, z * s);

		}
		//标准化，单位向量，平方和为1
		vector3<T> normalize() const {
			T sqt = 1 / sqrt(x * x + y * y + z * z);
			return (*this) * sqt;
		}

		T sum()const {
			return x + y + z;
		}
		T max() const {
			return max(x, max(y, z));
		}
		T min()const {
			return::min(x, min(y, z));
		}
		T aver()const {
			return (x + y + z) / (T)3;
		}
		void set(T x, T y, T z) {
			this->x = x; this->y = y; this->z = z;
		}
		void set(const vector2<T>& v, T z) {
			this->x = v.x; this->y = v.y; this->z = z;
		}
		void set(const vector4<T>& v) {
			this->x = v.x; this->y = v.y; this->z = v.z;
		}
		void set(const T* const arr) {
			this->x = arr[0]; this->y = arr[1]; this->z = arr[2];
		}
		string str()const {
			sc << x << ", " << y << ", " << z;
			return sc.str();
		}

		T& operator[](int i) {
			return (&x)[i];
		}
		const T& operator[](int i) const {
			return (&x)[i];
		}
		T len() const
		{
			return sqrt(x * x + y * y + z * z);
		}
		T square_sum()const {
			return x * x + y * y + z * z;
		}

		bool operator<(vector3<T>& o) const
		{
			return x < o.x&& y < o.y&& z < o.z;
		}

		//向量之间的运算
		vector3<T> operator+(const vector3<T>& p) const
		{
			return vector3<T>(x + p.x, y + p.y, z + p.z);
		}
		vector3<T> operator-(const vector3<T>& p) const
		{
			return vector3<T>(x - p.x, y - p.y, z - p.z);
		}
		vector3<T> operator*(const vector3<T>& p) const
		{
			return vector3<T>(x * p.x, y * p.y, z * p.z);
		}
		vector3<T> operator/(const vector3<T>& p) const
		{
			return vector3<T>(x / p.x, y / p.y, z / p.z);
		}
		vector3<T>& operator+=(const vector3<T>& p)
		{
			x += p.x; y += p.y;  z += p.z;
			return *this;
		}
		vector3<T>& operator-=(const vector3<T>& p)
		{
			x -= p.x; y -= p.y; z -= p.z;
			return *this;
		}
		vector3<T>& operator*=(const vector3<T>& p)
		{
			x *= p.x; y *= p.y; z *= p.z;
			return *this;
		}
		vector3<T>& operator/=(const vector3<T>& p)
		{
			x /= p.x; y /= p.y; z /= p.z;
			return *this;
		}

		//向量与标量的运算
		vector3<T> operator+(T t) const
		{
			return vector3<T>(t + x, t + y, t + z);
		}
		vector3<T> operator-(T t) const
		{
			return vector3<T>(x - t, y - t, t - z);
		}
		vector3<T> operator*(T t) const
		{
			return vector3<T>(t * x, t * y, t * z);
		}
		vector3<T> operator/(T t) const
		{
			return vector3<T>(x / t, y / t, z / t);
		}
		vector3<T>& operator+=(T t)
		{
			x += t; y += t; z += t;
			return *this;
		}
		vector3<T>& operator-=(T t)
		{
			x -= t; y -= t; z -= t;
			return *this;
		}
		vector3<T>& operator*=(T t)
		{
			x *= t; y *= t; z *= t;
			return *this;
		}
		vector3<T>& operator/=(T t)
		{
			x /= t; y /= t; z /= t;
			return *this;
		}
		vector3<T> operator-() const
		{
			return vector3<T>(-x, -y, -z);
		}
		T x, y, z;
	};
	template<class T>
	vector3<T> operator+(T t, const vector3<T>& v)
	{
		return vector3<T>(t + v.x, t + v.y, t + v.z);
	}
	template<class T>
	vector3<T> operator-(T t, const vector3<T>& v)
	{
		return vector3<T>(t - v.x, t - v.y, t - v.z);
	}
	template<class T>
	vector3<T> operator*(T t, const vector3<T>& v)
	{
		return vector3<T>(t * v.x, t * v.y, t * v.z);
	}
	template<class T>
	vector3<T> operator/(T t, const vector3<T>& v)
	{
		return vector3<T>(t / v.x, t / v.y, t / v.z);
	}

	template<class T>
	class vector4 {
	public:
		vector4() {
			x = y = z = w = 0;
		}
		vector4(T val) {
			x = y = z = w = val;
		}
		vector4(T x, T y, T z, T w = 0.0) {
			this->x = x; this->y = y; this->z = z; this->w = w;
		}
		vector4(const vector2<T>& v, T z, T w = 0.0) {
			this->x = v.x; this->y = v.y; this->z = z; this->w = w;
		}
		vector4(const vector3<T>& v, T w = 0.0) {
			this->x = v.x; this->y = v.y; this->z = v.z; this->w = w;
		}
		vector4(const T* const arr) {
			this->x = arr[0]; this->y = arr[1]; this->z = arr[2]; this->w = arr[3];
		}

		bool operator==(const vector4<T>& v)const {
			return x == v.x && y == v.y && z == v.z && w == v.w;
		}
		string str()const {
			sc << x << ", " << y << ", " << z << ", " << w;
			return sc.str();
		}

		T& operator[](int i) {
			return (&x)[i];
		}
		const T& operator[](int i) const {
			return (&x)[i];
		}
		void set(T x, T y, T z, T w) {
			this->x = x; this->y = y; this->z = z; this->w = w;
		}
		void set(const vector2<T>& v, T z, T w = 1) {
			this->x = v.x; this->y = v.y; this->z = z; this->w = w;
		}
		void set(const vector3<T>& v, T w = 1) {
			this->x = v.x; this->y = v.y; this->z = v.z; this->w = w;
		}

		void set(const T* const arr) {
			this->x = arr[0]; this->y = arr[1]; this->z = arr[2]; this->w = arr[3];
		}
		T sum()const {
			return x + y + z + w;
		}
		T max() {
			return max(max(x, w), max(y, z));
		}
		T min() {
			return::min(min(x, w), min(y, z));
		}
		T aver() {
			return (x + y + z + w) / (T)4;
		}
		T square_sum()const {
			return x * x + y * y + z * z + w * w;
		}
		//权重化，和为1,
		vector4<T> weightlize() {
			T sm = (x + y + z + w);
			if (abs(sm) < 0.0000001)return { 1,0,0,0 };
			sm = 1 / sm;
			return vector4<T>(x * sm, y * sm, z * sm, w * sm);
		}
		//标准化，单位向量，平方和为1
		vector4<T> normalize() {
			T sqt = 1 / sqrt(x * x + y * y + z * z + w * w);
			return vector4<T>(x * sqt, y * sqt, z * sqt, w * sqt);
		}

		void rand() {
			x = Randf();
			y = Randf();
			z = Randf();
			w = Randf();
		}
		void rand(T start, T end) {
			x = Randf(start, end);
			y = Randf(start, end);
			z = Randf(start, end);
			w = Randf(start, end);
		}
		vector4<T> tvec() {
			return vector4<T>(y, z, x, w);
		}
		T len() const
		{
			return sqrt(x * x + y * y + z * z + w * w);
		}

		bool operator<(vector4<T>& o) const
		{
			return x < o.x&& y < o.y&& z < o.z&& w < o.w;
		}

		//向量之间的运算
		vector4<T> operator+(const vector4<T>& p) const
		{
			return vector4<T>(x + p.x, y + p.y, z + p.z, w + p.w);
		}
		vector4<T> operator-(const vector4<T>& p) const
		{
			return vector4<T>(x - p.x, y - p.y, z - p.z, w - p.w);
		}
		vector4<T> operator*(const vector4<T>& p) const
		{
			return vector4<T>(x * p.x, y * p.y, z * p.z, w * p.w);
		}
		vector4<T> operator/(const vector4<T>& p) const
		{
			return vector4<T>(x / p.x, y / p.y, z / p.z, w / p.w);
		}
		vector4<T>& operator+=(const vector4<T>& p)
		{
			x += p.x; y += p.y;  z += p.z; w += p.w;
			return *this;
		}
		vector4<T>& operator-=(const vector4<T>& p)
		{
			x -= p.x; y -= p.y; z -= p.z; w -= p.w;
			return *this;
		}
		vector4<T>& operator*=(const vector4<T>& p)
		{
			x *= p.x; y *= p.y; z *= p.z; w *= p.w;
			return *this;
		}
		vector4<T>& operator/=(const vector4<T>& p)
		{
			x /= p.x; y /= p.y; z /= p.z; w /= p.w;
			return *this;
		}

		//向量与标量的运算
		vector4<T> operator+(T t) const
		{
			return vector4<T>(t + x, t + y, t + z, w + t);
		}
		vector4<T> operator-(T t) const
		{
			return vector4<T>(x - t, y - t, t - z, w - t);
		}
		vector4<T> operator*(T t) const
		{
			return vector4<T>(t * x, t * y, t * z, w * t);
		}
		vector4<T> operator/(T t) const
		{
			return vector4<T>(x / t, y / t, z / t, w / t);
		}
		vector4<T>& operator+=(T t)
		{
			x += t; y += t; z += t; w += t;
			return *this;
		}
		vector4<T>& operator-=(T t)
		{
			x -= t; y -= t; z -= t; w -= t;
			return *this;
		}
		vector4<T>& operator*=(T t)
		{
			x *= t; y *= t; z *= t; w *= t;
			return *this;
		}
		vector4<T>& operator/=(T t)
		{
			x /= t; y /= t; z /= t; w /= t;
			return *this;
		}
		vector4<T> operator-() const
		{
			return vector4<T>(-x, -y, -z, -w);
		}
		T x, y, z, w;
	};
	template<class T>
	vector4<T>& operator+(T t, const vector4<T>& v)
	{
		return vector4<T>(t + v.x, t + v.y, t + v.z, v.w + t);
	}
	template<class T>
	vector4<T>& operator-(T t, const vector4<T>& v)
	{
		return vector4<T>(t - v.x, t - v.y, t - v.z, t - v.w);
	}
	template<class T>
	vector4<T>& operator*(T t, const vector4<T>& v)
	{
		return vector4<T>(t * v.x, t * v.y, t * v.z, v.w * t);
	}
	template<class T>
	vector4<T>& operator/(T t, const vector4<T>& v)
	{
		return vector4<T>(t / v.x, t / v.y, t / v.z, t / v.w);
	}


	using uchar = unsigned char;
	using vec2 = vector2<float>;
	using vec3 = vector3<float>;
	using vec4 = vector4<float>;
	using ivec2 = vector2<int>;
	using ivec3 = vector3<int>;
	using ivec4 = vector4<int>;
	using cvec2 = vector2<uchar>;
	using cvec3 = vector3<uchar>;
	using cvec4 = vector4<uchar>;


	using pt = vec3;
	using pt2 = vec2;
	using pt3 = vec3;

	template<class T>
	inline T dot(const vector2<T>& v1, const vector2<T>& v2) {
		return v1.x * v2.x + v1.y * v2.y;
	}

	template<class T>
	inline T dot(const vector3<T>& v1, const vector3<T>& v2) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	template<class T>
	inline T dot(const vector4<T>& v1, const vector4<T>& v2) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
	}

	template<class T>
	vector3<T> cross(const vector3<T>& x, const vector3<T>& y) {
		return vector3<T>(
			x.y * y.z - y.y * x.z,
			x.z * y.x - y.z * x.x,
			x.x * y.y - y.x * x.y);
	}

	template<class T>
	vector3<T> cross(const vector3<T>& x, const vector3<T>& y, const vector3<T>& z) {
		return cross(y - x, z - x);
	}

	template<class T>
	vector4<T> cross(const vector4<T>& x, const vector4<T>& y) {
		return  vector4<T>(
			x.w * y.w - x.x * y.x - x.y * y.y - x.z * y.z,
			x.w * y.x + x.x * y.w + x.y * y.z - x.z * y.y,
			x.w * y.y + x.y * y.w + x.z * y.x - x.x * y.z,
			x.w * y.z + x.z * y.w + x.x * y.y - x.y * y.x);
	}

	template<class T>
	std::ostream& operator<<(std::ostream& o, const vector2<T>& m) {
		return o << m.str();
	}
	template<class T>
	std::ostream& operator<<(std::ostream& o, const vector3<T>& m) {
		return o << m.str();
	}
	template<class T>
	std::ostream& operator<<(std::ostream& o, const vector4<T>& m) {
		return o << m.str();
	}
}

////表示层的向量，内部存储为XYZ坐标系
//template<class T>
//class tvector3
//{
//public:
//	tvector3() {
//		x = y = z = 0;
//	}
//	tvector3(T x, T y, T z) {
//		this->x = x; this->y = y; this->z = z;
//	}
//	tvector3(const vector3<T>& v) {
//		this->x = v.x; this->y = v.y; this->z = v.z;
//	}
//	tvector3(const T* v) {
//		this->x = v[0]; this->y = v[1]; this->z = v[2];
//	}
//	vector3<T> vec() const {
//		return vector3<T>(y, z, x);
//	}
//	string str() const
//	{
//		return std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z);
//	}
//	T x, y, z;
//};
//
//template<class T>
//class tvector4
//{
//public:
//	tvector4() {
//		x = y = z = w = 0;
//	}
//	tvector4(const vector4<T>& v) {
//		x = v.y; y = v.z; z = v.x; w = v.w;
//	}
//	vector4<T> vec() const {
//		return vector4<T>(y, z, x, w);
//	}
//	string str() const
//	{
//		return to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ", " + to_string(w);
//	}
//	T x, y, z, w;
//};