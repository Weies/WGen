#pragma once
// 一些输入控件

#include"widget.h"
#include"painter.h"
#include"font.h"
using namespace events;

namespace ui {
	//大小写锁是否开启
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
	//是否大写状态
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

		//绘制时以pos为原点
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
		//end为负一时表示拷贝从begin到末尾的所有字符,copy的text不包含索引号为end的字符
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

		//注意插入后光标不变化,需要手动设置光标
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

		//获取第which个字符的的左上角坐标
		vec2 getLU(uint which) {
			return vec2(left() + padding_left + font.testWidth(string(text.begin(), text.begin() + which)), top() + (h - cursor_h) / 2);
		}

		//获取第which个字符的的右下角角坐标
		vec2 getRB(uint which) {
			return vec2(left() + padding_left + font.testWidth(string(text.begin(), text.begin() + which)), bottom() - (h - cursor_h) / 2);
		}

		//是否命中文本区域
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

		//给全局位置，计算光标的索引号
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
			//检测Ctrl键是否按下
			if (Ctrl()) {
				switch (key) {
				case KEY_A://Ctrl + A选中所有字符
					select_begin = 0; select_end = text.size(); curCursor = text.size();
					break;
				case KEY_C://Ctrl 和 C同时按下
					if (select_begin != select_end)//如果当前选中了内容
						copyText(select_begin, select_end);//将选中的文字复制到系统剪贴板
					break;
				case KEY_V:
					eraseSelected();
					//获取系统当前剪切板内容，插入到当前光标位置，并将光标后移
					curCursor += pasteText(curCursor);
					break;
				case KEY_X://剪切选中的内容
					//将选中的文字发送到系统剪切板，光标前移，删除选中的文字
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
			case GLFW_KEY_UP://上
				break;
			case GLFW_KEY_DOWN://下
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
//	//打开剪贴板  
//	if (!::OpenClipboard(hWnd))
//		return false;
//	//如果剪贴板有内容则关闭剪贴板
//	if (!EmptyClipboard())
//	{
//		CloseClipboard();
//		return false;
//	}
//	//获取需要设置文本的长度  
//	int len = strlen(text);
//	//申请剪贴板空间
//	HANDLE hClip = GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE , (len + 1) * sizeof(char*));
//	if (hClip == NULL)
//	{
//		CloseClipboard();
//		return false;
//	}
//	//给申请的空间加锁
//	char* pBuf = (char*)GlobalLock(hClip);
//	if (pBuf == NULL)
//	{
//		GlobalFree(hClip);
//		CloseClipboard();
//		return false;
//	}
//	//拷贝文本内容到剪贴板
//	memcpy((char*)pBuf , text , len * sizeof(char*));
//	pBuf[len] = NULL;
//	//操作完成，释放锁
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
////获取剪贴板文本内容
//string GetClipBoardText(HWND hWnd)
//{
//	ASSERT(hWnd);
//	string ClipBoardText;
//	//判断剪贴板的数据格式是否可以处理。  
//	if (!IsClipboardFormatAvailable(CF_TEXT))
//		return ClipBoardText;
//
//	//打开剪贴板。          
//	if (!::OpenClipboard(hWnd))
//		return ClipBoardText;
//
//	//获取数据  
//	HANDLE hMem = GetClipboardData(CF_TEXT);
//	if (hMem != NULL)
//	{
//		//获取字符串。  
//		LPSTR lpStr = (LPSTR)GlobalLock(hMem);
//		if (lpStr != NULL)
//		{
//			ClipBoardText = lpStr;
//			//释放锁内存  
//			GlobalUnlock(hMem);
//		}
//	}
//	//关闭剪贴板        
//	CloseClipboard();
//	return ClipBoardText;
//}
