#pragma once
#include"core/log/debuger.h"

#define COORDINATE_XYZ 0//��ѧ�ϵ�����ϵ
#define COORDINATE_ZXY 1//OpenGL������ϵ
#define COORDINATE_YXZ 2//ue4������ϵ
#define COORDINATE_XZY 3//unity������ϵ
//		  ������
//			|
//			|
//			|
//			|___________�ڶ���
//		   /
//		 /
//	   /
//��һ������
//

#define COORDINATE_USE COORDINATE_XYZ//��д��ʹ�õ�����ϵ
#define COORDINATE_TARGET COORDINATE_ZXY//Ŀ����Ⱦϵͳʹ�õ�����ϵ

//#if COORDINATE_USE == COORDINATE_XYZ
//
//namespace CDN {
//
//#if COORDINATE_TARGET == COORDINATE_ZXY
//
//	inline gm::vec3 tvec3(float x , float y , float z) {
//		return gm::vec3(y , z , x);
//	}
//
//	inline gm::vec3 tvec3(const gm::vec3& v) {
//		return gm::vec3(v.y , v.z , v.x);
//	}
//
//
//	inline gm::vec4 tvec4(float x , float y , float z , float w = 1.0) {
//		return gm::vec4(y , z , x , w);
//	}
//	inline gm::vec4 tvec4(const gm::vec4& v) {
//		return gm::vec4(v.y , v.z , v.x , v.w);
//	}
//
//
//	struct vec3 {
//		vec3(float x , float y , float z) {
//			this->x = y; this->y = z; this->z = x;
//		}
//		void set(float x , float y , float z) {
//			this->x = y; this->y = z; this->z = x;
//		}
//		gm::vec3 toXYZ() {
//			swap(x , z); swap(z , y);
//			return gm::vec3(x , y , z);
//		}
//		gm::vec3 vec() {
//			return gm::vec3(x , y , z);
//		}
//		float x , y , z;
//	};
//	struct vec4 {
//		vec4(float x , float y , float z , float w = 1.0f) {
//			this->x = y; this->y = z; this->z = x; this->w = w;
//		}
//		void set(float x , float y , float z , float w = 1.0f) {
//			this->x = y; this->y = z; this->z = x; this->w = w;
//		}
//		gm::vec4 toXYZ() {
//			swap(x , z); swap(z , y);
//			return gm::vec4(x , y , z , w);
//		}
//		gm::vec4 vec() {
//			return gm::vec4(x , y , z , w);
//		}
//		float x , y , z , w;
//	};
//#endif
//
//}
//#endif