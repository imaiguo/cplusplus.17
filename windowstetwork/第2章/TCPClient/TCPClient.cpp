//////////////////////////////////////////////////////////
// TCPClient.cpp文件


#include "../common/InitSock.h"
#include <stdio.h>


int main()
{
	CInitSock initSock;		// 初始化Winsock库
	// 创建套节字
	SOCKET streamSock = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(s == INVALID_SOCKET)
	{
		printf(" Failed socket() \n");
		return 0;
	}
	
	// 也可以在这里调用bind函数绑定一个本地地址
	// 否则系统将会自动安排
	
	// 填写远程地址信息
	sockaddr_in servAddr; 
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(4567);
	// 注意，这里要填写服务器程序（TCPServer程序）所在机器的IP地址
	// 如果你的计算机没有联网，直接使用127.0.0.1即可
	servAddr.sin_addr.S_un.S_addr = inet_addr("118.123.249.176");
	
	FD_SET fd = { 1, streamSock };
	TIMEVAL tv = { 5, 0 };

	if( ::select(0, NULL, &fd, NULL, &tv) <= 0 ) 

	if(::connect(streamSock, (sockaddr*)&servAddr, sizeof(servAddr)) ==  SOCKET_ERROR)
	{
		printf(" Failed connect() \n");
		return 0;
	}
	




	// 接收数据
	char buff[256];
	int nRecv = ::recv(streamSock, buff, 256, 0);
	if(nRecv > 0)
	{
		buff[nRecv] = '\0';
		printf(" 接收到数据：%s", buff);
	}
	
	// 关闭套节字
	::closesocket(streamSock);
	getchar();
	return 0;
}


