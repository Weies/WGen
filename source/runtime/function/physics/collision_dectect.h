#pragma once
#include"../base/global_values.h"
#include"core/math/math_include.h"

static const int _tri[12][3] =
{
	{0,2,1},{2,4,1},
	{3,2,0},{3,7,2},
	{1,3,0},{1,6,3},
	{6,1,4},{6,4,5},
	{4,2,5},{5,2,7},
	{5,7,3},{5,3,6}
};
static vec3 itface;

struct trian {
	trian() {}
	trian(vec3 v1, vec3 v2, vec3 v3) {
		p[0] = v1; p[1] = v2; p[2] = v3;
	}
	trian(vec3 v[3]) {
		memcpy(p, v, sizeof(p));
	}
	vec3 norm()const {
		return cross(p[1] - p[0], p[2] - p[0]);
	}
	vec3& operator[](int i) {
		return p[i];
	}
	const vec3& operator[](int i) const {
		return p[i];
	}
	vec3 p[3];
};

struct line {
	line() {}
	line(vec3 v1, vec3 v2) {
		p[0] = v1; p[1] = v2;
	}
	line(vec3 v[2]) {
		p[0] = v[0]; p[1] = v[1];
	}
	vec3& operator[](int i) {
		return p[i];
	}
	const vec3& operator[](int i) const {
		return p[i];
	}
	vec3 p[2];
};

struct ball {
	ball() {}
	ball(vec3 origin, float radius) {
		o = origin; r = radius;
	}
	vec3 o;
	float r;
};
struct cube {
	cube() {}
	cube(vec3 v1, vec3 v2, vec3 v3, vec3 v4) {
		p[0] = v1; p[1] = v2; p[2] = v3; p[3] = v4;
	}
	cube(vec3 v[4]) {
		memcpy(p, v, sizeof(p));
	}
	vec3& operator[](int i) {
		return p[i];
	}
	const vec3& operator[](int i)const {
		return p[i];
	}
	vec3 p[4];
};

struct CDResult {
	CDResult() {}
	CDResult(bool sect) {
		mIsSect = sect;
	}
	CDResult(const vec3& normal) {
		mNormal = normal; mIsSect = true;
	}
	/*CDResult(const trian& own, const trian& opp) {
		this->own = own; this->opp = opp;
		isSect = true;
	}*/

	operator bool() {
		return mIsSect;
	}

	//trian own;
	//trian opp;
	vec3 mNormal;
	bool mIsSect;
};

inline vec4 intersect(const trian& t, const  line& l) {
	vec3 n = cross(t[1] - t[0], t[2] - t[1]);
	vec3 d = l[1] - l[0];
	vec3 h = l[0] - t[0];
	float dt = dot(d, n);
	if (abs(dt) < 0.000001f) {
		//平行
	}
	float tt = -dot(n, h) / dt;
	return vec4(l[0] + tt * d, tt);
}

inline bool inPlain(const trian& t, const vec3& p) {
	return abs(dot(t.norm(), t[0] - p)) < 0.0001f;
}
//检测在同一平面的点是否在三角形内部
inline bool inTrian(const trian& t, const  vec3& p) {
	debug(abs(dot(t.norm(), t[0] - p)));
	vec3 u = t[1] - t[0]; vec3 v = t[2] - t[0];
	double uu = dot(u, u);
	double uv = dot(u, v);
	double vv = dot(v, v);
	vec3 w = p - t[0];
	double wu = dot(w, u);
	double wv = dot(w, v);
	double D = uv * uv - uu * vv;

	double s = (uv * wv - vv * wu) / D;
	if (s < 0.0 || s > 1.0)
		return false;

	double tt = (uv * wu - uu * wv) / D;
	if (tt < 0.0 || (s + tt) > 1.0)
		return false;
	return true;
}

inline bool _isSect(const line& l, const  line& n) {
	if (abs(det(mat3(l[1] - l[0], n[1] - n[0], l[0] - n[0]))) > 0.000001f)return false;

	return true;
}

//线段是否与三角形是否相交
inline bool _isSect(const trian& t, const  line& l) {
	vec3 n = cross(t[1] - t[0], t[2] - t[1]);
	vec3 d = (l[1] - l[0]);
	float dt = dot(d, n);
	if (abs(dt) < 0.000001f)return false; //直线与平面平行
	else {
		vec3 h = l[0] - t[0];
		float tt = -dot(n, h) / dt;
		if (tt < 0 || tt>1)return false;
		vec3 ip = l[0] + tt * d;

		vec3 u = t[1] - t[0]; vec3 v = t[2] - t[0];
		float uu = dot(u, u);
		float uv = dot(u, v);
		float vv = dot(v, v);
		vec3 w = ip - t[0];
		float wu = dot(w, u);
		float wv = dot(w, v);
		float D = uv * uv - uu * vv;

		float s = (uv * wv - vv * wu) / D;
		if (s < 0.0f || s > 1.0f)
			return false;

		float t = (uv * wu - uu * wv) / D;
		if (t < 0.0f || (s + t) > 1.0f)
			return false;

		return true;
	}

}

inline bool _isSect(const ball& b, const  vec3& p) {
	return (b.o - p).square_sum() <= b.r * b.r;
}

// 第一参数填发出碰撞检测请求的物体，第二个填被检测的物体
inline CDResult isSect(const  trian& t, const ball& b) {
	vec3 n = t.norm(); float len = 1.0 / n.len();
	float dt = dot(n, b.o - t[0]) * len;
	if (abs(dt) < 0.0001f || dt > b.r)return false;
	float rsq = b.r * b.r + 0.00001f;
	if ((b.o - t[0]).square_sum() < rsq || (b.o - t[1]).square_sum() < rsq || (b.o - t[2]).square_sum() < rsq)
		return { (t[0] + t[1] + t[2]) * 0.333 - b.o };
	return false;
}
inline CDResult isSect(const trian& s, const  trian& t) {
	if (_isSect(s, { t[0],t[1] }) || _isSect(s, { t[1],t[2] }) || _isSect(s, { t[0],t[2] })) return{ t.norm() };
	return false;
}

inline CDResult isSect(const ball& b, const  ball& t) {
	if ((b.o - t.o).square_sum() <= (b.r + t.r) * (b.r + t.r)) {
		return { b.o - t.o };
	}
	return false;
}
inline CDResult isSect(const cube& a, const  cube& b) {
	vec3 v[8] =
	{ a[0],a[1],a[2],a[3],a[1] + a[2] - a[0],
		a[1] + a[2] + a[3] - a[0] - a[0],a[1] + a[3] - a[0],a[2] + a[3] - a[0] };
	vec3 x[8] =
	{ b[0],b[1],b[2],b[3],b[1] + b[2] - b[0],
		b[1] + b[2] + b[3] - b[0] - b[0],b[1] + b[3] - b[0],b[2] + b[3] - b[0] };
	for (int i = 0; i < 12; ++i) {
		auto& d = _tri[i];
		for (int j = 0; j < 12; ++j) {
			auto& f = _tri[j];
			auto res = isSect(trian(v[d[0]], v[d[1]], v[d[2]]), trian(x[f[0]], x[f[1]], x[f[2]]));
			if (res) return res;
		}
	}
	return false;
}
inline CDResult isSect(const cube& a, const ball& b) {
	vec3 v[8] =
	{ a[0],a[1],a[2],a[3],a[1] + a[2] - a[0],
		a[1] + a[2] + a[3] - a[0] - a[0],a[1] + a[3] - a[0],a[2] + a[3] - a[0] };
	for (int i = 0; i < 12; ++i) {
		auto& d = _tri[i];
		auto res = isSect(trian(v[d[0]], v[d[1]], v[d[2]]), b);
		if (res)return res;
	}
	return false;
}


enum ColliType {
	Colli_None, Colli_Ball, Colli_Cube, Colli_Semiball, Colli_Mixure
};
//  碰撞体
class ColliBody {
public:
	ColliBody() {}
	ColliBody(ColliType tp, const SQT& model_matrix) {
		mType = tp;
		mModelTransform = &model_matrix;
		mIsModelSaved = model_matrix;
		if (tp == Colli_Ball)mColliInstance = new ball();
		ef(tp == Colli_Cube)mColliInstance = new cube();
	}
	~ColliBody() {
		if (!mColliInstance)return;
		if (mType == Colli_Ball)delete (ball*)mColliInstance;
		else if (mType == Colli_Cube)delete (cube*)mColliInstance;
	}
	void setMatReference(const SQT& model_matrix) {
		mModelTransform = &model_matrix;
	}
	void initBody(ColliType tp) {
		mType = tp;
		if (tp == Colli_Ball)mColliInstance = new ball();
		ef(tp == Colli_Cube)mColliInstance = new cube();
	}
	ColliBody& operator=(const ColliBody& b) {
		mModelTransform = b.mModelTransform;
		mType = b.mType;
		mIsModelSaved = b.mIsModelSaved;
		if (mColliInstance)delete mColliInstance;
		if (mType == Colli_Ball) mColliInstance = new ball(b.body<ball>());
		ef(mType == Colli_Cube)mColliInstance = new cube(b.body<cube>());
		return *this;
	}

	//等比缩放直接对模型矩阵做，非等比缩放调用这个函数。
	void scale(const vec3& v) {
		if (mType == Colli_Ball) {
			auto& b = body<ball>();
			b.r *= v.x;
		}
		ef(mType == Colli_Cube) {
			auto& b = body<cube>();
			b[0] *= v;	b[1] *= v;	b[2] *= v;	b[3] *= v;
		}
	}

	// 应用模型会将模型矩阵应用到碰撞体上，同时重置模型矩阵
	void applyModel() {
		if (!mModelTransform) return;
		SQT model = *(this->mModelTransform);
		if (mIsModelSaved == model)return;
		else {
			model = model * mIsModelSaved.inv();
			mIsModelSaved = *(this->mModelTransform);
		}
		if (mType == Colli_Cube) {
			cube& c = *(cube*)mColliInstance;
			c[0] = model * c[0]; c[1] = model * c[1]; c[2] = model * c[2]; c[3] = model * c[3];
		}
		ef(mType == Colli_Ball)
		{
			ball& c = *(ball*)mColliInstance;
			c.o = model * c.o;
			c.r = this->mModelTransform->s.len();
		}
		model = SQT();
	}

	CDResult detect(ColliBody& b) {//可以用位与操作优化if语句
		ASSERT(b.mType != Colli_None && mType != Colli_None && mColliInstance && b.mColliInstance);
		applyModel();
		b.applyModel();
		if (mType == Colli_Cube) {
			if (b.mType == Colli_Cube) return isSect(*((cube*)mColliInstance), *((cube*)b.mColliInstance));
			if (b.mType == Colli_Ball) return isSect(*((cube*)mColliInstance), *((ball*)b.mColliInstance));
		}
		if (mType == Colli_Ball) {
			if (b.mType == Colli_Ball) return isSect(*((ball*)mColliInstance), *((ball*)b.mColliInstance));
			if (b.mType == Colli_Cube) return isSect(*((cube*)b.mColliInstance), *((ball*)mColliInstance));
		}
		return false;
	}
	void setBodyAsStdCube() {
		if (mColliInstance == 0)mColliInstance = new cube;
		mType = Colli_Cube; mIsModelSaved = SQT();
		body<cube>() = cube(vec3(-0.5, 0.5, -0.5), vec3(0.5, 0.5, -0.5), vec3(-0.5, 0.5, 0.5), vec3(-0.5, -0.5, -0.5));
	}
	void setBodyAsActor() {
		if (mColliInstance == 0)mColliInstance = new cube;
		mType = Colli_Cube; mIsModelSaved = SQT();
		body<cube>() = cube(vec3(-0.55, 1.85, -0.55), vec3(0.55, 1.85, -0.55), vec3(-0.55, 1.85, 0.55), vec3(-0.55, -0.05, -0.55));
	}
	void setBodyAsStdSphere() {
		if (mColliInstance == 0)mColliInstance = new ball;
		mType = Colli_Ball; mIsModelSaved = SQT();
		body<ball>() = ball(vec3(0.0f), 1);
	}
	template<class T>
	T& body() {
		return *(T*)mColliInstance;
	}
	template<class T>
	const T& body()const {
		return *(T*)mColliInstance;
	}

	const SQT* mModelTransform = 0;
	SQT mIsModelSaved;
	void* mColliInstance = 0;
	ColliType mType = Colli_None;
};