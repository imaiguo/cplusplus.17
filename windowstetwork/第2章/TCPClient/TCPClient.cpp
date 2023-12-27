//////////////////////////////////////////////////////////
// TCPClient.cpp�ļ�


#include "../common/InitSock.h"
#include <stdio.h>


int main()
{
	CInitSock initSock;		// ��ʼ��Winsock��
	// �����׽���
	SOCKET streamSock = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(s == INVALID_SOCKET)
	{
		printf(" Failed socket() \n");
		return 0;
	}
	
	// Ҳ�������������bind������һ�����ص�ַ
	// ����ϵͳ�����Զ�����
	
	// ��дԶ�̵�ַ��Ϣ
	sockaddr_in servAddr; 
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(4567);
	// ע�⣬����Ҫ��д����������TCPServer�������ڻ�����IP��ַ
	// �����ļ����û��������ֱ��ʹ��127.0.0.1����
	servAddr.sin_addr.S_un.S_addr = inet_addr("118.123.249.176");
	
	FD_SET fd = { 1, streamSock };
	TIMEVAL tv = { 5, 0 };

	if( ::select(0, NULL, &fd, NULL, &tv) <= 0 ) 

	if(::connect(streamSock, (sockaddr*)&servAddr, sizeof(servAddr)) ==  SOCKET_ERROR)
	{
		printf(" Failed connect() \n");
		return 0;
	}
	




	// ��������
	char buff[256];
	int nRecv = ::recv(streamSock, buff, 256, 0);
	if(nRecv > 0)
	{
		buff[nRecv] = '\0';
		printf(" ���յ����ݣ�%s", buff);
	}
	
	// �ر��׽���
	::closesocket(streamSock);
	getchar();
	return 0;
}


