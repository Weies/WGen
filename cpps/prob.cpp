//#include"WGen.h"
//#include<iostream>
//
//using namespace std;
//vector<int> nm;
//
//void myPermute(int idx) {
//	if (idx == nm.size()) {
//		for (int i = 0; i < nm.size(); ++i)
//			debug << nm[i] << ", ";
//		debug << endl;
//		return;
//	}
//	for (int i = idx; i < nm.size(); ++i) {
//		swap(nm[i], nm[idx]);
//		myPermute(idx + 1);
//		swap(nm[i], nm[idx]);
//	}
//}
//
//int main()
//{
//	nm = vector<int>{ 1,2,3 };
//	myPermute(0);
//
//}