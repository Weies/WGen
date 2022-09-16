#pragma once

#include"core/base/basis.h"
#include"core/log/debuger.h"
#include"core/log/exception.h"
#include"core/math/math_include.h"
#include"core/data_structure/data_structure.h"

#include<gl/GL.h>
#include<GLFW/glfw3.h>
#include<GLEW/glew.h>

#include"color.h"
#include"colors.h"
#include"baseClass.h"

#include<cmath>
#include<vector>
#include<map>
#include<thread>
#include<algorithm>
#include<set>
#include<queue>
#define WIN32_LEAN_AND_MEAN 


using namespace gm;
using namespace std;
using winptr = GLFWwindow*;

//global �����ڷ��ʺ��������ȫ�ֱ���

#define ___global(type,name) inline type& _get_##name##(){\
	static type _##name;\
	return _##name;\
	}

namespace globals {

	extern float Priority;
	extern uint defaultShader;
	extern uint defaultVAO;
	extern uint defaultVBO;
	extern uint defaultTex;
	extern bool eventAble;//�¼��Ƿ����
	extern bool timerAble;//��ʱ���Ƿ񱻿���
	extern bool transViewport;
	extern float win_w;//��ʵ���
	extern float win_h;
	extern float pre_w;//���ڱ仯֮ǰ��ǰ�Ŀ��
	extern float pre_h;
	extern float scaleTimes;
	extern bool fixed;

	//������갴�µ�x,y���꣬�ƶ�ʱ�������
	extern int clickX;
	extern int clickY;

	extern bool useScale;//��ͼ�Ƿ�ʹ�����ţ���glPixel�Ƿ�����
	extern bool sticking;//��곤��
	extern bool mouseMoved;//��갴�º��Ƿ��ƶ��������ж�����Ƿ񳤰�
	extern int mouseX;
	extern int mouseY;//ʵʱ���������ڴ������λ��
	extern int oldX;
	extern int oldY;
	extern int mBtn;
	extern int mState;//ʵʱ�İ��������״̬
	extern float deltaX;
	extern float deltaY;//һ���϶����൱����һ����仯��
	extern bool specialKey;//�Ƿ������ⰴ��
	extern Color curColor;
	extern GLenum currentMode;
	extern float curPriority;
	extern Color curColor3;
	extern gm::mat4 curModel;
	extern gm::vec3 curNormal;
	extern float translateX;
	extern float translateY;//����ڣ�0,0�����ƽ�Ƶ�Ŀ��
	extern int timeDelay;//��ʱ���ӳ�
	extern bool LEFT_UP;//�Ƿ������Ͻ�Ϊԭ��
	extern float line_width;
	extern float point_size;
	extern float origin_x;
	extern float origin_y;
	extern bool isEditorMode;
	extern double gameTime;//��Ϸʱ��,����Ⱦ��ʼ��ȼ�ʱ
	extern double clockTime;//ʱ��ʱ�䣬����Ϸ��ͣʱ��ʱ��ʱ������ӣ���Ϸʱ�䲻��
	extern double frameps;//��¼ƽ����֡��
	extern double frameTime;//��¼��һ֡��ʱ��

	inline void useDefalut()
	{
		glUseProgram(defaultShader);
		glBindVertexArray(defaultVAO);
		glBindTexture(GL_TEXTURE_2D, defaultTex);
	}
	//��ȡ��Կ��
	inline int win_height()
	{
		return win_h;
	}
	inline int win_width()
	{
		return win_w;
	}

	class List {
	public:
		List()
		{
			arr = new point2[5000000];
			changeCapacity(ca2, false);
			cutoff[0] = 0;
		}
		void push_back(float x, float y)
		{
			x += origin_x; y += origin_y;
			arr[size].x = x;
			if (LEFT_UP)arr[size++].y = win_h - y;
			else		arr[size++].y = y;
			if (size == capacity)
				changeCapcity2();
		}
		void push_back(const point2& p)
		{
			push_back(p.x, p.y);
		}
		void reset()
		{
			size = 0;
			cur = 0;
		}
		void changeCapacity(int n, bool deleteBefore = true)
		{
			if (deleteBefore)
			{
				//debug(n);
				GLenum* mo = new GLenum[n + 5];
				Color* co = new Color[n + 5];
				int* c = new int[n + 5];
				bool* f = new bool[n + 5];
				float* p = new float[n + 5];
				copy(modes, modes + ca2, mo);
				copy(colors, colors + ca2, co);
				copy(cutoff, cutoff + ca2, c);
				copy(fixed, fixed + ca2, f);
				copy(prior, prior + ca2, p);
				/*free(normal);
				delete[] model;
				delete[] modes3;
				delete[] colors3;
				delete[] cutoff3;*/
				fixed = f;
				prior = p;
				modes = mo;
				colors = co;
				cutoff = c;
				return;
			}
			modes = new GLenum[ca2 + 5];
			colors = new Color[ca2 + 4];
			cutoff = new int[ca2 + 5];
			fixed = new bool[ca2 + 5];
			prior = new float[ca2 + 5];
		}
		void changeCapcity2()
		{
			capacity *= 1 + abs(7.0 - log10(capacity));
			point2* t = new point2[capacity + 10];
			copy(arr, arr + size, t);
			arr = t;
		}
		void start(GLenum mode)//Ĭ�ϼ̳����ȼ�
		{
			modes[cur] = mode;
			colors[cur] = curColor;
			prior[cur] = curPriority;
			fixed[cur] = globals::fixed;
		}
		int capacity = 100000; int ca2 = 100000;
		int cur = 0; int size = 0;
		GLenum* modes;
		Color* colors;
		float* prior;
		bool* fixed;
		int* cutoff;
		point2* arr;
	};

	class List3 {
	public:
		List3()
		{
			arr3 = new point<float>[capacity + 10];
			changeCapacity(ca2, false);
			cutoff3[0] = 0;
		}
		void changeCapacity(int n, bool deleteBefore = true)
		{
			if (deleteBefore)
			{
				gm::vec3* v = new gm::vec3[n + 5];
				gm::mat4* m = new gm::mat4[n + 5];
				GLenum* mo = new GLenum[n + 5];
				Color* co = new Color[n + 5];
				int* c = new int[n + 5];
				copy(normal, normal + ca2, v);
				copy(model, model + ca2, m);
				copy(modes3, modes3 + ca2, mo);
				copy(colors3, colors3 + ca2, co);
				copy(cutoff3, cutoff3 + ca2, c);
				//free(normal);
				//delete[] model;
				//delete[] modes3;
				//delete[] colors3;
				//delete[] cutoff3;
				normal = v;
				model = m;
				modes3 = mo;
				colors3 = co;
				cutoff3 = c;
				return;
			}
			normal = new gm::vec3[ca2 + 5];
			model = new gm::mat4[ca2 + 5];
			modes3 = new GLenum[ca2 + 5];
			colors3 = new Color[ca2 + 4];
			cutoff3 = new int[ca2 + 5];
		}
		void changeCapcity2()
		{
			capacity *= 1.0 + abs(8.0 - log10(capacity)) / 1.5;
			point<float>* t = new point<float>[capacity + 10];
			copy(arr3, arr3 + size3, t);
			delete[] arr3;
			arr3 = t;
		}

		void push_back3(float x, float y, float z)
		{
			arr3[size3++] = vec3(x, y, z);
			if (size3 == capacity)
			{
				changeCapcity2();
			}
		}

		void push_back3(const point<float>& p)
		{
			arr3[size3++] = p;
			if (size3 == capacity)
			{
				changeCapcity2();
			}
		}
		void reset()
		{
			size3 = 0;
			cur3 = 0;
		}
		void start3(GLenum mode)//Ĭ�ϼ̳����ȼ�
		{
			model[cur3] = curModel;
			modes3[cur3] = mode;
			colors3[cur3] = curColor3;
			normal[cur3] = curNormal;
		}
		void over()
		{
			if (++cur3 == ca2)
			{
				int ca = ca2;
				ca *= 1 + abs(6.0 - log10(ca));
				changeCapacity(ca);
				ca2 = ca;
			}
			cutoff3[cur3] = size3;
		}
		int capacity = 10; int ca2 = 10;
		int size3 = 0; int cur3 = 0;

		gm::vec3* normal;
		gm::mat4* model;
		GLenum* modes3;
		Color* colors3;
		int* cutoff3;
		point<float>* arr3;
	};

	___global(List, vers);
	___global(List3, vers3);
#define vers3 _get_vers3()
#define vers _get_vers()

	inline void glStart(GLenum mode)
	{
		currentMode = mode;
		vers.start(mode);
	}
	inline void glPixel(float x, float y)
	{
		vers.push_back(x, y);
	}
	inline void glPoint(const point2& p)
	{
		vers.push_back(p);
	}
	inline void glOver()
	{
		vers.cutoff[++vers.cur] = vers.size;
	}

	inline void glStart3(GLenum mode)
	{
		currentMode = mode;
		vers3.start3(mode);
	}
	inline void glOver3()
	{
		vers3.over();
	}
	inline void glPoint3(const point<float>& p)
	{
		vers3.push_back3(p);
	}
	inline void glPixel3(float x, float y, float z)
	{
		vers3.push_back3(x, y, z);
	}


}
