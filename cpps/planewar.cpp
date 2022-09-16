//#pragma once
//#include"WGen.h"
//#define point point<int>
//#include<time.h>
//Enemy enemy;
//Plane plane;
//int score = 0;
//int toret = 0;
//int tox = 0; int toy = 0;
//int toshot = 0;
//int lx; int ly;
//float deltax;
//float deltay;
//int life = 10;
//int hislife = 10;
//int behit = 0;
//bool gameover = false;
//bool win = true;
//bool start = false;
//
//GameSocket server(12345);
//Socket sock;
//
//void hit(bool label)
//{
//	if (label)
//		++behit;
//	if (toshot%10==0&&behit>0)
//	{
//		//sock.send("-"+itos(behit*10)+"HP value decrease\n");
//		enemy.HP -= behit*4;
//		score += 8*behit;
//		if (enemy.HP<=0)
//		{
//			hislife--;
//			score += 100;
//			enemy.HP = 1000;
//		}
//		behit = 0;
//	}
//}
//
//Button btn("Play开始");
//
//void display()
//{
//	ptr.setColor(0, 255, 0);
//	if (gameover)
//	{
//		canvas.killTimer();
//		if (::win)
//		{
//			canvas.setBGC(0, 255, 0);
//			canvas.setColor(255, 255, 255);
//			ptr.fillRect(200, 250, 220, 100);
//			canvas.setColor(0, 255, 0);
//			drawString(255, 310, "you win");
//			drawString(215, 270, "you got "+itos(score)+" score");
//		}
//		else {
//			canvas.setBGC(255, 0, 0);
//			canvas.setColor(255, 255, 255);
//			ptr.fillRect(200, 250, 220, 100);
//			canvas.setColor(0, 255, 0);
//			drawString(255, 310, "you lost");
//			drawString(215, 270, "you got "+itos(score)+" score");
//		}
//		canvas.killEvent();
//		plane.onmove = 0;
//	}
//	//绘制生命数
//	ptr.fix();
//	for (int i = 0; i<life; i++)
//	{
//		ptr.fillCircle(20+i*26, 20, 10);
//	}
//	canvas.setColor(255, 0, 0);
//	for (int i = 0; i<hislife; i++)
//	{
//		ptr.fillCircle(win_w-(20+i*26), win_h-20, 10);
//	}
//	ptr.stopfix();
//	//绘制我方子弹
//	canvas.setColor(0, 0, 255);
//	toret++;
//	if (toret>10)
//	{
//		plane.setColor(25, 120, 255);
//	}
//	for (int i = 0; i<plane.strbul.size(); i++)
//	{
//		ptr.fillRect(plane.strbul[i].x, plane.strbul[i].y, 10, 10);
//	}
//	for (int i = 0; i<plane.randbul.size(); i++)
//	{
//		ptr.fillRect(plane.randbul[i].x, plane.randbul[i].y, 10, 10);
//	}
//
//	//绘制敌方子弹
//	canvas.setColor(255, 25, 125);
//	for (int i = 0; i<enemy.randbul.size(); i++)
//	{
//		ptr.fillRect(enemy.randbul[i].x, enemy.randbul[i].y, 10, 10);
//	}
//	for (int i = 0; i<enemy.strbul.size(); i++)
//	{
//		ptr.fillRect(enemy.strbul[i].x, enemy.strbul[i].y, 10, 10);
//	}
//}
//
//void update()
//{
//	if (start)
//	{
//		++toshot;
//		enemy.moveto(enemy.pos.x+deltax, enemy.pos.y+deltay);
//		if (toshot%2==0)//子弹飞行速度
//		{
//			for (int i = 0; i<enemy.strbul.size(); i++)
//				enemy.strbul[i].y -= 1;
//			for (int i = 0; i<plane.strbul.size(); i++)
//				plane.strbul[i].y += 1;
//			for (int i = 0; i<plane.randbul.size(); i++)
//				plane.randbul[i].update();
//			for (int i = 0; i<enemy.randbul.size(); i++)
//				enemy.randbul[i].update();
//		}
//		if (toshot%100==0)//射击频率
//		{
//			plane.randbul.push_back(bullets(plane.pos.x-3, plane.pos.y+58));
//			enemy.randbul.push_back(bullets(enemy.pos.x-3, enemy.pos.y-58));
//			//sock.send('*'+itos(win_w-plane.pos.x)+"**"+itos(win_h-plane.pos.y)+"*\n");
//		}
//		if (toshot%200==0)
//		{
//			enemy.strbul.push_back(point(enemy.pos.x-3, enemy.pos.y-58));
//			enemy.strbul.push_back(point(enemy.pos.x-30, enemy.pos.y-58));
//			enemy.strbul.push_back(point(enemy.pos.x+24, enemy.pos.y-58));
//			plane.strbul.push_back(point(plane.pos.x-3, plane.pos.y+55));
//			plane.strbul.push_back(point(plane.pos.x-30, plane.pos.y+55));
//			plane.strbul.push_back(point(plane.pos.x+24, plane.pos.y+55));
//			toshot = 1;
//		}
//		for (int i = 0; i<plane.strbul.size(); i++)
//		{
//			hit(enemy.inArea(plane.strbul[i].x, plane.strbul[i].y));
//		}
//		for (int i = 0; i<plane.randbul.size(); i++)
//		{
//			hit(enemy.inArea(plane.randbul[i].x, plane.randbul[i].y));
//		}
//	}
//}
//
//int main()
//{
//	//sock = server.getUserSocketBlock();
//	//sock.connectToHost("172.25.224.25", 12345);
//	/*InputArea IP(300, 80);
//	IP.setPadding(20, 10);
//	IP.setWords("IP");*/
//	font.loadAsc();
//
//	hander = [=]() {
//		if (!que.empty())
//		{
//			int bit = 0;
//			string s = que.front();
//			switch (s[0])
//			{
//			case '*':
//				tox = atoi(s.c_str()+s.find('*')+1);
//				toy = atoi(s.c_str()+s.find("**")+2);
//				deltax = (tox-enemy.pos.x)*0.143;
//				deltay = (toy-enemy.pos.y)*0.143;
//				if (!start)
//				{
//					btn.setText("Playing");
//					start = true;
//				}
//				break;
//			case '%':
//				if (!start)
//				{
//					timer(15, update);
//					start = true;
//					btn.setText("Playing");
//				}
//				break;
//			case '-':
//				toret = 0;
//				bit = atoi(s.c_str()+1);
//				plane.setColor(255, 0, 0);
//				plane.HP -= bit;
//				if (plane.HP<=0)
//				{
//					life--;
//					if (life==0)
//					{
//						sock.send("$youwin\n");
//						gameover = true;
//						win = false;
//					}
//					plane.HP = 1000;
//				}
//				break;
//			case '$':
//				gameover = true;
//				win = true;
//				break;
//			default:
//				//debug(s);
//				break;
//			}
//			que.pop_front();
//		}
//	};
//
//	enemy.moveto(400, 500);
//	btn.moveto(400, 50);
//	canvas.setMouseHover([=](me& e) {
//		if (start)
//			plane.moveto(e.x, e.y);
//	});
//	canvas.setStickScale();
//	btn.onclick = [=](me& e)
//	{
//		if (!start)
//		{
//			timer(1, update);
//			start = true;
//			sock.send("%I am prepared\n");
//			btn.setText("Playing");
//		}
//	};
//	btn.setMovable(false);
//	canvas.setWindowSize(600, 600);
//	//canvas.setDisplayFunc(display);
//	canvas.setBGC(230, 230, 230);
//	canvas.showFrame();
//	emain_win.loop([&]() {
//		display();
//	});
//}