//#include"WGen.h"
//void push();
//class A {
//public:
//	queue<string> que;
//	void createThread() {
//		thread td([=]() {
//			que.push("dbushdw");
//			//push();
//		});
//		td.detach();
//	}
//};
//
//A obj;
//void push()
//{
//	obj.que.push("nxsoai");
//}
//
//int getSize()
//{
//	return obj.que.size();
//}
//int main()
//{
//	debug<<"before modify,obj.que.size= "<<getSize()<<endl;
//	obj.createThread();
//	debug<<"after createThread,obj.que.size= "<<getSize()<<endl;
//	this_thread::sleep_for(3000ms);
//	debug<<"after sleep 3s,obj.size= "<<getSize()<<endl;
//	eventloop();
//}
//#include"widget.h"
//#include<winddi.h>
//#include<winapifamily.h>
//#include<atlstr.h>
//INT CALLBACK NEnumFontNameProc(LOGFONT* plf, TEXTMETRIC* /*ptm*/, INT /*nFontType*/, LPARAM lParam/**/)
//{
//	//同步调用的回调
//	vector<CString>* sysFonts = (vector<CString>*)lParam;
//	CString strVal(L"");
//	if (sysFonts!=NULL)
//	{
//		strVal = plf->lfFaceName;
//		if (strVal.Left(1)!=L"@")
//		{
//			sysFonts->push_back(strVal);
//		}
//	}
//	return TRUE; //EnumFontFamilies 返回值由此回调返回决定
//}
//
//
//void GetSystemFont(HWND& hwnd)
//{
//	vector<CString> vFont;
//	HDC hdc = ::GetDC(hwnd);
//	int nRet = ::EnumFontFamilies(hdc, (LPTSTR)NULL, (FONTENUMPROC)NEnumFontNameProc, (LPARAM)&(g_vSysFonts));
//	::ReleaseDC(hwnd, hdc);
//}