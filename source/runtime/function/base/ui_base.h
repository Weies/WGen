#pragma once
#include"colors.h"
#include"global_values.h"
using namespace globals;

namespace ui {
#define UPPERLEFT	0
#define CENTER		1

	inline bool in_rect(vec2 pos, vec2 wihe, vec2 p) {
		return(pos.x <= p.x && p.x <= pos.x + wihe.x && pos.y <= p.y && p.y <= pos.y + wihe.y);
	}
	class BaseWidget;

	extern BaseWidget* cfocus;//��ǰ������뽹���
	extern BaseWidget* cur;//����϶������а��ŵĿؼ�
	extern void* win;
	enum UIType {
		t_BaseWidget = 0,
		t_Widget = 1,
		t_ScrollBar = 2,
		t_InputBox = 3,
		t_EventWidget = 4,
		t_InputArea = 5,
		t_Button = 6,
		t_Bar = 7,
		t_Window = 8,
		t_FixedWidget = 9,
		t_CameraBoard = 10,
	};



	//BaseWidget�������д��ڿؼ��Ļ���
	//pos�ǻ�ͼ��ԭ��,pos������Ϊ���Ͻǣ�Ҳ������Ϊ��ͼ������
	class BaseWidget {
	protected:
		us bit = 0;
	public:
		//prior���Դ�0��1024
		float		mPriority = 1.0;
		float		mDefaultPriority = 1.0;
		bool		mIsFixed = false;//�����Ƿ���transform�����Ӱ��
		union { float w; float mWdith; };
		union { float h; float mHeight; };//���
		vec2		mPosition;//���Ͻǵ�x,y����
		bool		mIsMovable = true;//�Ƿ���ƶ�
		bool		mIsShowing = true;//�Ƿ���ʾ0
		bool		mIsFocus = false;
		Color		mBackgroundColor;//������ɫ
		UIType		mType = t_BaseWidget;
		vec2		mOffsetUpperLeft;//���Ͻ���Ӧƫ��
		vec2		mOffsetBottomRight;	//���Ͻ���Ӧƫ��
		bool		mIsPosAsCenter = false;
		BaseWidget* mFather = 0;
		vector<BaseWidget*> mSons;

		string typeStr() const {
			switch (mType) {
			case t_BaseWidget:		return "BaseWidget";
			case t_Widget:			return "Widget";
			case t_ScrollBar:		return "ScrollBar";
			case t_InputBox:		return "InputBox";
			case t_EventWidget:		return "EventWidget";
			case t_InputArea:		return "InputArea";
			case t_Button:			return "Button";
			case t_Bar:				return "Bar";
			case t_Window:			return "Window";
			case t_FixedWidget:		return "FixedWidget";
			case t_CameraBoard:		return "CameraBoard";
			}
		}


		BaseWidget(BaseWidget* father = 0) :mFather(father), w(100), h(100), mPosition(100, 100), mBackgroundColor(SKYBLUE) {
			setPriority(curPrior);
			curPrior += 1;
			mDefaultPriority = mPriority;
		}

		void setParent(BaseWidget* father) {
			if (mFather)mFather->delChild(this);
			if (father == 0) {
				mFather = (BaseWidget*)win;
				mFather->addChild(this); return;
			}
			mFather = father;
			mFather->addChild(this);
		}
		bool addChild(BaseWidget* son) {
			int where = 0; son->mFather = this;
			for (int i = 0; i < mSons.size(); ++i) {
				if (mSons[i]->mPriority < son->mPriority)
					where = i;
				if (mSons[i] == son) {
					return false;
				}
			}
			mSons.insert(mSons.begin() + where, son); return true;
		}
		bool delChild(BaseWidget* son) {
			for (int i = 0; i < mSons.size(); ++i) {
				if (mSons[i] == son) {
					mSons.erase(mSons.begin() + i); return true;
				}
			}
			return false;
		}

		virtual bool inArea(float xx, float yy) const
		{
			vec2 pp = vec2(xx, yy);
			if (mIsPosAsCenter) pp += vec2(w, h) * 0.5;
			return in_rect(-mOffsetUpperLeft, vec2(w, h) + mOffsetBottomRight, pp);
		}
		void setUpperLeftOffset(float x, float y)
		{
			mOffsetUpperLeft.set(x, y);
		}
		void setBottomRightOffset(float x, float y)
		{
			mOffsetBottomRight.set(x, y);
		}
		//������Ӧ������posΪԭ��
		void setRange(float x, float y, float w, float h) {
			mOffsetUpperLeft.set(-x, -y); mOffsetBottomRight.set(w - this->w, h - this->h);
		}

		void set(us which, bool val) {
			bitSet(bit, which, val);
		}
		bool check(us which) const {
			return bitTest(bit, which);
		}
		virtual void setMovable(bool m) {
			mIsMovable = m;
		}
		virtual void draw() {};
		void setBGC(float r, float g, float b, float a = 1)
		{
			mBackgroundColor = Color(r, g, b, a);
		}
		void setBGC(const Color& c) {
			mBackgroundColor = c;
		}
		virtual void scale(float times = 1.0) {
			w *= times;
			h *= times;
		}
		void show(bool _show) {
			mBackgroundColor.a = max(0.5f, mBackgroundColor.a);
			mIsShowing = _show;
		}
		virtual void setFocus(bool focus = true)
		{
			if (focus) {
				cfocus = this; mIsFocus = true;
				mPriority = 1024;
			}
			else {
				cfocus = 0; mPriority = mDefaultPriority;
				mIsFocus = focus;
			}
		}
		void setPosAs(bool CENTER_or_UPPERLEFT) {
			mIsPosAsCenter = CENTER_or_UPPERLEFT;
		}
		virtual void resize(float width, float height) {
			w = width; h = height;
		}

		//��ѯpos��ȫ�ֵ�����
		vec2 queryGlobalPosition() const {
			vec2 ret = mPosition;
			const BaseWidget* ft = this;
			while (ft->mFather) {
				ft = ft->mFather;
				ret += ft->mPosition;
			}
			return ret;
		}
		vec2 queryScreenPosition() const {
			vec2 ret = mPosition;
			BaseWidget* ft = this->mFather;
			while (ft) {
				ret += ft->mPosition;
				ft = ft->mFather;
			}
			return ret;
		}

		//get the edge of the widget
		float left() const {
			if (mIsPosAsCenter) return -w / 2;
			else return 0;
		}
		float right() const {
			if (mIsPosAsCenter) return w / 2;
			else return w;
		}
		float top() const {
			if (mIsPosAsCenter) return -h / 2;
			else return 0;
		}
		float bottom() const {
			if (mIsPosAsCenter) return h / 2;
			else return h;
		}

		//��ѯ��posΪԭ�������
		vec2 center() const {
			if (mIsPosAsCenter)return vec2(0, 0);
			else return vec2(w, h) * 0.5;
		}

		//moveto��֤�������Ͻ���p��
		virtual void moveto(const vec2& p) {
			if (mIsPosAsCenter)mPosition = p + vec2(w, h) * 0.5;
			else mPosition = p;
		}
		virtual void moveto(float x, float y) {
			moveto(vec2(x, y));
		}
		//setCenter��֤����������p��
		virtual void setCenter(const vec2& cen) {
			if (mIsPosAsCenter)mPosition = cen;
			else mPosition = cen - vec2(w, h) * 0.5;
		}
		virtual void setCenter(float x, float y) {
			setCenter(vec2(x, y));
		}
		void setPriority(float pri) {
			mPriority = pri;
		}
		void setDefaultPri(float pri) {
			mDefaultPriority = pri;
		}
		void resetPri() {
			mPriority = mDefaultPriority;
		}

		//flow: �¼��Ƿ���������
		//����true���¼�������ϣ����ٽ��д���
		virtual bool handleKeyEvent(void* e, bool flow = false) {
			return false;
		}
		virtual bool handleMouseEvent(void* e, bool flow = true) {
			return false;
		}
		virtual bool handleRepaintEvent(void* e, bool flow = true) {
			if (!mIsShowing)return false;
			origin_x += mPosition.x; origin_y += mPosition.y; curPriority += mPriority;
			if (flow)for (int i = 0; i < mSons.size(); ++i) {
				mSons[i]->handleRepaintEvent(e);
			}
			mIsFocus = (cfocus == this);
			draw();
			curPriority -= mPriority; origin_x -= mPosition.x; origin_y -= mPosition.y;
			return false;
		}
		static int curPrior;
	};

	using bWid = BaseWidget;
};
