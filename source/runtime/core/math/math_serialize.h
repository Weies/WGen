#pragma once

#include"matrix_operation.h"

#include"core/meta/serializer.h"

using namespace gm;

inline Archive& operator<<(Archive& ar, vec2& v)
{
	ar << v.x << v.y;
	return ar;
}

inline Archive& operator<<(Archive& ar, vec3& v)
{
	ar << v.x << v.y << v.z;
	return ar;
}

inline Archive& operator<<(Archive& ar, vec4& v)
{
	ar << v.x << v.y << v.z << v.w;
	return ar;
}

inline Archive& operator<<(Archive& ar, ivec4& v)
{
	ar << v.x << v.y << v.z << v.w;
	return ar;
}

inline Archive& operator<<(Archive& ar, mat3& m)
{
	ar << m.v0 << m.v1 << m.v2;
	return ar;

}

inline Archive& operator<<(Archive& ar, mat4& m)
{
	ar << m.v0 << m.v1 << m.v2 << m.v3;
	return ar;

}

inline Archive& operator<<(Archive& ar, qua& q)
{
	ar << q.x << q.y << q.z << q.w;
	return ar;

}

inline Archive& operator<<(Archive& ar, SQT& q)
{
	ar << q.s << q.q << q.t;
	return ar;

}

