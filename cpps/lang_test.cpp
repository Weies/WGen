//#include"WGen.h">
//#include<algorithm>
//#include<numeric>
//#include<functional>
//#include<bitset>
//#include<stdio.h>
//using namespace std;
//struct s {
//	int* p;
//	int aa;
//	s* operator->() {
//		return this;
//	}
//};
//
//void  send(int* to, int* from, int  count)
////     Duff设施，有帮助的注释被有意删去了  
//{
//	int n = (count + 7) / 8;
//	switch (count % 8) {
//	case 0:    do {
//		*to++ = *from++;
//	case 7:          *to++ = *from++;
//	case 6:          *to++ = *from++;
//	case 5:          *to++ = *from++;
//	case 4:          *to++ = *from++;
//	case 3:          *to++ = *from++;
//	case 2:          *to++ = *from++;
//	case 1:          *to++ = *from++;
//	} while (--n > 0);
//	}
//}
//#pragma pack(1)
//struct A
//{
//	char b;
//	int c;
//	short g;
//	double f;
//};
//class As {
//public:
//	As() {}
//	As(int a) :As() {}
//};
//#include<utility>
////#pragma optimize("",off)
//
//int change_const(int b = 2) {
//	const int a = 1;
//	int c = 2;
//	const int* p = &a; int* pp = &c;
//	int* cc = pp + (p - pp);
//	*cc = 2;
//	int* bb = const_cast<int*>(&a); *bb = 5;
//	return a + b;
//}
//template<class T>
//void _mqsort(T& arr, int low, int high) {
//	if (high <= low) return;
//	int i = low;
//	int j = high + 1;
//	int key = arr[low];
//	while (true)
//	{
//		while (arr[++i] < key && i < high);
//		while (arr[--j] > key && j > low);
//		if (i >= j) break;
//		swap(arr[i], arr[j]);
//	}
//	/*中枢值与j对应值交换*/
//	swap(arr[low], arr[j]);
//	_mqsort(arr, low, j - 1);
//	_mqsort(arr, j + 1, high);
//}
//
//
//using p = pair<int, int>;
//
//pair<int, int> ppt[1000000];
//template<class T>
////经典快排
//void mqsort(T& v, int low, int high) {
//	ppt[0] = { low,high };
//	int s = 0; int e = 1;
//	while (s != e) {
//		p pp = ppt[s]; ++s;
//		int l = pp.first; int h = pp.second;
//		int i = pp.first; int j = pp.second + 1;
//		while (1) {
//			/*从左向右找比key大的值*/
//			while (v[++i] < v[l])
//			{
//				if (i == high) {
//					break;
//				}
//			}
//			/*从右向左找比key小的值*/
//			while (v[--j] > v[l])
//			{
//				if (j == low) {
//					break;
//				}
//			}
//			if (i >= j) break;
//			/*交换i,j对应的值*/
//			int temp = v[i];
//			v[i] = v[j];
//			v[j] = temp;
//		}
//		swap(v[l], v[j]);
//		if (j - 1 > l)ppt[e++] = { l,j - 1 };
//		if (j + 1 < h)ppt[e++] = { j + 1,h };
//	}
//}
////希尔排序
//template <typename T>
//void shell_sort(T array[], int length) {
//	int h = 1;
//	while (h < length / 3) {
//		h = 3 * h + 1;
//	}
//	while (h >= 1) {
//		for (int i = h; i < length; i++) {
//			for (int j = i; j >= h && array[j] < array[j - h]; j -= h) {
//				std::swap(array[j], array[j - h]);
//			}
//		}
//		h = h / 3;
//	}
//}
//
////三路快排
//template <typename T>
//void quick_sort(T arr[], const int len) {
//	if (len <= 1) return;
//	const T pivot = arr[rand() % len];
//	int i = 0, j = 0, k = len;
//	while (i < k) {
//		if (arr[i] < pivot)
//			swap(arr[i++], arr[j++]);
//		else if (pivot < arr[i])
//			swap(arr[i], arr[--k]);
//		else
//			i++;
//	}
//	quick_sort(arr, j);
//	quick_sort(arr + k, len - k);
//}
////找第K大的数
//template <typename T>
//T find_kth_element(T arr[], int rk, const int len) {
//	if (len <= 1) return arr[0];
//	const T pivot = arr[rand() % len];
//	int i = 0, j = 0, k = len;
//	while (i < k) {
//		if (arr[i] < pivot)
//			swap(arr[i++], arr[j++]);
//		else if (pivot < arr[i])
//			swap(arr[i], arr[--k]);
//		else
//			i++;
//	}
//	if (rk < j) return find_kth_element(arr, rk, j);
//	else if (rk >= k)
//		return find_kth_element(arr + k, rk - k, len - k);
//	return pivot;
//}
//
//
//int main() {
//	vector<int> lis{ 15,48,659,4,7,8,15,2,45,48,545,15,4,14,7,51 };
//	const int n = 1e4;
//	vector<int> v(n);
//	vector<int> t(n);
//	for (int i = 0; i < n; ++i) {
//		v[i] = rand(); t[i] = rand();
//	}
//	clock_t ti = clock();
//	//std::qsort();
//	//std::sort();
//	_mqsort(t, 0, n - 1);
//	
//	//debug(__builtin_clz(31));
//}