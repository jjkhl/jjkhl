**ʵս�ʼǻ����鼮��C++ʵս�ʼ�_�޽��桷**
# ����������ʽ
* �������������������ռ���snake_case��ʽ��ȫ�ֱ����ӡ�g_��ǰ׺
* �Զ����������շ�ʽ(CamelCase)��񣬳�Ա������snake_case,��Ա�����ӡ�m_��ǰ׺
* ��ͳ���ȫ����д������֮��ʹ���»�������
* ��Ҫ���»�����Ϊ������ǰ׺���ߺ�׺
**ʾ����**
```c++
#define MAX_PATH_LEN 256//����ȫ����д
int g_sys_flag;//ȫ�ֱ���
namespace linux_sys{//�����ռ䣬ȫ��Сд
    void get_rlimit_core();
}
class FilePath final//����������ĸ��д
{
    public:
        void set_path(const string& str);//������ȫСд
    private:
        string m_path;
        int m_level;//��Ա�������ǰ׺
};
```
# Ԥ����׶�
## include
�����ǰ��������ļ������Ա�дһЩ����Ƭ�Σ����`*.inc`�ļ��Ȼ����Ԥ����׶���ѡ��ؼ��ء�
ʾ����
```c++
//calc_values.inc
static unit32_t calc_table[] = {
    ...
};
//ʹ�÷�ʽ
#include "calc_values.inc"
static unit32_t* calc_table1={
    calc_table
};
```
## define
���չ�����滻������Ԥ����׶Σ����漰�������á��������ݡ�ָ��Ѱַ��û���κ������ڵ�Ч����ʧ�����Զ��ڵ���һЩƵ����С����Ƭ����˵���ú��װ��Ч����ʹ��inline�ؼ���Ҫ�á�
���ǣ��궨��û������������Զ��ȫ����Ч�����Զ���һЩ�����򻯴��롢����ʱ���õĺ꣬���������Ҫ��`#undef`ȡ�����塣
**ʾ����**
```c++
//��ʽһ
#define CUBE(a) (a)*(a)*(a)
cout<<CUBE(10)<<endl;
#undef CUBE
//��ʽ��
#ifdef AUTH_PWD
#undef AUTH_PWD
#endif
#define AUTH_PWD "xxx"
```
**�ı��滻ʾ��**
```c++
#include<iostream>
#define BEGIN(x) namespace x {//ʹ��BEGIN(X)�滻��namespace {
#define END(x)  }//ʹ��END(X)
BEGIN(x)
void hello(){
    std::cout<<"hello x"<<std::endl;
}
END(x)
using namespace std;
int main(int argc,char *argv[])
{
    x::hello();
    system("pause");
    return 0;
}
```
## Ԥ�������
|������|����|
|:--:|:--:|
|__cpluscplus|c++���Եİ汾��|
|__FILE__|Դ�ļ�����|
|__LINE__|Դ�ļ��к�|
|__DATE__|Ԥ����ʱ������|
|__has_include|�Ƿ����ĳ���ɰ����ļ�|
|__cpp_modules|�Ƿ�֧��ģ�����|
|__cpp_decltype|�Ƿ�֧��decltype����|
|__cpp_decltyoe_auto|�Ƿ�֧��decltype(auto)����|
|__cpp_lib_make_unique|�Ƿ��ṩ����make_unique()|
## ����׶ε����Խ���
����ʹ�����Է����ŵ���ʽ��ʾ����`[[...]]`
|������|����|
|:--:|:--:|
|noreturn|��ʾ���������������κ�ֵ|
|nodiscard|��ʾ������������Ժ�������ֵ|
|deprecated|����������ʹ��(����־���)|
|maybe_unused|��ʾ���ĳ�δ�����ʱ���ã�������|
|gnu::const|��Ǻ���ʱ�޸����õĳ����������ñ����������Ż�|
|gnu::constructor|��������main()֮ǰִ�У�Ч��������ȫ�ֶ���Ĺ��캯��|
|gnu::destructor|��������main()֮��ִ�У�Ч��������ȫ�ֶ������������|
|gnu::always_inline|Ҫ�������ǿ������������Ч����inline�ؼ���ǿ|
|gnu::hot|���"�ȵ�"������Ҫ��������������Ż�|
