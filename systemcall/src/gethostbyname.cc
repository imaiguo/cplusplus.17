#include <stdio.h>
#include <winsock.h>
int main()
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    hostent* he = gethostbyname("www.stackoverflow.com");
    char* ip = inet_ntoa(*(struct in_addr*)he->h_addr_list[0]);
    printf(ip);
}