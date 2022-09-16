//#include"widget.h"
//#include"graphOBJ.h"
//#include<time.h>
//#include<vector>
//Tailor win(400, 300);
//vector<state> list(100);
//void display()
//{
//	ptr.setColor(25, 125, 255,1);
//	for (int i = 0; i < lines.size(); i++)
//	{
//		ptr.drawLine(lines[i].p1.x, lines[i].p1.y,
//			lines[i].p2.x,lines[i].p2.y);
//	}
//}
//void reshape(int x, int y)
//{
//	lines.resize(0);
//	for (int i = 0; i < 15; i++)
//	{
//		lines.push_back(Line(0, rand() % int(win_h), win_w, rand() % int(win_h)));
//		lines.push_back(Line(rand() % int(win_w), 0, rand() % int(win_w), win_h));
//	}
//}
//int curr = 0;
//int frame = 0;
//int main()
//{
//	srand(time(0));
//	win.setColor(255,255,255,0.8);
//	for (int i = 0; i < 15; i++)
//	{
//		lines.push_back(Line(0, rand()%int(win_h), win_w, rand()%int(win_h)));
//		lines.push_back(Line(rand()%int(win_w), 0, rand()%int(win_w), win_h));
//	}
//
//	//timer(3, []() {
//	//	if (frame < 100)
//	//	{
//	//		win.gotoState(list[curr]);
//	//		frame++;
//	//	}
//	//	else curr=(curr+1)%100,frame=0;
//	//});
//
//	canvas.setReshapeFunc(reshape);
//	canvas.setDisplayFunc(display);
//	eventLoop();
//}