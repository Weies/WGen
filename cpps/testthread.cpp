//#include<thread>
//#include<iostream>
//#include<mutex>
//#include<future>
//#include<condition_variable>
//#include"widget.h"
//#include<sstream>
//using namespace std;
//int a = 0;
//mutex mu;
//condition_variable cond;
//bool yes = false;
//unique_lock<mutex> lockerr(mu);
//bool ret()
//{
//	return yes;
//}
//
//void fun(int b)
//{
//	mu.lock();
//	//cond.notify_all();
//	debug("thread 1 start");
//	Sleep(3000);
//	a = 4;
//	debug("after sleep 3000");
//	b = 3;
//	debug<<"thread 1 out: b="<<b<<endl;
//	
//	Sleep(3000);
//	debug<<"thread 1 sleep 3000 again"<<endl;
//	debug("thread 1 will notify");
//	debug("notify first time,when lock");
//	cond.notify_all();
//	Sleep(3000);
//	mu.unlock();
//	yes = true;
//	debug("notify second time,when unlock");
//	cond.notify_all();
//}
//
//void fun2(int b)
//{
//	unique_lock<mutex> locke(mu);//ָ��mu֮�󣬴�����������ȴ�
//	debug("thread 2 start");
//	debug("Threed 2 will be lock");
//	debug("Threed 2 is unlock");
//	b = 300;
//	debug<<"thread 2 out: b="<<b<<endl;
//	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
//	a = 400;
//	debug<<"thread 2 unlock res"<<endl;
//}
//
//void setTimer(int m, function<void(void)> timer)
//{
//	thread td([=]() {
//		while (true)
//		{
//			std::this_thread::sleep_for(std::chrono::milliseconds(m));
//			timer();
//		}
//	});
//	td.detach();
//}
//
//int main()
//{
//	int i = 0;
//	//thread t([]() {//���߳̽������̻߳ᱻ������ֹ
//	//	debug(" hello");
//	//	Sleep(3000);
//	//});
//	//t.detach();
//
//	//debug(t.hardware_concurrency());//Ӳ��֧�ֵ�����߳�
//	//debug(t.native_handle());
//
//
//	//�첽ִ�к��������ܲ��Ὠ���µ��̣߳�����future.get�����������̡߳�
//	//����get֮ǰ���߳�һֱִ�У����ǲ����Զ��˳�
//	
//	int b = 5;
//	thread td1(fun, b);
//	thread td2(fun2, b);
//	//td1.detach();
//	//td2.detach();
//	debug<<"main debug"<<endl;
//	//cond.wait(lockerr);//Ϊtrueʱֱ�������ȴ�,��Ϊtrue��notify��������
//	debug("main was unlocked");
//	//exit(12345);//���߳��˳����̱߳�����
//}
//
