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