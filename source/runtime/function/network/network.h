#pragma once
#include<WinSock2.h>
#include"core/log/debuger.h"
#include<thread>
#include<mutex>
#include<condition_variable>
#include<future>
#include<vector>
#include<queue>
using namespace std;

extern function<void(void)> hander;
extern bool SocketInited;
extern int NumOfSocks;
extern mutex mu;
extern unique_lock<mutex> locker;
extern condition_variable cond;
extern deque<string> que;
inline void initAPI()
{
	WORD word = MAKEWORD(2, 0);//�������汾�ź͸��汾��2.0
	WSAData data;
	if (WSAStartup(word, &data) != 0)//�ɹ�����0
		debug("Wrong when start up socket APIs,last error: " + WSAGetLastError());
	SocketInited = true;
}

inline string getHostByName(string s)
{
	if (!SocketInited)
		initAPI();
	return inet_ntoa(*((struct in_addr*)gethostbyname(s.c_str())->h_addr));
}

inline string getIP(string s)
{
	if (!SocketInited)
		initAPI();
	return inet_ntoa(*((struct in_addr*)gethostbyname(s.c_str())->h_addr));
}

class userInfo {
public:
	userInfo(string ipp, unsigned short portt) {
		ip = ipp;
		port = portt;
	}
	string toString()
	{
		return " ip: " + ip + ", port: " + itos(port);
	}
	string ip;
	unsigned short port;
};

inline userInfo getUserInfo(sockaddr_in in)
{
	auto port = ntohs(in.sin_port);
	auto ip = inet_ntoa(in.sin_addr);
	return userInfo(ip, port);
}

class AbstractSocket {
public:
	AbstractSocket() {
		if (!SocketInited)
			initAPI();
		NumOfSocks++;
	}
	void setPort(unsigned short port)
	{
		addr.sin_port = htons(port);
		//if (needbind&&_WINSOCK2API_::bind(sock, (sockaddr*)&addr, 16)<0)//=0�ɹ���<0ʧ��
		//	debug("Wrong when bind socket and address,last error"+WSAGetLastError());
	}

	void setIPAddress(string IPAddress = "ANY")
	{
		if (IPAddress == "ANY")
			addr.sin_addr.S_un.S_addr = INADDR_ANY;
		else addr.sin_addr.S_un.S_addr = inet_addr(IPAddress.c_str());
	}

	~AbstractSocket() {
		NumOfSocks--;
		shutdown(sock, SD_BOTH);
		closesocket(sock);
		if (NumOfSocks == 0)
		{
			WSACleanup();
			SocketInited = false;
		}
	}

	bool valid = true;
	sockaddr_in addr;
	SOCKET sock;
};


inline void push(string s)
{
	que.push_back(s);
}

class Socket :public AbstractSocket {//�ͻ����׽���
public:
	Socket() {
		valid = false;
	}

	Socket(string ip, unsigned short port)//�ͻ��˲���Ҫbind��IP,port���Ƿ�������
	{
		memset(&addr, 0, 16);
		addr.sin_addr.S_un.S_addr = inet_addr(ip.c_str());
		addr.sin_port = htons(port);
		addr.sin_family = AF_INET;
		sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	}

	void connect()//�Ѿ���ʼ������connect���������connectToHost
	{
		if (!valid) debug("Can not connect before assign IP&Port,please use connectToHost");
		else if (_WINSOCK2API_::connect(sock, (sockaddr*)&addr, 16) < 0)//��connectָ����������port���������ӣ�֮�����recv��send
		{
			debug("Wrong when connect to host: " + getUserInfo(addr).toString());
		}
		else
		{
			debug("Client connect succesfully");
			createThreadToListenNewMassage();
		}
	}

	void connectToHost(string ip, unsigned short port)
	{
		valid = true;
		memset(&addr, 0, 16);
		addr.sin_addr.S_un.S_addr = inet_addr(ip.c_str());
		addr.sin_port = htons(port);
		addr.sin_family = AF_INET;
		sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		connect();
	}

	void send(string s)
	{
		if (_WINSOCK2API_::send(sock, s.c_str(), s.length(), 0) < 0)
		{
			debug("Wrong when send MSG to host: " + getUserInfo(addr).toString());
		}
	}

	string receieve()//����������
	{
		if (que.empty())
			return "";
		string s = que.front();
		que.pop_front();
		return s;
	}

	string receieveBlock() //��������
	{
		if (que.empty())
			cond.wait(locker);//��������
		string s = que.front();
		que.pop_front();
		return s;
	}
private:
	friend class SVRSocket;
	friend class GameSocket;
	Socket(SOCKET s)//���ڷ��������ܵ�socket�Ĺ���
	{
		valid = true;
		sock = s;
		memset(&addr, 0, 16);
		int len = 16;
		getpeername(s, (sockaddr*)&addr, &len);
		createThreadToListenNewMassage();
	}
	void createThreadToListenNewMassage();
};

class SVRSocket :public AbstractSocket {//������׽���
public:				//�����з�����Ϣ�Ľӿ�,ͨ��getSocket֮�����ͨ��
	SVRSocket() { valid = false; };
	SVRSocket(unsigned short port, string IPAddress = "ANY");

	virtual void listen();

	bool connected() {
		return !socklist.empty();
	}

	shared_ptr<Socket> getUserSocket()
	{
		if (!mSockets.empty())
		{
			return mSockets.back();
		}
		return nullptr;
	}

	shared_ptr<Socket> getUserSocketBlock()
	{
		if (socklist.empty())
		{
			debug("queue is empty,blocked for client");
			cond.wait(locker);
		}
		return nullptr;
	}

	bool queryCreated = false;
	queue<SOCKET> socklist;
	queue<shared_ptr<Socket>> mSockets;
private:
	void createThreadToAccecptClient();
};

class GameSocket :AbstractSocket {
public:
	GameSocket() { valid = false; };
	GameSocket(unsigned short port, string IPAddress = "ANY");

	virtual void listen();

	void listenAt(unsigned short port, string IPAddress = "ANY");

	Socket& getUserSocket()
	{
		if (!socklist.empty())
		{
			static Socket so(socklist.front());
			return so;
		}
		Socket so;
		return so;
	}

	Socket& getUserSocketBlock()
	{
		if (socklist.empty())
		{
			debug("queue is empty,blocked for client");
			cond.wait(locker);
		}
		static Socket so(socklist.front());
		return so;
	}

	bool queryCreated = false;
	queue<SOCKET> socklist;
private:
	void createThreadToAccecptClient();
};

class UDPSocket :public AbstractSocket {//�ͻ����׽���
public:
	UDPSocket() { valid = false; };

	UDPSocket(string ip, unsigned short port)
	{
		init(ip, port);
	}

	void bind()
	{
		if (_WINSOCK2API_::bind(sock, (sockaddr*)&addr, 16) < 0)
		{
			debug("Wrong when bind socket with : " + getUserInfo(addr).toString());
		}
	}

	void init(string ip, unsigned short port = 14570)//ָ����������ip���Լ��Ķ˿�
	{
		memset(&addr, 0, 16);
		addr.sin_addr.S_un.S_addr = inet_addr(ip.c_str());
		addr.sin_port = htons(port);
		addr.sin_family = AF_INET;
		sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		createThreadToListenNewMessage();
	}

	void send(string s)
	{
		if (_WINSOCK2API_::sendto(sock, (s).c_str(), s.length(), 0, (sockaddr*)&addr, 16) < 0)
		{
			debug("Wrong when send MSG to host: " + getUserInfo(addr).toString());
		}
	}

	string receieve()
	{
		if (que.empty())
		{
			return "";
		}
		return que.front();
	}

	string receieveBlock()
	{
		if (que.empty())
		{
			debug("que is empty,waiting");
			cond.wait(locker);
		}
		return que.front();
	}
	queue<string> que;
private:
	void createThreadToListenNewMessage();
};

class UDPSSocket :public AbstractSocket {//������׽���
public:
	UDPSSocket() { valid = false; };

	UDPSSocket(unsigned short port, string ip = "ANY")
	{
		init(port, ip);
	}

	void init(unsigned short port = 14570, string ip = "ANY");//ָ���Է���ip���Լ��Ķ˿�

	void bind()
	{
		if (_WINSOCK2API_::bind(sock, (sockaddr*)&addr, 16) < 0)
		{
			debug("Wrong when bind socket with : " + getUserInfo(addr).toString());
		}
	}

	void send(string s)
	{
		if (_WINSOCK2API_::sendto(sendsock, (s).c_str(), s.length(), 0, (sockaddr*)&to, 16) < 0)
		{
			debug("Wrong when send MSG to host: " + getUserInfo(to).toString());
		}
	}

	string receieveBlock()
	{
		char c[1000] = {}; int len = 16;
		if (recvfrom(sock, c, 1000, 0, (sockaddr*)&to, &len) <= 0)
		{
			debug("receieve nothing");
		}
		return c;
	}
	sockaddr_in to;
	SOCKET sendsock;
	queue<string> que;
private:
};