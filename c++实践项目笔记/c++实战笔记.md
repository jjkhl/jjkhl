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