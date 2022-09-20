#include"graphOBJ.h"

Circle::Circle() {
	r = 20;
	px = 150; py = 150;
	rx = 400; ry = 300;
	w = 2 * r;
	h = 2 * r;
	//normalOffset();
	onmove = [=](MouseEvent& e)->bool {
		moveto(e.x, e.y);	return true;
	};
	onclick = [=](me& e)->bool {
		setPriority(1024);	return true;
	};
	onmouseup = [=](me& e)->bool {
		resetPri();	return true;
	};
	setBGC(255, 65, 20);
}
Circle::Circle(float xx, float yy, float rr) {
	moveto(xx, yy);
	r = rr;
	px = 150; py = 150;
	rx = 400; ry = 300;
	w = 2 * r;
	h = 2 * r;
	//normalOffset();
	onmove = [=](MouseEvent& e)->bool {
		moveto(e.x, e.y);	return true;
	};
	setStickScale();
	setBGC(255, 65, 20);
}

Rect::Rect() {
	mPosition.x = 100; mPosition.y = 100; h = 200; w = 200;
	setBGC(0, 255, 0);
	//setOffset(-100 , -100);
	onmove = [=](me& e)->bool
	{
		//this->setPriority(1024);
		moveto(e.x, e.y);	return true;
	};
	setStickScale();
	/*onmouseup = [=](me& e) {
		resetPri();
	};*/
}
Rect::Rect(float xx, float yy, float w, float h)
{
	setStickScale();
	mPosition.x = xx; mPosition.y = yy; h = h; w = w;
	setBGC(0, 255, 0);
	//setOffset(-w / 2 , -h / 2);
	onmove = [=](me& e)->bool
	{
		this->setPriority(1024);
		moveto(e.x, e.y);
		return true;
	};

	onmouseup = [=](me& e)->bool {
		resetPri();
		return true;
	};
}

Plane::Plane()
{
	setPriority(1024);
	moveto(300, 300);
	evtor.keydown() = ([=](ke& e)->bool {
		int key = e.key;
		switch (key)
		{
		case GLFW_KEY_DOWN:
			moveto(mPosition.x, mPosition.y - 15);
			break;
		case GLFW_KEY_UP:
			moveto(mPosition.x, mPosition.y + 15);
			break;
		case GLFW_KEY_RIGHT:
			moveto(mPosition.x + 15, mPosition.y);
			break;
		case GLFW_KEY_LEFT:
			moveto(mPosition.x - 15, mPosition.y);
			break;
		default:
			return false;
			break;
		}
		return true;
		});
	setBGC(25, 125, 255);
}

void Plane::draw()
{
	ptr.setColor(mBackgroundColor);
	glStart(GL_TRIANGLES);
	glPixel(mPosition.x, mPosition.y);
	glPixel(mPosition.x, mPosition.y + 50);
	glPixel(mPosition.x - 50, mPosition.y - 30);

	glPixel(mPosition.x + 50, mPosition.y - 30);
	glPixel(mPosition.x, mPosition.y);
	glPixel(mPosition.x, mPosition.y + 50);
	glOver();
	ptr.setColor(0, 255, 0);
	ptr.fillRect(mPosition.x - 25, mPosition.y + 60, HP / 100, 5);
	ptr.setColor(0, 0, 255);
	ptr.setCenter(mPosition.x, mPosition.y);
	ptr.cdrawCircle(30);
}

void Enemy::draw()
{
	ptr.setColor(255, 0, 0);
	glStart(GL_TRIANGLES);
	glPixel(mPosition.x, mPosition.y);
	glPixel(mPosition.x, mPosition.y - 50);
	glPixel(mPosition.x + 50, mPosition.y + 30);

	glPixel(mPosition.x - 50, mPosition.y + 30);
	glPixel(mPosition.x, mPosition.y);
	glPixel(mPosition.x, mPosition.y - 50);
	glOver();
	ptr.setColor(255, 0, 0);
	ptr.fillRect(mPosition.x - 25, mPosition.y - 70, HP / 20, 5);
}


BezierCurve::BezierCurve(const int pnum)
{
	Srand(time(0) % 127817 + 12143);
	num = pnum;
	c = new Circle * [100];
	for (int i = 0; i < pnum; i++)
	{
		c[i] = new Circle;
		c[i]->r = 10;
		c[i]->setBGC(255, 0, 0);
		c[i]->moveto(Rand() % int(win_w), Rand() % int(win_h));
	}
	tt = new point2[pnum + 100];
}

void BezierCurve::draw()
{
	if (busy)this_thread::sleep_for(10ms);

	if (!showing)return;
	ptr.setColor(0, 0, 255);
	glStart(GL_LINE_STRIP);
	for (int i = 0; i < num; i++)
		globals::glPixel(c[i]->mPosition.x, c[i]->mPosition.y);
	glOver();

	ptr.setColor(0, 205, 0);
	glStart(GL_POINTS);
	for (float t = 0.0; t <= 1; t += 0.0001)
	{
		for (int i = 0; i < num - 1; i++)//对每个点
		{
			for (int j = 0; j < num - i - 1; j++)//递推
			{
				if (i == 0)
					tt[j] = point2(c[j]->mPosition.x, c[j]->mPosition.y) * (1 - t) + point2(c[j + 1]->mPosition.x, c[j + 1]->mPosition.y) * t;
				else tt[j] = tt[j] * (1 - t) + tt[j + 1] * t;
			}
		}
		glPoint(tt[0]);
	}
	glOver();
	drawString(20, win_h - 70, L"Bezier曲线");
	if (busy)num++, busy = false;
}

BezierSurf::BezierSurf(const int pnum)
{
	Srand(time(0) % 12787 + 12143);
	num = pnum;
	c = new pot * [10];
	for (int i = 0; i < pnum; i++)
	{
		c[i] = new pot[10];
		for (int j = 0; j < num; j++)
		{
			c[i][j] = *new pot(Randf(), Randf(), Randf());
		}
	}
	tt = new pot * [pnum + 100];
	for (int i = 0; i < pnum; i++)
	{
		tt[i] = new pot[num];
		for (int j = 0; j < num; j++)
		{
			tt[i][j] = *new pot;
		}
	}
	tp = new pot[50];
}
void BezierSurf::draw()
{
	if (busy)this_thread::sleep_for(10ms);
	ptr3.setModel(mat4(1.0f));
	ptr3.setNormal(vec3(1.0, 1.0, 1.0));
	if (!showing)return;
	ptr3.setColor(0, 0, 255);

	for (int i = 0; i < num; i++)
	{
		glStart3(GL_LINE_STRIP);
		for (int j = 0; j < num; j++)
			globals::glPoint3(c[i][j]);
		glOver3();
	}
	for (int i = 0; i < num; i++)
	{
		glStart3(GL_LINE_STRIP);
		for (int j = 0; j < num; j++)
			globals::glPoint3(c[j][i]);
		glOver3();
	}

	ptr3.setColor(0, 255, 0);
	glStart3(GL_POINTS);
	for (float t = 0.0; t <= 1; t += 0.0005)
	{
		for (int k = 0; k < num; k++)
		{
			for (int i = 0; i < num - 1; i++)//对每个点
			{
				for (int j = 0; j < num - i - 1; j++)//递推
				{
					if (i == 0)
						tt[k][j] = c[k][j] * (1 - t) + c[k][j + 1] * t;
					else tt[k][j] = tt[k][j] * (1 - t) + tt[k][j + 1] * t;
				}
			}
		}
		for (float l = 0.0f; l <= 1.0f; l += 0.0005)
		{
			for (int i = 0; i < num - 1; i++)//对每个点
			{
				for (int j = 0; j < num - i - 1; j++)//递推
				{
					if (i == 0)
						tp[j] = tt[j][0];
					else tp[j] = tp[j] * (1 - l) + tp[j + 1] * l;
				}
			}
			//debug(tp[0].toString());
			glPoint3(tp[0]);
		}
	}
	glOver3();
	drawString(20, win_h - 70, L"Bezier曲线");
	if (busy)num++, busy = false;
}

BSplineCurve::BSplineCurve(const int pnum, int kk)//点数，次数
{
	k = kk + 1; num = pnum;
	seqt = new float[pnum + kk + 100];
	setClamped();
	//setEven();
	P = new point2[pnum + k + 100];
	Srand(time(0) % 1607);
	c = new Circle * [100];
	for (int i = 0; i < pnum; i++)
	{
		c[i] = new Circle;
		c[i]->r = 10;
		c[i]->setBGC(0, 0, 255);
		c[i]->moveto(Rand() % int(win_w), Rand() % int(win_h));
	}
}
void BSplineCurve::draw()
{
	if (busy)this_thread::sleep_for(10ms);
	if (showctrl)
	{
		ptr.setColor(0, 200, 0);
		glStart(GL_LINE_STRIP);
		for (int i = 0; i < num; i++)
			globals::glPixel(c[i]->mPosition.x, c[i]->mPosition.y);
		glOver();
	}
	ptr.setColor(255, 0, 0);
	glStart(GL_POINTS);
	for (int j = k - 1; j <= num; j++)
	{//j为区间的末端点
		for (float t = seqt[j]; t < seqt[j + 1]; t += 0.0001)
		{//在当前选定的区间[tj,tj+1)内

			for (int r = 0; r < k; r++)
			{//从第0层递推到r-1层,实际上递归了曲线的次数次
				for (int i = j; i >= j - k + r + 1; i--)//越接近起始点递归的层数越高，当
					//r=k-1时，递归到最后一层
				{
					if (r == 0) {//输入控制点
						P[i] = { c[i]->mPosition.x,c[i]->mPosition.y };
					}
					else {//递推
						P[i] = P[i] * sang(t - seqt[i], seqt[i + k - r] - seqt[i])
							+ P[i - 1] * sang(seqt[i + k - r] - t, seqt[i + k - r] - seqt[i]);
					}
				}
			}
			//debug(P[j].toString());
			glPoint(P[j]);
		}
	}
	glOver();
	drawString(20, win_h - 70, L"B样条曲线");
	if (busy)busy = false, ++num, setClamped();
}
void BSplineCurve::setClamped()
{
	for (int i = 0; i < k; i++)
	{
		seqt[i] = 0.0f;
	}
	for (int i = k; i < num; i++)
	{
		seqt[i] = (i - k + 1) * 1.0 / (num - k + 1);
	}
	for (int i = num; i <= num + k + 1; i++)
	{
		seqt[i] = 1.0f;
	}
}
