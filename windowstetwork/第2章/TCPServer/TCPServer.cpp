//////////////////////////////////////////////////
// TCPServer.cpp�ļ�


#include "../common/InitSock.h"
#include <stdio.h>
CInitSock initSock;		// ��ʼ��Winsock��


int main()
{
	// �����׽���
	SOCKET sListen = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sListen == INVALID_SOCKET)
	{
		printf("Failed socket() \n");
		return 0;
	}
	
	// ���sockaddr_in�ṹ
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(4567);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	
	// ������׽��ֵ�һ�����ص�ַ
	if(::bind(sListen, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		printf("Failed bind() \n");
		return 0;
	}
	
	// �������ģʽ
	if(::listen(sListen, 2) == SOCKET_ERROR)
	{
		printf("Failed listen() \n");
		return 0;
	}
	
	// ѭ�����ܿͻ�����������
	sockaddr_in remoteAddr; 
	int nAddrLen = sizeof(remoteAddr);
	SOCKET sClient;
	char szText[] = " TCP Server Demo! \r\n";
	while(TRUE)
	{
		// ����һ��������
		sClient = ::accept(sListen, (SOCKADDR*)&remoteAddr, &nAddrLen);
		if(sClient == INVALID_SOCKET)
		{
			printf("Failed accept()");
			continue;
		}
		
		printf(" ���ܵ�һ�����ӣ�%s \r\n", inet_ntoa(remoteAddr.sin_addr));




		// ��������
		char buff[1024];
		int nLen = sizeof(remoteAddr);
		int nRecv = ::recvfrom(sClient, buff, 1023, 0, (sockaddr*)&remoteAddr, &nLen); 
		if(nRecv > 0)
		{
			buff[nRecv] = '\0';
			printf(" ���յ����ݣ�%s����%s\n", ::inet_ntoa(remoteAddr.sin_addr), buff);
		}





		// ��ͻ��˷�������
		::send(sClient, szText, strlen(szText), 0);
		//����ʱ�䷢��  �ر�ͬ�ͻ��˵�����
		Sleep(100);
		::closesocket(sClient);
	}
		
	// �رռ����׽���
	::closesocket(sListen);
	return 0;
}

