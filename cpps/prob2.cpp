//#include <iostream>
//#include <vector>
//#include "WGen.h"
//#include <numeric>
//using namespace std;
//
////void qsort(vector<int>& a, int l, int r) {
////	if (l >= r)return;
////	int i = l; int j = r + 1;
////	while (true) {
////		while (i < r && a[++i] < a[l]);
////		while (j > l && a[--j] > a[l]);
////		if (i >= j)break;
////		swap(a[i], a[j]);
////	}
////	swap(a[l], a[j]);
////	qsort(a, l, j - 1);
////	qsort(a, j + 1, r);
////}
////#include <iostream>
////#include <vector>
////using namespace std;
////
////class segment_tree
////{
////public:
////	vector<int> a;
////	segment_tree(int n) : a(2 * n + 1, 0) {};
////	int ask(int l, int r)
////	{
////		return _ask(1, l, r, 1, a.size() - 1);
////	}
////	int _ask(int x, int le, int ri, int l, int r)
////	{
////		if (le == l && ri == r)
////			return a[x];
////		int m = (l + r) / 2;
////		if (ri <= m)
////			return _ask(x * 2, le, ri, l, m);
////		else if (le > m)
////			return _ask(x * 2 + 1, le, ri, m + 1, r);
////		else
////			return max(_ask(x * 2, le, ri, le, m), _ask(x * 2 + 1, le, ri, m + 1, ri));
////	}
////	void add(int p, int val)
////	{
////	}
////	void set(int p, int val)
////	{
////		this->p = p;
////		this->val = val;
////		_set(1, p, p, 1, a.size() - 1);
////	}
////	int p;
////	int val;
////	int _set(int x, int le, int ri, int l, int r)
////	{
////		if (le == l && ri == r)
////			return a[x] = val;
////		int m = (l + r) / 2;
////		if (ri <= p)
////			return _ask(x * 2, le, ri, l, m);
////		else if (le > p)
////			return _ask(x * 2 + 1, le, ri, m + 1, r);
////		else
////			return max(_ask(x * 2, le, ri, le, m), _ask(x * 2 + 1, le, ri, m + 1, ri));
////	}
////};
////
////class ST
////{
////public:
////	vector<int> a;
////	ST(int n) : a(2 * n, 0) {}
////	void build(vector<int>& arr) {
////		_build(arr, 1, 1, a.size() / 2);
////	}
////	void _build(vector<int>& arr, int x, int l, int r)
////	{
////		if (l == r) {
////			if (l >= arr.size())a[x] = 0;
////			else a[x] = arr[l - 1];
////			return;
////		}
////		int m = (r + l) / 2;
////		_build(arr, x * 2, l, m);
////		_build(arr, x * 2 + 1, m + 1, r);
////		a[x] = max(a[x * 2], a[x * 2 + 1]);
////	}
////	void set(int p, int val)
////	{
////		pos = p;
////		value = val;
////		_set(1, 1, a.size() / 2);
////	}
////	int pos;
////	int value;
////	void _set(int x, int l, int r)
////	{
////		if (l == r) {
////			a[x] = value; return;
////		}
////		int m = (r + l) / 2;
////		if (pos <= m)
////			_set(x * 2, l, m);
////		else
////			_set(x * 2 + 1, m + 1, r);
////		a[x] = max(a[x * 2], a[x * 2 + 1]);
////	}
////	void add(int p, int val)
////	{
////		pos = p;
////		value = val;
////		_add(1, 1, a.size() / 2);
////	}
////	void _add(int x, int l, int r)
////	{
////		if (l == r) {
////			a[pos] += value; return;//这里直接返回
////		}
////
////		int m = (r + l) / 2;
////		if (pos <= m)
////			_add(x * 2, l, m);
////		else
////			_add(x * 2 + 1, m + 1, r);
////		a[x] = max(a[x * 2], a[x * 2 + 1]);
////	}
////	int ask(int l, int r)
////	{
////		if (l > r)return 0;
////		return _ask(1, l, r, 1, a.size() / 2);
////	}
////	int _ask(int x, int le, int ri, int l, int r)
////	{
////		if (le == l && ri == r)
////			return a[x];
////		int m = (l + r) / 2;
////		if (ri <= m)
////		{//注意这里填le/ri
////			return _ask(x * 2, le, ri, l, m);
////		}
////		else if (le > m)
////		{
////			return _ask(x * 2 + 1, le, ri, m + 1, r);
////		}
////		else//只有这里填le,m
////			return max(_ask(x * 2, le, m, l, m), _ask(x * 2 + 1, m + 1, ri, m + 1, r));
////	}
////};
////
////int longest_subseq(vector<int> n)
////{
////	ST t(*max_element(n.begin(), n.end()));
////	int maax = 0;
////	for (int i = 0; i < n.size(); ++i)
////	{
////		int ma = t.ask(1, n[i] - 1);
////		if (ma + 1 > t.ask(n[i], n[i]))
////		{
////			t.set(n[i], ma + 1);
////			if (ma + 1 > maax)
////				maax = ma + 1;
////		}
////	}
////	return maax;
////}
////void permute(vector<int>& a, int idx)
////{
////	if (idx == a.size())
////	{
////		return;
////	}
////	for (int i = idx; i < a.size(); ++i)
////	{
////		std::swap(a[idx], a[i]);
////		permute(a, idx + 1);
////		std::swap(a[idx], a[i]);
////	}
////}
////
////class TreeArray {
////public:
////	vector<int> a;
////	TreeArray(int n) :a(n + 1) {}
////	void init(vector<int>& v) {
////		vector<int> sum(v.size() + 1);
////		sum[0] = 0; a[0] = 0;
////		for (int i = 0; i < v.size(); ++i)sum[i + 1] = sum[i] + v[i];
////		for (int i = 1; i <= v.size(); ++i) {
////			a[i] = sum[i] - sum[i - lb(i)];//i-lb(i)
////		}
////	}
////	int lb(int i) {
////		return i & (-i);
////	}
////	void set(int p, int val) {
////		int cur = val - ask(p, p);
////		while (p < a.size()) {
////			a[p] += cur;
////			p += lb(p);
////		}
////	}
////	void add(int p, int val) {
////		while (p < a.size()) {
////			a[p] += val;
////			p += lb(p);
////		}
////	}
////	int ask(int l, int r) {
////		return ask(r) - ask(l - 1);
////	}
////	int ask(int p) {
////		int ret = 0;
////		for (int i = p; i > 0; i -= lb(i))
////			ret += a[i];
////		return ret;
////	}
////};
////void ssqort(vector<int>& a, int low, int high) {
////	if (low >= high)return;
////	int i = low; int j = high + 1;
////	while (true) {
////		while (i < high && a[++i] < a[low]);
////		while (j > low && a[--j] > a[low]);
////		if (i >= j)break;
////		swap(a[i], a[j]);
////	}
////	swap(a[j], a[low]);
////	ssqort(a, low, j - 1);
////	ssqort(a, j + 1, high);
////}
////
////struct Edge {
////	int u; int v; int w; int next;
////};
////Edge g[1000]; int cnt = 0;
////int head[1000];
////void init() {
////	memset(head, -1, 4000);
////	for (int i = 0; i < 1000; ++i) {
////
////	}
////}
////void add_edge(int u, int v, int w) {
////	g[cnt].v = v;
////	g[cnt].w = w;
////	g[cnt].u = u;
////	g[cnt].next = head[u];
////	head[u] = cnt++;
////}
////void traverse() {
////	int v = 0;
////	for (int i = head[v]; ~i; i = g[i].next) {
////
////	}
////}
////int dis[100][100];
////void floyd() {
////	memset(dis, 0x7f, 10000 * 4);//最短路初始化为无穷
////	for (int k = 0; k < 100; ++k) {
////		for (int i = 0; i < 100; ++i) {
////			for (int j = 0; j < 100; ++j)
////				dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
////		}
////	}
////}
////void dijkstra(int from) {
////	vector<int> dis(100, 0x7fffffff); dis[from] = 0;
////	vector<bool> vis(100, 0);
////	using pa = pair<int, int>;
////	priority_queue<pa> q;
////	q.push({ 0,from });
////	while (!q.empty()) {
////		pa p = q.top(); q.pop();
////		int fro = p.second; vis[fro] = true;
////		for (int i = head[fro]; ~i; i = g[i].next) {
////			if (!vis[g[i].v] && dis[g[i].v] > dis[fro] + g[i].w) {
////				dis[g[i].v] = dis[fro] + g[i].w;
////				q.push({ dis[g[i].v],g[i].v });
////			}
////		}
////	}
////}
////void bellmanford(int from) {
////	vector<int> dis(100); dis[from] = 0;
////	for (int i = 0; i < 100; ++i) {
////		for (int j = 0; j < 200; ++j) {
////			//注意要存储from
////			dis[g[j].v] = min(dis[g[j].v], dis[g[j].u] + g[j].w);
////		}
////	}
////}
//////spfa和bell都需要保存g[i].from
////void spfa(int from) {
////	vector<int> dis(100, 0x7fffffff); dis[from] = 0;
////	queue<int> q; q.push(from); vector<bool> inque(100, 0);
////	while (!q.empty()) {
////		int fro = q.front(); q.pop(); inque[from] = 0;
////		for (int i = head[from]; ~i; i = g[i].next) {
////			if (dis[g[i].v] < dis[g[i].u] + g[i].w) {
////				dis[g[i].v] < dis[g[i].u] + g[i].w;
////				//cnt[g[i].v]++;
////				//更小时才考虑放入队列
////				if (!inque[g[i].v]) {
////					inque[g[i].v] = 1;
////					q.push(g[i].v);
////				}
////			}
////		}
////	}
////}
////void kahn() {
////	vector<int> indeg(100, 0);
////	for (int i = 0; i < cnt; ++i)
////		indeg[g[i].v] += 1;
////	vector<int> out; queue<int> q;
////	for (int i = 0; i < indeg.size(); ++i)
////		if (indeg[i] == 0)q.push(i);
////	while (!q.empty()) {
////		int fro = q.front(); q.pop(); out.push_back(fro);
////		if (out.size() > 100);//有环
////		for (int i = head[fro]; ~i; i = g[i].next) {
////			if (--indeg[g[i].v] == 0)q.push(g[i].v);
////		}
////	}
////	if (out.size() != 100) {//无法完成
////
////	}
////}
//
//void qsort(vector<int>& a, int low, int high) {
//	if (low >= high)return;
//	int i = low; int j = high + 1;
//	while (true) {
//		while (i < high && a[++i] < a[low]);//++！！
//		while (j > low && a[--j] > a[low]);
//		if (i >= j)break;
//		swap(a[i], a[j]);
//	}
//	swap(a[low], a[j]);
//	qsort(a, low, j - 1);
//	qsort(a, j + 1, high);
//}
//void permute(vector<int>& a, int idx) {
//	if (idx == a.size()) {
//		for (auto y : a)
//			debug << y << ", ";
//		debug();
//		return;
//	}
//	for (int i = 0; i < a.size(); ++i) {
//		swap(a[i], a[idx]);
//		permute(a, idx + 1);
//		swap(a[i], a[idx]);
//	}
//}
//class SegmentTree {
//public:
//	vector<int> a;
//	SegmentTree(int n) :a(n * 2) {}
//	void build(vector<int>& arr) {
//		_build(arr, 1, 1, a.size() / 2);//这里是a.size()/2
//	}
//	void _build(vector<int>& v, int x, int l, int r) {
//		if (l == r) {
//			a[x] = (l < v.size()) ? v[l] : 0;
//			return;
//		}
//		int m = (l + r) / 2;
//		_build(v, x * 2, l, m);
//		_build(v, x * 2 + 1, m + 1, r);
//		a[x] = max(a[x * 2], a[x * 2 + 1]);
//	}
//	int p, v;
//	void set(int pos, int value) {
//		p = pos; v = value;
//		_set(1, 1, a.size() / 2);
//	}
//	void _set(int x, int l, int r) {
//		if (l == r) {
//			a[x] = v; return;
//		}
//		int m = (l + r) / 2;
//		if (p <= m)_set(x * 2, l, m);
//		else _set(x * 2 + 1, m + 1, r);
//		a[x] = max(a[x * 2], a[x * 2 + 1]);
//	}
//	int ask(int l, int r) {
//		return _ask(1, l, r, 1, a.size() / 2);
//	}
//	int _ask(int x, int le, int ri, int l, int r) {
//		if (le == l && r == ri)return a[x];
//		int m = (l + r) / 2;
//		if (m >= ri)
//			return _ask(x * 2, le, ri, l, m);
//		else if (m < le)return _ask(x * 2, le, ri, m + 1, r);
//		else return max(_ask(x * 2, le, m, l, m), _ask(x * 2 + 1, m + 1, ri, m + 1, r));
//	}
//};
////void qsort(vector<int>& a, int l, int r) {
////	if (l >= r)return;
////	int i = l; int j = r + 1;
////	while (true) {
////		while (i < r && a[i] < a[l]);
////		while (j > l && a[j] > a[l]);
////		if (i >= j)break;
////		swap(a[i], a[j]);
////	}
////	swap(a[j], a[l]);
////	qsort(a, l, j - 1);
////	qsort(a, r + 1, r);
////}
////void permute(vector<int>& a, int idx) {
////	if (idx == a.size()) {
////		return;
////	}
////	for (int i = 0; i < a.size(); ++i) {
////		swap(a[i], a[idx]);
////		permute(a, idx + 1);
////		swap(a[i], a[idx]);
////	}
////}
//class SegTree {
//public:
//	vector<int> a;
//	SegTree(int n) :a(2 * n, 0) {}
//	void init(vector<int>& arr) {
//		build(arr, 1, 1, a.size() / 2);
//	}
//	void build(vector<int>& ar, int x, int l, int r) {
//		if (l == r) {
//			a[x] = (l < ar.size()) ? ar[l - 1] : 0;//减1
//			return;
//		}
//		int m = (l + r) / 2;
//		build(ar, x * 2, l, m);
//		build(ar, x * 2 + 1, m + 1, r);
//		a[x] = max(a[x * 2], a[x * 2 + 1]);
//	}
//	int ask(int l, int r) {
//		if (l > r)return 0;//！1
//		return _ask(1, l, r, 1, a.size() / 2);
//	}
//	int _ask(int x, int le, int ri, int l, int r) {
//		if (l == le && r == ri) {
//			return a[x];
//		}
//		int m = (l + r) / 2;
//		if (ri <= m)return _ask(x * 2, le, ri, l, m);//第2,3个参数！！！
//		else if (le > m)return _ask(x * 2 + 1, le, ri, m + 1, r);//m+1!!
//		else return max(_ask(x * 2, le, m, l, m), _ask(x * 2 + 1, m + 1, ri, m + 1, r));
//	}
//	int p; int v;
//	void set(int pos, int value) {
//		p = pos; v = value;
//		_set(1, 1, a.size() / 2);
//	}
//	void _set(int x, int l, int r) {
//		if (l == r) {
//			a[x] = v; return;
//		}
//		int m = (l + r) / 2;
//		if (p <= m)_set(x * 2, l, m);
//		else _set(x * 2 + 1, m + 1, r);
//		a[x] = max(a[x * 2], a[x * 2 + 1]);
//	}
//	void add(int pos, int value) {
//		p = pos; v = value;
//		_add(1, 1, a.size() / 2);
//	}
//
//	void _add(int x, int l, int r) {
//		if (l == r) {
//			a[x] += v; return;
//		}
//		int m = (l + r) / 2;
//		if (p <= m)_set(x * 2, l, m);
//		else _set(x * 2 + 1, m + 1, r);
//		a[x] = max(a[x * 2], a[x * 2 + 1]);
//	}
//};
//
//
//int main()
//{
//	vector<int> v{ 1,7,4,6,3 };
//	//qsort(v, 0, 4);
//	//permute(v, 0);
//	//SegTree s(*max_element(v.begin(), v.end()));
//	//s.init(v);
//	//debug(s.ask(2, 3));
//	//debug(s.ask(3, 5));
//	//s.set(2, 3);
//	//debug(s.ask(2, 3));
//	//debug(s.ask(3, 5));
//
//	vector<int> a{ 7, 8, 1, 4, 7, 9, 2, 1,10 };
//	SegTree tree(*max_element(a.begin(), a.end()) + 15);
//	int maax = 0;
//	for (int i = 0; i < a.size(); ++i) {
//		int ma = tree.ask(1, a[i] - 1);
//		int mm = tree.ask(a[i], a[i]);
//		if (ma + 1 > mm) {
//			maax = max(maax, ma + 1);
//			tree.set(a[i], ma + 1);
//		}
//	}
//	debug(maax);
//	//debug();
//}
//
////int main() {
////	vector<int> v{ 1,4,3};
////	qsort(v, 0, v.size() - 1);
////	debug.debugseq(v);
////	debug();
////}