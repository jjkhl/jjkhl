/*
 * @Description: 
 * @Version: 2.0
 * @Autor: jjkhl
 * @Date: 2021-11-29 10:03:29
 * @LastEditors: jjkhl
 * @LastEditTime: 2021-11-29 11:08:43
 */
#include<iostream>
#include<WinSock2.h>
#include<thread>
using namespace std;
int main()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2),&wsa);

    SOCKET client_sock=socket(AF_INET,SOCK_STREAM,0);
    sockaddr_in client_addr;
    memset(&client_addr,0,sizeof(client_addr));
    client_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    client_addr.sin_family=AF_INET;
    client_addr.sin_port=htons(2017);
    
    connect(client_sock,(SOCKADDR*)&client_addr,sizeof(SOCKADDR));
    cout << "==========*�ѽ���������*==========" << endl;
	while (true)
	{
		char* s = new char[100];
		cout << "С��: ";
		cin >> s;
		send(client_sock, s, strlen(s) * sizeof(char) + 1, 0);
		cout << "==========*�� �� �� ��*==========" << endl;
         if(strcmp(s,"quit")==0||strcmp(s,"Quit")==0)
        {
            break;
        }
	}
	char Buffer[MAXBYTE] = { 0 };
	recv(client_sock, Buffer, MAXBYTE, 0);
	cout << "ͨ���˿�:" << ntohs(client_addr.sin_port)
		<< "���յ�:" << Buffer << endl;
	closesocket(client_sock);
	WSACleanup();
	cout << "�ͻ��������ѹرա�" << endl;
	system("pause");
	return 0;
}