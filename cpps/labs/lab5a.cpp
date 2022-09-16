//#include"canvas.h"
//#include"graphBasic.h"
//#include"painter.h"
//#pragma optimize( "", off) 
//#define col 60
//#define winw 800
//#define winh 800
//
//float multi(float a[][col][3] , int i , int j , int k)
//{
//	if (i == 0 || i == col - 1 || j == 0 || j == col - 1)return 0.7f;
//	return (a[i - 1][j - 1][k] * 0.03125f + a[i][j - 1][k] * 0.125f + a[i + 1][j - 1][k] * 0.03125f +
//			a[i - 1][j][k] * 0.125f + a[i][j][k] * 0.375f + a[i + 1][j][k] * 0.125f +
//			a[i - 1][j + 1][k] * 0.03125f + a[i][j + 1][k] * 0.125f + a[i + 1][j + 1][k] * 0.03125f);
//}
//
//
//float matt[col][col][3] = { {{}} };
//float draw[col][col][3] = { {} };
//
//void drawGrid()
//{
//	ptr.setColor(255 , 255 , 255);
//	for (int i = 0; i < col; i++)
//		for (int j = 0; j < col; j++)
//		{
//			ptr.drawLine(i * (winw / col) , win_h , i * (winw / col) , 0);
//			ptr.drawLine(0 , j * (winh / col) , win_w , j * (winh / col));
//		}
//}
//
//void display()
//{
//	for (int i = 0; i < col; i++)
//	{
//		for (int j = 0; j < col; j++)
//		{
//			ptr.setColor(draw[i][j][0] * 255 , draw[i][j][1] * 255 , draw[i][j][2] * 255);
//			ptr.fillRect(i * (winw / col) , j * (winh / col) , (winw / col) , (winh / col));
//		}
//	}
//}
//
//void initial()
//{
//	for (int i = 0; i < col; i++)
//	{
//		for (int j = 0; j < col; j++)
//		{
//			matt[i][j][0] = 0.7f;
//			matt[i][j][1] = 0.7f;
//			matt[i][j][2] = 0.7f;
//		}
//	}
//}
//
//void antialiasing(bool on)
//{
//	for (int i = 0; i < col; i++)
//	{
//		for (int j = 0; j < col; j++)
//		{
//			if (on)
//			{
//				draw[i][j][0] = multi(matt , i , j , 0);
//				draw[i][j][1] = multi(matt , i , j , 1);
//				draw[i][j][2] = multi(matt , i , j , 2);
//			}
//			else
//			{
//				draw[i][j][0] = matt[i][j][0];
//				draw[i][j][1] = matt[i][j][1];
//				draw[i][j][2] = matt[i][j][2];
//			}
//		}
//	}
//}
//
//int aredrawing = 1;
//void inline drawBox(int x , int y , float r)
//{
//	if (aredrawing == 1)
//	{
//		matt[x][y][0] = 0.1 * r;
//		matt[x][y][1] = 0.4 * r;
//		matt[x][y][2] = r;
//	}
//	else
//	{
//		matt[x][y][0] = r;
//		matt[x][y][1] = 0.4 * r;
//		matt[x][y][2] = 0.5 * r;
//	}
//}
//
//int depth1(int x , int y)
//{
//	return 5 * x - 3 * y;
//}
//int depth2(int x , int y)
//{
//	return -5 * x + 2 * y + 200;
//}
//
//void drawTriangle(float x1 , float y1 , float x2 , float y2 , float x3 , float y3)
//{
//	float dx1 = -(x2 - x1) / (y2 - y1);
//	float dx2 = -(x3 - x1) / (y3 - y1);
//	float xl = x1 , xr = x1;
//
//	for (int y = y1; y >= y3; y--)
//	{
//		for (int x = xl; x <= xr ; x++)
//		{
//			if (aredrawing == 1)
//			{
//				//当这一点没有被着色   或者  已被着色但深度更大时更新这个点
//				if (depth1(x , y) > depth2(x , y) || matt[int(x)][int(y)][0] == 0.7f)
//					drawBox(x , y , 0.5 + depth1(x , y) * 0.005);
//			}
//			else
//			{
//				if (depth1(x , y) < depth2(x , y) || matt[int(x)][int(y)][0] == 0.7f)
//					drawBox(x , y , 0.5 + depth2(x , y) * 0.005);
//			}
//		}
//		if (y <= y2)
//			dx1 = -(x2 - x3) / (y2 - y3);
//		xl += dx1; xr += dx2;
//	}
//}
//
//int main()
//{
//	glDisable(GL_DEPTH_TEST);
//	canvas.showFrame();
//	canvas.setWindowSize(780 , 780);
//	canvas.setStickScale();
//	canvas.setDragging();
//	initial();
//
//
//	drawTriangle(50 , 55 , 5 , 30 , 40 , 2);
//	aredrawing = 2;
//	drawTriangle(35 , 55 , 5 , 40 , 55 , 4);
//
//
//	antialiasing(true);
//	//antialiasing(false);
//	eventLoop(
//		{
//				for (int i = 0; i < col; i++)
//				{
//					for (int j = 0; j < col; j++)
//					{
//						ptr.setColor(draw[i][j][0] * 255, draw[i][j][1] * 255, draw[i][j][2] * 255);
//						ptr.fillRect(i * (winw / col), j * (winh / col), (winw / col), (winh / col));
//					}
//				}
//				drawGrid();
//		}
//	);
//}