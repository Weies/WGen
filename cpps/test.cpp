//#pragma once
//#include<WinSock2.h>
//#include<socketapi.h>
//#include"graphBasic.h"
//#include<fstream>
//using namespace std;
//void ha()
//{
//	sockaddr_in addr;
//	addr.sin_family = AF_INET;
//	addr.sin_addr.S_un.S_addr = inet_addr("102.12.12.12");//�ַ���ת��Ϊ������
//	addr.sin_port = htons(80);
//	debug(inet_ntoa(addr.sin_addr));//������ת��Ϊ�ַ���
//	WORD word = MAKEWORD(2, 0);//�������汾�ź͸��汾��2.0
//	WSAData data;
//	WSAStartup(word, &data);//�ɹ�����0
//	//debug(data.szDescription);//�汾��Ϣ
//	//debug(data.szSystemStatus);//�׽���״̬��Running
//	//debug(data.iMaxSockets);//����������׽�����
//	char c[20];
//	gethostname(c, 20);//ȡ�õ�ǰ���������֣�weies����
//	hostent* p = gethostbyname("baidu.com");
//
//	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//	//����1�� ����Э�飺v4 AF_INET��v6 AF_INET6
//	//����2�� ���ô��䷽ʽ����ʽ SOCK_STREAM,���ݱ���SOCK_DGRAM
//	//����3�� ���ô���Э�飺IPPROTO_TCP,IPPROTO_UDP
//	//closesocket(sock);//�ر��׽���
//
//	SOCKADDR addr0 = sockaddr();
//	addr0.sa_data;
//	bind(sock, &addr0, 15);
//	listen(sock, 10);//�ڶ����������Ŷӵĳ���
//	connect(sock, &addr0, 15);//����ö��ֵ������ʱSOCK_ERROR
//	int* pp;
//	int ret0 = getsockname(sock, &addr0, pp);//������ȡ�Ѱ󶨣�������δ����bind��ϵͳ�Զ��󶨣����׽ӿڱ���Э���ַ��sockaddr=IP:PORT��
//	int ret1 = getpeername(sock, &addr0, pp);
//	//getpeername���������ָ���׽ӿ����ӵ�Զ�̵�ַ��Ϣ
//
//	SOCKET S = accept(sock, &addr0, pp);
//
//	//����������ȡip
//	struct hostent* pHostBaiDu = gethostbyname("www.baidu.com");
//	printf("Host name: %s/n", pHostBaiDu->h_name);
//	printf("IP Address: %s/n", inet_ntoa(*((struct in_addr*)pHostBaiDu->h_addr)));
//
//	//��������
//	int ret2 = send(sock, c, 10, 0);
//	int ret3 = sendto(sock, c, 10, 0, &addr0, 15);//��Ҫ�������������ӵ�UDP
//
//	int ret4 = recv(sock, c, 10, 0);
//	int ret5 = recvfrom(sock, c, 10, 0, &addr0, pp);
//
//	int ret6 = shutdown(sock, SD_BOTH);//�ڶ�������:SD_RECIEVE�رս���,SD_SEND�رս��ܡ�
//										//SD_BOTH�ر�˫��
//	int err = WSAGetLastError();//��ȡ��һ������
//	setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, c, 20);
//	closesocket(sock);//�ر��׽���
//}
//int main()
//{
//
//	WORD word = MAKEWORD(2, 0);//�������汾�ź͸��汾��2.0
//	WSAData data;
//	int ret = WSAStartup(word, &data);//�ɹ�����0
//	if (ret!=0)
//	{
//		debug("wrong when start up");
//		exit(0);
//	}
//	sockaddr_in svraddr;
//	memset(&svraddr, 0, 16);
//	svraddr.sin_port = htons(8080);
//	svraddr.sin_family = AF_INET;
//	svraddr.sin_addr.S_un.S_addr = INADDR_ANY;
//	SOCKET server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//
//	_WINSOCK2API_::bind(server, (sockaddr*)&svraddr, sizeof(svraddr));
//	if (listen(server, 10)!=0)
//	{
//		debug("wrong when listen");
//		debug(GetLastError());
//		exit(0);
//	}
//	sockaddr_in inaddr;
//	int len = 0;
//	int length = 0;
//	while (true)
//	{
//		len = sizeof(inaddr);
//		SOCKET so = accept(server, (sockaddr*)&inaddr, &len);
//		if (so==INVALID_SOCKET)continue;
//		char c[100];
//		if ((length=recv(so, c, 100, 0))<=0)//<0����=0�رգ�>0��ʾ���ܵ��ֽ���
//		{
//			debug("wrong when receieve");
//			debug(WSAGetLastError());
//			exit(0);
//		}i
//		else {
//			debugAll(c,length);
//			send(so, "success", 8, 0);
//		}
//		shutdown(so, SD_BOTH);
//		closesocket(so);
//	}
//
//	shutdown(server, SD_BOTH);
//	closesocket(server);
//	WSACleanup();
//}

//#include"globalValues.h"
//#include<iostream>
//using namespace globals;

//void makeorder(int& a, int& b, int& c)
//{
//    if (a>b)
//        swap(a, b);
//    else if (b>c)
//        swap(b, c);
//}
//void trisort(int a[], int s, int e)
//{
//    int to = e-s;
//    if (to<3)return;
//    to = to/2;
//    for (int i = 0; i<to; i++)
//    {
//        if (a[e-i]<a[s+i])
//            swap(a[s+i], a[e-i]);
//        makeorder(a[s+i], a[to], a[e-i]);
//    }
//    trisort(a, s, to);
//    trisort(a, to+1, e);
//}
//int main()
//{
//    int a[100] = { 5,1,4,9,3,7 };
//    for (int i = 0; i<100; i++)
//        a[i] = rand()%100;
//    trisort(a, 0, 9);
//    for (int i = 0; i<10; i++)
//        debug<<a[i]<<" ";
//}
