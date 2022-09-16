#pragma once
#include"matrix.h"

namespace gm {

	template<class T>
	inline T dot(const Mat<T>& M, const Mat<T>& N) {
		if (M.rows == N.rows && M.cols == N.cols) {
			T ret = 0;
			for (int i = 0; i < M.rows; ++i) {
				for (int j = 0; j < M.cols; ++j)
					ret += M[i][j] * N[i][j];
			}
			return ret;
		}
		if (M.rows == N.cols && M.rows == N.cols) {
			T ret = 0;
			for (int i = 0; i < M.rows; ++i) {
				for (int j = 0; j < M.cols; ++j)
					ret += M(i, j) * N(j, i);
			}
			return ret;
		}
		debug << "Matrix that not satisfy M.rows == N.rows && M.cols == N.cols "
			"or M.rows == N.cols && M.rows == N.cols cannot be dotted" << endl;
	}

	template<class T>
	inline mat2x2<T> operator+(const mat2x2<T>& A, const mat2x2<T>& B) {
		return mat2x2<T>(A[0] + B[0], A[1] + B[1]);
	}
	template<class T>
	inline mat2x2<T> operator+(const mat2x2<T>& A, const T& s) {
		return mat2x2<T>(A[0] + s, A[1] + s);
	}
	template<class T>
	inline mat2x2<T> operator+(const T& s, const mat2x2<T>& A) {
		return mat2x2<T>(A[0] + s, A[1] + s);
	}
	template<class T>
	inline mat2x2<T> operator-(const mat2x2<T>& A, const mat2x2<T>& B) {
		return mat2x2<T>(A[0] - B[0], A[1] - B[1]);
	}
	template<class T>
	inline mat2x2<T> operator-(const mat2x2<T>& A, const T& s) {
		return mat2x2<T>(A[0] - s, A[1] - s);
	}
	template<class T>
	inline mat2x2<T> operator-(const T& s, const mat2x2<T>& A) {
		return mat2x2<T>(A[0] - s, A[1] - s);
	}
	template<class T>
	inline mat2x2<T> operator*(const mat2x2<T>& A, const mat2x2<T>& B) {
		mat2x2<T> M = A.t();
		return mat2x2<T>(dot(M[0], B[0]), dot(M[1], B[0]),
			dot(M[0], B[1]), dot(M[1], B[1]));
	}
	template<class T>
	inline mat2x2<T> operator*(const mat2x2<T>& A, const T& s) {
		return mat2x2<T>(A[0] * s, A[1] * s);
	}
	template<class T>
	inline mat2x2<T> operator*(const T& s, const mat2x2<T>& A) {
		return mat2x2<T>(A[0] * s, A[1] * s);
	}


	template<class T>
	inline mat3x3<T> operator+(const mat3x3<T>& A, const mat3x3<T>& B) {
		return mat3x3<T>(A[0] + B[0], A[1] + B[1], A[2] + B[2]);
	}
	template<class T>
	inline mat3x3<T> operator+(const mat3x3<T>& A, const T& s) {
		return mat3x3<T>(A[0] + s, A[1] + s, A[2] + s);
	}
	template<class T>
	inline mat3x3<T> operator+(const T& s, const mat3x3<T>& A) {
		return mat3x3<T>(A[0] + s, A[1] + s, A[2] + s);
	}
	template<class T>
	inline mat3x3<T> operator-(const mat3x3<T>& A, const mat3x3<T>& B) {
		return mat2x2<T>(A[0] - B[0], A[1] - B[1], A[2] - B[2]);
	}
	template<class T>
	inline mat3x3<T> operator-(const mat3x3<T>& A, const T& s) {
		return mat3x3<T>(A[0] - s, A[1] - s, A[2] - s);
	}
	template<class T>
	inline mat3x3<T> operator-(const T& s, const mat3x3<T>& A) {
		return mat3x3<T>(A[0] + s, A[1] - s, A[2] - s);
	}
	template<class T>
	inline mat3x3<T> operator*(const mat3x3<T>& A, const mat3x3<T>& B) {
		mat3x3<T> M = A.t();
		return mat3x3<T>(
			dot(M[0], B[0]), dot(M[1], B[0]), dot(M[2], B[0]),
			dot(M[0], B[1]), dot(M[1], B[1]), dot(M[2], B[1]),
			dot(M[0], B[2]), dot(M[1], B[2]), dot(M[2], B[2]));
	}

	template<class T>
	inline mat3x3<T> operator*(const mat3x3<T>& A, const T& s) {
		return mat3x3<T>(A[0] * s, A[1] * s, A[2] * s);
	}
	template<class T>
	inline mat3x3<T> operator*(const T& s, const mat3x3<T>& A) {
		return mat3x3<T>(A[0] * s, A[1] * s, A[2] * s);
	}


	template<class T>
	inline mat4x4<T> operator+(const mat4x4<T>& A, const mat4x4<T>& B) {
		return mat4x4<T>(A[0] + B[0], A[1] + B[1], A[2] + B[2], A[3] + B[3]);
	}
	template<class T>
	inline mat4x4<T> operator+(const mat4x4<T>& A, const T& s) {
		return mat4x4<T>(A[0] + s, A[1] + s, A[2] + s, A[3] + s);
	}
	template<class T>
	inline mat4x4<T> operator+(const T& s, const mat4x4<T>& A) {
		return mat4x4<T>(A[0] + s, A[1] + s, A[2] + s, A[3] + s);
	}
	template<class T>
	inline mat4x4<T> operator-(const mat4x4<T>& A, const mat4x4<T>& B) {
		return mat2x2<T>(A[0] - B[0], A[1] - B[1], A[2] - B[2], A[3] - B[3]);
	}
	template<class T>
	inline mat4x4<T> operator-(const mat4x4<T>& A, const T& s) {
		return mat4x4<T>(A[0] - s, A[1] - s, A[2] - s, A[3] - s);
	}
	template<class T>
	inline mat4x4<T> operator-(const T& s, const mat4x4<T>& A) {
		return -mat2x2<T>(A[0] - s, A[1] - s, A[2] - s, A[3] - s);
	}

	template<class T>
	inline mat4x4<T> operator*(const mat4x4<T>& A, const mat4x4<T>& B) {
		mat4x4<T> M = A.t();
		return mat4x4<T>(dot(M[0], B[0]), dot(M[1], B[0]), dot(M[2], B[0]), dot(M[3], B[0]),
			dot(M[0], B[1]), dot(M[1], B[1]), dot(M[2], B[1]), dot(M[3], B[1]),
			dot(M[0], B[2]), dot(M[1], B[2]), dot(M[2], B[2]), dot(M[3], B[2]),
			dot(M[0], B[3]), dot(M[1], B[3]), dot(M[2], B[3]), dot(M[3], B[3]));
	}

	template<class T, class P>
	inline mat4x4<T> operator*(const mat4x4<T>& A, const quaternion<P>& q) {
		return A * q.mat4();
	}

	template<class T, class P>
	inline mat4x4<T> operator*(const quaternion<T>& q, const mat4x4<P>& B) {
		return q.mat4() * B;
	}

	template<class T>
	inline mat4x4<T> operator*(const mat4x4<T>& A, const T& s) {
		return mat4x4<T>(A[0] * s, A[1] * s, A[2] * s, A[3] * s);
	}
	template<class T>
	inline mat4x4<T> operator*(const T& s, const mat4x4<T>& A) {
		return mat4x4<T>(A[0] * s, A[1] * s, A[2] * s, A[3] * s);
	}

	template<class T>
	inline Mat<T> operator*(const Mat<T>& M, const Mat<T>& N) {
		if (M.rows != N.cols) {
			debug << "Matrix that not satisfy M.rows == N.cols cannot be multiply" << endl;
			return Mat<T>(0, 0);
		}
		Mat<T> t(M.rows, N.cols);
		for (int i = 0; i < M.rows; ++i) {
			for (int j = 0; j < N.cols; ++j) {
				T r = 0;
				for (int k = 0; k < M.cols; ++k) {
					r += M(i, k) * N(k, j);
				}
				t(i, j) = r;
			}
		}
		return t;
	}

	template<class T>
	inline Mat<T> operator+(const Mat<T>& M, const Mat<T>& N) {
		if (M.rows != N.rows || M.cols != N.cols) {
			debug << "Matrix that not satisfy M.rows == N.rows && M.cols == N.cols cannot be add" << endl;
			return Mat<T>(0, 0);
		}
		Mat<T> t(M.rows, M.cols);
		const int s = M.rows * M.cols;
		for (int i = 0; i < s; ++i) {
			t.v[i] = M.v[i] + N.v[i];
		}
		return t;
	}

	template<class T>
	inline Mat<T> operator-(const Mat<T>& M, const Mat<T>& N) {
		if (M.rows != N.rows || M.cols != N.cols) {
			debug << "Matrix that not satisfy M.rows == N.rows && M.cols == N.cols cannot be subtract" << endl;
			return Mat<T>(0, 0);
		}
		Mat<T> t(M.rows, M.cols);
		const int s = M.rows * M.cols;
		for (int i = 0; i < s; ++i) {
			t.v[i] = M.v[i] - N.v[i];
		}
		return t;
	}

	template<class T>
	inline vector2<T> operator*(const mat2x2<T>& A, const vector2<T>& v) {
		mat2x2<T> M = A.t();
		return vector2<T>(dot(M[0], v), dot(M[1], v));
	}

	template<class T>
	inline vector3<T> operator*(const mat3x3<T>& A, const vector3<T>& v) {
		mat3x3<T> M = A.t();
		return vector3<T>(dot(M[0], v), dot(M[1], v), dot(M[2], v));
	}

	template<class T>
	inline	vector4<T> operator*(const mat4x4<T>& A, const vector4<T>& v) {
		mat4x4<T> M = A.t();
		return vector4<T>(dot(M[0], v), dot(M[1], v), dot(M[2], v), dot(M[3], v));
	}


	template<class T>
	mat2x2<T> transpose(const mat2x2<T>& m) {
		return m.t();
	}

	template<class T>
	mat3x3<T> transpose(const mat3x3<T>& m) {
		return m.t();
	}

	template<class T>
	mat4x4<T> transpose(const mat4x4<T>& m) {
		return m.t();
	}


	template<class T>
	vector2<T> normalize(const vector2<T>& v) {
		return v / v.len();
	}

	template<class T>
	vector3<T> normalize(const vector3<T>& v) {
		return v / v.len();
	}

	template<class T>
	vector4<T> normalize(const vector4<T>& v) {
		return v / v.len();
	}

	template<class T>
	vec3 getNormal(const vector3<T>& p1, const vector3<T>& p2, const vector3<T>& p3, bool normalize = false)
	{
		if (normalize) return gm::normalize(cross<T>(p2 - p1, p3 - p1));
		return cross<T>(p2 - p1, p3 - p1);
	}


	template<class T>
	const T* value_ptr(const vector2<T>& v) {
		return &v.x;
	}

	template<class T>
	const T* value_ptr(const vector3<T>& v) {
		return &v.x;
	}

	template<class T>
	const T* value_ptr(const vector4<T>& v) {
		return &v.x;
	}

	template<class T>
	const T* value_ptr(const mat2x2<T>& v) {
		return &v.v0.x;
	}

	template<class T>
	const T* value_ptr(const mat3x3<T>& v) {
		return &v.v0.x;
	}

	template<class T>
	const T* value_ptr(const mat4x4<T>& v) {
		return &v.v0.x;
	}

	template<class T>
	vector2<T> rotc(T cx, T cy, T px, T py, T rotdeg) {
		vector2<T> p(px - cx, py - cy);
		p.rot(rotdeg);
		return p + vector2<T>(cx, cy);
	}

	//#define center(x,y) (((x)+(y))/2.0)

	template<class T>
	T det(const mat2x2<T>& m) {
		return
			+m[0][0] * m[1][1]
			- m[1][0] * m[0][1]
			;
	}

	template<class T>
	T det(const mat3x3<T>& m) {
		return
			+m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2])
			- m[1][0] * (m[0][1] * m[2][2] - m[2][1] * m[0][2])
			+ m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2]);
	}

	template<class T>
	T det(const mat4x4<T>& m) {
		return
			-m[3][0] * det(mat3x3<T>(m[1], m[2], m[3]))
			+ m[3][1] * det(mat3x3<T>(m[0], m[2], m[3]))
			- m[3][2] * det(mat3x3<T>(m[0], m[1], m[3]))
			+ m[3][3] * det(mat3x3<T>(m[0], m[1], m[2]))
			;
	}

	template<class T>
	mat2x2<T> inverse(mat2x2<T> const& m)
	{
		T OneOverDeterminant = static_cast<T>(1) / (
			+m[0][0] * m[1][1]
			- m[1][0] * m[0][1]);

		mat2x2<T> Inverse(
			+m[1][1] * OneOverDeterminant,
			-m[0][1] * OneOverDeterminant,
			-m[1][0] * OneOverDeterminant,
			+m[0][0] * OneOverDeterminant);

		return Inverse;
	}

	template<typename T>
	mat3x3<T> inverse(const mat3x3<T>& m)
	{
		T OneOverDeterminant = static_cast<T>(1) / (
			+m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2])
			- m[1][0] * (m[0][1] * m[2][2] - m[2][1] * m[0][2])
			+ m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2]));

		mat3x3<T> Inverse;
		Inverse[0][0] = +(m[1][1] * m[2][2] - m[2][1] * m[1][2]) * OneOverDeterminant;
		Inverse[1][0] = -(m[1][0] * m[2][2] - m[2][0] * m[1][2]) * OneOverDeterminant;
		Inverse[2][0] = +(m[1][0] * m[2][1] - m[2][0] * m[1][1]) * OneOverDeterminant;
		Inverse[0][1] = -(m[0][1] * m[2][2] - m[2][1] * m[0][2]) * OneOverDeterminant;
		Inverse[1][1] = +(m[0][0] * m[2][2] - m[2][0] * m[0][2]) * OneOverDeterminant;
		Inverse[2][1] = -(m[0][0] * m[2][1] - m[2][0] * m[0][1]) * OneOverDeterminant;
		Inverse[0][2] = +(m[0][1] * m[1][2] - m[1][1] * m[0][2]) * OneOverDeterminant;
		Inverse[1][2] = -(m[0][0] * m[1][2] - m[1][0] * m[0][2]) * OneOverDeterminant;
		Inverse[2][2] = +(m[0][0] * m[1][1] - m[1][0] * m[0][1]) * OneOverDeterminant;

		return Inverse;
	};
	template<class T>
	mat4x4<T> call(mat4x4<T> const& m)
	{
		T Coef00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
		T Coef02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
		T Coef03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];

		T Coef04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
		T Coef06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
		T Coef07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];

		T Coef08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
		T Coef10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
		T Coef11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];

		T Coef12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
		T Coef14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
		T Coef15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];

		T Coef16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
		T Coef18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
		T Coef19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];

		T Coef20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
		T Coef22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
		T Coef23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

		vector4<T> Fac0(Coef00, Coef00, Coef02, Coef03);
		vector4<T> Fac1(Coef04, Coef04, Coef06, Coef07);
		vector4<T> Fac2(Coef08, Coef08, Coef10, Coef11);
		vector4<T> Fac3(Coef12, Coef12, Coef14, Coef15);
		vector4<T> Fac4(Coef16, Coef16, Coef18, Coef19);
		vector4<T> Fac5(Coef20, Coef20, Coef22, Coef23);

		vector4<T> Vec0(m[1][0], m[0][0], m[0][0], m[0][0]);
		vector4<T> Vec1(m[1][1], m[0][1], m[0][1], m[0][1]);
		vector4<T> Vec2(m[1][2], m[0][2], m[0][2], m[0][2]);
		vector4<T> Vec3(m[1][3], m[0][3], m[0][3], m[0][3]);

		vector4<T> Inv0(Vec1 * Fac0 - Vec2 * Fac1 + Vec3 * Fac2);
		vector4<T> Inv1(Vec0 * Fac0 - Vec2 * Fac3 + Vec3 * Fac4);
		vector4<T> Inv2(Vec0 * Fac1 - Vec1 * Fac3 + Vec3 * Fac5);
		vector4<T> Inv3(Vec0 * Fac2 - Vec1 * Fac4 + Vec2 * Fac5);

		vector4<T> SignA(+1, -1, +1, -1);
		vector4<T> SignB(-1, +1, -1, +1);
		mat4x4<T> Inverse(Inv0 * SignA, Inv1 * SignB, Inv2 * SignA, Inv3 * SignB);

		vector4<T> Row0(Inverse[0][0], Inverse[1][0], Inverse[2][0], Inverse[3][0]);

		vector4<T> Dot0(m[0] * Row0);
		T Dot1 = (Dot0.x + Dot0.y) + (Dot0.z + Dot0.w);

		T OneOverDeterminant = static_cast<T>(1) / Dot1;

		return Inverse * OneOverDeterminant;
	}

	template<class T>
	mat4x4<T> inverse(mat4x4<T> const& m)
	{
		T Coef00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
		T Coef02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
		T Coef03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];

		T Coef04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
		T Coef06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
		T Coef07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];

		T Coef08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
		T Coef10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
		T Coef11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];

		T Coef12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
		T Coef14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
		T Coef15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];

		T Coef16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
		T Coef18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
		T Coef19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];

		T Coef20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
		T Coef22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
		T Coef23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

		vector4<T>  Fac0(Coef00, Coef00, Coef02, Coef03);
		vector4<T>  Fac1(Coef04, Coef04, Coef06, Coef07);
		vector4<T>  Fac2(Coef08, Coef08, Coef10, Coef11);
		vector4<T>  Fac3(Coef12, Coef12, Coef14, Coef15);
		vector4<T>  Fac4(Coef16, Coef16, Coef18, Coef19);
		vector4<T>  Fac5(Coef20, Coef20, Coef22, Coef23);
		vector4<T>  Vec0(m[1][0], m[0][0], m[0][0], m[0][0]);
		vector4<T>  Vec1(m[1][1], m[0][1], m[0][1], m[0][1]);
		vector4<T>  Vec2(m[1][2], m[0][2], m[0][2], m[0][2]);
		vector4<T>  Vec3(m[1][3], m[0][3], m[0][3], m[0][3]);
		vector4<T>  Inv0(Vec1 * Fac0 - Vec2 * Fac1 + Vec3 * Fac2);
		vector4<T>  Inv1(Vec0 * Fac0 - Vec2 * Fac3 + Vec3 * Fac4);
		vector4<T>  Inv2(Vec0 * Fac1 - Vec1 * Fac3 + Vec3 * Fac5);
		vector4<T>  Inv3(Vec0 * Fac2 - Vec1 * Fac4 + Vec2 * Fac5);
		vector4<T>  SignA(+1, -1, +1, -1);
		vector4<T>  SignB(-1, +1, -1, +1);

		mat4x4<T> Inverse(Inv0 * SignA, Inv1 * SignB, Inv2 * SignA, Inv3 * SignB);

		vector4<T> Row0(Inverse[0][0], Inverse[1][0], Inverse[2][0], Inverse[3][0]);

		vector4<T> Dot0(m[0] * Row0);
		T Dot1 = (Dot0.x + Dot0.y) + (Dot0.z + Dot0.w);

		T OneOverDeterminant = static_cast<T>(1) / Dot1;

		return Inverse * OneOverDeterminant;
	}


}