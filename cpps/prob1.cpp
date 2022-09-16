//#include <iostream>
//#include <vector>
//#include"WGen.h"
//#include<numeric>
//using namespace std;
//class segment_tree
//{
//public:
//	vector<int> a;
//	segment_tree(int n) : a(2 * n, 0) {};
//	int ask(int l, int r)
//	{
//		if (l > r)return 0;
//		return _ask(1, l, r, 1, a.size() / 2);
//	}
//	int _ask(int x, int le, int ri, int l, int r)
//	{
//		if (le == l && ri == r)
//			return a[x];
//		int m = (l + r) / 2;
//		if (ri <= m)
//			return _ask(x * 2, le, ri, l, m);
//		else if (le >= m)
//			return _ask(x * 2 + 1, le, ri, m + 1, r);
//		else
//			return max(_ask(x * 2, le, m, l, m), _ask(x * 2 + 1, m + 1, ri, m + 1, r));
//	}
//
//	void set(int p, int val)
//	{
//		this->p = p;
//		this->val = val;
//		_set(1, 1, a.size() / 2);
//	}
//	int p;
//	int val;
//	int _set(int x, int l, int r)
//	{
//		if (l == r)
//			return a[x] = val;
//		int m = (l + r) / 2;
//		if (p <= m)
//			_set(x * 2, l, m);
//		else
//			_set(x * 2 + 1, m + 1, r);
//		a[x] = max(a[x * 2], a[x * 2 + 1]);
//	}
//};
//int longest_subseq(vector<int> n)
//{
//	segment_tree t(*max_element(n.begin(), n.end()));
//	int maax = 0;
//	for (int i = 0; i < n.size(); ++i)
//	{
//		int ma = t.ask(1, n[i] - 1);
//		if (ma + 1 > t.ask(1, n[i]))
//		{
//			t.set(n[i], ma + 1);
//			if (ma + 1 > maax)
//				maax = ma + 1;
//		}
//	}
//	return maax;
//}
//
//int main()
//{
//	debug(longest_subseq({ 1,4,15,78,2, 7,5,7,8,9 }));
//}