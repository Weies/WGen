//#include"network.h"
//#include"widget.h"
//int main()
//{
//	SVRSocket svr(8022);//绑定服务器的端口
//	svr.listen();//开始监听
//	this_thread::sleep_for(200ms);//线程休眠200ms，其实这里没有必要
//	Socket s=svr.getUserSocketBlock();//阻塞线程接受客户端，并创建一个新的套接字
//	string ss=s.receieveBlock();//使用新接手的客户端来阻塞接受信息
//	debug(ss);//输出信息
//	eventLoop();//事件循环（这是一个宏定义），这里程序可以直接终止
//}