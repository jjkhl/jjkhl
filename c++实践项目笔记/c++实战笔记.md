<h5 align="center">ʵս�ʼǻ����鼮��C++ʵս�ʼ�_�޽��桷</h5>

# ��һ��c++��������
## ����������ʽ
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
# �ڶ���Ԥ����׶�
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
cout<<CUBE(10)<<end;
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
void hello(*-+){
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
|`__FILE__`|Դ�ļ�����|
|`__LINE__`|Դ�ļ��к�|
|`__DATE__`|Ԥ����ʱ������|
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
## ��̬���ԺͶ�̬����
### ��̬����
���壺��������ʱ������
ͷ�ļ���<cassert>
�꣺`assert`
ʾ����assert(p=227)
Ч��������һ�����ʽ�ض�Ϊ�棬����ж�Ϊ�٣�������������Ϣ��Ȼ����ú���abort()��ֹ��������С�
### ��̬����
���壺�������ʱ������
�꣺`static_assert`
ʾ����
```c++
static_assert(sizeof(long)>=8,"must run on x64")
```
Ч��������׶�������ʽ��ֵ��false�ͻᱨ�����±���ʧ�ܡ�
��鷶Χ��ֻ�ܼ�����ʱ�Ĳ��������ͣ��޷��������ʱ�ı�����ָ�롢�ڴ����ݵȡ�

### ģ��Ԫ����
```c++
//c++17ģ��Ԫ������������is_xxx<T>::value
static_assert(is_integral_V<T>);//����T����������
static_assert(is_pointer_V<T>);//����T��ָ������
static_assert(is_default_constructible_V<T>);//����T����Ĭ�Ϲ��캯��
```
# ������C++������������
## ����׼��
### final��ʶ��
```c++
class DemoClass final//��ֹ�κ��˼̳�
{...};

class Interface
{
    virtual void f()=0;
};

class Abstract: public Interface{
    virtual void f() final //�麯������final����ֹ����̳�
    {...}
};

class Implement final: public Abstract//ʵ���࣬final��ֹ�䱻�̳�
{
    ...
};
```

### default/delete����
* ��������������
���캯�����������������ƹ��캯�������Ƹ�ֵ������ת�ƹ��캯����ת�Ƹ�ֵ����
* default
���ڱȽ���Ҫ�¹��캯��������������ʹ��`=default`��ʽ����ȷ�ظ��߱���������Ĭ��ʵ�֡�
```c++
class DemoClass final
{
    public:
        DemoClass()=default;//��ȷ���߱�������ʹ��Ĭ��ʵ��
        ~DemoClass()=default;//��ȷ���߱�������ʹ��Ĭ��ʵ��
}
```
* delete
�����κκ�����ʽ����ȷ��ֹ����ʽ��ʹ��
```c++
class DemoClass final
{
    public:
        DemoClass(const DemoClass&) = delete;//��ֹ���ƹ��캯��
        DemoClass & operator=(const DemoClass&) = delete;//��ֹ���Ƹ�ֵ����
};
//����ʱ���뱨��
DemoClass obj1;
DemoClass obj2=obj1;//���󣬲��ɸ���
```
### explicit����
explicit�ؼ���ֻ���������ڲ��Ĺ��캯�������ϣ��������������ⲿ�ĺ�������(����ʵ��)�ϣ����������ǲ��ܽ�����ʽת����explicit�ؼ��������ڵ��������Ĺ��캯����������캯���ж�����������Ǵӵڶ���������ʼ���������������Ĭ�ϸ�ֵ��Ҳ����Ӧ��explicit�ؼ���
```c++
class DemoClass final
{
    public:
        explicit DemoClass(const string_type& str);//��ʽ���������캯��
        explicit operator bool();//��ʽת��Ϊbool
};
//����ʽ
DemoClass obj = "stint ctor";
bool b=obj;
//��ȷ��ʽ
DemoClass obj = (DemoClass) "sting ctor";
bool b = static_cast<bool>(obj);
```
## [ί�й��캯��](https://cloud.tencent.com/developer/article/1187765#:~:text=%E5%A7%94%E6%89%98%E6%9E%84%E9%80%A0%E5%87%BD%E6%95%B0%EF%BC%88Delegating,Constructor%EF%BC%89%E7%94%B1C%2B%2B11%E5%BC%95%E5%85%A5%EF%BC%8C%E6%98%AF%E5%AF%B9C%2B%2B%E6%9E%84%E9%80%A0%E5%87%BD%E6%95%B0%E7%9A%84%E6%94%B9%E8%BF%9B%EF%BC%8C%E5%85%81%E8%AE%B8%E6%9E%84%E9%80%A0%E5%87%BD%E6%95%B0%E9%80%9A%E8%BF%87%E5%88%9D%E5%A7%8B%E5%8C%96%E5%88%97%E8%A1%A8%E8%B0%83%E7%94%A8%E5%90%8C%E4%B8%80%E4%B8%AA%E7%B1%BB%E7%9A%84%E5%85%B6%E4%BB%96%E6%9E%84%E9%80%A0%E5%87%BD%E6%95%B0%EF%BC%8C%E7%9B%AE%E7%9A%84%E6%98%AF%E7%AE%80%E5%8C%96%E6%9E%84%E9%80%A0%E5%87%BD%E6%95%B0%E7%9A%84%E4%B9%A6%E5%86%99%EF%BC%8C%E6%8F%90%E9%AB%98%E4%BB%A3%E7%A0%81%E7%9A%84%E5%8F%AF%E7%BB%B4%E6%8A%A4%E6%80%A7%EF%BC%8C%E9%81%BF%E5%85%8D%E4%BB%A3%E7%A0%81%E5%86%97%E4%BD%99%E8%86%A8%E8%83%80%E3%80%82)
ί�й��캯����Delegating Constructor����C++11���룬�Ƕ�C++���캯���ĸĽ��������캯��ͨ����ʼ���б����ͬһ������������캯����Ŀ���Ǽ򻯹��캯������д����ߴ���Ŀ�ά���ԣ���������������͡�
```c++
//��ʹ��֮ǰ
class Foo
{
public:
    Foo() :type(4), name('x') {initRest();}
    Foo(int i) : type(i), name('x') {initRest();}
    Foo(char c) :type(4), name(c) {initRest();}

private:
    void initRest() {/* init othre members */}
    int type;
    char name;
    //...
};
//ʹ��ί�й��캯��֯��
class Foo
{
public:
    Foo() {initRest(); }
    Foo(int i) : Foo() {type = i;}
    Foo(char e) : Foo() {name = e;}
private:
    void initRest() { /* init othre members */}
    int type{1};
    char name{'a'};
};
```
## ��Ա������ʼ��
����������������ͬʱ������ֵ��ʵ�ֳ�ʼ����
## ��̬��Ա������ʼ��
const�ľ�̬��Ա������������������ʱ���ʼ����
��const�ľ�̬��Ա������������ʵ���ļ�"*.cpp"���ʼ������Ϊ��Ҫ����Ψһ�Ĵ洢�ռ䡣
�����������Ա�֤����ͷ�ļ����������ٴΣ���̬��Ա����Ҳֻ��Ψһһ��ȫ��ʵ����
**ʾ����**
```c++
class DemoInit final
{
    public:
        static const int x = 0;//��̬��������ֱ�ӳ�ʼ��
        static string prefix = "xx";//�޷�ͨ������
};
string DemoInit::prefix= "xx";//��Ҫ������ʵ�ֳ�ʼ��

//c++17������Ա������ʼ����ʽ�Ĳ�һ������
//��������
class DemoInit final
{
public:
    inline static string prefix = "xx";//c++17�б�������
};
```
## ���ͱ���
```c++
using unit_t = unsigned int;
typedef unsigned int unint_t;
```
## �Զ������Ƶ�(auto��decltype)
### auto
* autoĬ���Ƶ�ֵ����
* autoֻ�����ڳ�ʼ���ĳ���
```c++
auto str = "hello";//�Զ��Ƶ�Ϊconst char [6]����
auto str = "hello"s;//c++14�Ժ����Ƶ���string����
auto x= 10L;//auto�Ƶ���long��x��long
auto& x1=x;//auto�Ƶ���long��x1��long&
auto* x2=&x;//auto�Ƶ���long,x2��long*
const auto& x3=x;//auto�Ƶ���long��x3��const long&
auto x4=&x3;//auto�Ƶ���const long*,x4��const long*
auto&& x5=x;//�����Ƶ����������ͣ�auto�Ƶ���long,x5��long&

auto get_a_set(){
    std::set<int> a={1,2,3};
    return a;
}//c++14֮���Զ��Ƶ���������ֵ
```
### decltype
```c++
int x=0;
decltype(x) x1;//�Ƶ�Ϊint��x1��int
decltype(x)& x2=x;//�Ƶ�Ϊint��x2��int&�����ñ��븳ֵ
decltype(x)* x3;//�Ƶ�Ϊint��x3��int*
decltype(&x) x4;//�Ƶ�Ϊint*��x4��int*
decltype(&x)* x5;//�Ƶ�Ϊint*��x5��int**
```
### �ۺ�ʹ��
```c++
int x=0;
decltype(auto) x1=(x);//�Ƶ�Ϊint&
decltype(auto) x2=&x;//�Ƶ�Ϊint*
decltype(auto) x3=x1��//�Ƶ�Ϊint&��x3��x1�Ƶ�һ��
```
## ���������
### const��volatile
* c++17����`std::as_const()`��������`const_cast`���������ѱ���ת��Ϊ��������
* `const &`���������κ����ͣ�������������ڲ�����������͡�
* const���������γ�Ա��������ʾ�ú���ֻ����const��Ա���������޸Ķ����״̬��const����ֻ�ܵ���const��Ա������
* volatile��ʾ���������ԡ����Բ�����ķ�ʽ���޸ģ���ֹ�������Ż�����Ӱ�����ܣ��������á�
### volatile��mutable
volatile���������κα���
mutableֻ�������ඨ������ĳ�Ա��������ʾ������ʹ��const������Ҳ�ǿ����޸ĵ�
```c++
class DemoClass final
{
private:
    using mutex_type int;
    mutable mutex_type m_mutex;//���Ϊmutable��Ա����
public:
    void save_data const
    {
        m_mutex++;//ֻ�����޸ı��Ϊmutable�ĳ�Ա����
        m_value++;//�޸����������ᵼ�±������
    }
};
```
### constexpr�ؼ���
const�ܶ�������ʱ�ĳ�����constexpr��ʵ�ֱ����ڵĳ�����
## [�쳣](https://www.runoob.com/cplusplus/cpp-exceptions-handling.html)
### ΪʲôҪ���쳣
c++֮ǰ�������쳣�Ļ����ֶ��Ǵ����룺����ִ�к����鷵��ֵ��ȫ�ֵ�errno(���Է��ش������Լ�����)�����Ƿ����������������ִ������һ�δ������������
�����������������У�������ҵ���߼����������������һ��˼άҪ������������ص�������������ת�����Ա����ԡ�
�쳣������Դ������ȱ�ݶ���Ƶģ�
* �쳣�Ĵ���������ȫ������throw�׳��쳣��Ϳ��Բ��ùܣ���������붼������ר�ŵ�catch��������ͳ��׷�����ҵ���߼��ʹ������߼�����������������
* �쳣���Բ��ܱ����ԣ����봦����������������ⲻдcatchģ��ȥ�����쳣����ô����һֱ���ϲ��ң�ֱ���ܹ��ҵ�һ���ܹ������catch�顣���ʵ��û�У�����ͻ�����ֹͣ���У����׵���ʾ���Ƿ����˴���
* �쳣�������ڴ������޷�ʹ�õس��ϡ������еĺ���û�з���ֵ�����߷���ֵ�޷���ʾ���󣬶�ȫ�ֵ�errno��̫���ţ���c++������ϣ�����Ҳ����ʹ���쳣���������

### �쳣���÷�
һ���÷���try�ѿ��ܷ����쳣�Ĵ��롰������������дcatch��ȥ�����쳣������
```mermaid
graph LR
  range_error-->runtime_error
  overflow_error-->runtime_error
  invalid_argument-->logic_error
  length_error-->logic_error

  bad_alloc-->exception
  runtime_error-->exception
  logic_error-->exception
  cad_cast-->exception
```
��ļ̳���Ȳ�Ҫ����3�㣬�������ǿ��Դ�runtime_error�������Լ����쳣��
```c++
class my_exception:public std::runtime_error
{
public:
    using this_type = my_exception;//���Լ����쳣���������
    using super_type = std::runtime_error;//������Ҳ�������
    my_exception(const char* msg) : super_type(msg) {}
    my_exception() = default;
    ~my_exception() = default;
private:
    int code=0;
}
```
���׳��쳣��ʱ����ò�Ҫֱ����throw�ؼ��֣�����Ҫ�����װΪһ�������������Ҫֱ����new/delete�ؼ��ֵĵ������ơ���ͨ������һ���м������ø��ߵĿɶ��ԡ���ȫ�Ժ�����ԡ�
```c++
[[noreturn]]                      // ���Ա�ǩ
void raise(const char* msg)      // ������װthrow��û�з���ֵ
{
    throw my_exception(msg);     // �׳��쳣��Ҳ�����и�����߼�
}
try
{
    raise("error occured");     // ������װthrow���׳��쳣
}
catch(const exception& e)      // const &�����쳣�������û���
{
    cout << e.what() << endl;  // what()��exception���麯��
}
void func_noexcept() noexcept            // �����������׳��쳣
{
    cout << "noexcept" << endl;
}
```
### ʹ���쳣���б�׼��
* ���������ԵĴ���
* ��������²Żᷢ���Ĵ���
* ����Ӱ���������̣����ѻָ�������״̬�Ĵ���
* �����޷�������Ҫ����͸������ջ�����ݵ��ϲ���ܱ�����Ĵ���
���繹�캯��������ڲ���ʼ��ʧ�ܣ��޷��������캯������ô������߼�Ҳ�ͽ��в���ȥ��������ʱ�������쳣������
�����д�ļ���ͨ���ļ�ϵͳ���ٳ������ʹ�ô������������ļ������ڡ�Ȩ�޴���Ⱦ��Ե�̫���£���ʱҲӦ��ʹ���쳣��
�෴�����Ӿ���Socketͨ�š���Ϊ������·�Ĳ��ȶ�����̫�࣬�շ�����ʧ�ܺܶࡣ��Ȼ����ĺ�������أ����ǳ���Ƶ�ʺܸߣ�ʹ���쳣������ߴ���ɱ���Ϊ�����ܿ��ǣ����Ǽ������벢���ԱȽϺá�
### ��֤���׳��쳣
`noexcept`��ר�����κ��������߱�����������������׳��쳣���������ܹ��Ժ��������Ż������ø���ջչ���Ķ�����룬�����쳣����ĳɱ���
����noexcept���εĺ���Ҳ���׳��쳣��������˼�ǣ����Ҷ����ŵ���׳��쳣����Ҳ���봦���쳣�����������쳣�����������ҡ������øɴ�㣬ֱ�ӱ���(crash/core dump)��
ʵ����
```c++
void func_noexcept() noexcept //�����������׳��쳣
{
    cout<<"noexcept"<<endl;
}
```
һ����Ϊ����Ҫ�Ĺ��캯��(��ͨ���캯�������ƹ��캯����ת�ƹ��캯��)����������Ӧ�þ�������Ϊ`noexcept`���Ż����ܣ���������������뱣֤�������׳��쳣��

## ����ʽ���
### lambda���ʽ
```c++
//һ��ʹ�÷�ʽ
auto func=[](int x){ return x;}
//������ʽ
cout<<*find_if(begin(v),end(v),[](int x){return x>=5;})<<endl;
//��ʾ��ʽ
auto func=[](long x) ->int//lambda���ʽ��ʾָ������ֵ����
{
    return static_cast<int>(x);
}
```
### lambda��������`[]`
* [=]����ֵ���������ⲿ���������ʽ�ڲ���ֵ�ĸ��ƣ������޸�
* [&]�������ò��������ⲿ�������ڲ������õķ�ʽʹ�ã������޸�
* []��Ҳ������ȷд���ⲿ��������ָ����ֵ��������ò���
**ʵ����**
```c++
int x=33;
auto f1 = [=]()
{
    //x+=10;    //����x�޷��޸�
};
auto f2 = [&]()
{
    x+=10;
};
auto f3 = [=, &x]() //��ʾx�������ò���������������ֵ����
{
    x+=20;
};
//��ֵ�������������mutable
auto f4 = [=] () mutable //mutable�����޸Ĳ�������ĸ���
{
    x+=10;
};
```
## �������ֿռ�
�������ֿռ��Ч�����������ֿռ��࣬����ı����������ȳ�Աͬ���ܹ����ⲿֱ��ʹ�ã���Ҳ���ų�����ֿռ��޶������Ը���
```c++
inline namespace tmp{
    auto x=0L;
    auto str="hello";
}
cout<<x<<endl;//����ֱ��ʹ���ڲ���Ա������Ҫ���ֿռ�����
cout<<tmp::str<<endl;//Ҳ���Լ����ֿռ��޶�
```
### [ö��](https://www.runoob.com/w3cnote/cpp-enums-intro-and-strongly-typed.html)
ʾ����
```c++
enum class Company
{
    Apple,Google,Facebook;
};
Company x=1;//���󣬲��ܴ�����ֱ��ת��
auto v=Company::Apple;//������������޶�������ʹ���Զ������Ƶ�

int i=v;//���󣬲���ֱ��ת��Ϊ����
auto i=static_cast<int>(v);//������ʽǿ��ת��
```
c++20����ʹ��`using`�ؼ�����ʹ��ö����
```c++
using enum Company;//��ö�����������
auto v=Apple;//������Ҫ�����޶�
```
# ������c++��׼��
## ����ָ��
����ָ�뱳��ĺ��ĸ����Ƕ�̬�����ڴ������Ȩ������ָ�뱻��Ϊ����ӵ�л��������ָ��Ķ��󡣵���Ҫ�õ���ָ��ӵ�ж�̬����Ķ���ʱ������ʹ�ö�ռָ�롣���������Ȩ���Դ�һ����ռָ��ת�Ƶ���һ��ָ�룬��ת�Ʒ�ʽΪ������ʼ��ֻ����һ��ָ����Ϊ�������ߡ�����ռָ���뿪���������Ҫӵ�в�ͬ�Ķ���ʱ�������Զ��ͷ��Լ�������Ķ���
* [assert()����](https://blog.csdn.net/cwdben/article/details/116053192)�ж�ָ�������Ƿ�Ϊ�գ������޷�ͨ����
### ר��ָ��(unique_ptr)
ר��ָ������򵥡�������ʹ�õ�����ָ��֮һ����������ʱ�������ģ�����ָ�����ͣ����磺
```c++
//��ʼ����ʽһ
unique_ptr<int> p1(new int(10));
//��ʽ��Ҳ�����ȶ���һ��δ��ʼ����ָ�룬Ȼ���ٸ�ֵ
unique_ptr<int> p2;
p2=unqiue_ptr<int> (new int);
*p2=10;
//��ʽ��
unique_ptr<int> p1(new int);
*p1=10;
//c++14���й�������make_unique�ڴ�������ָ��ʱǿ�Ƴ�ʼ��
auto p3=make_unique<int>(42);
//make_unique����ģ��
template<class T,class... Args>//�ɱ����ģ��
std::unique_ptr<T>//���ص�����ָ��
my_make_unique(Arg&&... args)//�ɱ����ģ�����ڲ���
{
    return std::unique_ptr<T>(
        new T(std::forward<Args>(args)...);//"����ת��"
    )
}
```
* unique_ptr����ȨΨһ���κ�ʱ��ֻ���С�һ���ˡ�ӵ�С�����ʹ��`std::move()`��ʽ��������Ȩת�ƣ���ʱԭ����unique_ptr����˿�ָ�롣
* ���������ʱ��`unique_ptr`��Ϊ��Ա����ô�౾��Ҳ�ǲ��ɸ��Ƶġ�Ҳ����˵��unique_ptr�Ὣ����Ψһ����Ȩ�����Դ��ݸ����ĳ����ߡ�
<h5 align="center">unique_ptr��Ա����</h5>

|��Ա����|����|
|:--:|:--|
|move|ת������Ȩ|
|reset|�����ɸ�����ָ�������κο��ܴ��ڵĶ��󡣸�����ָ�뱻��Ϊ��|
|reset(T* ptr)|�����ɸ�����ָ�뵱ǰ������κο��ܴ��ڵĶ��󡣸�����ָ�������������ָ�� ptr ָ��Ķ���|
|get()|���ظ�����ָ����������ָ��ָ��Ķ������ĳ��ָ����Ҫ���ݸ����������� �ú�������֪������β�������ָ�룬�� get() �����ǳ�����|
|release|����������ָ����Ŀ���Ȩ�������ر����ָ�룬��ָ����Ϊ�գ������ͷ��ڴ�|
* release�᷵��ֱ�ߵ�ָ�룬�������ͷ��ڴ棻reset���ͷ��ڴ�
```c++
// ������Ȩ��p1ת�Ƹ�p2
unique_ptr<string> p1(new string("abc"));
unique_ptr<string> p2(p1.release());   // p1.release()�Ὣp1�ÿգ���������ָ���ָ��,��ʱ*p2="abc";

unique_ptr<string> p3(new string("dfseg"));
// ������Ȩ��p3ת�Ƹ�p2
p2.reset(p3.release());  
// p3�ÿգ�������ָ��
// p2�ͷ�ԭ��ָ��Ķ��󣬲�����ָ��p3��ָ��,*p2="dfseg"
//ʾ����ַ��https://blog.csdn.net/readyone/article/details/112297215
```
* ֵ������Ҫʹ��move()�����ô��ݲ���Ҫ
```c++
    //����ʹ��ͨ��ֵ���ݵ��β�
    void fun1(unique_ptr<int> uptrParam)
    {
        cout << *uptrParam << endl;
    }
    //����ʹ��ͨ�����ô��ݵ�ֵ
    void fun2(unique_ptr<int>& up)
    {
        cout<<*up<<endl;
    }
    int main()
    {
        unique_ptr<int> uptr(new int);
        *uptr = 10;
        fun1(move (uptr)); // �ڵ�����ʹ�� move
        fun2(uptr);
    }
```
## ����ָ��(shared_ptr)
ͷ�ļ���`memory`
��`unique_ptr`����������ڣ���������Ȩ���Ա���ȫ������֧�ָ��Ƹ�ֵ���������ͬʱӵ�С�
```c++
auto p1=make_shared<int>(2);
//use_count()�����ж�ָ������Ȩ
//p1.use_count()=1
auto p2=p1;
//p1.use_count()=2
//p2.use_count()=2
```
* shared_ptr��֧�ְ�ȫ�����������ڲ�ʹ�������ü������ʼ���ü���Ϊ1����ʾֻ��һ�������ߣ�����������Ƹ�ֵ��Ҳ���ǹ����ʱ�����ü����ͻ����ӣ�����������ʱ�����ü����ͻ���١�ֻ�е����ü���Ϊ0ʱ��shared_ptr�Ż���������delete���ͷ��ڴ档
* ͬһָ�벻��ͬʱΪ���shared_ptr������и�ֵ
* �ڳ�ʼ�� shared_ptr ����ָ��ʱ���������Զ�����ָ���ڴ���ͷŹ������������ڴ�����ü���Ϊ 0 ʱ�������ȵ��������Զ�����ͷŹ���
* �ο���ַ(http://c.biancheng.net/view/7898.html)
<h5 align="center">shared_ptr<T>ģ���ೣ�ó�Ա����</h5>

|��Ա����|����|
|:--:|:--|
|swap()|����2����ͬ����shared_ptrָ�������|
|reset()|������û��ʵ��ʱ���ú�����ʹ��ǰ shared_ptr ��ָ���ڴ�����ü����� 1��ͬʱ����ǰ��������Ϊһ����ָ�룻��Ϊ��������һ��������Ķ��ڴ�ʱ������øú����� shared_ptr ������øô洢�ռ������Ȩ���������ü����ĳ�ʼֵΪ 1|
|get()|���shared_ptr�����ڲ���������ָͨ��|
|use_count()|����ͬ��ǰshared_ptr����(������)ָ����ͬ������shared_ptr���������|
|unique()|�жϵ�ǰshared_ptr����ָ��Ķ��ڴ棬�Ƿ���������shared_ptr����ָ����|

## ������ָ��(weak_ptr)
ͷ�ļ���`memory`
* һ����`shared_ptr`����ָ�����ʹ�ã���`weak_ptr`����ָ��ָ���ĳ`shared_ptr`ָ����ͬʱ��`weak_ptr `ָ�벢����ʹ��ָ���ڴ�����ü����� 1��ͬ������` weak_ptr`ָ�뱻�ͷ�ʱ��֮ǰ��ָ���ڴ�����ü���Ҳ������˶��� 1��Ҳ����˵��`weak_ptr` ����ָ�벢����Ӱ����ָ���ڴ�ռ�����ü�����
* [��Ա����](http://c.biancheng.net/view/7918.html)
<h5 align="center">weak_ptr��Ա����</h5>

|��Ա����|����|
|:--:|:--|
|operator=()|����`=`�������weak_ptrָ�����ֱ�ӱ�weak_ptr��shared_ptrָ�븳ֵ|
|swap(x)|����x��ʾͬ���͵�weak_ptrָ�룬�ú������Ի���2��ͬ����weak_ptrָ�������|
|reset()|����ǰweak_ptrָ����Ϊ��ָ��|
|use_count()|�鿴ָ��͵�ǰweak_ptrָ����ͬ��shared_ptrָ�������|
|expired()|�жϵ�ǰweak_ptrָ���Ƿ����(ָ��Ϊ�գ���ָ��Ķ��ڴ��Ѿ����ͷ�)|
|lock()| 	�����ǰ weak_ptr �Ѿ����ڣ���ú����᷵��һ���յ� shared_ptr ָ�룻��֮���ú�������һ���͵�ǰ weak_ptr ָ����ͬ�� shared_ptr ָ�롣|
* weak_ptrһ����Ҫ��;����������ȷ�����Ҵ���shared_ptr�������ڲ���weak_ptr������thisָ�룬Ȼ�����lock()��ȡshared_ptr
```c++
#include <iostream>
#include <memory>
using namespace std;
int main()
{
    std::shared_ptr<int> sp1(new int(10));
    std::shared_ptr<int> sp2(sp1);
    std::weak_ptr<int> wp(sp2);
    //����� wp ָͬ��� shared_ptr ����ָ�������
    cout << wp.use_count() << endl;
    //�ͷ� sp2
    sp2.reset();
    cout << wp.use_count() << endl;
    //���� lock() ����������һ���� wp ָͬ��� shared_ptr ����ָ�룬��ȡ��洢������
    cout << *(wp.lock()) << endl;
    return 0;
}
```
## �ַ���
c++�е��ַ�������`string`��������ʵ����һ���������ͣ�����ģ����`basic_string`���ػ���ʽ����һ�����ͱ�����
```c++
using string = std::basic_string<char>;
```
### ԭʼ�ַ���
c++11Ϊ������������һ����ԭʼ�ַ��������±�ʾ��ʽ��ת����`"\n"`��ʾ�س���ԭʼ�ַ�����ʽ���Թر�ת��ʹ�á�ʾ����
```c++
auto str=R"(nier"automata)";//ԭʼ�ַ�����nier_automata
//���������+Բ���š���ʽ
auto str = R"==(R"(xxx)")==";//���R"(xxx)"
```
### �ַ���ת������
* stoi()/stol()/stoll()���԰��ַ���ת��Ϊ����
* stof()/stod()���԰��ַ���ת��Ϊ������
* to_string()���԰�������������ת��Ϊ�ַ���
### ����ֵ��׺
c++14���������׺��s������ȷ���������ַ������ͣ�ʾ����
```c++
auto str="hello"s;//�Զ��Ƶ�Ϊstring����
```
### �ַ�����ͼ
c++17������������ʹ��C�ַ�������ȡ�Ӵ��ȵ��µ��ַ�����`string_view`������һ���ַ�������ͼ���ɱ��ܵͣ��ڲ�ֻ����һ��ָ��ͳ��ȣ������Ǹ��ƻ����޸Ķ��ǳ����ۡ�
�ڸ����ϣ�`string_view`�������Ϊ���´��룺
```c++
class string_view{
private:
    const char* m_ptr;//ָ���ַ�������ʼ��ַ
    std::size_t m_size;//�ַ�������
public:
    ...//���ֲ�������
};
```
����δ�����Կ���`string_view`��4���ص㣺
* ��Ϊ�ڲ�ʹ���˳���ָ�룬��������һ��ֻ����ͼ��ֻ�ܲ鿴�ַ������޷��޸ģ��൱��"const string&"���������ܰ�ȫ��
* ��Ϊ�ڲ�ʹ�����ַ�ָ�룬����������ֱ�Ӵ�C�ַ������죬û�С�const string&������ʱ���󴴽�������������������ҳɱ��͡�
* ��Ϊʹ�õ���ָ�룬���Ա���Ҫ�������õ����ݿ���ʧЧ����`weak_ptr`һ������������
* ��Ϊ����һ��ֻ����ͼ�����Բ��ܱ�֤�ַ���ĩβһ����NULL���޷��ṩ��Ա����c_str()��Ҳ����˵�������Խ�string_viewת��Ϊ��NULL��β���ַ�ָ�룬��������C�������Ρ�
ʾ����
```c++
using namespace std::literals;
auto sv1="viewit"sv;
//�����ڲ���ָ��ͳ���
string_view sv{"god of war"s};
string str1=sv.substr(4,2);//str1=of
sv.remove_prefix(3);//ɾ��ǰ�����ַ���sv= of war

sv.remove_suffix(4);//ɾ�����ĸ��ַ���sv=god of
```
### �ַ�����ʽ��
c++20�������Ӹ�ʽ����`format`������������`printf()`����ʹ���˿ɱ����ģ�壬�Ӷ���֧�����������Ĳ�������ʵ���˱��������ͼ�飬�������ܰ�ȫ��
��ʽռλ���Ļ�����ʽ��`{���:��ʽ��־}`�����治�����������(��0��ʼ)���ú���Ĳ�������������Ӹ��ֱ�־�����Ƹ�ʽ
|����|����|
|:--:|:---|
|<|���������|
|>|�����Ҷ���|
|+|Ϊ������������ű��|
|-|Ϊ������ӡ�-����ǣ������ޱ��|
|�ո�|Ϊ������ӡ�-����ǣ�����ǰ�ӿո�|
|b|��ʽ��Ϊ����������|
|d|��ʽ��Ϊʮ��������|
|o|��ʽ��Ϊ�˽�������|
|x/X|��ʽ��Ϊʮ����������|
|#|��ʮ����������ʾ`0b��0o��0x`ǰ׺|
|����|��ʽ������Ŀ��|
ʾ����
```c++
format("()",100L);//ֱ�Ӹ�ʽ�����������100
format("{0}-{0}, {1} {2}", "hello", 2.718,3.14);//�����hello-hello,2.718,3.14
format("{:>10}", "hello");//�Ҷ��룬10���ַ��Ŀ�ȣ������     hello
format("{:04},{:+04}",100L,88);//ָ�����Ϳ�ȣ�Ĭ��ʮ����,�����0100, +088
format("{0:x},{0:#X}",200L);//��ʽ��Ϊʮ�����ƣ�64,0X64
format("{:04o},{:04b}",7,5);//��ʽ��Ϊ�˽���/�����ƣ����Ϊ4�������0007,0101
```
## [������ʽ](https://docs.microsoft.com/zh-cn/cpp/standard-library/regular-expressions-cpp?view=msvc-170)
ͷ�ļ���<regex>
������ʽ��һ�������ģʽ�������ԣ�ר��Ϊ�����ı�����ƣ���������һ���Ͻ����﷨���򣬿���ʵ�ָ��ӵ�ƥ�䡢���Һ��滻������
|����|����|
|:--:|:---|
|.|ƥ�����ⵥ���ַ�|
|$|ƥ���е�ĩβ|
|^|ƥ���еĿ�ͷ|
|()|�����ӱ��ʽ�����Ա����û��ظ�|
|*|���Ԫ�ؿ����ظ�������|
|+|��ʾԪ�ؿ����ظ�һ�λ���|
|?|��ʾԪ�ؿ����ظ�0�λ�1��|
|`|`|ƥ�������ε�Ԫ��֮һ|
|[]|�����ַ����ϣ��г������ַ������巶Χ�������Ǽ��ϵĲ���|
|`\`|ת����������ַ���ת���������ƥ��|
|\d|ƥ������[0-9]|
|\D|\dȡ��|
|\w|ƥ����ĸ[a-z]�����֡��»���|
|\W|\wȡ��|
|\s|ƥ��ո�|
|{n}|ǰ��Ԫ���ظ�n��|
|{n,}|ǰ���Ԫ���ظ�����n��|
|{n,m}|ǰ��Ԫ���ظ�����n�Σ�����m��|
### ������ʽ����
c++������ʽ��Ҫ�õ������ࣺ
* regex����ʾһ��������ʽ����basic_regex���ػ���ʽ
* smatch����ʾ������ʽ��ƥ��������match_results���ػ���ʽ

�ڴ���������ʽ�����ʱ�����ǻ����Դ���һЩ����ı�־�����ڿ�������Ĵ�����̡���Щ��־��λ�������ռ�std::regex_constants�У�����ʾ����
* icase��ƥ��ʱ���Դ�Сд
* optimize�������Ż�������ʽ����������������ʽ����Ĺ���ʱ��
* ECMAScript��ʹ��ECMAScript�����﷨��Ҳ��Ĭ���﷨
* awk/grep/egrep��ʹ��awk/grep/egrep���﷨

ʾ����
```c++
using namespace std::regex_constants;
regex reg1{"xyz",icase|optimize};//���Դ�Сд�Ҿ����Ż�
```
### [������ʽ�㷨](https://blog.csdn.net/qq_44519484/article/details/107965931)
c++������ʽ�㷨��3�֣��ֱ�ʵ��ƥ�䡢���Һ��滻�����Ƕ���**ֻ������**��
* regex_match����ȫƥ��һ���ַ���
* regex_search�����ַ��������һ������ƥ��
* regex_replace��������������滻
### ����ƥ��
ƥ�����жϸ������ַ����Ƿ񸴺�ĳ��������ʽ
ʾ����
```c++
auto reg=make_regex(R"(^(\w+\:(\w)$)");
assert(regex_match("a:b",reg));//����ƥ��ɹ�
assert(regex_match("a,b",reg));//����ƥ��ʧ��
//regex_match����һ������3��������������ʽ�����ƥ��ɹ�������ͻ�洢�ٵڶ��������֣�Ȼ��������һ��ȥ�����ӱ��ʽ
auto str="neir:automata"s;
smatch result;
regex_match(str,result,reg);//����ƥ��ɹ�
//result[0]=neir:automata
//result[1]=neir
//result[2]==automata
//��֧��regex_match("xxx",result,reg)��ʽ
```
### �������
regex_search��Ҫ��ȫ��ƥ�䣬ֻҪ�ҵ�һ������ģʽ���Ӵ���ʾ����
```c++
auto str="god of wars"s;
regex reg("(\w+)\s(\w)");
smatch res;
bool found=regex_search(str,res,reg);
//������"unix"ǰ׺��".com"��׺
auto reg1(R"(^unix)");
auto reg2(R"(com$)");
```
### �����滻
regex_replace����Ҫƥ���������ǻ᷵��һ���ַ�����ʾ����
```c++
string s = "ab123cdef"; 
regex ex("\\d");//��һ�����ֱ�Ϊx
regex ex("\\d+");//���������ֱ�Ϊx
string r = regex_replace(s, ex, "x"); 
//����ʹ��regex_replace("123ss", ex, "x")�ĸ�ʽ
//�������
string str="god of wars"s;
regex reg1("\\w+$");
regex reg2("^\\w+");
cout<<regex_replace(regex_replace(str,reg1,"peace"),reg2,"godness")<<endl;
//regex_replace������������ѭPCRE������ʽ׼�򣬿���ʹ��"$N"������ƥ����ӱ��ʽ����"$&"����������ƥ����
regex reg("(\\w+)\\s(\\w+)");
//regex reg(R"((\w+)\s(\w+))");
cout<<regex_replace("hello mike",reg,"$2-says-$1($&)")<<endl;//�����mike-says-hello(hello mike)
```
## ��׼����
* ��������������ѡ��array/vector�������ٶ���죬�ɱ����
* list/forward_list������ṹ�������ɾ����Ч�ʸߣ�������Ч�ʵ�
* ���������Ǻ�����ṹ���Զ���key�Զ����򣬲���Ч�ʸߣ����в���ɱ���
* ����������ɢ�б�ṹ����ɢ��ֵ����洢λ�ã����ҺͲ���ĳɱ����ܵ͡�
* �����������������������ڹ���������Ԫ����key�ĸ������Ԫ��ʵ�������ڲ���key������Ҫ�����key����ȱȽϺ�����ɢ�к�����
c++��������Ԫ�صķ��ʷ�ʽ��Ϊ��˳�����������������������������������������е�һ���������ԣ���������Ԫ�ز��õ���**ֵ����**��Ҳ����˵������洢����Ԫ�صĸ��������������á�
һ�������ʽ�Ǿ���ΪԪ��ʵ��ת�ƹ��캯����ת�Ƹ�ֵ�������ڼ���������ʱ��ʹ��[std::move()](https://blog.csdn.net/p942005405/article/details/84644069)��ת��Ԫ�أ�����Ԫ�ظ��Ƶĳɱ���
```c++
#include <iostream>
#include <utility>
#include <vector>
#include <string>
int main()
{
  std::string str = "Hello";
  std::vector<std::string> v;
  //���ó���Ŀ������캯�����½��ַ����飬��������
  v.push_back(str);
  std::cout << "After copy, str is \"" << str << "\"\n";
  //�����ƶ����캯�����Ϳ�str���Ϳպ���ò�Ҫʹ��str
  v.push_back(std::move(str));
  std::cout << "After move, str is \"" << str << "\"\n";
}
//�����After copy, str is "Hello". After move, str is "".
```
c++11֮������������`emplace_back()`���������������Ծ͵ع���Ԫ�أ�ʡȥ�˹�����ٸ��ơ�ת�Ƶĳɱ���������Ч���������������㡣
### ˳������
˳�������������ݽṹ������Ա���5�֣������洢������(arrary/vector/deque)��ָ��ṹ������(list/forward_list)
* array/vectorֱ�Ӷ�ӦC���������飬�ڴ沼�ֺ�C��ȫ���ݣ������ǳɱ���͡��ٶ��������������ǵ��������������Ƿ��ܶ�̬������array�Ǿ�̬���飬��С�ڳ�ʼ����ʱ��͹̶���vector�Ƕ�̬���飬�������԰���������
* dequeҲ�Ƕ�̬���������飬��vector�������������ǿ��������˸�Ч�����ɾ��Ԫ�أ�vectorֻ����ĩ����push_bakc׷��Ԫ�ء�
* vector/deque���Ԫ����Ϊ�������洢�ģ��������м�����ɾ��Ч�ʺܵͣ���list/forward_list��Ϊ�����������ɾ���Ĳ���ֻ��Ҫ����ָ�룬����������λ�õĲ����ܸ�Ч��
* ����ṹ��ȱ���ǲ���Ч�ʵͣ�ֻ������ָ��˳����ʣ��ⷽ�治��vector������ʵ�Ч�ʸߡ�list��˫������������ǰ������������forward_list�ǵ�������ֻ����ǰ����������Ч�ʺܵ͡�
### ��������
����������Ԫ���ڲ���������ͱ�����ĳ�ֹ����Զ����µ�������c++����������ʹ�õ������ṹ��ͨ���Ǻ��������������ò������ܵĶ�������
��׼��һ����4������������set/multiset��map/multimap��set�Ǽ��ϣ�map�ǹ������飬��multiǰ׺��������ʾ���������ظ���key(Ĭ��Ϊ��С����)�����ڲ��ṹ����ǰ׺����ͬ��
### ��������
��������ͬ���Ǽ��Ϻ͹������飬�÷�����������һ������������ڲ������ݽṹ�������Ǻ����������ɢ�б�Ҳ�й�ϣ��(hash table)
����������4�֣�unordered_set/unordered_multiset/unordered_map/unordered_multimap��

## ��������
������������ȫ���������Ķ��壬�����÷�����;���ֺ�������(�����ṩ��emplace()����)��
��4������������optional/variant/any/tuple
* optional��Ҫ������ʾֵ��Ч����Ч���÷���������ָ��
* variant��һ��һ����������������������ʱ�ı����ͣ�ʵ�ַ��Ͷ�̬
* any��variant���ƣ������������������ͣ�������ʱ������ͻ�����
* tuple���Դ�����ֲ�ͬ���͵����ݣ�Ҳ��������һ����������
* optional/variant/any���κ�ʱ��ֻ�ܳ���һ��Ԫ�أ���tuple����Գ��ж��Ԫ��
### ��ѡֵ(optional)
optional���Խ��ƿ���ֻ������һ��Ԫ�ص�����������ͨ���ж������Ƿ�Ϊ���������Ч����Ч����˿��Ե��ó�Ա����has_value()��ʾ�����£�
```c++
optional<int> op;
auto op1=make_optional<int>();//Ĭ��ֵ��0
assert(!op.has_value());//Ĭ������Чֵ
if(op.has_value())
    cout<<op.value()<<endl;//���ֵ�����ã�op.value�ȼ���*op;
else
    cout<<op.value_or(99)<<endl;//��Ч��᷵�ظ��������ֵ
```
### �ɱ�ֵ(variant)
c++17�����ģ����variant��������Ϊ��һ������union�����Ծۺ��κ����ͣ�ͬʱ�������ֺ�union����һ����
ʾ����
```c++
variant<int float,double> v;
v=42;//v.index()=0
v=3.14f;//v.index()=1
v=2.718;//v.index()=2
//��ȡֵ
get<1>(v)//�������ֵΪ1��ֵ
get<double>(v)//���double���͵�ֵ
//��get()���ʵ��˲����ڵ�ֵ�ͻ����׳��쳣�ķ�ʽ�������û�����

//get_if()��ָ��ķ�ʽ����variant�ڲ���ֵ������ڲ���ֵ�����ڣ��ͻ᷵�ؿ�ָ��
auto p=get_if<float>(&v);

//visit()����Ҫ�������͵�����������һ������ҵ���޼��ķ�����������ר�Ŵ���variant����
variant<int,string> v;
auto vistor=[](auto& x){
    x+=x;
    cout<<x<<endl;
};
v=10;
std::visit(vistor,v);//���20
v="ok";
std::visit(vistor,v);//���okok
```
### ����ֵ(any)
any����ģ���࣬�ܹ�������ʱ����ı����ͣ����޽�ġ�
```c++
//���캯��
any a;
a=10;
auto b=make_any<int>(1);
cout<<any_cast<int>(a)<<endl;//���a��ֵ
auto p=any_cast<int>(&a);//ת�ͳ�ָ��
auto& p=any_cast<int&>(a);//ת�ͳ�����
```
### ��Ԫ��(tuple)
tuple��������pair��࣬����Ҫ��ģ������б�������Ԫ�����ͣ�����ʹ�ù�������make_tuple()��ͨ��ʹ����������������λ��
```c++
//���캯��
tuple<int,double,string> t1{0,1.1,"x"};
auto t2=make_tuple(1L,"hi"s);
//ֵ�����
get<1>(t1)//���1.1
```
## [��׼�㷨](http://c.biancheng.net/view/7469.html)
### ����������
�㷨ֻ��ͨ��������ȥ��ӷ��������Լ�Ԫ�أ������㷨�Ĵ���Χ���������ɵ����������ġ�
����һ����ṩ��Ա����begin/end/cbegin/cend��ǰ׺c��ʾ����������������������Զ������Ƶ����������ʹ��ȫ�ֺ���begin/end/cbegin/cend��
```c++
vector<int> v={1,2,3,4,5};
auto iter1=v.begin();//��Ա������ȡ�����������Զ������Ƶ�
auto iter2=v.end();
auto iter3=std::begin(v);//ȫ�ֺ�����ȡ�����������Զ������Ƶ�
auto iter4=std::end(v);
```
���������ú������£�
* advance()��������ǰ�������ָ������
* next()/prev()����õ�����ǰ��ĳ��λ�ã������������ƶ�
* distance()����������������֮��ľ���
```c++
array<int,5> arr={1,2,3,4,5};
auto start=begin(arr);
auto last=end(arr);
assert(distance(start,last)==5);
auto p=next(start);
assert(distance(start,p)==1);
assert(distance(p,start)==-1);

advance(last,-2);//������last����2��
```
### �����㷨
for_each�㷨��Ҫ��������ֽ�������֣�Ҳ������������(һ����������Ԫ�أ�һ����������Ԫ��)���������ֵĺ������ȷ������Ҳ�и��õķ�װ��
```c++
vector<int> v={1,2,3,4,5};
//range-forѭ��
for(const auto&x:v)
{
    cout<<x<<",";
}
//for_each+lambda
auto print=[](const auto&x){cout<<x<<",";};
for_each(cbegin(v),cend(v),print);
//for_each+�ڲ�����lambda���ʽ
for_each(cbegin(v),cend(v),[](const auto&x){
    cout<<x<<",";
});
```
c++17��ʼ��for_each_n���Բ��ñ���������ֻ��Ҫ����
```c++
for_each_n(
    cbegin(v),3,//ָ�����͸���
    [](const auto&x)
    {
        ...
    }
);
```
### �����㷨
�����㷨ʾ����
|������|����|
|:--:|:---|
|sort|��������|
|reverse|��ת���д���|
|shuffle|�����������|
|stable_sort|Ҫ���������Ȼ����Ԫ�ص����˳��|
|partial_sort|ѡ��ǰ����|
|nth_element|ѡ��ǰ����������Ҫ��������ų�����|
|nth_element|����λ�����ٷ�λ��|
|partition/stable_partition|����ĳ�ֹ����Ԫ�طֳ�����|
|minmax_element|���һ�������һ��|
ʾ�����룺
```c++
vector<int> v={3,5,7,1,10,99,42};
std:reverse(begin(v),end(v));//���{42,99,10,1��7��5��3}
//�����������Ԫ��
minstd_rand rand;
std::shuffle(begin(v),end(v),rand);
//���ǰ����
std::partial_sort(begin(v),next(begin(v),3),end(v));//���{1,3,7,5,10,99,42}ǰ2λ���򣬺��漸λ����
//ȡǰ������������������
std::nth_element(begin(v),next(begin(v),2),end(v));//ǰ2λȡ������Ԫ��ȫ������
//����õ���λ��
auto mid=next(begin(v),size(v)/2);
std::nth_element(begin(v),mid,end(v));//��ʱmidΪ��λ����*midȡֵ;
//�ҳ����д���9����
auto pos=std::partition(begin(v),end(v),[](const auto& x){return x>9;});
auto print=[](const auto& x){cout<<x<<",";};
for_each(begin(v),pos,print);
//�ҳ�������С����
auto [mi,ma]=std::minmax_element(cbegin(v),cend(v));
```
* **��Щ�����㷨����Ҫ������ʵ�����(minmax_element����)�������������˳������array/vector��ʹ��**
### �����㷨
ʹ�������㷨��Ŀ�������㷨���������Ϳ��Կ��ٲ��ң���Լʱ�䡣�����������ϲ��ң�������㷨��Ȼ�Ƕ��ֲ��ң���Ӧ��׼���㷨binary_search
```c++
vector<int> v={3,5,1,7,10,99,42};
std::sort(begin(v),esystem("pause");nd(v));
auto found=std::binary_search(cbegin(v),cend(v),7);//���ֲ��ң�ֻ��ȷ��Ԫ���ڲ���
```
����Ҫ������������ִ�и���Ч�Ķ��ֲ��ң�ʹ��lower_bound(���ڵ���)��upper_bound(����)��
```c++
delctype(cend(v)) pos;//����һ��������
pos=std::lower_bound(cbegin(v),cend(v),7);//�ҵ���һ�����ڵ���7��λ��
found=(pos!=cend(v)&&(*pos==7));//��Ҫ�жϵ������Ƿ���Ч��ֵ�Ƿ���Ч
```
������δ������㷨ʾ����
```c++
//find()����
vector<int> v={1,9,11,3,5,7};
decltype(end(v)) pos;
pos=std::find(begin(v),end(v),3);//�ҵ��״�3���ֵ�λ��
assert(pos!=end(v));//��end()�Ƚϲ���֪���Ƿ��ҵ�
//find_if()����
pos=std::find_if(begin(v),end(v),[](auto x){return x%2==0;});
assert(pos!=end(v));
//find_first_if()����
array<int,2> arr={3,5};//��������
pos=std::first_first_if(begin(v),end(v),begin(arr),end(arr));//����һ��������
assert(pos!=end(v));
``` 
### ��Χ�㷨
c++20�����µ�range���ͣ��������Ϊָ����ĩλ�õĵ���������pair<begin,end>��
```c++
vector<int> v={9,5,1,7,3};
auto print=[](const auto& x){cout<<x<<",";};
namespace ranges=std::ranges;//�����ռ���������ڼ򻯴���
ranges::for_each(v,print);//��Χfor_each�㷨
ranges::count_if(v,[](auto& x){return x>=5;});

minstd_rand rand;//<random>
ranges::shuffle(v,rand);

ranges::stable_sort(v);//��Χ�������Ԫ��
ranges::binary_search(v,7);//��Χ���ֲ����㷨
auto pos=ranges::lower_bound(v,3);//��Χ���ֲ���3�Ƿ����
ranges::partial_sort(v,next(begin(v)),3);//��Χ��������
auto [mi,ma]=ranges::minmax_element(v);//��Χ������Сֵ�����ֵ
```
c++20��viewλ�������ռ�std::views�����ú������£�
|������|����|
|:--:|:---|
|take|ѡ��view��ǰN��Ԫ��|
|drop|����view��ǰN��Ԫ��|
|keys|ѡ��pair���first��Ա|
|values|ѡ��pair���second��Ա|
|reverse|����(��ת)view�������Ԫ��|
|filter|ʹ��ν�ʺ���ɸѡ��view����ض�Ԫ��|
```c++
vector<int> v={3,7,2,4,9,6,8,1,5};
namespace views=std::views;
for(auto&& x:v|views::drop(3)|views::reverse){
    cout<<x<<',';
}//���5,1,8,6,9,4
```
## �̲߳���
**��õĲ�������û�в�������õĶ��߳̾���û�ж��߳�**
### ���ε���
�����ⲻ�˳�ʼ�����ݣ������ڶ��߳����̲߳������û��ĳ��ͬ���ֶ������ƣ��ͻᵶ�ӳ�ʼ������������С�
once_flag���ͱ������ԺܺõĽ��������⣬�������Ϊ��̬��ȫ�ֵ�(�߳̿ɼ�)����Ϊ��ʼ����־��
```c++
static std::once_flag flag;//ȫ�ֳ�ʼ����־
//Ȼ�����ר�ŵ�call_once()�������Ժ���ʽ��̵ķ�ʽ���������־�ͳ�ʼ������������c++�ͻᱣ֤����ʹ����߳�����call_once()��Ҳֻ��һ���̻߳�ɹ���ʼ��
auto f=[](){
    cout<<"tid="<<this_thread::get_id()<<endl;//����߳�ID
    std::call_once(flag,[](){
        cout<<"only once"<<endl;
    });
};
//�߳�����
thread t1(f);
thread t2(f);
```
call_once��ȫ�����˳�ʼ��ʱ�Ĳ�����ͻ�������ĵ���λ�ø����������������̣߳�Ҳ���Ժ����ɵؽ�����߳������ﱻ���ۺܾõ�˫�ؼ�����⣬�������滥���������ʵ�ֳ�ʼ����
### �ֲ��洢
����ȨӦ�����̶߳�ռ������Ӧ���ɶ��̹߳�ͬӵ�У����ڽ����ֲ߳̾��洢(thread local storage)��
```c++
//������һ���̶߳�ռ������Ȼ����lambda���ʽ�������ã��ٽ���Ž�����߳�������
thread_local int n=0;//�ֲ߳̾��洢����
auto f=[&](int x){
    n+=x;//ʹ���ֲ߳̾�����������Ӱ��
    cout<<n<<endl;//�����֤���
};
//�����߳�
thread t1(f,10);
thread t2(f,20);
//���10��20����������
```
### ԭ�ӱ���
���ڽ��ͬ�����⣬�������ɱ����ߣ����Զ�С���ݣ�����ԭ�ӻ��������á�
ԭ���ڶ��߳����������˼���ǲ��ɷֵģ�����Ҫô��ɣ�Ҫ��δ��ɣ����ܱ��κ��ⲿ������ϣ�����һ��ȷ���ġ�������״̬������Ҳ�Ͳ�����ھ�����д�����⡣
���������в���������ԭ�ӻ��ģ�Ŀǰ��c++֧��һЩ����������ԭ�ӻ����磺
```c++
using atomic_bool = std::atomic<bool>;//ԭ�ӻ�bool
using atomic_int = std::atomic<int>;//ԭ�ӻ�int
using atomic_long=std::atomic<long>;//ԭ�ӻ�long
```
ԭ�ӱ�������ģ����atomic���ػ���ʽ��������ԭʼ�����ͣ�������ͬ�Ľӿڣ���������bool/int/long����һģһ��������ȴ��ԭ�ӻ��ģ����̶߳�д����������������������͵�һ����Ҫ�������ǣ��������˸��ƹ��캯���������ڳ�ʼ����ʱ����"="�ĸ�ֵ��ʽ��ֻ����Բ���Ż����ţ�
```c++
atomic_int x{0};
atomic_long y{1000L};
assert(++x==1);//��������
y+=200;//�ӷ�����
assert(y<2000);//�Ƚ�����
```
����ģ���������㣬ԭ�ӱ���������ԭ�ӻ��������£�
|������|����|
|:--:|:---|
|store|д��������ԭ�ӱ�������һ��ֵ|
|load|����������ȡԭ�ӱ������ֵ|
|fetch_add|�ӷ�����������ԭֵ|
|fetch_sub|��������������ԭֵ|
|exchange|������������ֵ�󷵻�ԭֵ|
```c++
atomic_uint x{0};
x.store(10);
assert(x.load()==10);
auto v=x.fetch_add(5);//����ԭֵ
assert(v==10&&x==15);

v=x.fetch_sub(2);
assert(v==15&&x==13);

auto u=x.exchange(100);
assert(u==13&&x==100);
```
`compare_exchange_weak/compare_exchange_strong`���Ƚϲ�����(Compare And Swap,CAS)���������ȱȽ�ԭֵ����������д�룬���򷵻�ԭֵ��
**w==x����w=x��Ȼ��x�ͺ�һ��Ԫ�ؽ�����w!=x����w=x**
```c++
atomic_int example{100};
int expect=1000;
auto flag=example.compare_exchange_strong(expect,10);//expect!=example������flag=false,example����,expect=example=100

atomic_int example{0};
int expect=0;
auto flag=example.compare_exchange_strong(expect,10);//example=expect������flag=true,example=10,expect����

//example.compare_exchange_weak(expected, value);
if (expected==example){
    example = value;
    return true;
}
else
{
    expected = example;
    return false;
}
```
TAS(Test And Set)����������Ҫ�õ�һ�������ԭ������`atomic_flag`
�����Ǽ򵥵�bool�ػ�(����atomic<bool>)��û��store/load������ֻ��test_and_set()��ʵ��TAS����֤����������
```c++
static atomic_flag flag{false};//ԭ�ӱ�־λ����ֵΪfalse
auto f=[&]()
{
    auto value=flag.test_and_set();//��TAS����Ϊtrue������ԭֵ
    if(value)
    {
        cout<<"flag has been set."<<endl;
    }
    else
    {
        cout<<"set flag by "<<this_thread::get_id()<<endl;
    }
};
thread t1(f);
thread t2(f);
```
### �߳̽ӿ�
#### ��������
�����ռ�std::this_thread��4���̹߳��������ߣ�������ʵ���̵߳ĵ��Ⱥ͹���
|������|����|
|:--:|:---|
|get_id()|��õ�ǰ�̵߳�ID|
|yield()|��ʱ�ó��̵߳�ִ��Ȩ����ϵͳ���µ���|
|sleep_for()|ʹ��ǰ�߳�˯�ߵȴ�һ��ʱ��|
|sleep_until()|ʹ��ǰ�߳�˯�ߵȴ���ĳ��ʱ���|
#### �߳���
c++11��thread�����߳���������ó�Ա����join()���ȴ��߳̽�����c++20����������߳���jthread�����thread�࣬���ڶ���������ʱ���Ǽ򵥵������̣߳������ȵ���join()���ȴ��߳̽���������١�
```c++
auto task=[]()
{
    this_thread::sleep_for(1s);
    cout<<"sleep for 1s"<<endl;
};
thread t(task);
t.join;
//ʹ��jthread��
jthread jt{task};//�����̣߳����Զ������ȴ��߳̽���
```
#### �첽����
������Ҫֱ��ʹ��thread/jthread��д���̳߳�����ð��������ص��ײ㣬�����������̲߳�����õ��̡߳���
���������ǵ��ú���`asynv()`���������첽����һ�����������Ķ���������һ���߳�ȡִ�У��������Ա�֤����������
```c++
auto task=[](auto x)
{
    this_thread::sleep_for(x*1ms);
    cout<<"sleep for "<<x<<endl;
    return x;
};
auto f=std::async(task,10);
f.wait();//�ȴ��������
assert(f.valid());//ȷʵ���������
cout<<f.get()<<endl;//��ȡ�����ִ�н��
```
* async()���ú�᷵��һ��future������������Ϊ�ñ����Ǵ�����ִ�н���ġ��ڻ�������������з���ֵ�������ó�Ա����get()��ȡ������get()ֻ�ܵ���**һ��**���ٴλ�ȡ����ᷢ�������׳��쳣std::future_error
* **���صĿ�**���û����ʽ��ȡasync()�ķ���ֵ(future����)����������ֵû�б����գ��ͳ�����ʱ���󣬻�ͬ������ֱ��������ɡ�**�����ʽ**auto f=std::async(task,...)
#### ��������
c++17����`scoped_lock`������һ��RAII�ͻ������������ߣ������Զ���������Χ������/�������ǳ��ʺϳ�ʼ��ʹ�ã�����������if��䣬Ȼ���Զ�������
```c++
int x=0;
mutex mu1,mu2;//����������
if(scoped_lock guard(mu1,mu2);x==0)//ͬʱ����������������������ж�����
{
    cout<<"scoped_locked"<<endl;//�뿪if��䣬���������Զ�����
}
```