#pragma once
#include"vector.h"

namespace gm {
	//都是列向量
	template<class T>
	struct mat2x2 {
	public:
		mat2x2() {}
		//对角线设置该元素
		mat2x2(T val) {
			v0.x = val; v1.y = val;
		}
		mat2x2(T x1, T y1, T x2, T y2) {
			v0.set(x1, y1); v1.set(x2, y2);
		}
		mat2x2(const vector2<T>& ve) {
			v0[0] = ve.x;
			v1[1] = ve.y;
		}
		mat2x2(const vector2<T>& p1, const vector2<T>& p2) {
			v0 = p1; v1 = p2;
		}
		mat2x2<T> t() const {
			return mat2x2<T>(v0.x, v1.x,
				v0.y, v1.y);
		}
		mat2x2<T> operator-() const {
			return mat2x2<T>(-v0, -v1);
		}
		vector2<T>& operator[](int i) {
			return (&v0)[i];
		}
		const vector2<T>& operator[](int i) const {
			return (&v0)[i];
		}
		string str()const {
			mat2x2<T> m = this->t();
			sc << m.v0 << '\n' << m.v1;
			return sc.str();
		}
		vec2 v0; vec2 v1;
	};

	template<class T>
	struct mat4x4;

	template<class T>
	struct mat3x3 {
	public:
		mat3x3() {}
		//对角线设置该元素
		mat3x3(T val) {
			v0.x = val; v1.y = val; v2.z = val;
		}
		mat3x3(T x0, T y0, T z0, T x1, T y1, T z1, T x2, T y2, T z2) {
			v0.set(x0, y0, z0); v1.set(x1, y1, z1); v2.set(x2, y2, z2);
		}
		mat3x3(const mat4x4<T>& m) {
			v0 = m[0]; v1 = m[1]; v2 = m[2];
		}
		mat3x3(const vector3<T>& v0, const vector3<T>& v1, const vector3<T>& v2) {
			this->v0 = v0; this->v1 = v1; this->v2 = v2;
		}
		mat3x3(const vector3<T>& ve) {
			v0[0] = ve.x;
			v1[1] = ve.y;
			v2[2] = ve.z;
		}
		mat3x3<T> t() const {
			return mat3x3<T>(v0.x, v1.x, v2.x,
				v0.y, v1.y, v2.y,
				v0.z, v1.z, v2.z);
		}
		mat3x3 operator-() const {
			return mat3x3(-v0, -v1, -v2);
		}
		vector3<T>& operator[](int i) {
			return (&v0)[i];
		}
		const vector3<T>& operator[](int i) const {
			return (&v0)[i];
		}
		string str()const {
			mat3x3<T> m = this->t();
			sc << m.v0 << '\n' << m.v1 << '\n' << m.v2;
			return sc.str();
		}
		vector3<T> v0; vector3<T> v1; vector3<T> v2;
	};

	template<class T>
	struct quaternion;

	struct SQT;

	template<class T>
	struct mat4x4 {
	public:
		mat4x4() {}
		//对角线设置该元素
		mat4x4(T val) {
			v0.x = val; v1.y = val; v2.z = val; v3.w = val;
		}
		mat4x4(const mat3x3<T>& m, T const& val = 0) {
			v0 = m[0]; v1 = m[1]; v2 = m[2]; v3.w = val;
		}
		mat4x4(const mat3x3<T>& m, const vector4<T>& vv) {
			v0 = m[0]; v1 = m[1]; v2 = m[2]; v3 = vv;
		}
		// 注意是依次填入四个列向量
		mat4x4(T x0, T y0, T z0, T w0, T x1, T y1, T z1, T w1, T x2, T y2, T z2, T w2, T x3, T y3, T z3, T w3) {
			v0.set(x0, y0, z0, w0); v1.set(x1, y1, z1, w1);
			v2.set(x2, y2, z2, w2); v3.set(x3, y3, z3, w3);
		}
		mat4x4(const vector4<T>& p0, const vector4<T>& p1, const vector4<T>& p2, const vector4<T>& p3) {
			v0 = p0; v1 = p1; v2 = p2; v3 = p3;
		}

		mat4x4(const vector4<T>& ve) {
			v0[0] = ve.x;
			v1[1] = ve.y;
			v2[2] = ve.z;
			v3[3] = ve.w;
		}

		mat4x4(const quaternion<T>& q) {
			(*this) = q.mat4();
		}

		mat4x4(const SQT& q);

		vec3 p()const {
			return vec3(v3) / v3[3];
		}
		mat4x4<T> t() const {
			return mat4x4<T>(
				v0.x, v1.x, v2.x, v3.x,
				v0.y, v1.y, v2.y, v3.y,
				v0.z, v1.z, v2.z, v3.z,
				v0.w, v1.w, v2.w, v3.w);
		}
		mat4x4<T> operator-() {
			return mat4x4<T>(-v0, -v1, -v2, -v3);
		}
		vector4<T>& operator[](int i) {
			return (&v0)[i];
		}
		const vector4<T>& operator[](int i) const {
			return (&v0)[i];
		}
		string str()const {
			mat4x4<T> m = this->t();
			sc << m.v0 << '\n' << m.v1 << '\n' << m.v2 << '\n' << m.v3;
			return sc.str();
		}
		vector4<T> v0; vector4<T> v1; vector4<T> v2; vector4<T> v3;
	};

	template<class T, int n_component>
	struct vec {
	public:
		vec() {}
		T& operator[](uint i) {
			return v[i];
		}
		const T& operator[](uint i) const {
			return v[i];
		}
		T v[n_component];
	};


	//按行索引
	template<class T>
	struct Mat {
	public:
		Mat() {}
		Mat(uint row, uint col) {
			rows = row; cols = col;
			v = new T[row * col];
		}

		Mat(uint row, uint col, void* const arr) {
			v = (T*)arr; rows = row; cols = col;
		}

		Mat(uint row, uint col, const uchar* const arr) {
			v = (T*)arr; rows = row; cols = col;
		}

		void set(const T& value) {
			const int s = rows * cols;
			for (int i = 0; i < s; ++i) {
				v[i] = value;
			}
		}

		void set(const void* const arr) {
			const int s = rows * cols;
			for (int i = 0; i < s; ++i) {
				v[i] = arr[i];
			}
		}

		T& val() {
			return v[0];
		}

		Mat<T>& operator=(const Mat<T>& m) {
			delete[] v;
			v = m.v;
			rows = m.rows; cols = m.cols;
			return*this;
		}

		void swap(Mat<T>& otr) {
			std::swap(v, otr.v);
			std::swap(rows, otr.rows);
			std::swap(cols, otr.cols);
		}

		Mat<T> operator[](uint i) {
			return Mat<T>(cols, 1, v + i * cols);
		}


		Mat<T>& operator=(const T& val) {
			v[0] = val;
			return *this;
		}

		T& operator()(uint i, uint j) {
			return v[i * cols + j];
		}

		const T& operator()(uint i, uint j) const {
			return v[i * cols + j];
		}

		Mat<T> t() {
			Mat<T> tt(cols, rows);
			for (int i = 0; i < cols; ++i) {
				for (int j = 0; j < rows; ++j) {
					tt.v[i * rows + j] = v[j * cols + i];
				}
			}
			return tt;
		}

		T* v = 0;
		uint rows; uint cols;
	};

	//四元数不保证单位长度，请务必输入单位化的数据
	template<class T>
	struct quaternion {
	public:
		quaternion() :x(0), y(0), z(0), w(1) {}
		quaternion(T x, T y, T z, T w) {
			this->x = x; this->y = y; this->z = z; this->w = w;
		}
		quaternion(const vector4<T>& v) {
			x = v.x; y = v.y; z = v.z; w = v.w;
		}
		quaternion(const vector3<T>& v) {
			x = v.x; y = v.y; z = v.z; w = 0.0f;
		}
		quaternion(vector3<T> axis, T const& rad, bool norm = false) {
			if (norm) axis = axis.normalize();
			w = cos(rad / 2.0); T si = sin(rad / 2.0);
			x = axis.x * si; y = axis.y * si; z = axis.z * si;
		}
		quaternion(const mat3x3<T>& m) {
			T t = m[0][0] + m[1][1] + m[2][2];
			if (t > 0) {
				T s = sqrt(t + 1);
				w = s * 0.5;
				s = 0.5 / s;
				x = (m[1][2] - m[2][1]) * s;
				y = (m[2][0] - m[0][2]) * s;
				z = (m[0][1] - m[1][0]) * s;
			}
			else
			{
				int i = 0;
				if (m[1][1] > m[0][0])i = 1;
				if (m[2][2] > m[i][i])i = 2;
				const int next[3] = { 1,2,0 };
				int j = next[i]; int k = next[j];
				T s = sqrt(m[i][i] - m[j][j] - m[k][k] + 1);
				(&x)[i] = s * 0.5;
				if (abs(s) > 0.00001f)t = 0.5 / s;
				else t = s;
				w = (m[j][k] - m[k][j]) * t;
				(&x)[j] = (m[i][j] + m[j][i]) * t;
				(&x)[k] = (m[i][k] + m[k][i]) * t;
			}
		}

		void set(T x, T y, T z, T w) {
			this->x = x; this->y = y; this->z = z; this->w = w;
		}

		bool operator==(const quaternion<T>& q)const {
			return x == q.x && y == q.y && z == q.z && w == q.w;
		}

		//线性插值LERP
		quaternion<T> lerp(quaternion<T> q, T q_coff)const {
			T co = x * q.x + y * q.y + z * q.z + w * q.w;
			if (co < 0) q = q * -1;
			gm::vector4<T> v = vec4();
			v = v + (q.vec4() - v) * q_coff;
			return v.normalize();
		}
		//球面插值SLERP
		quaternion<T> slerp(quaternion<T> q, T q_coff)const {
			T co = x * q.x + y * q.y + z * q.z + w * q.w;
			if (co < 0) q = q * (-1), co = -co;
			T c1, c2;
			if (co > 0.9995) {
				c1 = 1.0 - q_coff; c2 = q_coff;
			}
			else
			{
				T si = sqrt(1.0 - co * co);
				T a = atan2(si, co);
				c1 = sin((1.0 - q_coff) * a) / si;
				c2 = sin(q_coff * a) / si;
			}
			return (*this) * c1 + q * c2;
		}

		vector3<T> axis()const {
			return vector3<T>(x, y, z).normalize();
		}

		T theta()const {
			return acos(w) * 2.0;
		}

		vector4<T> vec4() const {
			return vector4<T>(x, y, z, w);
		}
		vector3<T> vec3() const {
			return vector3<T>(x, y, z);
		}

		quaternion<T> normalize() {
			float val = 1.0f / sqrt(x * x + y * y + z * z + w * w);
			return quaternion<T>((*this) * val);
		}
		string str() const {
			sc << x << ", " << y << ", " << z << ", " << w;
			return sc.str();
		}

		//p*q表示先p再q，由于叉乘，其结果与p*q不同
		quaternion<T> operator*(const quaternion<T>& q) const {
			gm::vector3<T> v1(x, y, z); gm::vector3<T> v2(q.x, q.y, q.z);
			gm::vector3<T> v = w * v2 + q.w * v1 + cross(v1, v2);
			return quaternion<T>(v.x, v.y, v.z, w * q.w - dot(v1, v2));
		}
		quaternion<T>& operator*=(const quaternion<T>& q) {
			gm::vector3<T> v1(x, y, z); gm::vector3<T> v2(q.x, q.y, q.z);
			gm::vector3<T> v = w * v2 + q.w * v1 + cross(v1, v2);
			x = v.x; y = v.y; z = v.z; w = w * q.w - dot(v1, v2);
			return *this;
		}

		gm::vec4 operator*(const T& v) const {
			return gm::vec4(x, y, z, w) * v;
		}

		quaternion<T> inv()const {
			return quaternion<T>(-x, -y, -z, w);
		}

		vector3<T> rotate(const vector3<T>& v)const {
			quaternion<T> q = (*this) * quaternion(v.x, v.y, v.z, 0) * inv();
			return vector3<T>(q.x, q.y, q.z);
		}
		mat3x3<T> mat3()const {
			return mat3x3<T>(
				1 - 2 * y * y - 2 * z * z, 2 * x * y + 2 * w * z, 2 * x * z - 2 * w * y,
				2 * x * y - 2 * w * z, 1 - 2 * x * x - 2 * z * z, 2 * y * z + 2 * x * w,
				2 * x * z + 2 * y * w, 2 * y * z - 2 * x * w, 1 - 2 * x * x - 2 * y * y
				);
		}
		mat4x4<T> mat4()const {
			return gm::mat4x4<T>(mat3(), 1);
		}
		T  x, y, z, w;
	};

	using mat2 = mat2x2<float>;
	using mat3 = mat3x3<float>;
	using mat4 = mat4x4<float>;
	using qua = quaternion<float>;

	//先平移，再缩放/旋转（由于是等比缩放，可以先缩放，也可以后缩放）
	struct SQT {
	public:
		SQT() : q(0, 0, 0, 1), t(0, 0, 0), s(1) {}
		SQT(const vec3& S, const qua& Q, const vec3& T) {
			q = Q; s = S; t = T;
		}
		SQT(const mat4& m) {
			mat3 ma(m);
			s.x = ma[0].len(); s.y = ma[1].len(); s.z = ma[2].len();
			ma[0] *= 1.0f / s.x; ma[1] *= 1.0f / s.y; ma[2] *= 1.0f / s.z;
			q = qua(ma);
			t = m[3];
		}
		SQT operator*(const SQT& sqt)const {
			return SQT(s * sqt.s, q * sqt.q, t + s * q.rotate(sqt.t));
		}
		SQT& operator*=(const SQT& sqt) {
			s = s * sqt.s; q = q * sqt.q; t = t + s * q.rotate(sqt.t);
			return *this;
		}

		SQT& operator = (const SQT& qt) {
			s = qt.s; t = qt.t; q = qt.q;
			return *this;
		}

		bool operator == (const SQT& qt)const {
			return s == qt.s && q == qt.q && t == qt.t;
		}

		vec3 operator*(const vec3& v)const {
			return t + s * q.rotate(v);
		}

		SQT lerp(const SQT& o, float o_coff)const {
			return SQT(gm::lerp(s, o.s, o_coff), q.lerp(o.q, o_coff), gm::lerp(t, o.t, o_coff));
		}

		SQT inv() const {
			return SQT(1.0f / s, q.inv(), (q.inv() * qua(-1.0f / s * t) * q).vec3());
		}

		gm::mat4 mat4() const {
			gm::mat4 m(q.mat3(), 1.0f);
			m[0] *= s; m[1] *= s; m[2] *= s;
			m[3] = t; m[3][3] = 1;
			return m;
		}
		string str()const {
			sc << "S: " << s << "  Q: " << q << " T: " << t;
			return sc.str();
		}
		union {
			qua q;
			qua rotation;
		};

		union {
			vec3 translation;
			vec3 p;
			vec3 t;
		};
		union {
			vec3 s;
			vec3 scale;
		};

	};

	template<class T>
	mat4x4<T>::mat4x4(const SQT& q) {
		(*this) = q.mat4();
	}

	template<class T>
	inline quaternion<T> lerp(const quaternion<T>& q1, const quaternion<T>& q2, T q2_coff) {
		return q1.slerp(q2, q2_coff);
	}

	inline SQT lerp(const SQT& v1, const SQT& v2, float v2_coff) {
		return v1.lerp(v2, v2_coff);
	}

	template<class T>
	inline mat4x4<T> operator*(const mat4x4<T>& A, const SQT& q) {
		return A * q.mat4();
	}

	inline std::ostream& operator<<(std::ostream& o, uchar c) {
		int val = c;
		o << val;
		return o;
	}


	template<class T>
	std::ostream& operator<<(std::ostream& o, const mat4x4<T>& m) {
		return o << m.str();
	}
	template<class T>
	std::ostream& operator<<(std::ostream& o, const mat3x3<T>& m) {
		return o << m.str();
	}
	template<class T>
	std::ostream& operator<<(std::ostream& o, const mat2x2<T>& m) {
		return o << m.str();
	}
	template<class T>
	std::ostream& operator<<(std::ostream& o, const Mat<T>& m) {
		return o << m.str();
	}
	template<class T>
	std::ostream& operator<<(std::ostream& o, const quaternion<T>& q) {
		return o << q.str();
	}
	inline std::ostream& operator<<(std::ostream& o, const SQT& q) {
		return o << q.str();
	}

};