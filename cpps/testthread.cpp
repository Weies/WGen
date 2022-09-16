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
//	unique_lock<mutex> locke(mu);//指定mu之后，创建即锁定或等待
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
//	//thread t([]() {//主线程结束该线程会被立刻终止
//	//	debug(" hello");
//	//	Sleep(3000);
//	//});
//	//t.detach();
//
//	//debug(t.hardware_concurrency());//硬件支持的最大线程
//	//debug(t.native_handle());
//
//
//	//异步执行函数，可能不会建立新的线程，调用future.get可以阻塞主线程。
//	//调用get之前主线程一直执行，但是不会自动退出
//	
//	int b = 5;
//	thread td1(fun, b);
//	thread td2(fun2, b);
//	//td1.detach();
//	//td2.detach();
//	debug<<"main debug"<<endl;
//	//cond.wait(lockerr);//为true时直接跳过等待,当为true且notify才跳出。
//	debug("main was unlocked");
//	//exit(12345);//主线程退出子线程被抛弃
//}
//
