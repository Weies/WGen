//#include"widget.h"
//#include<list>
//#include<algorithm>
//using namespace std;
//class node {
//public:
//	node() {}
//	node(float xx , float yy , float dd) {
//		x = xx; y = yy; d = dd;
//	}
//	bool operator<(const node& otr) const
//	{
//		return x < otr.x;
//	}
//	node* next = 0;
//	float x;
//	float y;
//	float d;
//};
//
//class Lists {
//public:
//	void push_back(const node& n) {//插入时自动排序
//		if (size == 0)
//		{
//			first = new node(n);
//			back = first;
//		}
//		else
//		{
//			node* t = first;
//			while (t->next && t->next->x < n.x) {
//				t = t->next;
//			};
//			node* temp = t->next;
//			t->next = new node(n);
//			t->next->next = temp;
//		}
//		size++;
//	}
//	void erase(float y)
//	{
//		if (size == 0)return;
//		if (first->y == y)
//		{
//			node* t = first;
//			first = first->next;
//			size--;
//			free(t);
//		}
//		else
//		{
//			node* t = first->next; node* f = first;
//			while (t) {
//				if (t->y == y)
//				{
//					f->next = t->next;
//					free(t);
//					size--;
//					break;
//				}
//				f = t; t = t->next;
//			}
//		}
//	}
//	int size = 0;
//	node* first;
//	node* back;
//};
//float k(point<float> p1 , point<float> p2)
//{
//	return -(p2.x - p1.x) / (p2.y - p1.y);
//}
//int numl = 7;
//vector<Line> line;
//Line scan(0 , win_h , win_w , win_h);
//
//int main()
//{
//	point<float> p[100];
//	srand(time(0) - 14e8);
//	for (int i = 0; i < numl; i++)
//	{
//		p[i] = point<float>(rand() % (int)win_w , rand() % (int)win_h);
//	}
//	p[0] = point<float>(40 , 300);
//	p[1] = point<float>(160 , 400);
//	p[2] = point<float>(350 , 550);
//	p[3] = point<float>(450 , 480);
//	p[4] = point<float>(500 , 280);
//	p[5] = point<float>(470 , 180);
//	p[6] = point<float>(200 , 80);
//
//	Lists l;
//
//	stimer(10 , [= , &l]() {
//		for (int i = win_h; i > 0; i--)//从上到下扫描
//		{
//			scan.p1.y = i; scan.p2.y = i;
//			this_thread::sleep_for(5ms);
//			for (int j = 0; j < numl; j++)//遍历每一个点，确认是否有更新
//			{
//				if (p[j].y == i)//点的y坐标等于扫描线的坐标，说明有更新
//				{
//					int f = (j + numl - 1) % numl;
//					int b = (j + numl + 1) % numl;
//					if (p[f].y < i)//前一个点在这个点的下面，删除这点并插入新的点
//					{
//						l.erase(p[j].y);
//						l.push_back(node(p[j].x , p[f].y , k(p[j] , p[f])));
//					}
//					else
//					{
//						l.erase(p[j].y);//否则直接删除这点
//					}
//
//					if (p[b].y < i)
//					{
//						l.erase(p[j].y);
//						l.push_back(node(p[j].x , p[b].y , k(p[j] , p[b])));
//					}
//					else
//					{
//						l.erase(p[j].y);
//					}
//				}
//			}
//
//			node* t = l.first;
//			for (int j = 0; j < l.size / 2; j++) {
//				line.push_back(Line(t->x , i , t->next->x , i));
//				t->x += t->d; t = t->next; t->x += t->d; t = t->next;
//			}
//		}
//	});
//
//	eventLoop({
//			ptr.setColor(0, 0, 255);
//			glStart(GL_LINE_LOOP);
//			for (int i = 0; i < numl; i++)
//			{
//				glPixel(p[i].x, p[i].y);
//			}
//			glOver();
//			ptr.drawLine(scan);
//			ptr.setColor(255, 0, 0);
//			for (int i = 0; i < line.size(); i++)
//				ptr.drawLine(line[i]);
//			  });
//	return 0;
//}