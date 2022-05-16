<h1 align="center">Linux�����ܷ��������</h1>

**���ıʼ���Ҫ��[TCP/IP������(��ʥ��)�ʼ�](../�����Ĵ��/TCPIP������(��ʥ��)/������.md)һ��ʹ��**
�ο��ʼǵ�ַ��
* https://blog.csdn.net/jojozym/article/details/106034037
* https://github.com/HiganFish/Notes-HighPerformanceLinuxServerProgramming
# TCP/IPЭ�����
## ��1�� TCP/IPV4Э����

![](picture/TCP_IPЭ������ϵ�ṹ����ҪЭ��.png)

TCP/IPЭ������һ���Ĳ�Э��ϵͳ���Ե׶��Ϸֱ���������·�㡢����㡢����㡢Ӧ�ò㡣�ϲ�Э��ʹ���²�Э���ṩ�ķ�����ͼ1-1��ʾ��

### ������·��
�ò�ʵ���������ӿڵ��������������Դ�������������ý���ϵĴ��䣬���õ�Э����ARPЭ��(Address Resolve Protocol����ַ����Э��)��RARPЭ��(Reverse Address Resolve Protocol����ַ����Э��)��

<strong style="color:red">RARPЭ��һ������������ϵ����̹���վ</strong>������û�д洢���ʣ����̹���վ�޷���ס�Լ���IP��ַ�����Կ������������ϵ������ַ���������ѯ�����IP��ַ��

ARPЭ����Ϊ��Ҫ����<strong style="color:red">��ʵ������������ַ�����������ַ��ת��</strong>������һ��ֻ��IP��ַ��MAC��ַ��ת�����乤��ԭ���ǣ��������Լ����ڵ�����㲥һ��ARP���󣬸��������Ŀ������������ַ���������������յ��������ʱ��ֻ�б������Ŀ���������Ӧһ��ARPӦ�����а������Լ��������ַ��

### �����
<strong style="color:red">�����ʵ�����ݰ���ѡ·��ת��</strong>��ͨѶ����̨����һ�㲻��ֱ������������ͨ������м�ڵ�(·����)���ӡ��������������ѡ����Щ�м�ڵ㣬��ȷ����̨����֮���ͨѶ·����

���������ĵ�Э����IPЭ��(Internet Protocol��������Э��)��IPЭ��������ݰ���Ŀ��IP��ַ���������Ͷ����������һ����Ҫ��Э����ICMPЭ��(Internet Control Message Protocol�����������Ʊ���Э��)������IPЭ�����Ҫ���䣬��Ҫ���ڼ���������ӡ�

### �����
�����Ϊ��̨�����ϵ�Ӧ�ó����ṩ�˵��˵�ͨ�š��������ʹ�õ�����ͨ�ŷ�ʽ��ͬ��<strong style="color:red">�����ֻ����ͨ�ŵ���ʼ�κ�Ŀ�Ķˣ������ں����ݰ�����ת����</strong>��
![](picture/����������������.png)

ͼ1-3�У���ֱ��ʵ�߼�ͷ��ʾTCP/IPЭ����֮���ʵ��ͨ�ţ���ˮƽ�����߼�ͷ��ʾ�߼�ͨ����·��ͬʱ��������·��(��������)��װ����������ĵ���ϸ�ڣ�������װ���������ӵ�ϸ�ڣ��������ΪӦ�ó����װ��һ���˵��˵��߼�ͨ����·���������ݵ��շ�����·�ĳ�ʱ�����ȡ�

��������ҪЭ����Ҫ��������TCPЭ�顢UDPЭ���SCTPЭ�顣

TCPЭ��(Transaction Control Protocol���������Э��)ΪӦ�ò��ṩ<strong style="color:red">�ɿ��ġ��������Ӻͻ�����</strong>�ķ�����ʹ�ó�ʱ�ش�������ȷ�ϵȷ�ʽ��ȷ�����ݰ�����ȷ�ط�����Ŀ�Ķˣ�TCP�����ǿɿ��ġ�

UDPЭ��(User Datagram Protocol���û����ݱ�Э��)ΪӦ�ò��ṩ<strong style="color:red">���ɿ��������Ӻͻ������ݱ�</strong>�ķ�������UDPЭ���޷���֤���ݴӷ��Ͷ���ȷ�ش��͵�Ŀ�Ķˣ��������;��ʧ����UDPֻ�Ǽ򵥵�֪ͨӦ�ó�����ʧ�ܣ���ˣ�ʹ��UDP��Ӧ�ó���ͨ��Ҫ�Լ���������ȷ�ϡ���ʱ�ش����߼���UDP�ǻ������ݱ��ķ���ÿ��UDP���ݱ�����һ�����ȣ����ն˱����Ըó���Ϊ��С��λ������������һ���Զ������������ݽ����ضϡ�

### Ӧ�ò�
<strong style="color:red">Ӧ�ò㸺����Ӧ�ó�����߼�</strong>��������·�㡢�����ʹ���㸺��������ͨ��ϸ�ڣ��ⲿ�ֱ�����ȶ��ָ�Ч��������Ƕ����ں˿ռ���ʵ�֣���Ӧ�ò������û��ռ�ʵ�֣���Ϊ���������ڶ��߼��������ļ����䡢���Ʋ�ѯ���������ȡ�

Ӧ�ò�Э���кࣺܶ
* ping��Ӧ�ó��򣬶�����Э�飬������ICMP���ļ���������ӣ��ǵ������绷���ıر����ߡ�
* telnetЭ����һ��Զ�̵�½Э�飬��ʹ�������ڱ������Զ������
* OSPF(Open Shortest Path First���������·������)Э����һ�ֶ�̬·�ɸ���Э�飬����·����֮���ͨ�ţ��Ը��߶Է����Ե�·����Ϣ��
* DNS(Domain Name Service����������)Э���ṩ����������IP��ַ��ת����

### ��װ
ͨ����װ(encapsulation)����ʵ���ϲ�Э��ʹ���²�Э���ṩ�ķ���
Ӧ�ò��send/write������㣺TCP ����/UDP���ݰ�����·�㣺ip���ݱ���������·�㣺֡(frame��֡������䵥Ԫ,MTU)
![](picture/��װ.png)

### ����
������·���Ӧ�ò�����У�����Э��
![](picture/��̫��֡�ķ��ù���.png)

��̫���������֡1518�ֽ� ��ȥ14ͷ�� ֡β4У��
MTU: ֡������䵥Ԫ һ��Ϊ1500�ֽ�
MSS: TCP���ݰ������������� 1460�ֽ� = 1500�ֽ� - 20Ipͷ-20TCPͷ ���ж����40�ֽڿ�ѡ����

### ARPЭ��
1. ��<strong style="color:red">ʵ��������·���ַ�����������ַ��ת��</strong>��IP��ַ����̫����ַ(MAC��ַ)����ԭ���������Լ����ڵ�����㲥һ��ARP���󣬸��������Ŀ������������ַ���������ϵ��������������յ�������󣬵�ֻ�б������Ŀ��������Ӧһ��ARPӦ�����а����Լ��������ַ��

2. ARPά��һ�����ٻ��棬������������(�������ص�ַ)��������ʵĻ���IP��ַ�������ַ��ӳ�䡣�������Ա����ظ���ARP��������˷������ݰ����ٶ�
> Linuxʹ��arp�������鿴���޸�ARP���ٻ��档

### DNS����ԭ��
DNS��һ�׷ֲ�ʽ����������ϵͳ����ʾ<strong style="color:red">����/ip֮����໥ӳ��</strong>��ÿ��DNS�������϶�����Ŵ�����������IP��ַ��ӳ�䣬���Ҷ�̬���¡�

## ��2�� IPЭ�����
���ã�Ϊ�ϲ�Э���ṩ��״̬�������ӡ����ɿ��ķ���

��״̬��ָIPͨ��˫����ͬ���������ݵ�״̬��Ϣ���������IP���ݱ��ķ��͡�����ͽ��ն����໥������û�������Ĺ�ϵ��ȱ�����޷�����������ظ���IP���ݱ����ŵ��Ǽ򵥸�Ч�����ӣ�UDPЭ���HTTPЭ�顣

��������ָIPͨ��˫���������õ�ά�ֶԷ����κ���Ϣ������ϲ�Э��ÿ�η������ݣ���������ȷָ���Է���IP��ַ��

���ɿ���ָIPЭ�鲻�ܱ�֤IP���ݱ�׼ȷ�ص�����նˣ���ֻ�ǳ�ŵ�����Ŭ��(besteffort)��

### IPV4Э����
![](picture/IPV4ͷ���ṹ.png)
IPV4��ͷ���ṹ����һ��Ϊ20�ֽ�

* 4λ�汾�ţ�version��ָ��IPЭ��İ汾����IPv4��˵����ֵ��4��
* 4λͷ�����ȣ�headerlength����ʶ��IPͷ���ж��ٸ�32bit�֣�4�ֽ�)����Ϊ4λ����ܱ�ʾ15������IPͷ�����60�ֽڡ�
* 8λ�������ͣ�Type Of Service��TOS)����һ��3λ������Ȩ�ֶΣ������Ѿ������ԣ���
* 4λ��TOS�ֶκ�1λ�����ֶΣ�������0����4λ��TOS�ֶηֱ��ʾ����С��ʱ���������������߿ɿ��Ժ���С���á����������һ������Ϊ1��Ӧ�ó���Ӧ�ø���ʵ����Ҫ����������������ssh��telnet�����ĵ�¼������Ҫ������С��ʱ�ķ��񣬶��ļ��������ʦ����Ҫ����������ķ���
* 16λ�ܳ��ȣ�totallength)��ָ����IP���ݱ��ĳ��ȣ����ֽ�Ϊ��λ�����IP���ݱ�����󳤶�Ϊ65535��2^(16)-1)�ֽڡ�

��IP���ݱ��ĳ��ȳ���MTU ���ᱻ��Ƭ����. ��Ƭ���ܷ����ڷ��Ͷ�, Ҳ���ܷ�������ת·����, �����ܱ���η�Ƭ. ֻ�������յ�Ŀ�������, ��Щ��Ƭ�Żᱻ�ں��е�ipģ��������װ��

## ��3�� TCPЭ�����
��IPЭ����ȸ�����Ӧ�ò㣬�����Ӧ�ó����о��и�ǿ�Ŀɲ����ԡ�
### TCP������ص�
TCPЭ�����UDPЭ���ص㣺<strong style="color:red">�������ӡ��ֽ����Ϳɿ�����</strong>��

TCPЭ���������һ��һ�����Թ㲥�Ͷಥ(Ŀ���Ƕ��������ַ)��Ӧ�ó�����ʹ��TCP����

���Ͷ�ִ�е�д�����ͽ��ն�ִ�еĶ���������֮��û���κ�������ϵ��������ֽ����ĸ��Ӧ�ó�������ݵķ��ͺͽ���ʱû�б߽����ơ�

### TCPͷ���ṹ
![](picture/TCPͷ���ṹ.png)
* 16λ�˿ںţ���֪�����ñ��Ķε�Դ�˿��Լ�Ŀ�Ķ˿ڡ�����֪������ʹ�õĶ˿ںŶ�������/etc/services�ļ��С�
* 32���кţ�һ��TCPͨ��(��TCP���ӽ������Ͽ�)������ĳһ�����䷽���ϵ��ֽ�����ÿ���ֽڵı�š�
* 32λȷ�Ϻţ���������һ����������TCP���Ķε���Ӧ����ֵ���յ���TCP���Ķε����ֵ+1��
* 4λͷ�����ȣ���ʶ��TCPͷ���ж���32bit��(4�ֽ�)����Ϊ4λ����ܱ�ʾ15������IPͷ�����60�ֽڡ�
* 16λ���ڴ�С��TCP�������Ƶ�һ���ֶΡ�������ָ����ͨ�洰�ڣ������߶Է����˵�TCP���ջ������������ɶ����ֽ����ݣ������Է��Ϳ��Կ��Ʒ������ݵ��ٶȡ�
* 16λУ��ͣ��ɷ��Ͷ���䣬���ն˶�TCP���Ķ�ִ��CRC�㷨�Լ���TCP���Ķ��ڴ���������Ƿ��𻵣��������TCPͷ�������ݲ��֡�
* 16λ����ָ�룺���Ͷ�����ն˷��ͽ������ݵķ�������һ������ƫ��������������ֶε�ֵ��Ӱ�Ŷ�����һ���������ݵ���һ�ֽڵ���š�
* 6λ��־λ
ACK��־: ��ʾȷ�Ϻ��Ƿ���Ч.  `ȷ�ϱ��Ķ�`
PSH��־: ��ʾ���ն�Ӧ�ó����TCP���ܻ������ж�������, Ϊ���������ڳ��ռ�
RST��־: Ҫ��Է����½�������       `��λ���Ķ�`
SYN��־: ��־������һ������       `ͬ�����Ķ�`
FIN��־: ֪ͨ�Է���������Ҫ�ر���,  `�������Ķ�`

### TCP���ӵĽ����͹ر�
seq�����к�
ack��ȷ�Ϻ�
SYN��ͬ������

<strong style="color:red">���ն˵�ack���ǵ��ڷ��Ͷ˵�seq+1</strong>

A �� TCP �� B �������������ĶΣ����ײ��е�ͬ��λ SYN = 1����ѡ����� seq = x��������������ʱ�ĵ�һ�������ֽڵ������ x��

B �� TCP �յ����������Ķκ���ͬ�⣬�򷢻�ȷ�ϡ�B ��ȷ�ϱ��Ķ���Ӧʹ SYN = 1��ʹ ACK = 1����ȷ�Ϻ�ack = x+1���Լ�ѡ������ seq = y��

A �յ��˱��Ķκ��� B ����ȷ�ϣ��� ACK = 1��ȷ�Ϻ� ack = y + 1��A �� TCP ֪ͨ�ϲ�Ӧ�ý��̣������Ѿ�������

B �� TCP �յ����� A ��ȷ�Ϻ�Ҳ֪ͨ���ϲ�Ӧ�ý��̣�TCP �����Ѿ�������
![](picture/��������.png)
![](picture/�Ĵλ���.png)

![](picture/TCP���ӵĽ����͹ر�.png)

![](picture/TCP���ӵĽ����ͶϿ������пͻ��˺ͷ���˵�״̬�仯.png)

#### TIME_WAIT
�����״̬���ͻ�������Ҫ�ȴ�һ�γ�Ϊ2MSL��MaximumSegmentLife�����Ķ��������ʱ�䡵��ʱ�䣬������ȫ�رա�MSL��TCP���Ķ��������е��������ʱ�䣬��׼�ĵ�RFCn22�Ľ���ֵ��2min��

TIME_WAIT״̬���ڵ�ԭ��
* �ɿ�����ֹTCP����
* ��֤�ó�����TCP���Ķ����㹻��ʱ�䱻ʶ�𲢶���

### ��λ���Ķ�
��λ���ĶΣ�����RST��־�ı��ĶΣ�����֪ͨ�Է��ر����ӻ����½�������

����������
* ���ʲ����ڵĶ˿�
* �쳣��ֹ���ӣ�����ʹ��socketѡ���`SO_LINGER`�����͸�λ���ĶΣ����쳣��ֹһ�����ӡ�һ��������RST���ĶΣ����Ͷ������Ŷӵȴ����͵����ݶ�����������
* ���������ӣ�����ͻ���(�������)�����ڰ��״̬������д�����ݣ���Է�����Ӧһ����λ���ĶΡ�

### TCP����������
�������ݽ��������ٵ��ֽڣ�ʹ�����Ӧ�ó���(��Э��)��ʵʱ��Ҫ��ߣ�����telnet��ssh�ȡ�

��ʱȷ�ϣ��ͻ�����Է��������ص����������͵�ȷ�ϱ��Ķβ�Я���κ�Ӧ�ó������ݣ���������ÿ�η��͵�ȷ�ϱ��Ķζ���������Ҫ���͵�Ӧ�ó������ݡ�������������ȷ���յ������ݣ�������һ���ӳ�ʱ���鿴�����Ƿ���������Ҫ���ͣ���������ȷ����Ϣһ�𷢳���<strong style="color:red">��ʱȷ�ϵĺô��ǿ��Լ��ٷ���TCP���Ķε�������</strong>


Nagle �㷨��Ӧ���� TCP ���һ�����㷨��ֻ���յ�ǰһ���ݵ� ACK ��Ϣʱ��Nagle �㷨�Żᷢ����һ���ݡ�
TCP Ĭ��ʹ�� Nagle �㷨����˻�����޶ȵؽ��л��壬ֱ���յ� ACK �Ž����ݷ��ͳ�ȥ��
![Nagle�㷨](picture/Nagle�㷨.png)

Nagle �㷨���ŵ㣺���Ա�������������������������ʹ�� Nagle �㷨�����ݵ������������������ͳ�ȥ���������������С�İ�������ͼ��ʾ�����������縺�ء�

Nagle �㷨��ȱ�㣺�ܶ�ʱ��ή�ʹ����ٶȡ���ʹ�� Nagle �㷨ʱ����������ȴ� ACK ���ľͿ��Է��ͳ�ȥ��û�еȴ�ʱ�䡣�ڷ��ʹ��ļ�����ʱ�������ԡ���Ϊ������ļ����������Ƿ�ʹ��Nagle �㷨���������������С���ݰ�������ʹ�� Nagle �㷨���õȴ� ACK ���ģ��ٶȸ��졣

### TCP�ɿ�������

���ʹ���������ݵ�ʱ�򣬷��ͷ����������Ͷ��TCP���ĶΣ����շ�����һ����ȷ��������Щ���ĶΡ�

### TCP��ʱ�ش�
TCP��������ܹ��ش���ʱʱ����δ�յ�ȷ�ϵ�TCP���ĶΡ�Ϊ�ˣ�TCPģ��Ϊÿ��TCP���Ķζ�ά��һ���ش���ʱ�����ö�ʱ����<strong style="color:red">TCP���Ķε�һ������ʱ����</strong>��

TCP�ش����ԣ���ʱʱ�����ѡ�����ִ�ж��ٴ��ش���
�ش����Է����ڳ�ʱ֮ǰ���������ش���

### TCPӵ������
TCPӵ����׼�ĵ���RFC 5681��

�ŵ㣺������������ʡ����Ͷ����ʡ���֤������Դ��ÿ���������Ĺ�ƽ�ԡ�

ӵ�����Ƶı��������ʹ��ڣ����Ͷ�һ��������д�������������ΪSWND(Send Window)��

ӵ��ӵ�еĲ��֣���������ӵ�����⡢�����ش������ٻָ�

Ϊʲô��Ҫӵ�����ƣ�
* SWND̫С���������Ե������ӳ٣�̫��ᵼ������ӵ��

���շ�����ͨ�����մ���(RWND)�����Ʒ��ʹ���(SWND)��������Ȼ����������ڷ��Ͷ�������һ����Ϊӵ������(Congestion Window��CWND)��״̬������

## ������ TCP/IPͨ�Ű���������Internet�ϵ�Web������
![](picture/ͨ���������������Internet�ϵ�Web������.png)
![](picture/DNS��ѯ.png)

# ������������ܷ��������
## ������Linux�����̻���API

[��ϸ���ܼ���������.md���ļ�](../�����Ĵ��/TCPIP������(��ʥ��)/������.md)

## ������ �߼�I/O����
���ڴ����ļ��������ĺ�����pipe��dup/dup2����
���ڶ�д���ݵĺ�����readv/writev��sendfile��mmap/munmap��splice��tee����
���ڿ���I/O��Ϊ�����Եĺ�����fcntl����

### [pipe����](../�����Ĵ��/TCPIP������(��ʥ��)/������.md#multiprocess)
���ã����ڴ���ҹ��ܵ�����ʵ�ֽ��̼�ͨ��
```c++
// ��������
// �����ļ����������� fd[0] ���� fd[1]д�� ����ܵ�
// �ɹ�����0, ����һ�Դ򿪵��ļ����������������ָ�������
// ʧ�ܷ���-1 errno
#include <unistd.h>
int pipe(int fd[2]);
```

```c++
//˫��ܵ�
// ��һ������Ϊ Э��PF_UNIX(������AF_UNIX)�о�����ָ��Э��ʹ��PF����һЩ
//�ɹ�����0��ʧ�ܷ���-1������errno
#include <sys/types.h>
#include <sys/socket.h>
int socketpair(int domain, int type, int protocol, int fd[2]);

ʾ�����룺
#include<stdio.h>
#include<string.h>//strlenͷ�ļ�
#include<unistd.h>//forkͷ�ļ�
#include<sys/types.h>
#include<sys/socket.h>
int main()
{
    int fd[2];
    socketpair(AF_UNIX,SOCK_STREAM,0,fd);
    int pid=fork();
    if(0==pid)//�ӽ���
    {
        close(fd[0]);
        char a[]="123";
        send(fd[1],a,strlen(a),0);
    } 
    else if(pid>0)
    {
        close(fd[1]);
        char b[20]={};
        recv(fd[0],b,20,0);
        printf("%s\n",b);
    }
    return 0;
}
```
### [dup��dup2����](../�����Ĵ��/TCPIP������(��ʥ��)/������.md#dup&dup2)
����һ�����е��ļ�������
```c
#include <unistd.h>
// ���ص��ļ�����������ȡϵͳ��ǰ���õ���С����ֵ
int dup(int oldfd);
// ������newfd���ƶ��µ��ļ�������, ���newfd�Ѿ��������ȹر�
// ���newfd==oldfd �򲻹ر�newfdֱ�ӷ���
int dup2(int oldfd, int newfd);
```

dup��������һ���µ��ļ�������, �µ��ļ���������ԭ�е��ļ���������ָͬ����ͬ��Ŀ��.

���ڹص���`STDOUT_FILENO`dup��С�ļ�Ϊ`STDOUT_FILENO`���Ա�׼�������������ļ�֮��
```c
int main()
{
    int filefd = open("/home/lsmg/1.txt", O_WRONLY);
    close(STDOUT_FILENO);
    dup(filefd);
    printf("123\n");
    exit(0);
}
```

### readv��writev����
readv���������ݴ��ļ�������������ɢ���ڴ���У�writev�����򽫶���ɢ���ڴ�����һ��д���ļ��������С�
```c
#include <sys/uio.h>
// count Ϊ vector�ĳ���, ��Ϊ�ж��ٿ��ڴ�
// �ɹ�ʱ����д��\��ȡ�ĳ��� ʧ�ܷ���-1
ssize_t readv(int fd, const struct iovec* vector, int count);
ssize_t writev(int fd, const struct iovec* vector, int count);

struct iovec {
	void* iov_base /* �ڴ���ʼ��ַ*/
	size_t iov_len /* ����ڴ泤��*/
}
```

### sendfile����
sendfile�����������ļ�������֮��ֱ�Ӵ�������(��ȫ���ں��в���)���Ӷ��������ں˻��������û�������֮������ݿ�����Ч�ʺܸߣ�����Ϊ**�㿽��**��
```c
#include <sys/sendfile.h>
// offsetΪָ�������������￪ʼ��, ���ΪNULL ��ӿ�ͷ��ȡ
ssize_t sendfile(int out_fd, int in_fd, off_t* offset, size_t count);

//in_fd�����������ݵ��ļ�������
//out_fd����д�����ݵ��ļ�������
//offset��ָ�������ļ�����ָ��λ�ã�Ĭ����ʼλ��
//count��ָ��������ֽ���
O_RDONLYֻ��ģʽ
O_WRONLYֻдģʽ
O_RDWR��дģʽ
int open(file_name, flag);
```
stat�ṹ��, ����fstat����, **��ֱ�����ļ������֤**
```c
#include <sys/stat.h>
struct stat
{
    dev_t       st_dev;     /* ID of device containing file -�ļ������豸��ID*/
    ino_t       st_ino;     /* inode number -inode�ڵ��*/
    mode_t      st_mode;    /* protection -����ģʽ?*/
    nlink_t     st_nlink;   /* number of hard links -������ļ���������(Ӳ����)*/
    uid_t       st_uid;     /* user ID of owner -user id*/
    gid_t       st_gid;     /* group ID of owner - group id*/
    dev_t       st_rdev;    /* device ID (if special file) -�豸�ţ�����豸�ļ�*/
    off_t       st_size;    /* total size, in bytes -�ļ���С���ֽ�Ϊ��λ*/
    blksize_t   st_blksize; /* blocksize for filesystem I/O -ϵͳ��Ĵ�С*/
    blkcnt_t    st_blocks;  /* number of blocks allocated -�ļ���ռ����*/
    time_t      st_atime;   /* time of last access -�����ȡʱ��*/
    time_t      st_mtime;   /* time of last modification -����޸�ʱ��*/
    time_t      st_ctime;   /* time of last status change - */
};
```

### mmap������munmap����
`mmap`������������һ���ڴ�ռ䣬`munmap`�ͷ�����ڴ�

```c
#include <sys/mman.h>

// start �ڴ���ʼλ��, ���ΪNULL��ϵͳ����һ����ַ lengthΪ����
// port���� PROT_READ(�ɶ�) PROT_WRITE(��д) PROT_EXEC(��ִ��), PROT_NONE(���ɷ���)
// flag���� �ڴ汻�޸ĺ����Ϊ
// - MAP_SHARED ���̼乲���ڴ�, ���ڴ���޸ķ�ӳ��ӳ���ļ���
// - MAP_PRIVATE Ϊ���ý���˽��, �Ը��ڴ�ε��޸Ĳ��ᷴӳ���ļ���
// - MAP_ANONUMOUS ���Ǵ��ļ�ӳ�����, ���ݱ���ʼ��Ϊ0, �����������������
// �ɹ���������ָ��, ʧ�ܷ��� -1
void* mmap(void* start, size_t length, int port, int flags, int fd, off_t offset);
// �ɹ�����0 ʧ�ܷ���-1
int munmap(void* start, size_t length);
```

### splice����
splice���������������ļ�������֮���ƶ����ݣ�Ҳ���㿽��������
```c++
#include<fcntl.h>
ssize_t splice(int fd_in, loff_t* off_in, int fd_out, loff_t* off_out, size_t len, unsigned int flags);
// fd_in Ϊ�ļ�������, ���Ϊ�ܵ��ļ��������� off_in����ΪNULL, ����Ϊ��ȡ��ʼƫ��λ��
// lenΪָ���ƶ������ݳ���, flags����������������ƶ�.
// - SPLICE_F_NONBLOCK ������splice����, �������ļ����������������
// - SPLICE_F_MORE ���ں�һ����ʾ, ������splice���ý���ȡ���������
```

|flags��������ֵ|����|
|---|---|
|SPLICE_F_MOVE|���鰴��ҳ�ڴ��ƶ����ݡ�|
|SPLICE_F_NONBLOCK|��������splice��������ʵ��Ч�����ܵ��ļ����������������״̬|
|SPLICE_F_MORE|��ʾ�ں˺���������ȡ��������|
|SPLICE_F_GIFT|��spliceû��Ч��|

### tee����
tee�����������ܵ��ļ�������֮�丳ֵ���ݣ�Ҳ���㿽��������

```c++
#include<fcntl.h>
ssize_t tee(int fd_in, int fd-out, size_t len,unsigned int flags);
//fd_in��fd_out����Ϊ�ܵ��ļ�������
//�ɹ������������ļ�������֮�丳ֵ���ֽ�����û�и����κ����ݷ���0��ʧ�ܷ���-1������errno
```

### fcntl����
fcntl����(file control)�ṩ�˶��ļ��������ĸ��ֲ������ơ�
```c++
#include<fcntl.h>
int fcntl(int fd, int cmd, ...);
//fd�����������ļ�������
//cmd��ִ�и������Ͳ���
```

**fcntl֧�ֵĳ��ò����������**

<div style="text-align: center;">
<table align="center">
    <tr>
        <td>��������</td>
        <td>����</td>
        <td>����</td>
        <td>��������������</td>
        <td>�ɹ�ʱ����ֵ</td>
    </tr>
    <tr>
        <td rowspan="2">�����ļ�������</td>
        <td>F_DUPFD</td>
        <td>����һ���µ��ļ�����������ֵ���ڻ����arg</td>
        <td>long</long>
        <td>�´������ļ�������ֵ</td>
    </tr>
    <tr>
        <td>F_DUPFD_CLOEXEC</td>
        <td>��<strong>F_DUPFD</strong>���ƣ������ڴ����ļ���������ͬʱ��������close-on-exec��־
        <td>long</td>
        <td>�´������ļ�������ֵ</td>
    </tr>
    <tr>
        <td rowspan="2">��ȡ�������ļ��������ı�־</td>
        <td>F_GETFD</td>
        <td>��ȡfd�ı�־������close_on_exec��־</td>
        <td>��</td>
        <td>fd�ı�־</td>
    </tr>
    <tr>
        <td>F_SETFD</td>
        <td>����fd�ı�־</td>
        <td>long</td>
        <td>0</td>
    </tr>
    <tr>
        <td rowspan="2">��ȡ�������ļ�������״̬</td>
        <td>F_GETFL</td>
        <td>��ȡfd��״̬��־</td>
        <td>void</td>
        <td>fd��״̬��־</td>
    </tr>
    <tr>
        <td>F_SETFL</td>
        <td>����fd��״̬��־</td>
        <td>long</td>
        <td>0</td>
    </tr>
    <tr>
        <td rowspan="4">�����ź�</td>
        <td>F_GETOWN</td>
        <td>���SIGIO��SIGURG�źŵ��������̵�PID����������ID</td>
        <td>��</td>
        <td>�źŵ��������̵�PID����������ID</td>
    </tr>
    <tr>
        <td>F_SETOWN</td>
        <td>�趨SIGIO��SIGURG�źŵ���������PID����������ID</td>
        <td>long</td>
        <td>0</td>
    </tr>
    <tr>
        <td>F_GETSIG</td>
        <td>��ȡ��Ӧ�ó���֪ͨfd�ɶ����дʱ�����ĸ��ź�֪ͨ���¼���</td>
        <td>��</td>
        <td>�ź�ֵ��0��ʾSIGIO</td>
    </tr>
    <tr>
        <td>F_SETSIG</td>
        <td>��fd�ɶ����дʱ��ϵͳӦ�ô����ĸ��ź���֪ͨӦ�ó���</td>
        <td>long</td>
        <td>0</td>
    </tr>
    <tr>
        <td rowspan="2">�����ܵ�����</td>
        <td>F_SETPIPE_SZ</td>
        <td>������fdָ���Ĺܵ���������/proc/sys/fs/pipe-size-max�ں˲����ƶ���fcntl�����õĹܵ���������</td>
        <td>long</td>
        <td>0</td>
    </tr>
    <tr>
        <td>F_GETPIPE_SZ</td>
        <td>��ȡ��fdָ���Ĺܵ�������</td>
        <td>��</td>
        <td>�ܵ�����</td>
    </tr>
</table>
</div>

fcntl������������һ���ļ�����������Ϊ�����������£�
```c++
int setnonblocking(int fd)
{
    int old_option=fcntl(fd,F_GETFL);//��ȡ�ļ��������ɵ�״̬��־
    int new_option=old_option|O_NONBLOCK;//���÷�������־
    fcntl(fd,F_SETFL,new_option);
    return old_option;//�����ļ��������ɵ�״̬��־���Ա��պ�ָ�
}
```

## ������ Linux����������淶
����������淶��
* Linux����������һ���Ժ�̨������ʽ���С���̨�����ֳ��ػ�����(daemon)����û�п����նˣ����Ҳ������������û����룬�ػ����̵ĸ�����ͨ����init����(PIDΪ1�Ľ���)��
* Linux����������ͨ����һ����־ϵͳ���������������־���ļ����еĸ߼����������������־��ר�ŵ�UDP���������󲿷ֺ�̨���̶���`/var/log`Ŀ¼��ӵ���Լ�����־��¼��
* Linux����������һ����ĳ��ר�ŵķ�root������С�����mysqld��httpd��syslogd�Ⱥ�̨���̣��ֱ�ӵ���Լ��������˻�mysql��apache��syslog��
* Linux����������ͨ���ǿ����õġ�����������ͨ���ܴ���ܶ�������ѡ����һ�����е�ѡ��̫�࣬������������ļ�������
* Linux����������ͨ������������ʱ������һ��PID�ļ�������`/var/run`Ŀ¼�У����Լ�¼�ú�̨���̵�PID/
* Linux����������ͨ����Ҫ����ϵͳ��Դ�����ƣ���Ԥ�������ܳ��ܶ�󸺺ɡ�
### 7.1 ��־
#### 7.1.1 Linuxϵͳ��־
`rsyslogd`�ػ����̼��ܽ����û������������־��Ҳ�ܽ����ں���־��

`rsyslogd`�ػ������ڽ��յ��û����̻��ں��������־�󣬻�����������ĳЩ�ض�����־�ļ���Ĭ���£�������Ϣ�ᱣ����`/var/log/debug`�ļ�����ͨ��Ϣ������`/var/log/messages`�ļ����ں���Ϣ������`/var/log/kern.log`�ļ���

#### 7.1.2 syslog����
```shell
sudo service rsyslog restart // �����ػ�����
```
Ӧ�ó���ʹ��`syslog����`��`rsyslogd�ػ�����ͨ��`
�����������£�
```c
#include <syslog.h>
// priority��������ν����ʩֵ(��¼��־��Ϣ��Դ, Ĭ��ΪLOG_USER)����־����İ�λ��
// - 0 LOG_EMERG  /* ϵͳ������*/
// - 1 LOG_ALERT   /* ������Ҫ������ȡ�ж�*/
// - 2 LOG_CRIT /* �ǳ����ص����*/
// - 3 LOG_ERR  /* ����*/
// - 4 LOG_WARNING /* ����*/
// - 5 LOG_NOTICE /* ֪ͨ*/
// - 6 LOG_INFO /* ��Ϣ*/
//  -7 LOG_DEBUG /* ����*/
void syslog(int priority, const char* message, .....);

// identͨ���趨Ϊ�������֣��ᱻ�������־��Ϣ���ں�ʱ��֮��
// logopt �Ժ��� syslog���õ���Ϊ��������
// -  0x01 LOG_PID  /* ����־��Ϣ�а�������PID*/
// -  0x02 LOG_CONS /* �����Ϣ���ܼ�¼����־�ļ�, ���ӡ���ն�*/
// -  0x04 LOG_ODELAY /* �ӳٴ���־����ֱ����һ�ε���syslog*/
// -  0x08 LOG_NDELAY /* ���ӳٴ���־����*/
// facility���������޸�syslog�����е�Ĭ����ʩֵ
void openlog(const char* ident, int logopt, int facility);

// maskpri һ����λ 0000-0000
// ��������һ��0��Ϊ1 ��ʾ ��¼0�������־
// ������������0����Ϊ1 ��ʾ��¼0��1�������־
// ����ͨ��LOG_MASK() ���趨 ����LOG_MASK(LOG_CRIT) ��ʾ������������0��Ϊ1, ��ʾֻ��¼LOG_CRIT
// ���ֱ������setlogmask(3); 3�Ķ����������������Ϊ1 ���¼ 0��1�������־
int setlogmask(int maskpri);

// �ر���־����
void closelog();
```

### 7.2 �û���Ϣ
#### 7.2.1 UID��EUID��GID��EGID
UID - ��ʵ�û�ID
EUID - ��Ч�û�ID - ������Դ����
GID - ��ʵ��ID
EGID - ��Ч��ID
```c
#include <sys/types.h>
#include <unistd.h>

uid_t getuid();
uid_t geteuid();
gid_t getgid();
gid_t getegid();
int setuid(uid_t uid);
int seteuid(uid_t euid);
int setgid(gid_t gid);
int setegid(gid_t gid);
```

һ������ӵ�������û�ID��UID��EUID��EUID���ڵ�Ŀ���Ƿ�������Դ���ʣ���ʹ�����г�����û�ӵ�иó������Ч�û�?Ȩ�ޡ�

**`root`�û�uid��gid��Ϊ0**

#### �л��û�
```c++
staitic bool switch_to_user(uid_t user_id, gid_t gp_id)
{
    //ȷ����ǰ�û�����root
    if((0==user_id)&&(0==gp_id)) return false;
    //ȷ����ǰ�û��ǺϷ��û���root��Ŀ���û�
    gid_t gid=getgid();
    uid_t uid=getuid();
    if(((0!=gid)||(0!=uid))&&((gid!=gp_id)&&(uid!=user_id)))
        return false;
    //�������root��������Ŀ���û�
    if(0!=uid)
    {
        return true;
    }
    //�л���Ŀ���û�
    if((setgid(gp_id)<0)||(setuid(user_id)<0))
        return false;
    return true;
}
```

### 7.3 ���̼��ϵ
#### 7.3.1 ������
Linux��ÿ�����̶�������һ�������飬������ǳ���PID��Ϣ�⣬���н�����ID(PGID)��

ÿ�������鶼��һ��������̣���PGID��PID��ͬ�������齫һֱ���ڣ�ֱ���������н��̶��˳������߼��뵽���������顣

һ������ֻ�������Լ������ӽ��̵�PGID�����ҵ��ӽ��̵���execϵ�к���������Ҳ�������ڸ������ж�������PGID��

#### 7.3.2 �Ự
һЩ�й����Ľ����齫�γ�һ���Ự(session)�����溯�����ڴ���һ���Ự��
```c++
#include<unistd.h>
pid_t setsid(void);

pid_t getsid(pid_t pid);
```
�ú��������ɽ������������̵��ã����ڷ�������̣����øú����������Դ����»Ự�������ԣ�
* ���ý��̳�Ϊ�Ự�����죬��ʱ�ý������»Ự��Ψһ��Ա
* �½�һ�������飬��PGID�ǵ��ý��̵�PID�����ý��̳�Ϊ���������
* ���ý��̼�˦���նˡ�

### 7.4 ϵͳ��Դ����
```c++
#include<sys/resource.h>
int getrlimit(int resource,struct rlimit *rlim);
int setrlimit(int resource,const struct rlimit *rlim);

struct rlimit
{
    rlim_t rlim_cur;
    rlim_t rlim_max;
};
```
### 7.5�ı乤��Ŀ¼�͸�Ŀ¼
��ȡ���̵�ǰ����Ŀ¼�͸ı���̹���Ŀ¼��
```c++
#include<unistd.h>
char* getcwd(char* buf,size_t size);
int chdir(const char* path);
int rootdir(const char* path);//�л����̸�Ŀ¼
//bufָ���ڴ����ڴ洢���̵�ǰ����Ŀ¼�ľ���·���������С��size����
//pathָ��Ҫ�л�����Ŀ��Ŀ¼
```
### 7.6 �����������̨��
�ý������ػ����̵ķ�ʽ����
```c++
#include<unistd.h>
int daemon(int nochdir, int noclose);
//nochdir��ָ���Ƿ�ı乤��Ŀ¼��0��ʾ��Ϊ��Ŀ¼"/"
//noclose��0��ʾ��׼���롢��׼����ͱ�׼���������������/dev/null�ļ�
//�ɹ�����0��ʧ�ܷ���-1������errno
```

## �ڰ��� �����ܷ�����������
���½���ȫ����ģ����շ����������һ��ԭ��������������Ϊ����������Ҫģ�飺
* I/O����Ԫ
* �߼���Ԫ
* �洢��Ԫ
### 8.1 ������ģ��
#### 8.1.1 C/Sģ��
C/S(�ͻ���/������)ģ�ͣ����пͻ��˶�ͨ�����ʷ���������ȡ��Ҫ����Դ���ʺ���Դ��Լ��еĳ��ϡ�
�ŵ㣺ʵ�ּ�
ȱ�㣺��������ͨ�ŵ����ģ����ʹ���ᵼ����Ӧ��æ

![TCP�������Ϳͻ��˵Ĺ�������](picture/TCP��������.png)
��ģ���߼���
* ���������������ȴ���һ��(����)����socket��������bind��������󶨵�����������Ȥ�Ķ˿��ϣ�Ȼ�����listen�����ȴ��ͻ����ӡ��������ȶ�����֮�󣬿ͻ��˾Ϳ��Ե���connect������������������ӡ�

* ���ڿͻ��������������������첽�¼�����������Ҫĳ��I/Oģ����������һ�¼���

#### 8.1.2 P2Pģ��
P2P(Peer to Peer����Ե�)ģ���������Է�����Ϊ���ĵĸ�֣��������������������»ع�Եȵĵ�λ��

�ŵ㣺��Դ��֡����ɹ���
ȱ�㣺�û�֮�䴫���������࣬���縺�ؼ��أ�����֮����ѻ��෢��

### 8.2 ��������̿��
![�������������](picture/�������������.png)
����������ģ�鹦������
|ģ��|��������������|��������Ⱥ|
|:--:|:--:|:--:|
|I/O����Ԫ|����ͻ����ӣ���д��������|��Ϊ�����������ʵ�ָ��ؾ���|
|�߼���Ԫ|ҵ����̻��߳�|�߼�������|
|����洢��Ԫ|�������ݿ⡢�ļ��򻺴�|���ݿ������|
|�������|����Ԫ֮���ͨ�ŷ�ʽ|��������֮�������TCP����|

I/O����Ԫ�Ƿ���������ͻ����ӵ�ģ�顣��ͨ��Ҫ������¹������ȴ��������µĿͻ����ӣ����տͻ����ݣ�����������Ӧ���ݷ��ظ��ͻ��ˡ����ڷ�������Ȩ��˵��I/O����Ԫ��һ��ר�ŵĽ������������ʵ�ָ��ؾ��⣬�������߼���������ѡȡ������С��һ̨��Ϊ�¿ͻ�����

һ���߼���Ԫͨ����һ�����̻��̡߳�������������ͻ����ݣ�Ȼ�󽫽�����ݸ�I/O����Ԫ����ֱ�ӷ��͸��ͻ��ˣ�����ʹ�����ַ�ʽȡ�����¼�����ģʽ�����Է�������Ⱥ���ԣ�һ���߼���Ԫ�������һ̨�߼���������������ͨ��ӵ�ж���߼���Ԫ��ʵ�ֶԶ���ͻ�����Ĳ��д���

����洢��Ԫ���������ݿ⡢������ļ���������һ̨�����ķ��������������Ǳ���ģ�����ssh��telnet�ȵ�¼����Ͳ���Ҫ�����Ԫ��

��������Ǹ���Ԫ֮���ͨ�ŷ�ʽ�ĳ���I/O����Ԫ���յ��ͻ�����ʱ����Ҫ��ĳ�ַ�ʽ֪ͨһ���߼���Ԫ�����������ͬ��������߼���Ԫͬʱ����һ���洢Ԫʱ��Ҳ��Ҫ����ĳ�ֻ�����Э������̬�������������ͨ����ʵ��Ϊ�ص�һ���֡����ڷ�������Ⱥ���ԣ���������Ǹ�̨������֮��Ԥ�Ƚ����ġ�̬�ġ����õ�TCP���ӡ�����TCP��������߷�����֮�佻�����ݵ�Ч�ʣ���Ϊ�������˶�̬����TCP���ӵ��µĶ����ϵͳ������

### 8.3 I/Oģ��
socket�ڴ���ʱĬ���������ģ�����ͨ��socketϵͳ���õĵڶ�����������`SOCK_NONBLOCK`��־������ͨ��fcntlϵͳ���õ�`F_SETFL`�����������Ϊ���������������ļ�������Ϊ����I/O�����������ļ�������Ϊ������I/O��

����I/Oִ�е�ϵͳ���ÿ�����Ϊ�޷�������ɶ�������ϵͳ����ֱ���ȴ����¼�����Ϊֹ��

������I/Oִ�е�ϵͳ�����������������أ������¼��Ƿ��Ѿ�����������¼�û��������������Щϵͳ���þͷ���-1���ͳ�������һ����

I/O��������õ�I/O���ƻ��ƣ���ָ���ǣ�Ӧ�ó���ͨ��I/O���ú������ں�ע��һ���¼����ں�ͨ��I/O���ú��������о������¼�֪ͨ��Ӧ�ó���

Linux���õ�I/O���ú�����select��poll��epoll_wait��I/O���ú��������������ģ���������߳���Ч�ʵ�ԭ��������������ͬʱ�������I/O�¼���������

SIGIO�ź�Ҳ������������I/O�¼������ǿ���Ϊһ��Ŀ���ļ�������ָ���������̣���ô��ָ�����������̽�����SIGIO�źš�

ͬ��I/O��IO�Ķ�д������������I/O�¼�����֮����Ӧ�ó�������ɡ���ģ��Ҫ���û���������ִ��I/O�����������ݴ��ں˻����������û���������������ݴ��û�������д���ں˻�������������I/O��I/O���ú��ź�����I/O����ͬ��I/Oģ�͡�

�첽I/O���û�����ֱ�Ӷ�I/Oִ�ж�д��������Щ���������ں��û���д������λ�ã��Լ�I/O�������֮���ں�֪ͨӦ�ó���ķ�ʽ��

�ܽ᣺ͬ��I/O��Ӧ�ó���֪ͨ����I/O�����¼����첽I/O��Ӧ�ó���ֹͣ��I/O�����ʱ�䡣

|I/Oģ��|��д�����������׶�|
|:--:|:--:|
|����I/O|���������ڶ�д����|
|I/O����|����������I/O����ϵͳ���ã�����ͬʱ�������I/O�¼�����I/O����Ķ�д�����Ƿ�������|
|SIGIO�ź�|�źŴ�����д�����¼����û�����ִ�ж�д����������û�������׶�|
|�첽I/O|�ں�ִ�ж�д������������д����¼�������û�������׶�|

### 8.4 ���ָ�Ч���¼�����ģʽ
#### 8.4.1 Reactorģʽ
ReactorģʽҪ�����߳�(I/O����Ԫ)ֻ��������ļ��������Ƿ����¼��������еĻ����������¼�֪ͨ�����߳�(�߼���Ԫ)��
ʹ��ͬ��I/Oģ��(��epoll_waitΪ��)ʵ�ֵ�Reactorģʽ�������̣�
1. ���߳���epoll�ں��¼���ע��socket�ϵĶ������¼�
2. ���̵߳���epoll_wait�ȴ�socket�������ݿɶ�
3. ��socket�������ݿɶ�ʱ��epoll_wait֪ͨ���̡߳����߳���socket�ɶ��¼�����������С�
4. ˯������������ϵ�ĳ�������̱߳����ѣ�����socket��ȡ���ݣ�������ͻ�����Ȼ����epoll�ں��¼���ע���socket�ϵ�д����ʱ��5. ���̵߳���epoll_wait�ȴ�socket��д
6. ��socket��дʱ��epoll_wait֪ͨ���̡߳����߳̽�socket��д�¼�����������С�
7. ˯������������ϵ�ĳ�������̱߳����ѣ�����socket��д�����������ͻ�����Ľ����
![Reactorģʽ](picture/Reactorģʽ.png)

#### 8.4.2 Proactorģʽ
Proactorģʽ������I/O�����������̺߳��ں������������߳̽�������ҵ���߼���

ʹ���첽I/Oģ��(��aio_read��aio_writeΪ��)ʵ�ֵ�Proactorģʽ�Ĺ�������:
1. ���̵߳���aio_read�������ں�ע��socket�ϵĶ�����¼����������ں��û�����������λ�ã��Լ����������ʱ���֪ͨӦ�ó���
2. ���̼߳������������߼�
3. ��socket�ϵ����ݱ������û����������ں˽���Ӧ�ó�����һ���źţ���֪ͨӦ�ó��������Ѿ����á�
4. Ӧ�ó���Ԥ�ȶ���õ��źŴ�������ѡ��һ�������߳�������ͻ����󡣹����̴߳�����ͻ�����֮�󣬵���aio_write�������ں�ע��socket��д����¼����������ں��û�д������λ�ã��Լ�д�������ʱ���֪ͨӦ�ó���
5. ���̼߳������������߼�
6. ���û������������ݱ�д��socket֮���ں˽���Ӧ�ó�����һ���źţ���֪ͨӦ�ó��������Ѿ��������
7. Ӧ�ó���Ԥ�ȶ���õ��źŴ�������ѡ��һ�������߳�������ͻ����󣬱�������Ƿ�ر�socket��
![Proactorģʽ](picture/Proactorģʽ.png)

����ͼ�У�����socket�Ķ�д�¼���ͨ��aio_read/aio_write���ں�ע��ģ�����ں˽�ͨ���ź�����Ӧ�ó��򱨸�����socket�ϵĶ�д�¼������ԣ����߳��е�epoll_wait���ý�����������socket�ϵ����������¼��������������������socket�ϵĶ�д�¼���

#### 8.4.3 ģ��Proactorģʽ
ԭ�����߳�ִ�����ݶ�д��������д���֮�����߳������߳�֪ͨ��һ"���ʱ��"���ӹ����̵߳ĽǶ����������Ǿ�ֱ�ӻ�����ݶ�д�Ľ����������Ҫ����ֻ�ǶԶ�д�Ľ�������߼�����
ʹ��ͬ��I/Oģ��(��epoll_waitΪ��)ģ���Proactorģʽ�Ĺ����������£�
1. ���߳���epoll�ں��¼���ע��socket�ϵĶ������¼�
2. ���̵߳���epoll_wait�ȴ�socket�������ݿɶ�
3. ��socket�������ݿɶ�ʱ��epoll_wait֪ͨ���̡߳����̴߳�socketѭ����ȡ���ݣ�ֱ�������ݿɶ���Ȼ�󽫶�ȡ�������ݷ�װ��һ��������󲢲���������С�
4. ˯������������ϵ�ĳ�������̱߳����ѣ������������󲢴���ͻ�����Ȼ����epoll�ں��¼���ע���socket�ϵ�д�����¼�
5. ���̵߳���epoll_wait�ȴ�socket�������ݿ�д
6. ��socket��д��epoll_wait֪ͨ���̣߳����߳���socket��д�����������ͻ�����Ľ����
![ģ��Proactorģʽ](picture/ͬ��IOģ��Proactorģʽ.png)

### 8.5 ���ָ�Ч�Ĳ���ģʽ
�����Ϊ�����ܼ���(CPUʹ�úܶ�, IO��Դʹ�ú���)��IO�ܼ���(������).
ǰ��ʹ�ò�����̷����ή��Ч��, �����������Ч��
��������ж���̺Ͷ��߳����ַ�ʽ

����ģʽ - IO��Ԫ�Ͷ���߼���Ԫ֮��Э���������ķ���.
��������Ҫ�����ֲ���ģʽ����ͬ��/���첽(half-sync/half-async)ģʽ���쵼��/׷����(Leader/Followers)ģʽ��
#### 8.5.1 ��ͬ��/���첽ģʽ
��I/Oģ���У�ͬ�����첽���ֵ�ʱ�ں���Ӧ�ó���֪ͨ���Ǻ���I/O�¼�(�Ǿ����¼���������¼�)���Լ�����˭�����I/O��д(��Ӧ�ó������ں�)��

�ڲ���ģ���У�ͬ����ָ������ȫ���մ������е�˳��ִ�У��첽��ָ�����ִ����Ҫ��ϵͳ�¼���������������ϵͳ�¼������նˡ��źŵȡ�
![�����е�ͬ�����첽](picture/����ģʽ�е�ͬ�����첽.png)

�첽�߳�ִ��Ч�ʸߣ�ʵʱ��ǿ����Ƕ��ʽ������õ�ģ�ͣ�����д���첽��ʽִ�еĳ�����Ը��ӣ����ڵ��Ժ���չ�����Ҳ��ʺϴ����Ĳ�����

ͬ���߳��߼��򵥣���Ч����Խϵͣ�ʵʱ�Խϲ

������(��Ҫ�Ϻõ�ʵʱ������ͬʱ�������ͻ�����) - һ��ʹ��ͬ���̺߳��첽�߳���ʵ��,��Ϊ��ͬ��/���첽ģʽ

ͬ���߳� - ����ͻ��߼�, ������������еĶ���

�첽�߳� - ����IO�¼�, ���յ��ͻ���������װ��������󲢲����������

��ͬ��/���첽ģʽ�ı��壺��ͬ��/�뷴Ӧ��(half-sync/half-reactive)ģʽ
![��ͬ��/�뷴Ӧ��](picture/��ͬ��_�뷴Ӧ��ģʽ.png)
��ͬ��/�뷴Ӧ��ģʽ�У��첽�߳�ֻ��һ���������߳����䵱���������������socket�ϵ��¼���

#### 8.5.2 �쵼��/׷����ģʽ
�쵼�ߣ�׷����ģʽ�Ƕ�������߳���������¼�Դ���ϣ������������ַ��������¼���һ��ģʽ��������ʱ��㣬���򶼽���һ���쵼���̣߳����������I/O�¼����������߳�����׷���ߣ������������̳߳��еȴ���Ϊ�µ��쵼�ߡ���ǰ���쵼�������⵽I/O�¼�������Ҫ���̳߳�����ѡ���µ��쵼���̣߳�Ȼ����I/O�¼�����ʱ�����쵼�ߵȴ��µ�I/O�¼�����ԭ�����쵼������I/O�¼�������ʵ���˲�����

### 8.6 ����״̬��
```c
// ״̬����������״̬��
STATE_MACHINE(Package _pack) {
	
	PackageType _type = _pack.GetType();
	switch(_type) {
		case type_A:
			xxxx;
			break;
		case type_B:
			xxxx;
			break;
	}
}

// ��״̬ת�Ƶ�����״̬��
STATE_MACHINE() {
	State cur_State = type_A;
	while(cur_State != type_C) {
	
		Package _pack = getNewPackage();
		switch(cur_State) {
			
			case type_A:
				process_package_state_A(_pack);
				cur_State = type_B;
				break;
			case type_B:
				xxxx;
				cur_State = type_C;
				break;
		}
	}
}
```

### 8.7 ��߷��������ܵ���������
#### 8.7.1 ��
���̳غ��̳߳أ��ÿռ任ʱ��
#### 8.7.2 ���ݸ���
�����ܷ�����Ӧ�ñ��ⲻ��Ҫ�ĸ���
#### 8.7.3 �������л�����
����`��`���������� ��Ӧ�ô���̫��Ĺ�������, ����ʹ��ר�ŵ�ҵ���߼��̡߳�

## �ھ��� I/O����
I/O����ʹ�ó�����ͬʱ��������ļ�������������߳�������ܣ��������������Ҫʹ�øü�����
* �ͻ��˳�����Ҫͬʱ������socket���������connect����
* �ͻ��˳���Ҫͬʱ�����û�������������ӣ��������ҳ���
* TCP������Ҫͬʱ�������socket������socket����ʱI/O����ʹ�����ĳ���
* ������Ҫͬʱ����TCP�����UDP��������������
* ��������Ҫͬʱ��������˿ڣ����ߴ�����ַ�����xinetd������

Linux��ʵ��I/O���õ�ϵͳ������Ҫ��select��poll��epoll��

### 9.1 selectϵͳ����
selectϵͳ���õ���;����һ��ָ��ʱ���ڣ������û�����Ȥ���ļ��������ϵĿɶ�����д���쳣���¼���

#### select API
```c++
#include<sys/select.h>
int select(int nfds, fd_set* readfds, fd_set* writefds, fd_set* exceptfds, struct timeval* timeout);
//nfds��ָ�����������ļ���������������ͨ��������Ϊselect�����������ļ������������ֵ��1����Ϊ�ļ��������Ǵ�0��ʼ�����ġ�
//readfds��writefds��exceptfds�ֱ�ָ��ɶ�����д���쳣���¼���Ӧ���ļ����������ϡ�

//����fd_set�ĺ�
FD_ZERO(fd_set* fdset);
FD_SET(int fd, fd_set* fdset);
FD_CLR(int fd, fd_set* fdset);
FD_ISSET(int fd, fd_set* fdset);
// ���� timeval ��ʱʱ��
struct timeval
{
	long tv_sec; // ��
	long tv_usec; // ΢��
}
```

**socket�ɶ�����**
- socket�ں˽��ջ������е��ֽ������ڻ�������ˮλ���SO_RCVLOWAT����ʱ�����������ض���socket�����Ҷ��������ص��ֽ�������0
- socketͨ�ŵĶԷ��ر�����, ��socket�Ķ���������0
- ����socket�����µ���������
- socket����δ����Ĵ���, ����ʹ��getsockopt����ȡ���������

**socket��д����**
- socket�ں˵ķ��ͻ������Ŀ����ֽ������ڻ�������ˮλ���
- socket��д�������ر�, �Ա��رյ�socketִ��д�������ᴥ��һ��SIGPIPE�ź�
- socketʹ�÷�����connect ���ӳɹ���ʧ�ܺ�

socket�쳣������
* socket���մ�������

#### 9.1.3 �����������
��Դ����9-1

### 9.2 pollϵͳ����
pollϵͳ���ú�select���ƣ���Ҳ����ָ��ʱ������ѯһ���������ļ����������Բ��������Ƿ��о�����
```c++
#include<poll.h>
int poll(struct pollfd* fds, nfds_t nfds,int timeout);
```
fds����һ��pollfd�ṹ���͵����飬ָ���������Ǹ���Ȥ���ļ��������Ϸ����Ŀɶ�����д���쳣���¼���

nfds��ָ���������¼�����fds�Ĵ�С

timeout��ָ��poll�ĳ�ʱֵ����λ�Ǻ��롣��timeout=-1��poll���ý���Զ������ֱ��ĳ���¼���������timeout=0��poll���ý��������ء�

```c++
struct pollfd
{
    int fd;//�ļ�������
    short events;//ע����¼�
    short revents;//ʵ�ʷ������¼������ں����
};
```
poll֧�ֵ��¼��������£�Ĭ�϶��ǿ�����Ϊ������������`POLLERR`��`POLLHUP`��`POLLNVAL`������Ϊ�������⣺
|�¼�|����|
|:--:|:--:|
|POLLIN|����(������ͨ���ݺ���������)�ɶ�|
|POLLRDNORM|��ͨ���ݿɶ�|
|POLLRDBAND|���ȼ������ݿɶ�(Linux��֧��)|
|POLLPRI|�����ȼ����ݿɶ�������TCP��������|
|POLLOUT|����(������ͨ���ݺ���������)��д|
|POLLWRNORM|��ͨ���ݿ�д|
|POLLWRBAND|���ȼ����ݿ�д|
|POLLRDHUP|TCP���ӱ��Է��رգ����߶Է��ر���д���������Ҫʹ������¼������붨��_GNU_SOURCE ��|
|POLLERR|����|
|POLLHUP|���𡣱���ܵ���д�˱��رպ󣬶����������Ͻ��յ�POLLHUP�¼�|
|POLLNVAL|�ļ�������û�д�|

### 9.3 epollϵ��ϵͳ����
epoll��select��poll������
* epollʹ��һ�麯���������
* epoll���û����ĵ��ļ��������ϵ��¼������ں����һ��ʱ�����
* epoll��Ҫʹ��һ��������ļ�����������Ψһ��ʶ�ں��е�����¼���

```c++
#include<sys/epoll>
//�����ļ�������
int epoll_create(int size);
//�����ں��¼���
int epoll_ctl(int epfd,int op,int fd, struct epoll_event *event);

```
fd��Ҫ�������ļ�������
op��ָ����������

�������ͣ�
* EPOLL_CTL_ADD�����¼�����ע��fd�ϵ��¼�
* EPOLL_CTL_MOD���޸�fd�ϵ�ע���¼�
* EPOLL_CTL_DEL��ɾ��fd�ϵ�ע���¼�

#### epoll_wait����
���壺��һ�γ�ʱʱ���ڵȴ�һ���ļ��������ϵ��¼�
```c++
#include<sys/epoll.h>
int epoll_wait(int epfd,struct epoll_event* events,int maxevents,int timeout);
//�ɹ����ؾ������ļ�������������ʧ�ܷ���-1������errno
```
timeout��ָ��epoll�ĳ�ʱֵ����λ�Ǻ��롣��timeout=-1��epoll���ý���Զ������ֱ��ĳ���¼���������timeout=0��epoll���ý��������ء�

maxevents��ָ���������¼��ĸ������������0��

epoll_wait���������⵽�¼����ͽ����о������¼����ں��¼���(��epfd����ָ��)�и��Ƶ����ĵڶ�������eventsָ��������С��������ֻ�������epoll_wait��⵽�ľ����¼������������Ӧ�ó������������ļ���������Ч�ʡ�

poll��epollʹ���ϵĲ��
```c++
//poll
int ret=poll(fds,MAX_EVENT_NUMBER,-1);
//��Ҫ����������ע���ļ����������ҵ����еľ�����
for(int i=0;i<MAX_EVENT_NUMBER;++i)
{
    if(fds[i].events&POLLIN)
    {
        int sockfd=fds[i].fd;
        //����sockfd
    }
}

//epoll
int ret=epoll_wait(epollfd,events,MAX_EVENT_NUMBER;-1);
for(int i=0;i<ret;++i)
{
    int sockfd=events[i].data.fd;
    //ֱ�Ӵ���sockfd
}
```

#### 9.3.3 LT��ETģʽ
[LT��ETģʽ���](https://cloud.tencent.com/developer/article/1636224)

LT(Level Trigger)����ƽ����ģʽ��Ĭ��ģʽ
LTģʽ�µ�epoll�൱��һ��Ч�ʽϸߵ�poll
����ˮƽ����ģʽ��һ���¼�ֻҪ�У��ͻ�һֱ������

ET(Edge Trigger)�����ش���ģʽ, epoll�ĸ�Ч����ģʽ
����epoll�ں��¼�����ע��һ���ļ��������ϵ�EPOLLET�¼���ʱ��, epoll����ETģʽ����������ļ�������

���ڱ�Ե����ģʽ��ֻ��һ���¼����޵��вŻᴥ����һ����Ҫ������ģʽ

#### 9.3.4 EPOLLONESHOT�¼�
���¼����ڽ�����߳�(�����)ͬʱ����һ��socket�ľ��档
����ע����EPOLLONESHOT�¼����ļ�������������ϵͳ��ഥ������ע���һ���ɶ�����д���쳣�¼�����ֻ�ܴ���һ�Ρ�

### 9.4 ����I/O���ú����ıȽ�
![I/O���ú����Ƚ�](picture/����IO���ñȽ�.png)

### 9.6 �����ҳ���
#### �ͻ���
```c++
/*
�ͻ��˳���ʹ��poollͬʱ�����û��������������
��������splice����ͨ���ܵ����û���������ֱ�Ӷ������������ϲ�����
�Ӷ�ʵ�������㿽��������˳����ִ��Ч��
*/
#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<poll.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>
// #include<sys/types.h>
#include<sys/socket.h>
//ʹ����POLLRDHUP����Ҫ����_GUN_SOURCE��
#define _GUN_SOURCE 1
#define BUFSIZE 64

int main(int argc,char **argv)
{
    if(argc<=2)
    {
        printf("usage: %s ip_address port_number\n",basename(argv[0]));
        return 1;
    }
    const char* ip=argv[1];
    int port=atoi(argv[2]);
    sockaddr_in addr;
    bzero(&addr,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=inet_addr(ip);
    addr.sin_port=htons(port);

    int sockfd=socket(PF_INET,SOCK_STREAM,0);
    assert(sockfd>=0);

    if(connect(sockfd,(sockaddr*)&addr,sizeof(addr))==-1)
    {
        printf("connection failed\n");
        close(sockfd);
        return 1;
    }

    pollfd fds[2];
    //ע���ļ�������0(��׼����)���ļ�������sockfd�ϵĿɶ��¼�
    fds[0].fd=0;
    fds[0].events=POLLIN;
    fds[0].revents=0;//ʵ�ʷ������¼������ں˲���

    fds[1].fd=sockfd;
    //POLLRDHUP��д�˹ر������ӣ����Ҫʹ������¼������붨��_GNU_SOURCE ��
    fds[1].events=POLLIN|POLLRDHUP;
    fds[1].revents=0;

    char read_buf[BUFSIZE];
    int pipefd[2];
    int ret=pipe(pipefd);//�����ܵ���0�Ƕ����ܵ���1��д��ܵ�
    assert(ret!=-1);

    while(true)
    {
        //2ָ�����¼�����fds��С��-1��ʾpoll��������ĳ���¼�����
        ret=poll(fds,2,-1);
        if(ret<0)
        {
            printf("poll failure\n");
            break;
        }
        //���sock��ǰ�¼�ΪPOLLIN
        if(fds[1].revents&POLLIN)
        {
            memset(read_buf,'\0',BUFSIZE);
            recv(fds[1].fd,read_buf,BUFSIZE-1,0);
            printf("%s\n",read_buf);
        }
        //sock���Է��رգ���Է��ر���д����
        else if(fds[1].revents&POLLRDHUP)
        {
            printf("server close the connection\n");
            break;
        }

        //��ǰ��׼����������
        if(fds[0].revents&POLLIN)
        {
            //ʹ��splice���û����������ͨ���ܵ�ֱ��д��sockfd��(�㿽��)
            //SPLICE_F_MORE��ʾ�ں˺���������ȡ�������ݣ�SPLICE_F_MOVE������ҳ�ڴ��ƶ�����
            ret=splice(0,NULL,pipefd[1],NULL,32768,SPLICE_F_MORE|SPLICE_F_MOVE);
            ret=splice(pipefd[0],NULL,sockfd,NULL,32768,SPLICE_F_MORE|SPLICE_F_MOVE);
        }
    }
    close(sockfd);
    return 0;
}
```

#### ��������
```c++
/*
����������ʹ��pollͬʱ�������socket������socket�����������ռ任ȡ�¼��Ĳ�����߷���������
*/
#include<assert.h>
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<poll.h>
#include<fcntl.h>
#include<arpa/inet.h>
#include<sys/socket.h>
//ʹ����POLLRDHUP����Ҫ����_GUN_SOURCE��
#define _GNU_SOURCE 1
#define BUFSIZE 64
#define USER_LIMIT 5//����û�����
#define FD_LIMIT 65535//�ļ��������������

//�ͻ����ݣ��ͻ���socket��ַ����д���ͻ��˵����ݵ�λ�á��ӿͻ��˶��������
struct client_data
{
    sockaddr_in address;
    char* write_buf;
    char buf[BUFSIZE];
};

//���÷�����
int setNonBlocking(int fd)
{
    //��ȡfd��״̬��־
    int old_option=fcntl(fd,F_GETFL);
    int new_option=old_option|O_NONBLOCK;
    fcntl(fd,F_SETFL,new_option);
    //���ؾ�״̬��־
    return old_option;
}

int main(int argc,char **argv)
{
    if(argc<=2)
    {
        printf("usage: %s ip_address port_number\n",basename(argv[0]));
        return 1;
    }
    const char *ip=argv[1];
    int port=atoi(argv[2]);

    int ret=0;
    sockaddr_in addr;
    bzero(&addr,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=inet_addr(ip);
    addr.sin_port=htons(port);

    int listenfd=socket(PF_INET,SOCK_STREAM,0);
    assert(listenfd>-1);

    ret=bind(listenfd,(sockaddr*)&addr,sizeof(addr));
    assert(ret!=-1);

    ret=listen(listenfd,5);
    assert(ret!=-1);

    //����users���飬����FD_LIMIT��client_data����
    //����Ԥ�ڣ�ÿ�����ܵ�socket���Ӷ����Ի��һ�������Ķ��󣬲���socket��ֵ����ֱ������socket���Ӷ�Ӧ��client_data����
    //���ַ�ʽ�ǽ�socket�Ϳͻ����ݹ����ļ򵥶���Ч�ķ�ʽ��
    client_data *users=new client_data[FD_LIMIT];
    //��Ȼ�������㹻���client_data���󣬵�Ϊ�����poll���ܣ������б�Ҫ�����û�����
    pollfd fds[USER_LIMIT+1];
    int user_counter=0;
    //��ʼ��
    for(int i=1;i<=USER_LIMIT;i++)
    {
        fds[i].fd=-1;
        fds[i].events=0;
    }
    fds[0].fd=listenfd;
    //�ɶ����쳣
    fds[0].events=POLLIN|POLLERR;
    fds[0].revents=0;

    while(true)
    {
        //user_counter+1��ʾ�������¼�����fds�Ĵ�С
        ret=poll(fds,user_counter+1,-1);
        if(ret<0)
        {
            printf("poll failure\n");
            break;
        }
        for(int i=0;i<user_counter+1;i++)
        {
            if((fds[i].fd==listenfd)&&(fds[i].revents&POLLIN))
            {
                sockaddr_in addr;
                socklen_t addr_sz=sizeof(addr);
                int connfd=accept(listenfd,(sockaddr*)&addr,&addr_sz);
                if(connfd<0)
                {
                    printf("errno is: %d\n",errno);
                    continue;
                }
                //���������࣬��ر��µ�������
                if(user_counter>=USER_LIMIT)
                {
                    const char *info="too many users\n";
                    printf("%s",info);
                    send(connfd,info,strlen(info),0);
                    close(connfd);
                    continue;
                }
                //�����µ����ӣ�ͬʱ�޸�fds��users����
                //users[connfd]��Ӧ���������ļ�������connfd�Ŀͻ�����
                user_counter++;
                users[connfd].address=addr;
                //���÷�����
                setNonBlocking(connfd);
                fds[user_counter].fd=connfd;
                fds[user_counter].events=POLLIN|POLLRDHUP|POLLERR;
                fds[user_counter].revents=0;
                printf("comes a new user, now have %d users\n",user_counter);
            }
            else if(fds[i].revents&POLLERR)
            {
                printf("get an error from %d\n",fds[i].fd);
                char errors[100];
                memset(errors,'\0',100);
                socklen_t length=sizeof(errors);
                if(getsockopt(fds[i].fd,SOL_SOCKET,SO_ERROR,&errors,&length)<0)
                    printf("get socket option failed\n");
                continue;
            }
            else if(fds[i].revents&POLLRDHUP)
            {
                //����ͻ��˹ر����ӣ���ô������Ҳ�رն�Ӧ���ӣ������û�����-1
                //users���齫���һ���û����ļ�������ǰ����ɾ����λ��
                users[fds[i].fd]=users[fds[user_counter].fd];

                close(fds[i].fd);
                //��ɾ��λ�õ��ļ��������滻Ϊ���һλ���ļ�������
                fds[i--]=fds[user_counter--];
                printf("a client left\n");
            }
            else if(fds[i].revents&POLLIN)
            {
                int connfd=fds[i].fd;
                memset(users[connfd].buf,'\0',BUFSIZE);
                ret=recv(connfd,users[connfd].buf,BUFSIZE-1,0);
                printf("get %d bytes of client data %s from %d\n",ret,users[connfd].buf,connfd);
                if(ret<0)
                {
                    //���������������ر�����
                    //��������ض�
                    if(errno!=EAGAIN)
                    {
                        close(connfd);
                        users[fds[i].fd]=users[fds[user_counter].fd];
                        fds[i--]=fds[user_counter--];
                    }
                }
                else if(ret>0)
                {
                    //������յ��ͻ������ݣ���֪ͨ����socket����׼��д����
                    for(int j=1;j<user_counter+1;j++)
                    {
                        if(fds[j].fd==connfd)
                        {
                            continue;
                        }
                        fds[j].events|=~POLLIN;
                        fds[j].events|=POLLOUT;
                        users[fds[j].fd].write_buf=users[connfd].buf;
                    }
                }
            }
            else if(fds[i].revents&POLLOUT)
            {
                int connfd=fds[i].fd;
                if(!users[connfd].write_buf)
                {
                    continue;
                }
                ret=send(connfd,users[connfd].write_buf,strlen(users[connfd].write_buf),0);
                //�ָ������ݵ�״̬
                users[connfd].write_buf=NULL;
                fds[i].events|=~POLLOUT;
                fds[i].events|=POLLIN;
            }
        }
    }
    delete [] users;
    close(listenfd);
    return 0;
}
```

### 9.7 ͬʱ����TCP��UDP����
��bindϵͳ���õĲ���������һ��socketֻ����һ��socket��ַ�󶨣���һ��socketֻ����������һ�����ڡ�I/O�����ܹ��÷�����������Թ���������socket��Ҳ����ͬʱ����ö˿��ϵ�TCP��UDP����

#### �����
```c++
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <pthread.h>

#define MAX_EVENT_NUMBER 1024
#define TCP_BUFFER_SIZE 512
#define UDP_BUFFER_SIZE 1024

int setnonblocking( int fd )
{
    int old_option = fcntl( fd, F_GETFL );
    int new_option = old_option | O_NONBLOCK;
    fcntl( fd, F_SETFL, new_option );
    return old_option;
}

void addfd( int epollfd, int fd )
{
    epoll_event event;
    event.data.fd = fd;
    //���ñ�Ե����ģʽ
    event.events = EPOLLIN | EPOLLET;
    // event.events = EPOLLIN;
    //epollfd�趨Ϊfd��Ȼ������fdΪ������
    epoll_ctl( epollfd, EPOLL_CTL_ADD, fd, &event );
    setnonblocking( fd );
}

int main( int argc, char* argv[] )
{
    if( argc <= 2 )
    {
        printf( "usage: %s ip_address port_number\n", basename( argv[0] ) );
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi( argv[2] );

    int ret = 0;
    struct sockaddr_in address;
    //��TCP socket
    bzero( &address, sizeof( address ) );
    address.sin_family = AF_INET;
    inet_pton( AF_INET, ip, &address.sin_addr );
    address.sin_port = htons( port );

    int listenfd = socket( PF_INET, SOCK_STREAM, 0 );
    assert( listenfd >= 0 );

    ret = bind( listenfd, ( struct sockaddr* )&address, sizeof( address ) );
    assert( ret != -1 );

    ret = listen( listenfd, 5 );
    assert( ret != -1 );
    //��UDP socket
    bzero( &address, sizeof( address ) );
    address.sin_family = AF_INET;
    inet_pton( AF_INET, ip, &address.sin_addr );
    address.sin_port = htons( port );
    int udpfd = socket( PF_INET, SOCK_DGRAM, 0 );
    assert( udpfd >= 0 );

    ret = bind( udpfd, ( struct sockaddr* )&address, sizeof( address ) );
    assert( ret != -1 );

    epoll_event events[ MAX_EVENT_NUMBER ];
    int epollfd = epoll_create( 5 );
    assert( epollfd != -1 );

    //ע��TCP socket��UDP socket�ϵĿɶ��¼�
    addfd( epollfd, listenfd );
    addfd( epollfd, udpfd );

    while(true)
    {
        int number = epoll_wait( epollfd, events, MAX_EVENT_NUMBER, -1 );
        if ( number < 0 )
        {
            printf( "epoll failure\n" );
            break;
        }
    
        for ( int i = 0; i < number; i++ )
        {
            int sockfd = events[i].data.fd;
            if ( sockfd == listenfd )
            {
                struct sockaddr_in client_address;
                socklen_t client_addrlength = sizeof( client_address );
                int connfd = accept( listenfd, ( struct sockaddr* )&client_address, &client_addrlength );
                addfd( epollfd, connfd );
            }
            else if ( sockfd == udpfd )
            {
                char buf[ UDP_BUFFER_SIZE ];
                memset( buf, '\0', UDP_BUFFER_SIZE );
                struct sockaddr_in client_address;
                socklen_t client_addrlength = sizeof( client_address );

                ret = recvfrom( udpfd, buf, UDP_BUFFER_SIZE-1, 0, ( struct sockaddr* )&client_address, &client_addrlength );
                if( ret > 0 )
                {
                    sendto( udpfd, buf, UDP_BUFFER_SIZE-1, 0, ( struct sockaddr* )&client_address, client_addrlength );
                }
            }
            else if ( events[i].events & EPOLLIN )
            {
                char buf[ TCP_BUFFER_SIZE ];
                while( 1 )
                {
                    memset( buf, '\0', TCP_BUFFER_SIZE );
                    ret = recv( sockfd, buf, TCP_BUFFER_SIZE-1, 0 );
                    if( ret < 0 )
                    {
                        if( ( errno == EAGAIN ) || ( errno == EWOULDBLOCK ) )
                        {
                            break;
                        }
                        close( sockfd );
                        break;
                    }
                    else if( ret == 0 )
                    {
                        close( sockfd );
                    }
                    else
                    {
                        send( sockfd, buf, ret, 0 );
                    }
                }
            }
            else
            {
                printf( "something else happened \n" );
            }
        }
    }

    close( listenfd );
    return 0;
}
```

