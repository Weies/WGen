//#include"WGen.h"
//#include<iostream>
//#include<vector>
//using namespace std;
//
////int main() {
////	int N; vector<int> li;
////	int tp;
////	while (N--) {
////		cin >> tp;
////		li.push_back(tp);
////	}
////	int sh; cin >> sh;
////	vector<int> o; o.resize(li.size());
////	for (int i = 0; i < li.size(); ++i) {
////		o[i] = li[(i + sh) % li.size()];
////	}
////	for (int i = 0; i < li.size(); ++i) {
////		cout << o[i] << " ";
////	}
////}
//
//bool check(int a, int b, int c, int m) {
//	if (m * (m - 1) / 2 < c)return true;
//	else return false;
//}
//
//int main() {
//	int a, b, c;
//	//4 2 6
//	cin >> a >> b >> c;
//
//	int l = 0; int r = c; int m;
//	while (l < r) {
//		m = (l + r) / 2;
//		if (check(a, b, c, m))l = m;
//		else r = m;
//	}
//	cout << m;
//}
//
////int main() {
////	int K, L, R, T, X, Y;
////	int N; cin >> N;
////	while (N--) {
////		bool t = true;
////		cin >> K >> L >> R >> T >> X >> Y;
////		for (int i = 0; i < T; ++i) {
////			if (K + Y < R)K += Y;
////			K -= X;
////			if (!(K <= R && K >= L)) {
////				cout << "No" << endl, t = 0; break;
////			}
////		}
////		if (t)cout << "Yes" << endl;
////	}
////}