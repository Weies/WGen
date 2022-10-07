#pragma once

#include"serializer.h"

inline Archive& operator<<(Archive& ar, vec2& v)
{
	return ar << v.x << v.y;
}

inline Archive& operator<<(Archive& ar, vec3& v)
{
	return ar << v.x << v.y << v.z;
}

inline Archive& operator<<(Archive& ar, vec4& v)
{
	return ar << v.x << v.y << v.z << v.w;
}

inline Archive& operator<<(Archive& ar, ivec4& v)
{
	return ar << v.x << v.y << v.z << v.w;
}

inline Archive& operator<<(Archive& ar, mat3& m)
{
	return ar << m.v0 << m.v1 << m.v2;
}

inline Archive& operator<<(Archive& ar, mat4& m)
{
	return ar << m.v0 << m.v1 << m.v2 << m.v3;
}

inline Archive& operator<<(Archive& ar, qua& q)
{
	return ar << q.x << q.y << q.z << q.w;
}

inline Archive& operator<<(Archive& ar, Transform& q)
{
	return ar << q.s << q.q << q.t;
}

