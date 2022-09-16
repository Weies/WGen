//#include <iostream>
//#include"WGen.h"
//#include<set>
//#include<new>
//using namespace std;
//
//// f[i][w] = max(f[i-1][w-wi]+wi,f[i-1][w]);
////
//constexpr int maxn = 10;
//int W, N;
//int f[maxn][100];
//int w[maxn];
//int g[maxn];
//struct {
//	unsigned short rsv : 7,
//		type : 5,
//		log : 1,
//		log_begin : 1,
//		log_end : 1;
//}flags;
//
////void* operator new(size_t size)throw(std::nothrow_t) {
////	void* p = malloc(size);
////	debug((uint)p);
////	return p;
////}
//
//class Mynew {
//public:
//	Mynew()throw(std::bad_alloc) { p = 78; }
//	/*void* operator new(size_t size) {
//		auto* pp = malloc(size);
//		return pp;
//	}*/
//
//	virtual void my() {
//
//	}
//	int p = 156;
//private:
//};
//ll qow(ll a, ll p) {
//	ll ret = 1;
//	while (p) {
//		if (p & 1)ret *= a;
//		a *= a;
//		p >>= 1;
//	}
//	return ret;
//}
//
//int main()
//{
//	Mynew* mn = new Mynew;
//	//debug(mn->p);
//	int a[10] = { 1,7,8,4,5,4,4 };
//	memset(a, 2, sizeof(a));
//	for (auto x : a) {
//		debug(x);
//	}
//	//thread t; t.join();
//	
//	//debug.debugbit((void*)a, 32);
//	return 0;
//	//cin.tie(0);
//	//cin.sync_with_stdio(0);
//	//cin >> W >> N;
//	//for (int i = 0; i < N; ++i)
//	//{
//	//    cin >> w[i] >> g[i];
//	//}
//	//// f[0][W] =
//	//for (int i = 1; i < N; ++i)
//	//{
//	//    for (int j = 0; j <= W; ++j)
//	//    {
//	//        int ma = 0;
//	//        if (j - w[i - 1] >= 0)
//	//            ma = f[i - 1][j - w[i - 1]] + g[i];
//	//        f[i][j] = max(ma, f[i - 1][j]);
//	//    }
//	//}
//	//debug << f[N - 1][W];
//	vector<int> i{ 1,5,5,5,7,8,5,1,8,4 };
//	//sort(i.begin(), i.end());
//	//debug(*lower_bound(i.begin(), i.end(), 65));
//	//*min_element(i.begin(), i.end());
//	//minmax_element(i.begin(), i.end());
//	sort(i.begin(), i.end());
//	multiset<int> se;
//	se.emplace(2); se.emplace(3);
//	se.emplace(1); se.emplace(2); se.emplace(3);
//	se.emplace(1); se.emplace(1);
//	auto it = se.find(1);
//	/*while (it != se.end()) {
//		debug(*it++);
//	}*/
//	/*auto itt = unique(i.begin(), i.end());
//	i.resize(itt - i.begin());
//	for (auto it = i.begin(); it != itt; ++it) {
//		debug(*it);
//	}*/
//
//
//}