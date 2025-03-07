#include"network.h"

function<void(void)> hander = 0;
bool SocketInited = false;
int NumOfSocks = 0;
mutex mu;
unique_lock<mutex> locker(mu);
condition_variable cond;
deque<string> que;

void Socket::createThreadToListenNewMassage()
{
	//建立守护线程监听回复
	thread td([=]() {
		char c[20000] = {};
		int timeout = 10000 * 1000;
		setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&(timeout), sizeof(int));
		while (true)
		{
			int num_bytes = (recv(sock, c, 500, 0));
			if (num_bytes < 0)
			{
				debug("Error happened  when recv");
				valid = false;
				return;
			}
			else if (num_bytes = 0)
			{
				debug("The connection was closed by the server");
				valid = false;
				break;
			}
			else
			{
				push(c);
				//hander();
				//处理新消息
				//
				//
				cond.notify_all();
				memset(c, 0, 20000);
			}
		}
		});
	td.detach();
}

SVRSocket::SVRSocket(unsigned short port, string IPAddress)
{
	memset(&addr, 0, 16);
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	if (IPAddress == "ANY")
		addr.sin_addr.S_un.S_addr = INADDR_ANY;
	else addr.sin_addr.S_un.S_addr = inet_addr(IPAddress.c_str());
	if (_WINSOCK2API_::bind(sock, (sockaddr*)&addr, 16) < 0)//=0成功，<0失败
		debug("Wrong when bind socket and address,last error" + WSAGetLastError());
}
void SVRSocket::listen()
{
	if (_WINSOCK2API_::listen(sock, 50) < 0)
	{
		debug("Wrong when start listen,last error: " + WSAGetLastError());
	}
	else
		//创建线程一直查询是否有新的连接
		if (!queryCreated)
		{
			createThreadToAccecptClient();
			queryCreated = true;
			debug("Begin listening.");
		}
}
void SVRSocket::createThreadToAccecptClient()
{
	thread td([=]() {//监听新连接的用户
		int len = 16;
		sockaddr_in address;
		while (true)
		{
			len = 16;
			SOCKET so = accept(sock, (sockaddr*)&address, &len);
			if (so == INVALID_SOCKET)continue;
			else
			{
				debug("Server accepted a new client, " + getUserInfo(address).toString());
				socklist.push(so);
				mSockets.push(shared_ptr<Socket>(new Socket(so)));
				cond.notify_all();
			}
		}
		});
	td.detach();
}
GameSocket::GameSocket(unsigned short port, string IPAddress)
{
	memset(&addr, 0, 16);
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	if (IPAddress == "ANY")
		addr.sin_addr.S_un.S_addr = INADDR_ANY;
	else addr.sin_addr.S_un.S_addr = inet_addr(IPAddress.c_str());
	if (_WINSOCK2API_::bind(sock, (sockaddr*)&addr, 16) < 0)//=0成功，<0失败
		debug("Wrong when bind socket and address,last error" + WSAGetLastError());
	listen();
}

void GameSocket::listen()
{
	if (_WINSOCK2API_::listen(sock, 50) < 0)
	{
		debug("Wrong when start listen,last error: " + WSAGetLastError());
	}
	else
		//创建线程一直查询是否有新的连接
		if (!queryCreated)
		{
			createThreadToAccecptClient();
			queryCreated = true;
		}
}
void GameSocket::listenAt(unsigned short port, string IPAddress)
{
	memset(&addr, 0, 16);
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	if (IPAddress == "ANY")
		addr.sin_addr.S_un.S_addr = INADDR_ANY;
	else addr.sin_addr.S_un.S_addr = inet_addr(IPAddress.c_str());
	if (_WINSOCK2API_::bind(sock, (sockaddr*)&addr, 16) < 0)//=0成功，<0失败
		debug("Wrong when bind socket and address,last error" + WSAGetLastError());
	listen();
}
void GameSocket::createThreadToAccecptClient()
{
	thread td([=]() {//监听新连接的用户
		int len = 16;
		sockaddr_in address;
		while (true)
		{
			len = 16;
			SOCKET so = accept(sock, (sockaddr*)&address, &len);
			if (so == INVALID_SOCKET)continue;
			else
			{
				debug("Server accepted a new client, " + getUserInfo(address).toString());
				socklist.push(so);
				cond.notify_all();
			}
		}
		});
	td.detach();
}

void UDPSocket::createThreadToListenNewMessage()
{
	thread query([=]() {
		char c[500] = {};
		int len = 16;
		while (true)
		{
			if (recvfrom(sock, c, 500, 0, (sockaddr*)&addr, &len) <= 0)
			{
				debug("The opposite is not online");
				break;
			}
			else
			{
				que.push(c);
				memset(c, 0, 500);
				cond.notify_all();
			}
		}
		});
	query.detach();
}

void UDPSSocket::init(unsigned short port, string ip)//指定对方的ip和自己的端口
{
	memset(&addr, 0, 16);
	memset(&to, 0, 16);
	to.sin_family = AF_INET;

	addr.sin_addr.S_un.S_addr = INADDR_ANY;
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	sendsock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	bind();
}