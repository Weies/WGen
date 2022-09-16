//#include"../source/runtime/WGen.h"
//#include"../source/runtime/function/physics/collision_dectect.h"
//
//vector<StaticObject*> obj;
//bool ren_qiu = true;
//int stage = 0;
//Button btn1("");
//bool render_gun = false;
//int keys = 0;
//SQT mo;
//ColliBody body(Colli_Cube, mo);
//AudioPlayer ap;
//Sphere sp(120);
//SkyBox b;
//SkeletonObject mm;
//Cube cub[10];
//Actor m;
//Render3D ren;
//PhongRender phong;
////CameraBoard cam(ca);
//SkeletonObject am;
//SkeletonObject bull;
//Button btn("");
//struct bul {
//	vec3 pos;
//	vec3 dir;
//	float st;
//};
//vector<bul> buls;
//SkeletonObject key;
//bool sim = false;
//
//bool CD(StaticObject* ob) {
//	for (int i = 0; i < obj.size(); ++i) {
//		if (obj[i] == ob)continue;
//		auto res = ob->ColliDetect(*obj[i]);
//		if (!res)continue;
//		vec3 n = -res.mNormal.normalize();
//		if (dot(n, ob->frontv()) > 0)return true;
//	}
//	return false;
//}
//
//
//float y(float x) {
//	return -0.5 / 250000 * (x - 500) * (x - 500) + 0.5;
//}
//
//class QiuQiu :public SkeletonObject {
//public:
//	enum QiuState {
//		Forward = 0, Backward = 1, Run = 2, Dance = 3,
//		Idle = 4, Jump = 5, Fire = 6, Attack = 7
//	};
//	QiuState	mCurState = Idle;
//	float	velocity = 0.0;
//	float	acceleration = 0.0;
//	float	max_v = 2.0;
//	float	max_a = 4.0;
//	vec2	eye;
//	vec2	fron;
//	float	HP = 500;
//	float	res = 0;
//	const int const atk[7] = { 0,1,2,6,7,8,10 };
//	bool active = false;
//	QiuQiu() {
//		readDRO("asset/models/yuan/qiuqiu/qiuqiu.dro");
//		removeAnimationShift(4);
//		removeAnimationShift(3);
//		setState(Run);
//	}
//	void lookToDir(const vec3& dir) {
//		vec2 t = PitchYaw(dir.normalize());
//		mModelTransform.q = qua(vec3(0, 1, 0), t.y);
//	}
//	void drawHP() {
//		float hp_w = 400;
//		float hp_h = 15;
//		float r = min(HP, 500.0f) / 500;
//		float x = (win_w - hp_w) * 0.5; float y = 15;
//		ptr.setColor(WHITE);
//		ptr.fillRect(vec2(x, y), vec2(x + hp_w, y + hp_h));
//		ptr.setColor(255, 0, 0, 0.5);
//		ptr.fillRect(vec2(x, y), vec2(x + hp_w * r, y + hp_h));
//	}
//	void simulate() {
//		if (!active)return;
//		drawHP();
//		vec3 dir = m.p() - p();
//		if (dir.square_sum() > 4 && mCurState != Run) {
//			setState(Run);
//		}
//		if (dir.square_sum() < 4 && mCurState != Attack) {
//			vec3 fv = frontv();
//			mModelTransform.t += fv * 1.5;
//			if (body.detect(m.mColliBody)) {
//				m.play(45, 1.0, 100);
//				timer(600, [&]()->bool {
//					m.setState(ActorState::Idle);
//					return true;
//					});
//				m.mHP -= 15;
//			}
//			mModelTransform.t -= fv * 1.5;
//			setState(Attack);
//			ap.close("awu");
//			ap.open("asset/models/yuan/qiuqiu/awu.mp3", "awu");
//			ap.play("awu");
//		}
//		lookToDir(dir);
//
//		if (mCurState == Run) {
//			acceleration = (max_v - velocity) * 0.5;
//			velocity = min(velocity + acceleration, max_v);
//		}
//		ef(mCurState == Idle) {
//			acceleration = -velocity / 8.0;
//			velocity = max(0.0f, velocity + acceleration);
//		}
//		ef(mCurState == Backward) {
//			acceleration = -(max_v - velocity) / 2.0;
//			velocity = max((velocity + acceleration), -max_v / 4.0f);
//		}
//		ef(mCurState == Forward) {
//			acceleration = (max_v - velocity) / 2.0;
//			velocity = min((velocity + acceleration), max_v / 4.0f);
//		}
//		ef(mCurState == Fire) {
//			acceleration = (max_v * 0.1 - velocity) * 0.05;
//			velocity = min(velocity, velocity + acceleration);
//		}
//		ef(mCurState == Attack) {
//			velocity = 0;
//		}
//		if (abs(velocity) > 0.01) {
//			forward(velocity / frameps);
//		}
//		//else if (mCurState != Fire)mCurState = Idle;
//	}
//	//沿当前前进方向前进len长度
//	void forward(float len) {
//		vec3 front = len * frontv();
//		mModelTransform.t += front;
//	}
//	void backward(float len) {
//		forward(-len);
//	}
//	void leftward(float len) {
//		vec3 lv = len * leftv();
//		mModelTransform.t += lv;
//	}
//	void rightward(float len) {
//		leftward(-len);
//	}
//
//	void setState(QiuState s) {
//		double transt = 150;
//		mCurState = s; int ran = 0;
//		switch (s) {
//		case Idle:
//			play(9, 1.0, transt);
//			break;
//		case Forward:
//			play(4, 1.0, transt);
//			break;
//		case Backward:
//			play(4, -1.0, transt);
//			break;
//		case Dance:
//			play(0, 1.0, transt);
//			break;
//		case Run:
//			play(3, 1.43, transt);
//			break;
//		case Jump:
//			play(2, 1.0, transt);
//			timer(mAnims[2].mDuring + transt, [&]()->bool {
//				mCurState = Run;
//				forward(mPose[0].t.len());
//				//mPose[0].t = -jos[0].off_set.t;
//				play(3, 1.0);
//				updatePose();
//				return true;
//				});
//			break;
//		case Attack:
//			ran = rand() % 7;
//			if (ran == mCurAnimIndex)ran = (ran + 1) % 7;
//			play(atk[ran], 2.0, transt * 3);
//			timer((mAnims[ran].mDuring + transt * 3) / 2.0, [&]()->bool {
//				mCurState = Run;
//				forward(mPose[0].t.len());
//				play(3, 1.0);
//				updatePose();
//				return true;
//				});
//			break;
//		default: break;
//		}
//	}
//};
//QiuQiu qiuqiu;
//
//
//
//
//bool whenBoxing() {
//	static int hand = 0;
//	if (m.mCurState == Boxing) {
//		if (hand)timor.stop(hand), hand = 0;
//		int ran = Rand() % 4;
//		int a[4] = { 4,5,6,23 };
//		int p = a[ran]; if (p == m.mCurAnimIndex)p = a[(ran + 1) % 4];
//		m.play(p, 2.0, 100);
//
//		ColliBody& bo = m.mColliBody;
//		m.mModelTransform.t += m.frontv();
//		if (bo.detect(qiuqiu.mColliBody)) {
//			qiuqiu.HP -= 45;
//			ap.close("box");
//			ap.open("audio/boxing1.mp3", "box");
//			ap.play("box");
//			if (qiuqiu.HP < 0 && stage == 0) {
//				qiuqiu.active = false;
//				stage = 1; double tm = gameTime; vec3 f = m.frontv() + vec3(0, 0.126, 0);
//				m.setState(Idle);
//				ca.anim(SQT(1.0, dirvQua(normalize(qiuqiu.p() + f * 5 - ca.mo.p)), qiuqiu.p() + f * 5), 500, 2000);
//
//				timer(0.0, [=]()->bool {
//					qiuqiu.mModelTransform.t += f * 0.32; qiuqiu.mModelTransform.q *= qua(vec3(1, 2, 3), 0.1, true);
//					if (gameTime - tm > 5000) {
//						qiuqiu.moveto(vec3(0, -100, 0)); qiuqiu.active = false;
//						btn.slowIn(0.8, 1000);
//						btn.setText("哦，飞走的丘丘人身上好像掉落了什么东西", false);
//						key.moveto(m.p() + m.frontv() * 2 + vec3(0, 0.5, 0));
//						m.setState(Idle);
//						ca.anim(SQT(1.0, m.mModelTransform.q, key.p()), 1000, 1000, 0.13);
//
//						int hand = timer(0.0, []()->bool {
//							key.scale(20);
//							if (key.mColliBody.detect(m.mColliBody)) {
//								btn1.show(true);
//								btn1.setText("一把破旧的钥匙");
//							}
//							else btn1.show(false);
//							key.scale(0.05);
//							return false;
//							});
//
//						btn1.onclick = [=](me& e)->bool {
//							//m.mHasGun = true;
//							addHint(100, 100, "获得一把钥匙，现在你已经有1把钥匙了", 3000);
//							timor.stop(hand);
//							key.mModelTransform.t = vec3(0, -100, 0);
//							timer(100, []() {btn1.show(false); });
//							btn.setText("或许这种破旧的钥匙能够帮助你离开这里呢", false);
//							timer(2000, []() {btn.setText("到别处看看吧", false); });
//							timer(5000, []() {btn.slowOut(1000);; });
//							return true;
//						};
//						return true;
//					}
//					return false;
//					});
//			}
//		}
//		m.mModelTransform.t -= m.frontv();
//		hand = timer((m.mAnims[a[ran]].mDuring + 100) / 2.0, whenBoxing);
//	}
//	return true;;
//};
//int hd1 = 0; int hd2 = 0;
//vec3 off(-0.4, 0.1, 2.2);
//vec3 vp = m.mViewpoint;
//
//void bindEvent() {
//	evtor.keyup() = ([&](ke& e)->bool {
//		if (e.key == KEY_W)
//			m.setState(Idle);
//		if (e.key == KEY_F && m.mHasGun) {
//			m.mCurState = Idle;
//			m.play(14, 1.0, 300);
//			m.setCameraOffset(0.0f);
//			m.syncCamera();
//			timer(100.0, [&]()->bool {
//				ap.close("fi");
//				return true;
//				});
//			timor.stop(hd1);
//			timor.stop(hd2);
//		}
//		return true;
//		});
//	evtor.keydown() = ([&](ke& e)->bool {
//		if (e.key == KEY_F) {
//			if (!m.mHasGun) {
//				if (m.mCurState == Boxing)return true;
//				m.mCurState = Boxing;
//				whenBoxing();
//				return true;
//			}
//			m.mCurState = Fire;
//			m.mFrontDirection.x = m.mEyeDirection.x;
//			m.mModelTransform.q = qua(vec3(0, 1, 0), m.mFrontDirection.x);
//			m.play(11, 6.0, 200);
//			ap.open("asset/audio/fire.mp3", "fi");
//			ap.volume("fi", 300);
//			ap.play("fi", 1);
//			m.setCameraOffset(off);
//			timer(100.0, [&]()->bool {
//				m.syncCamera();
//				return true;
//				});
//			hd1 = timer(3000.0, [&]()->bool {
//				m.setState(Idle);
//				hd2 = timer(300.0, [&]()->bool {
//					ap.close("fi");
//					return true;
//					});
//				return true;
//				});
//		}
//		if (e.key == KEY_C) {
//			m.setState(Idle);
//			m.play(rand() % m.mAnims.size(), 1, 200);
//		}
//		return true;
//		});
//}
//SQT qs[10]; SQT qt[10];
//void initModel() {
//
//	sp.translate(vec3(0, 300.5, 0));
//	sp.scale(250);
//	sp.addTexture("asset/imgs/ch.jpg", texture_diffuse, -1);
//	key.loadModel("asset/models/key.obj");
//	key.setColor(Color(230, 180, 70));
//	key.calcuNormal(0, 1); key.translate(0, 0.5, 0);
//	key.scale(0.1);
//	//地面
//	cub[0].translate(vec3(0.0, -0.5, 0.0));
//	cub[0].scale(vec3(400, 1, 400));
//	cub[0].addTexture("asset/imgs/grand.jpg", texture_diffuse, 4);
//	cub[0].scaleTexture(4, 0.01);
//
//	//墙壁
//	cub[1].translate(vec3(100, 5, 0.0));
//	cub[1].scale(vec3(0.5, 10, 200));
//	cub[1].addTexture("asset/imgs/brickwall.jpg", texture_diffuse, -1);
//	cub[1].scaleTexture(-1, vec2(0.05, 1));
//
//	cub[2].translate(vec3(-100, 5, 0.0));
//	cub[2].scale(vec3(0.5, 10, 200));
//	cub[2].addTexture("asset/imgs/brickwall.jpg", texture_diffuse, -1);
//	cub[2].scaleTexture(-1, vec2(0.05, 1));
//
//	cub[3].translate(vec3(0, 5, 100));
//	cub[3].scale(vec3(200, 10, 0.5));
//	cub[3].addTexture("asset/imgs/brickwall.jpg", texture_diffuse, -1);
//	cub[3].scaleTexture(-1, vec2(0.05, 1));
//
//	cub[4].translate(vec3(0, 5, -100.0));
//	cub[4].scale(vec3(200, 10, 0.5));
//	cub[4].addTexture("asset/imgs/brickwall.jpg", texture_diffuse, -1);
//	cub[4].scaleTexture(-1, vec2(0.05, 1));
//
//
//	const float len = 60; const float of = 100 - len;
//	cub[5].translate(vec3(of, 5, of));
//	cub[5].scale(vec3(2 * len, 10, 0.5));
//	cub[5].addTexture("asset/imgs/brickwall.jpg", texture_diffuse, -1);
//	cub[5].scaleTexture(-1, vec2(0.05, 1));
//
//	cub[6].translate(vec3(-of, 5, of));
//	cub[6].scale(vec3(0.5, 10, 2 * len));
//	cub[6].addTexture("asset/imgs/brickwall.jpg", texture_diffuse, -1);
//	cub[6].scaleTexture(-1, vec2(0.05, 1));
//
//	cub[7].translate(vec3(-of, 5, -of));
//	cub[7].scale(vec3(2 * len, 10, 0.5));
//	cub[7].addTexture("asset/imgs/brickwall.jpg", texture_diffuse, -1);
//	cub[7].scaleTexture(-1, vec2(0.05, 1));
//
//	cub[8].translate(vec3(of, 5, -of));
//	cub[8].scale(vec3(0.5, 10, 2 * len));
//	cub[8].addTexture("asset/imgs/brickwall.jpg", texture_diffuse, -1);
//	cub[8].scaleTexture(-1, vec2(0.05, 1));
//
//	cub[9].scale(vec3(4, 0.1, 4));
//	cub[9].addTexture("asset/imgs/ch.jpg", texture_diffuse, -1);
//	qs[0] = cub[0].mModelTransform;
//	for (int i = 1; i < 9; ++i) {
//		qs[i] = cub[i].mModelTransform;
//		obj.push_back(&cub[i]);
//	}
//	obj.push_back(&m);
//	phong.addLights();
//}
//
//void initActor() {
//	mm.readDRO("asset/models/gun/M416/M416.dro");
//	bull.loadModel("asset/models/gun/bullet.FBX");
//	bull.translate(vec3(0, 4, 0));
//	bull.scale(0.08);
//	bull.rotate(-90, vec3(0, 1, 0));
//	bull.setColor(Color(155, 131, 63));
//	body.setBodyAsStdCube();
//	qiuqiu.setState(QiuQiu::Idle);
//	qiuqiu.play(2);
//	qiuqiu.mColliBody.setBodyAsActor();
//	obj.push_back(&qiuqiu);
//	qiuqiu.HP = 100;
//}
//
//void gameBegin() {
//	btn.resize(400, 100);
//	btn.setText("啊，我为什么会在这里？", false);
//	btn.setBGC(Color(255, 255, 255, 0.5));
//	btn.show(false);
//	btn.setCenter(400, 200);
//	btn.onmove = 0;
//	btn1.show(false); btn1.resize(100, 30);
//	eventAble = false;
//
//
//	m.moveto(vec3(90, 0, 90)); vec3 p = m.camerap();
//	m.mModelTransform.q *= qua(vec3(0, 1, 0), 3.14);
//	m.play(8);
//	m.syncCamera();
//	btn.onclick = [=](me& e)->bool {
//		//环顾四周，发现丘丘人
//		if (stage == 0) {
//			btn.setText("快看那边，那是？？？？", 0);
//			ca.mo.q *= qua(vec3(0, 1, 0), 1.54);
//			ca.transit(p, m.mModelTransform.q, 1000);
//			timer(1000, [=]() {
//				m.mModelTransform.q *= qua(vec3(0, 1, 0), 1.56);
//				ca.transit(p, m.mModelTransform.q, 1000);
//				qiuqiu.moveto(vec3(70, 0, 90));
//				qiuqiu.active = true;
//				timer(1000, [&]() {
//					vec2 v = PitchYaw(ca.frontv());
//					m.mEyeDirection = vec2(v.y, v.x);
//					m.mFrontDirection = vec2(v.y, 0);
//					m.syncCamera();
//					btn.setText("一只奇怪的丘丘人？算了打倒它吧！", 0);
//					});
//				timer(3000, [&]() {
//					btn.setText("按F键进行攻击", 0);
//					btn.slowOut(1000, 2000);
//					});
//				});
//		}
//		return true;
//	};
//	btn.show(0);
//
//	SQT gi(1.0, dirvQua(ca.frontv()), ca.p());
//	ap.open("asset/audio/stone1.mp3", "st");
//	ap.play("st");
//	ca.mo = SQT(1, qua(0.706812, 0, 0, 0.707401), vec3(0, 149.938, -0.0020833));
//	timer(1000, [=]() {	ca.transit(gi, 80000); stage = 13; });
//	timer(3000, [=]() {	ca.transit(gi, 20000); });
//	timer(7000, [=]() {	ca.transit(gi, 4000); });
//	timer(10000, [=]() {
//		ca.transit(gi, 1600);
//		for (int i = 1; i < 9; ++i) {
//			qt[i] = cub[i].mModelTransform;
//		}
//		double tm = gameTime;
//		timer(0.0, [=]()->bool {
//			for (int i = 1; i < 9; ++i) {
//				cub[i].mModelTransform = qt[i].lerp(qs[i], (gameTime - tm) / 1600);
//			}
//			if (gameTime - tm > 1600) {
//				stage = 0;
//				for (int i = 0; i < 9; ++i) {
//					cub[i].mModelTransform = qs[i];
//				}
//				return true;
//			}
//			return false;
//			});
//		});
//	timer(11600, [=]() {
//		m.syncCamera(); stage = 0; btn.slowIn(0.8, 1000, 1000);
//		});
//	timer(14600, []() {
//		ap.open("asset/audio/bgm.mp3", "bgm");
//		ap.play("bgm", 1);
//		ap.volume("bgm", 300);
//		sim = true;
//		});
//	//出现提示框
//	stage = 0;
//	//btn.slowIn(0.8, 1000, 1000);
//}
//
//void  checkStage() {
//	if (stage == 1) {
//		mo.t = vec3(-25, 0, 35); mo.s = 10;
//		if (body.detect(m.mColliBody)) {
//			m.setState(Idle);
//			ca.anim(vec3(0, 0, 0), dirvQua(normalize(-m.p())), 1000, 2000, 0.15);
//			btn.slowIn(0.8, 1000);
//			btn.setText("看，那边有个奇怪的平台", 0);
//			timer(3000, []() {
//				btn.setText("我们过去看看吧", 0);
//				});
//			stage = 2;
//			timer(5000, []() {m.syncCamera(); btn.slowOut(1000); });
//		}
//	}
//	if (stage == 2) {
//		mo.t = vec3(0, 0, 0); mo.s = 2;
//		if (body.detect(m.mColliBody)) {
//			btn1.show(true);
//			btn1.setText("离开：需要1/4把钥匙");
//			btn1.onclick = [](me& e)->bool {
//				addHint(100, 100, "钥匙不足！！还差3把钥匙", 2000);
//				btn.slowIn(0.8, 1000);
//				btn.setText("好像需要足够多的钥匙才能离开这里");
//				timer(3000, []() {btn.setText("再在这里周围转转吧"); });
//				timer(5000, []() {btn.slowOut(1000); });
//				stage = 3;
//				mm.moveto(vec3(75, 0.8, -25)); mm.mModelTransform.s = 1; mm.mModelTransform.q = qua();
//				render_gun = true;
//				return true;
//			};
//		}
//		else btn1.show(false);
//	}
//	if (stage == 3) {
//		mo.s = 3; mo.t = vec3(75, 0, -25);
//		if (body.detect(m.mColliBody)) {
//			btn1.show(true);
//			btn1.setText("M416自动步枪");
//			btn1.onclick = [](me& e)->bool {
//				m.mHasGun = true;
//				btn1.show(0);
//				btn.slowIn(0.6, 500);
//				btn.setText("试试这把新武器这么样吧", 0);
//				timer(3000, []() { btn.setText("按F键开火", 0); });
//				timer(7000, []() {
//					btn.setText("看那边！！"); vec3 p(75, 0, -80);
//					qiuqiu.moveto(p); qiuqiu.active = 1;
//					qiuqiu.HP = 500; ren_qiu = true;
//					m.setState(Idle);
//					ca.anim(p, dirvQua(normalize(p - m.p())), 2000, 2000, 0.22);
//					});
//				timer(13000, []() {btn.setText("又有一只丘丘人？快消灭它！"); });
//				btn.slowOut(1000, 16000);
//				return true;
//			};
//		}
//		else btn1.show(false);
//	}
//	if (stage == 4 || stage == 7) {
//		mo.t = key.mModelTransform.t; mo.s = 2;
//		if (body.detect(m.mColliBody)) {
//			btn1.show(true);
//			btn1.setText("拾取钥匙");
//			btn1.onclick = [](me& e)->bool {
//				btn.slowIn(0.8, 1000);
//				if (stage == 4)btn.setText("其他地方应该还有钥匙，快去收集吧！");
//				else btn.setText("还差最后一把钥匙了，加油！");
//				timer(3000, []() { btn.slowOut(1000);; });
//				btn1.show(0);
//				key.mModelTransform.t = vec3(0, -100, 0);
//				stage += 1;
//				return true;
//			};
//		}
//		else btn1.show(false);
//	}
//	if (stage == 5) {
//		mo.t = vec3(26, 0, -45); mo.s = 10;
//		if (body.detect(m.mColliBody)) {
//			btn.slowIn(0.8, 1000); btn.setText("快看那边也有一只丘丘人，快消灭它！");
//			vec3 p(-85, 0, -70);
//			qiuqiu.moveto(p); qiuqiu.active = 1;
//			ca.anim(p, 1000, 1500, 0.22); m.setState(Idle);
//			qiuqiu.HP = 500; ren_qiu = true;
//			timer(3000, []() { btn.slowOut(1000); });
//			stage += 1;
//		}
//		else btn1.show(false);
//	}
//	if (stage == 8) {
//		mo.t = vec3(-45, 0, -25); mo.s = 10;
//		if (body.detect(m.mColliBody)) {
//			qiuqiu.moveto(vec3(-75, 0, 75));
//			ca.anim(qiuqiu.p(), 2000, 1000, 0.22);
//			m.setState(Idle);
//			qiuqiu.active = 1;
//			qiuqiu.HP = 500;
//			stage += 1;
//			btn.slowIn(0.8, 1000); btn.setText("消灭这只丘丘人就能拿到所有钥匙了吧！");
//			timer(3000, []() { btn.slowOut(0); });
//		}
//		else btn1.show(false);
//	}
//	if (stage == 10) {
//		mo.t = key.mModelTransform.t; mo.s = 2;
//		if (body.detect(m.mColliBody)) {
//			btn1.show(true); btn1.setAlpha(1);
//			btn1.setText("拾取钥匙");
//			btn1.onclick = [](me& e)->bool {
//				btn.slowIn(0.8, 1000);
//				btn.slowOut(1000, 5000);
//				btn.setText("钥匙集齐了，快去平台那里吧！", 0);
//				key.mModelTransform.t = vec3(0, -100, 0);
//				btn1.show(0);
//				stage = 11;
//				return true;
//			};
//		}
//		else btn1.show(false);
//	}
//	if (stage == 11) {
//		mo.p = vec3();
//		if (body.detect(m.mColliBody)) {
//			btn1.show(true);
//			btn1.setText("离开：需要4/4把钥匙");
//			btn1.onclick = [](me& e)->bool {
//				ap.close("bgm");
//				btn1.show(0); m.play(8); eventAble = 0;
//				int tm = gameTime;
//				timer(0.0, [=]()->bool {
//					ca.lookToDirection(m.p() - ca.p());
//					if (gameTime - tm > 7000)return true;
//					return false;
//					});
//				ap.close("st");
//				ap.open("asset/audio/stone1.mp3", "st");
//				ap.play("st");
//				timer(200.0, [=](te& e)->bool {
//					e.delay = 0; float y = m.mModelTransform.t.y;
//					m.mModelTransform.t.y += y * 0.005 + 0.04;
//					cub[9].mModelTransform.t.y += y * 0.005 + 0.04;
//					if (gameTime - tm > 7000) {
//						stage = 12;
//						return true;
//					}
//					return false;
//					});
//				timer(7000, [=]() {
//					ca.transit(vec3(0, 150, 0), dirvQua(vec3(0, -1, 0)), 8000);
//					});
//				timer(14000, [=]() {
//					ca.transit(vec3(0, 150, 0), dirvQua(vec3(0, -1, 0)), 6000);
//					});
//				timer(19909, []() {	ca.transit(vec3(0, 150, 0), dirvQua(vec3(0, -1, 0)), 10000); stage = 13; });
//				return true;
//			};
//		}
//		else btn1.show(false);
//	}
//
//}
//
//
//int main() {
//	StaticObject* mesh = new Cube();
//	//mesh->__vptr[1]();
//	debug(typeid(*mesh).name());
//	//main_win.set(SHOW_FPS, true);
//	//glEnable(GL_FOG);
//	ap.open("asset/audio/end.mp3", "end");
//	key.rotate(45, vec3(0, 1, 0));
//	SQT t(0.3351, qua(0.512335, -0.511895, -0.487393, 0.487776), vec3(-0.840639, 1.41175, 0.0602751));
//	t = translate(t, vec3(1.3, 0, -0.5));
//	t.q *= qua(vec3(0, 1, 0), radians(35.8));
//	//_1;
//	initModel();
//	bindEvent();
//	initActor();
//	gameBegin();
//	SQT bu;
//	bu.s = 0.2;
//	vec3 buloff(0, 1.31, 3.0);
//	int ls = 0;
//	qua qbefore = bull.mModelTransform.q;
//	bool playover = true;
//	auto las = Idle;
//	vector<bul> part; int pals = 0;
//	float stime = gameTime;
//	int cur = 1;
//	float tt = 0;
//	double lstime = 0;
//	CameraBlock block;
//	float deg = 1;
//	//m.mHasGun = 1; render_gun = 1; m.moveto(vec3(10, 0, 1)); sim = true;
//	//stage = 8; //m.mModelTransform.t = vec3();
//	//qiuqiu.moveto(vec3(10, 0, 10));
//
//	SQT sqt(0.3351, qua(vec3(1, 0, 0), -1.37) * qua(vec3(0, 0, 1), 1.57) * qua(vec3(1, 0, 0), -0.27), vec3(0, 1.25, -0.15));
//	sqt = translate(sqt, vec3(0.5, 0, -0.35));
//	btn1.onmove = 0;
//
//	main_win.loop([&]() {
//		block = ca.getBlock();
//		phong.setBlock(block);
//		if (m.mHasGun && stage < 12) {
//			ptr.setColor(RED);
//			ptr.fillPie(win_w / 2, win_h / 2, 2);
//		}
//
//		//ptr3.drawCoord(mm.mModelTransform, 2.0);
//		mo.s = 0.6;
//		for (int i = ls; i < buls.size(); ++i) {
//			if (buls[i].pos.square_sum() < 40000) {
//				buls[i].pos += buls[i].dir * (Randf() + 1.0f) * 5.0;
//				bu.t = buls[i].pos;
//				bull.mModelTransform.t = bu.t;
//				bull.mModelTransform.q *= dirvQua(buls[i].dir);
//				phong << bull;
//				bull.mModelTransform.q = qbefore;
//				mo.t = bu.t;
//				if (body.detect(qiuqiu.mColliBody) && qiuqiu.active) {
//					ls = max(i, ls);
//					part.push_back({ mo.t,vec3(Randf(),0,Randf()).normalize() * 0.3,float(gameTime) });
//					qiuqiu.HP -= 4 * (1 - qiuqiu.res);
//					if (qiuqiu.HP < 0) {
//						if (stage == 3 || stage == 6) {
//							qiuqiu.active = 0;
//							double tm = gameTime;
//							timer(0.0, [=]()->bool {
//								qiuqiu.translate(vec3(0, -0.03, 0));
//								if (qiuqiu.p().y < -2) {
//									stage += 1;
//									vec3 p = qiuqiu.p(); p.y = 0.5;
//									mo.t = p; mo.s = 2; key.moveto(p);
//									m.setState(Idle);
//									ca.anim(p, dirvQua(normalize(p - m.p())), 2000, 2000, 0.08);
//									timer(2000, []() {
//										btn.slowIn(0.8, 1000); btn.setText("好像又有一把钥匙，去捡起来吧");
//										});
//									timer(5000, []() {btn.slowOut(1000); });
//									return true;
//								}
//								return false;
//								});
//						}
//						else if (stage == 9) {
//							qiuqiu.HP = 500;
//							qiuqiu.res = min(0.9, qiuqiu.res + 0.4);
//							qiuqiu.scale(1.5); qiuqiu.active = 1;
//							qiuqiu.max_v *= 1.5;
//							btn.slowIn(0.8); btn.setText("啊？这只丘丘人好像变得更大更快更强了？");
//							key.moveto(qiuqiu.p() + vec3(0, 0.5, 0));
//							timer(2000, []() {
//								m.setState(Idle);
//								ca.anim(key.p(), 1000, 1000, 0.08);
//								btn.setText("最后一把钥匙在那边，快去捡起来");
//								stage = 10;
//								});
//							btn.slowOut(1000, 6000);
//						}
//						break;
//					}
//					if (playover) {
//						stime = gameTime;
//						ap.close("bulhit");
//						ap.open("asset/audio/bulhit.wav", "bulhit");
//						ap.play("bulhit");
//						playover = false;
//						timor.push(100.0, [&]()->bool {
//							if (!playover)playover = true;
//							return true;
//							});
//					}
//				}
//			}
//			else ls = max(ls, i);
//		}
//		for (int i = pals; i < part.size(); ++i) {
//			if (part[i].st + 2000 < gameTime)pals = max(pals, i);
//			part[i].dir.y += (y(gameTime + 1000 / frameps - part[i].st) - y(gameTime - part[i].st));
//			part[i].pos += part[i].dir * 0.1;
//			ptr3.setColor(250, 17, 26, (Randf() + 1) * 0.5);
//			ptr3.fillCube(SQT(0.3, qua(vec3(0, 1, 0), 2 * part[i].dir.z + part[i].dir.x) *
//				qua(vec3(1, 0, 0), part[i].dir.y * 3), part[i].pos));
//		}
//		if (m.mCurState == Fire) {
//			buls.push_back({ m.mModelTransform.t + m.mModelTransform.q.rotate(buloff),m.mEyeDirectionv() });
//		}
//		las = m.mCurState;
//		checkStage();
//		if (sim) {
//			m.simulate(CD(&m));
//			qiuqiu.simulate();
//		}
//
//		if (m.mHasGun) {
//			if (m.mCurState == Fire)mm.mModelTransform = m.mModelTransform * m.mPose[24] * t;
//			else mm.mModelTransform = m.mModelTransform * m.mPose[1] * sqt;
//		}
//		if (render_gun)
//			phong << mm;
//		phong << m;
//		if (ren_qiu)phong << qiuqiu;
//		if (stage >= 12)cub[0].mModelTransform.q = qua(vec3(0, 1, 0), -0.013) * cub[0].mModelTransform.q; phong << cub[0];
//		for (int i = 1; i < 10; ++i) {
//			if (stage >= 12)cub[i].mModelTransform.q = qua(vec3(0, 1, 0), 0.00680) * cub[i].mModelTransform.q;
//			phong << cub[i];
//		}
//		phong << sp << key << b;
//		sp.rotate(1, vec3(0, 1, 0));
//		ren.renderList(block);
//		});
//
//
//}