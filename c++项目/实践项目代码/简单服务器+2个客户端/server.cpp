/*
 * @Description: 
 * @Version: 2.0
 * @Autor: jjkhl
 * @Date: 2021-11-26 20:41:28
 * @LastEditors: jjkhl
 * @LastEditTime: 2021-11-28 21:27:07
 */
#include<iostream>
#include<thread>
#include<mutex>
#include<vector>
#include<WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
typedef struct my_file
{
    SOCKET client_sock;
    sockaddr_in client_addr;
    int id;
}F;
void transmit(const LPVOID &p)
{
    F *temp=(F*) p;
    cout<<"==========*�� �� �� �� ��*=========="<<endl;
    cout<<"�ȴ��ͻ��˷�����Ϣ..."<<endl;
    while(true)
    {
        //�ӿͻ��˴���������
        char Buff[MAXBYTE]={0};
        recv(temp->client_sock,Buff,MAXBYTE,0); 
        cout << "�̣߳�" << temp->id << "\t�˿ںţ�"
			<< ntohs(temp->client_addr.sin_port) << endl;
		cout << "�ͻ���: " << Buff << endl;
        const char *s="Server file";
        send(temp->client_sock,s,strlen(s)*sizeof(char)+1,0);
        cout<<"�̣߳�"<<temp->id<<"ͨ���ͻ��˵�"<<ntohs(temp->client_addr.sin_port)
        <<"�Ŷ˿ڷ��ͣ�"<<s<<endl;
        cout<<"==========*�ѷ���==========*"<<endl;
        if(strcmp(Buff,"quit")==0||strcmp(Buff,"Quit")==0)
            {
                cout<<"�̣߳�"<<temp->id<<"�˳�������"<<endl;
                break;
            }
    }
    return;
}
int main()
{
    vector<thread> v_thread(20);
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2),&wsa);

    SOCKET serv_sock=socket(AF_INET,SOCK_STREAM,0);

    sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(2017);
    serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

    bind(serv_sock,(SOCKADDR*)&serv_addr,sizeof(SOCKADDR));
    listen(serv_sock,20);

    for(int i=0;i<20;i++)
    {
        F *tmp=new F;
        sockaddr_in client_addr;
        int nSize=sizeof(SOCKADDR);
        SOCKET client_sock=accept(serv_sock,(SOCKADDR*)&client_addr,&nSize);
        tmp->client_sock=client_sock;
        tmp->client_addr=client_addr;
        tmp->id=i+1;
        v_thread.push_back(thread(transmit,tmp));
        // v_thread.back().join();
    }
    cout << WSAGetLastError() << endl; //�鿴������Ϣ
    closesocket(serv_sock);
    WSACleanup();
    return 0;
}