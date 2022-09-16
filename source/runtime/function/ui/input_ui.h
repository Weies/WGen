#pragma once
// һЩ����ؼ�

#include"widget.h"
#include"painter.h"
#include"font.h"
using namespace events;

namespace ui {
	//��Сд���Ƿ���
	inline bool Caps() {
		return  GetKeyState(VK_CAPITAL);
	}
	inline bool Shift() {
		return ((GetKeyState(VK_SHIFT) & 0x8000) != 0);
	}
	inline bool Ctrl() {
		return  GetKeyState(VK_CONTROL) & 0x8000;
	}
	inline bool Alt() {
		return GetKeyState(VK_MENU);
		//return GetKeyState(VK_F)
	}
	//�Ƿ��д״̬
	inline bool Cap() {
		return (Caps() ^ Shift());
	}
	inline void hideMouseCursor() {
		glfwSetInputMode(mainwin, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}


	class InputBox :public Widget {
	public:
		InputBox(bWid* father = 0) {
			mType = t_InputBox;
			setParent(father);
			setBGC(255);
			setPosAs(CENTER);
			resize(200, 40);
			mIsMovable = false;
			onkeydown = [this](ke& e)->bool {
				processKey(e); return true;
			};
			onkeystick = [this](ke& e)->bool { processKey(e); return true; };
			onclick = [this](me& e)->bool {
				if (hitText(vec2(e.x, e.y))) {
					curCursor = caculCursorPos(e.x);
					select_begin = 0; select_end = 0;
				}
				return true;
			};
			onmove = [this](me& e)->bool {
				if (hitText(vec2(e.x, e.y))) {
					if (!start_select) {
						start_select = true;
						select_begin = caculCursorPos(e.x);
						select_end = select_begin;
						curCursor = select_begin;
					}
					else {
						select_end = caculCursorPos(e.x);
						curCursor = select_end;
					}
				}
				else if (mIsMovable)translate(deltaX, deltaY);
				return true;
			};
			onmouseup = [this](me& e)->bool {
				if (start_select) {
					start_select = false;
					select_end = caculCursorPos(e.x);
				}
				return true;
			};
			timer(500.0, [this]()->bool {
				cursorShowing = !cursorShowing;

				return false;
				});
		}

		InputBox(int w, int h, bWid* father = 0) :InputBox()
		{
			setParent(father);
			resize(w, h);
		}
		void resize(int w, int h) {
			Widget::resize(w, h);
			padding_top = padding_bottom = (h - cursor_h) / 2;
		}

		//����ʱ��posΪԭ��
		void draw()
		{
			glLineWidth(1);
			ptr.fix();
			ptr.setColor(mBackgroundColor);
			ptr.setCenter(0, 0);
			ptr.cfillRect(this->w - 2, this->h - 2);
			ptr.setColor(border_color);
			ptr.cdrawRect(this->w, this->h);
			ptr.setColor(select_bgc);
			ptr.fillRect(getLU(select_begin), getRB(select_end));
			if (text.size() == 0) {
				font.setColor(font_color.setAlpha(0.5));
				rcvdrawString(left() + padding_left, center().y, hint);
			}
			else {
				font.setColor(font_color);
				rcvdrawString(left() + padding_left, 0, text);
			}
			ptr.setColor(cursor_color);
			if (cursorShowing && mIsFocus)
				ptr.fillRect(left() + padding_left + font.testWidth(string(text.begin(), text.begin() + curCursor))
					, -cursor_h / 2.0f, cursor_w, cursor_h);
			ptr.stopfix();
			glLineWidth(line_width);
		}

		Color cursor_color = DARK;
		Color border_color = DARK;
		Color font_color = SKYBLUE;
		Color select_bgc = SKYBLUE.setAlpha(0.5);
		float padding_left = 12; float padding_right = 12;
		float padding_top = 5; float padding_bottom = 5;
		float cursor_h = 30.0f; float cursor_w = 2.0f;

		string Text()
		{
			return text;
		}

		void setText(string str)
		{
			text = str;
			curCursor = str.length();
		}
		void setHint(const string& s) {
			hint = s;
		}
		//endΪ��һʱ��ʾ������begin��ĩβ�������ַ�,copy��text������������Ϊend���ַ�
		uint copyText(uint begin = 0, uint end = -1) {
			if (begin > text.size())excep(WERROR_ARGUMENT, "index out of range");
			string str;
			if (end > text.size()) {
				str = string(text.begin() + begin, text.end());
				glfwSetClipboardString(mainwin, str.c_str()); return text.size() - begin;
			}
			str = string(text.begin() + begin, text.begin() + end);
			glfwSetClipboardString(mainwin, str.c_str());
			return end - begin;
		}
		uint pasteText(uint idx) {
			ASSERT(idx <= text.size());
			string str = glfwGetClipboardString(mainwin);
			text.insert(text.begin() + idx, str.begin(), str.end());
			return str.size();
		}

		//ע�������겻�仯,��Ҫ�ֶ����ù��
		void insertChar(uint where, char c) {
			text.insert(text.begin() + where, c);
		}
		void insert(uint where, const string& s) {
			text.insert(text.begin() + where, s.begin(), s.end());
		}
		function<void(ke& e)> onenter = 0;
		int curCursor = 0; uint select_begin = 0; uint select_end = 0;
		string text; string hint;
		bool cursorShowing = true; bool start_select = false;
	private:

		//��ȡ��which���ַ��ĵ����Ͻ�����
		vec2 getLU(uint which) {
			return vec2(left() + padding_left + font.testWidth(string(text.begin(), text.begin() + which)), top() + (h - cursor_h) / 2);
		}

		//��ȡ��which���ַ��ĵ����½ǽ�����
		vec2 getRB(uint which) {
			return vec2(left() + padding_left + font.testWidth(string(text.begin(), text.begin() + which)), bottom() - (h - cursor_h) / 2);
		}

		//�Ƿ������ı�����
		bool hitText(const vec2& p) {
			return in_rect(vec2(left() - 5, top() + (h - cursor_h) / 2), vec2(w - 14, cursor_h), p);
		}
		void eraseSelected() {
			if (select_begin != select_end) {
				if (select_begin > select_end)swap(select_begin, select_end);
				text.erase(text.begin() + select_begin, text.begin() + select_end);
				if (curCursor == select_end)curCursor -= select_end - select_begin;
				select_begin = select_end = 0;
			}
		}

		//��ȫ��λ�ã��������������
		uint caculCursorPos(float global_x) {
			float x = global_x - left() - 7;
			int f = 0; int e = text.size();
			int mid = (f + e) / 2;
			while (f < e) {
				if (x < font.testWidth(string(text.begin(), text.begin() + mid))) {
					e = mid - 1;
				}
				else f = mid + 1;
				mid = (f + e) / 2;
			}
			return f;
		}
		void processKey(ke& e) {
			int key = e.key;
			//���Ctrl���Ƿ���
			if (Ctrl()) {
				switch (key) {
				case KEY_A://Ctrl + Aѡ�������ַ�
					select_begin = 0; select_end = text.size(); curCursor = text.size();
					break;
				case KEY_C://Ctrl �� Cͬʱ����
					if (select_begin != select_end)//�����ǰѡ��������
						copyText(select_begin, select_end);//��ѡ�е����ָ��Ƶ�ϵͳ������
					break;
				case KEY_V:
					eraseSelected();
					//��ȡϵͳ��ǰ���а����ݣ����뵽��ǰ���λ�ã�����������
					curCursor += pasteText(curCursor);
					break;
				case KEY_X://����ѡ�е�����
					//��ѡ�е����ַ��͵�ϵͳ���а壬���ǰ�ƣ�ɾ��ѡ�е�����
					if (select_begin != select_end) {
						copyText(select_begin, select_end);
						curCursor -= select_end - select_begin;
						text.erase(text.begin() + select_begin, text.begin() + select_end);
					}
					break;
				default:
					//debug << "Ctrl with unkonwn key" << key << endl;
					break;
				}
				return;
			}
			if (key >= ' ' && key <= 'a')
			{
				if ('A' <= key && key <= 'Z') {
					if (!Cap())key += 'a' - 'A';
				}
				else if (Shift()) {
					switch (key) {
					case ';':
						key = ':';
						break;
					case '\'':
						key = '\"';
						break;
					case '/':
						key = '?';
						break;
					case ',':
						key = '<';
						break;
					case '.':
						key = '>';
						break;
					case '[':
						key = '{';
						break;
					case ']':
						key = '}';
						break;
					case '\\':
						key = '|';
						break;
					case '=':
						key = '+';
						break;
					case '-':
						key = '_';
						break;
					case '1':
						key = '!';
						break;
					case '2':
						key = '@';
						break;
					case '3':
						key = '#';
						break;
					case '4':
						key = '$';
						break;
					case '5':
						key = '%';
						break;
					case '6':
						key = '^';
						break;
					case '7':
						key = '&';
						break;
					case '8':
						key = '*';
						break;
					case '9':
						key = '(';
						break;
					case '0':
						key = ')';
						break;
					case '`':
						key = '~';
						break;
					default:
						break;
					}
				}
				eraseSelected();
				insertChar(curCursor, key);
				++curCursor;
				return;
			}
			if (key < 330 && key >= 320) {
				eraseSelected();
				insertChar(curCursor, char(key - 320 + '0'));
				++curCursor;
				return;
			}
			switch (e.key)
			{
			case GLFW_KEY_DELETE:case GLFW_KEY_BACKSPACE:
				if (select_begin != select_end) {
					eraseSelected();
				}
				else if (curCursor > 0)
				{
					text.erase(text.begin() + curCursor - 1, text.begin() + curCursor);
					curCursor--;
				}
				break;
			case GLFW_KEY_ENTER:
				if (onenter)onenter(e);
				setFocus(false);
				break;
			case GLFW_KEY_UP://��
				break;
			case GLFW_KEY_DOWN://��
				break;
			case GLFW_KEY_LEFT:
				if (curCursor > 0)
					curCursor--;
				break;
			case GLFW_KEY_RIGHT:
				if (curCursor < text.length())
					curCursor++;
				break;
			case KEY_ESCAPE:
				mIsFocus = false;
				break;
			case KEY_TAB:
				text += char('\t');
				++curCursor;
				break;
			case 345:
				break;
			default:
				//debug << "unknown key: " << key << endl;
				break;
			}
		}
	};

	class InputArea :public Widget {
	public:
		int marginleft = 10;
		int margintop = 5;
		InputArea(int w, int h) :Widget(w, h)
		{
			mType = t_InputArea;
			box1.setText("hahhaa");
			onmove = [=](me& e)->bool {
				moveto(e.x, e.y);
			};
			moveto(400, 100);
			resize(w, h);
			box1.onmove = 0;
		}
		void moveto(float x, float y)
		{
			mPosition.x = x; mPosition.y = y;
			box1.moveto(x, y + this->h / 4);
			box2.moveto(x, y - this->h / 4);
		}
		void setWords(string s)
		{
			leftWords = s;
		}

		void setPadding(int x, int y)
		{
			marginleft = x;
			margintop = y;
			box1.resize(this->w - 2 * marginleft, this->h / 2 - margintop);
			box2.resize(this->w - 2 * marginleft, this->h / 2 - margintop);
		}

		void resize(int w, int h)
		{
			this->w = w; this->h = h;
			box1.resize(w - 2 * marginleft, h / 2 - margintop);
			box2.resize(w - 2 * marginleft, h / 2 - margintop);
		}

		void draw()
		{
			ptr.fix();
			ptr.setColor(255, 255, 255);
			ptr.setCenter(mPosition.x, mPosition.y);
			ptr.cfillRect(this->w, this->h);
			ptr.setColor(0, 0, 0);
			//drawString(pos.x-50, pos.y, leftWords);
			ptr.stopfix();
		}
		InputBox box1; InputBox box2;
		string leftWords;
	};
}

//bool SetClipBoardText(LPCSTR text , HWND hWnd)
//{
//	ASSERT(hWnd);
//	//�򿪼�����  
//	if (!::OpenClipboard(hWnd))
//		return false;
//	//�����������������رռ�����
//	if (!EmptyClipboard())
//	{
//		CloseClipboard();
//		return false;
//	}
//	//��ȡ��Ҫ�����ı��ĳ���  
//	int len = strlen(text);
//	//���������ռ�
//	HANDLE hClip = GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE , (len + 1) * sizeof(char*));
//	if (hClip == NULL)
//	{
//		CloseClipboard();
//		return false;
//	}
//	//������Ŀռ����
//	char* pBuf = (char*)GlobalLock(hClip);
//	if (pBuf == NULL)
//	{
//		GlobalFree(hClip);
//		CloseClipboard();
//		return false;
//	}
//	//�����ı����ݵ�������
//	memcpy((char*)pBuf , text , len * sizeof(char*));
//	pBuf[len] = NULL;
//	//������ɣ��ͷ���
//	GlobalUnlock(hClip);
//	if (NULL == SetClipboardData(CF_TEXT , hClip))
//	{
//		GlobalFree(hClip);
//		CloseClipboard();
//		return false;
//	}
//	CloseClipboard();
//	return true;
//}
//
////��ȡ�������ı�����
//string GetClipBoardText(HWND hWnd)
//{
//	ASSERT(hWnd);
//	string ClipBoardText;
//	//�жϼ���������ݸ�ʽ�Ƿ���Դ���  
//	if (!IsClipboardFormatAvailable(CF_TEXT))
//		return ClipBoardText;
//
//	//�򿪼����塣          
//	if (!::OpenClipboard(hWnd))
//		return ClipBoardText;
//
//	//��ȡ����  
//	HANDLE hMem = GetClipboardData(CF_TEXT);
//	if (hMem != NULL)
//	{
//		//��ȡ�ַ�����  
//		LPSTR lpStr = (LPSTR)GlobalLock(hMem);
//		if (lpStr != NULL)
//		{
//			ClipBoardText = lpStr;
//			//�ͷ����ڴ�  
//			GlobalUnlock(hMem);
//		}
//	}
//	//�رռ�����        
//	CloseClipboard();
//	return ClipBoardText;
//}
