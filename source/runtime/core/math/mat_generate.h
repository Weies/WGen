#pragma once
#include"matrix.h"
#include"matrix_operation.h"

namespace gm {

	//生成的正交投影矩阵以左下角为原点
	template<typename T>
	mat4x4<T> ortho(T left, T right, T bottom, T top)
	{
		mat4x4<T> Result(static_cast<T>(1));
		Result[0][0] = static_cast<T>(2) / (right - left);
		Result[1][1] = static_cast<T>(2) / (top - bottom);
		Result[2][2] = -static_cast<T>(1);
		Result[3][0] = -(right + left) / (right - left);
		Result[3][1] = -(top + bottom) / (top - bottom);
		return Result;
	}

	template<typename T>
	mat4x4<T> ortho(T left, T right, T bottom, T top, T zNear, T zFar)
	{
		mat4x4<T> Result(1);
		Result[0][0] = static_cast<T>(2) / (right - left);
		Result[1][1] = static_cast<T>(2) / (top - bottom);
		Result[2][2] = -static_cast<T>(2) / (zFar - zNear);
		Result[3][0] = -(right + left) / (right - left);
		Result[3][1] = -(top + bottom) / (top - bottom);
		Result[3][2] = -(zFar + zNear) / (zFar - zNear);
		return Result;
	}

	template<typename T>
	mat4x4<T> perspective(T fovy, T aspect, T zNear, T zFar)
	{

		T const tanHalfFovy = tan(fovy / static_cast<T>(2));

		mat4x4<T> Result(static_cast<T>(0));
		Result[0][0] = static_cast<T>(1) / (aspect * tanHalfFovy);
		Result[1][1] = static_cast<T>(1) / (tanHalfFovy);
		Result[2][2] = -(zFar + zNear) / (zFar - zNear);
		Result[2][3] = -static_cast<T>(1);
		Result[3][2] = -(static_cast<T>(2) * zFar * zNear) / (zFar - zNear);
		return Result;
	}

	template<typename T, typename R>
	mat4x4<T> rotate(mat4x4<T> const& m, R degree, vector3<T> const& v)
	{
		T angle = (T)degree;
		T const a = radians(angle);
		T const c = cos(a);
		T const s = sin(a);

		vector3<T> axis(normalize(v));
		vector3<T> temp((T(1) - c) * axis);

		mat4x4<T> Rotate;
		Rotate[0][0] = c + temp[0] * axis[0];
		Rotate[0][1] = temp[0] * axis[1] + s * axis[2];
		Rotate[0][2] = temp[0] * axis[2] - s * axis[1];

		Rotate[1][0] = temp[1] * axis[0] - s * axis[2];
		Rotate[1][1] = c + temp[1] * axis[1];
		Rotate[1][2] = temp[1] * axis[2] + s * axis[0];

		Rotate[2][0] = temp[2] * axis[0] + s * axis[1];
		Rotate[2][1] = temp[2] * axis[1] - s * axis[0];
		Rotate[2][2] = c + temp[2] * axis[2];

		mat4x4<T> Result;
		Result[0] = m[0] * Rotate[0][0] + m[1] * Rotate[0][1] + m[2] * Rotate[0][2];
		Result[1] = m[0] * Rotate[1][0] + m[1] * Rotate[1][1] + m[2] * Rotate[1][2];
		Result[2] = m[0] * Rotate[2][0] + m[1] * Rotate[2][1] + m[2] * Rotate[2][2];
		Result[3] = m[3];
		return Result;
	}

	template<typename T>
	mat4x4<T> translate(const mat4x4<T>& m, const vector3<T>& v)
	{
		mat4x4<T> Result(m);
		Result[3] = m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3];
		return Result;
	}

	template<typename T>
	SQT translate(SQT m, const vector3<T>& v)
	{
		m.t = m.t + m.s * m.q.rotate(v);
		return m;
	}

	template<typename T>
	mat3x3<T> translate(const mat3x3<T>& m, const vector2<T>& v)
	{
		mat4x4<T> Result(m);
		Result[2] = m[0] * v[0] + m[1] * v[1] + m[2];
		return Result;
	}

	template<typename T>
	mat4x4<T>  scale(mat4x4<T> const& m, vector3<T> const& v)
	{
		mat4x4<T> Result;
		Result[0] = m[0] * v[0];
		Result[1] = m[1] * v[1];
		Result[2] = m[2] * v[2];
		Result[3] = m[3];
		return Result;
	}

	template<typename T>
	SQT  scale(SQT m, vector3<T> const& v)
	{
		m.s *= v.x;
		return m;
	}

	template<typename T>
	mat4x4<T>  scale(mat4x4<T> const& m, T const& v)
	{
		mat4x4<T> Result;
		Result[0] = m[0] * v;
		Result[1] = m[1] * v;
		Result[2] = m[2] * v;
		Result[3] = m[3];
		return Result;
	}

	template<typename T>
	SQT scale(SQT m, T const& v)
	{
		m.s *= v;
		return m;
	}


	template<class T>
	mat3x3<T> scale(const mat3x3<T>& m, vector2<T>& v) {
		mat3x3<T> result;
		result[0] = m[0] * v[0];
		result[1] = m[1] * v[1];
		result[2] = m[2];
		return result;
	}

	template<class T>
	mat3x3<T> scale(const mat3x3<T>& m, T const& v) {
		mat3x3<T> result;
		result[0] = m[0] * v;
		result[1] = m[1] * v;
		result[2] = m[2];
		return result;
	}

	template<typename T>
	mat4x4<T>  scale(mat4x4<T> const& m, T const& v, const vector3<T>& center)
	{
		return translate(mat4(1.0), -center) * scale(mat4(1.0), v) * translate(mat4(1.0), center) * m;
	}

	template<typename T>
	mat4x4<T>  scale(mat4x4<T> const& m, vector3<T> const& v, const vector3<T>& center)
	{
		return translate(mat4(1.0), -center) * scale(mat4(1.0), v) * translate(mat4(1.0), center) * m;
	}


	//以center为中心缩放
	template<class T>
	mat3x3<T> scale(const mat3x3<T>& m, T const& v, const vector2<T>& center) {
		return mat3(
			v, 0.0, 0.0,
			0.0, v, 0.0,
			center.x * (1 - v), center.y * (1 - v), 1.0)
			* m;
	}

	template<class T>
	mat3x3<T> scale(const mat3x3<T>& m, const vector2<T>& v, const vector2<T>& center) {
		return mat3(
			v.x, 0.0, 0.0,
			0.0, v.y, 0.0,
			center.x * (1 - v.x), center.y * (1 - v.y), 1.0)
			* m;
	}


	template<typename T>
	mat4x4<T> lookAt(vector3<T> const& eye, vector3<T> const& center, vector3<T> const& up)
	{
		vector3<T>  const f(normalize(center - eye));
		vector3<T>  const s(normalize(cross(f, up)));
		vector3<T>  const u(cross(s, f));

		mat4x4<T> Result(1);
		Result[0][0] = s.x;
		Result[1][0] = s.y;
		Result[2][0] = s.z;
		Result[0][1] = u.x;
		Result[1][1] = u.y;
		Result[2][1] = u.z;
		Result[0][2] = -f.x;
		Result[1][2] = -f.y;
		Result[2][2] = -f.z;
		Result[3][0] = -dot(s, eye);
		Result[3][1] = -dot(u, eye);
		Result[3][2] = dot(f, eye);
		return Result;
	}
	template<typename T>
	mat4x4<T> lookAt(vector3<T> const& eye, vector3<T> const& front)
	{
		vector3<T>  const f = front.normalize();
		vector3<T>  const s(cross(f, vec3(0, 1, 0)));
		vector3<T>  const u(cross(s, f));

		mat4x4<T> Result(1);
		Result[0][0] = s.x;
		Result[1][0] = s.y;
		Result[2][0] = s.z;
		Result[0][1] = u.x;
		Result[1][1] = u.y;
		Result[2][1] = u.z;
		Result[0][2] = -f.x;
		Result[1][2] = -f.y;
		Result[2][2] = -f.z;
		Result[3][0] = -dot(s, eye);
		Result[3][1] = -dot(u, eye);
		Result[3][2] = dot(f, eye);
		return Result;
	}

	inline mat4x4<float> lookAt(const SQT& q)
	{
		vector3<float>  const f = q.q.rotate(vec3(0, 0, 1));
		vector3<float>  const s(cross(f, vec3(0, 1, 0)));
		vector3<float>  const u(cross(s, f));

		mat4x4<float> Result(1);
		Result[0][0] = s.x;
		Result[1][0] = s.y;
		Result[2][0] = s.z;
		Result[0][1] = u.x;
		Result[1][1] = u.y;
		Result[2][1] = u.z;
		Result[0][2] = -f.x;
		Result[1][2] = -f.y;
		Result[2][2] = -f.z;
		Result[3][0] = -dot(s, q.p);
		Result[3][1] = -dot(u, q.p);
		Result[3][2] = dot(f, q.p);
		return Result;
	}
}
