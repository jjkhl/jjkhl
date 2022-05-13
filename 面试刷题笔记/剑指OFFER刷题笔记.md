# 剑指OFFER
## 第二章
### 面试题1：赋值运算函数
为CMyString的声明添加赋值运算符函数
```c++
class CMyString
{
public:
    CMyString(char* pData=nullptr);
    CMyString(const CMYString& str);
    ~CMyString(void);
private:
    char* m_pData;
};
```
方案一：
```c++
CMyString& CMyString::operator=(const CMyString& str)
	{
		if(this==&str)
			return *this;//this和str不能为同一个实例，否则当前空间会被delete
		delete[] m_pData;
		m_pData=nullptr;

		m_pData=new char[strlen(m_pData)+1];//分配失败抛出异常怎么办
		strcpy(m_pData,str.m_pData);

		return *this;
	}
```
最佳方案：先创建一个临时实例，在交换临时实例和原来实例。
```c++
CMyString& CMyString::operator=(const CMyString& str)
{
    //第一步：创建temp临时对象，让temp.m_pData指向str.m_pData的地址(A)
    //第二步：创建data_t临时对象(地址B)，让它指向temp.m_pData的地址(A)
    //第三步：让地址A(temp.m_pData地址)指向m_pData的地址(C)
    //此时：data_t(地址A,str的地址)，temp.mpData(地址C,原this指针地址),m_pData(地址B,原data_t的地址,指向str.m_pData)
    //最后结束时，临时对象都会被释放掉，即地址C被delete，地址C因为是只读属性而无法进行操作。
    if(this!=&str)
    {
        CMyString temp(str);
        char* data_t=temp.m_pData;//相当于new空间
        temp.m_pData=m_pData;//相当于delete[] m_pData;
        m_pData=data_t;
    }
    return *this;
}
```
## 面试题2：实现[Singleton模式](https://www.cnblogs.com/sunchaothu/p/10389842.html#%E4%B8%80%E4%BB%80%E4%B9%88%E6%98%AF%E5%8D%95%E4%BE%8B)
方案1:有缺陷的懒汉式
内容：只有使用时才实例化对象，如果不被调用就不会占用内存
问题：
1.线程安全——加锁解决
2.内存泄漏：无delete对象——使用共享指针
```c++
#include <iostream>
// version1:
// with problems below:
// 1. thread is not safe
// 2. memory leak

class Singleton{
private:
    Singleton(){
        std::cout<<"constructor called!"<<std::endl;
    }
    Singleton(Singleton&)=delete;
    Singleton& operator=(const Singleton&)=delete;
    static Singleton* m_instance_ptr;
public:
    ~Singleton(){
        std::cout<<"destructor called!"<<std::endl;
    }
    static Singleton* get_instance(){
        if(m_instance_ptr==nullptr){
              m_instance_ptr = new Singleton;
        }
        return m_instance_ptr;
    }
    void use() const { std::cout << "in use" << std::endl; }
};

Singleton* Singleton::m_instance_ptr = nullptr;

int main(){
    Singleton* instance = Singleton::get_instance();
    Singleton* instance_2 = Singleton::get_instance();
    return 0;
}
//输出结果:constructor called!
```
方案2：线程安全、内存安全的懒汉式单例
问题：使用智能指针会要求用户也得使用智能指针，非必要不应该提出这种约束; 使用锁也有开销; 同时代码量也增多了，实现上我们希望越简单越好。还有更加严重的问题，在某些平台（与编译器和指令集架构有关），双检锁会失效！
```c++
#include <iostream>
#include <memory> // shared_ptr
#include <mutex>  // mutex

// version 2:
// with problems below fixed:
// 1. thread is safe now
// 2. memory doesn't leak

class Singleton{
public:
    typedef std::shared_ptr<Singleton> Ptr;
    ~Singleton(){
        std::cout<<"destructor called!"<<std::endl;
    }
    Singleton(Singleton&)=delete;
    Singleton& operator=(const Singleton&)=delete;
    static Ptr get_instance(){

        // "double checked lock"
        if(m_instance_ptr==nullptr){
            std::lock_guard<std::mutex> lk(m_mutex);
            if(m_instance_ptr == nullptr){
              m_instance_ptr = std::shared_ptr<Singleton>(new Singleton);
            }
        }
        return m_instance_ptr;
    }


private:
    Singleton(){
        std::cout<<"constructor called!"<<std::endl;
    }
    static Ptr m_instance_ptr;
    static std::mutex m_mutex;
};

// initialization static variables out of class
Singleton::Ptr Singleton::m_instance_ptr = nullptr;
std::mutex Singleton::m_mutex;

int main(){
    Singleton::Ptr instance = Singleton::get_instance();
    Singleton::Ptr instance2 = Singleton::get_instance();
    return 0;
}
//输出：constructor called!
//     destructor called!
```
方案3：局部静态变量
解释：如果当变量在初始化的时候，并发同时进入声明语句，并发线程将会阻塞等待初始化结束。这样保证了并发线程在获取静态局部变量的时候一定是初始化过的，且<strong style="color:red">只有一次初始化</strong>，所以具有线程安全性，而c++静态变量的生存期是从声明到程序结束。
```c++
#include <iostream>

class Singleton
{
public:
    ~Singleton(){
        std::cout<<"destructor called!"<<std::endl;
    }
    Singleton(const Singleton&)=delete;
    Singleton& operator=(const Singleton&)=delete;
    static Singleton& get_instance(){//返回引用才能获取对象
        static Singleton instance;
        return instance;

    }
private:
    Singleton(){
        std::cout<<"constructor called!"<<std::endl;
    }
};

int main(int argc, char *argv[])
{
    Singleton& instance_1 = Singleton::get_instance();
    Singleton& instance_2 = Singleton::get_instance();
    return 0;
}
//输出：constructor called!
//     destructor called!
```
## 面试题3：[数组中重复的数字](https://leetcode-cn.com/problems/shu-zu-zhong-zhong-fu-de-shu-zi-lcof/)
[思路地址](https://leetcode-cn.com/problems/shu-zu-zhong-zhong-fu-de-shu-zi-lcof/solution/mian-shi-ti-03-shu-zu-zhong-zhong-fu-de-shu-zi-yua/)
```c++
class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        int i = 0;
        while(i < nums.size()) {
            if(nums[i] == i) {
                i++;
                continue;
            }
            if(nums[nums[i]] == nums[i])
                return nums[i];
            swap(nums[i],nums[nums[i]]);
        }
        return -1;
    }
};
```
## 面试题4：[二维数组中的查找](https://leetcode-cn.com/problems/er-wei-shu-zu-zhong-de-cha-zhao-lcof/)
```c++
//左下角查找
class Solution {
public:
    bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
        int i = matrix.size() - 1, j = 0;
        while(i >= 0 && j < matrix[0].size())
        {
            if(matrix[i][j] > target) i--;
            else if(matrix[i][j] < target) j++;
            else return true;
        }
        return false;
    }
};
//右上角查找
class Solution {
public:
    bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
        if(matrix.size()==0||matrix[0].size()==0) return false;
        int i=0,j=matrix[0].size()-1;
        while(i<matrix.size()&&j>=0)
        {
            if(target>matrix[i][j])
                ++i;
            else if(target<matrix[i][j])
                --j;
            else return true;
        }
        return false;
    }
};
```
## 面试题5：[替换空格](https://leetcode-cn.com/problems/ti-huan-kong-ge-lcof/)
```c++
//库函数的使用
class Solution {
public:
    string replaceSpace(string s) {
        int size = s.size();
        for(int i=0;i<size;i++)
        {
            if(s[i]==' ')
            {
                s.insert(i,"%20");
                i+=2;
                s.erase(i+1,1);
                size+=2;

                }
        }
        return s;
    }
};
//原数组改动
class Solution {
public:
    string replaceSpace(string s) {
int count=0,len=s.size();
    for(char c:s)
        if(c==' ')
            ++count;
    s.resize(len+2*count);
    for(int i=len-1,j=s.size()-1;i<j;i--,j--)
    {
        if(s[i]==' ')
        {
            s[j-2]='%';
            s[j-1]='2';
            s[j]='0';
            j-=2;
        }
        else
            s[j]=s[i];
    }
    return s;
    }
};
```
## 面试题6：[从头到尾打印链表](https://leetcode-cn.com/problems/cong-wei-dao-tou-da-yin-lian-biao-lcof/)
```c++
//时间换空间：先反转链表
class Solution {
public:
    vector<int> reversePrint(ListNode* head) {
    vector<int> res;
    if(head==NULL) return res;
    ListNode* pre=NULL;
    ListNode* cur=head;
    ListNode* tmp;
    while(cur)
    {
        tmp=cur->next;
        cur->next=pre;
        pre=cur;
        cur=tmp;
    }
    while(pre)
    {
        res.emplace_back(pre->val);
        pre=pre->next;
    }
    return res;
    }
};
//栈的使用/**
class Solution {
public:
    vector<int> reversePrint(ListNode* head) {
     vector<int> res;
     stack<int> st;
     if(NULL==head) return res;
     while(head)
     {
         st.emplace(head->val);
         head=head->next;
     }
     while(!st.empty())
     {
         res.emplace_back(st.top());
         st.pop();
     } 
     return res;
    }
};
```

## 面试题7：[重建二叉树](https://leetcode-cn.com/problems/zhong-jian-er-cha-shu-lcof/)
```c++
//前序和中序遍历重构二叉树
class Solution {
public:
TreeNode* helpBuildTree(
vector<int>& preorder,int  preBegin,int preEnd,
vector<int>& inorder,int inBegin,int inEnd)
{
    if(preBegin>=preEnd||inBegin>=inEnd) return NULL;
    TreeNode* root=new TreeNode(preorder[preBegin]);
    int index=inBegin;
    while(inorder[index]!=root->val)
    {
        ++index;
    }
    int inLeftBegin=inBegin;
    int inLeftEnd=index;
    
    int leftSize=inLeftEnd-inBegin;

    int inRightBegin=index+1;
    int inRightEnd=inEnd;

    int rightSize=inRightBegin-inRightEnd;

    int preLeftBegin=preBegin+1;
    int preLeftEnd=preLeftBegin+leftSize;

    int preRightBegin=preLeftEnd;
    int preRightEnd=preEnd;

    root->left=helpBuildTree(preorder,preLeftBegin,preLeftEnd,inorder,inLeftBegin,inLeftEnd);
    root->right=helpBuildTree(preorder,preRightBegin,preRightEnd,inorder,inRightBegin,inRightEnd);
    return root;
}
TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
{
    return helpBuildTree(preorder,0,preorder.size(),inorder,0,inorder.size());
}
};
```
## 面试题8：[二叉树的下一个结点](https://www.nowcoder.com/practice/9023a0c988684a53960365b889ceaf5e?tpId=13&tqId=23451&ru=/practice/6fe361ede7e54db1b84adc81d09d8524&qru=/ta/coding-interviews/question-ranking)
```c++
/*
struct TreeLinkNode {
    int val;
    struct TreeLinkNode *left;
    struct TreeLinkNode *right;
    struct TreeLinkNode *next;
    TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) {

    }
};
*/
//next表示父节点
class Solution {
public:
    TreeLinkNode* GetNext(TreeLinkNode* pNode) {
        if (!pNode)
            return NULL;
        // 若该结点存在右子树
        if (pNode->right) {
            TreeLinkNode* rightChild = pNode->right; 
            // 寻找右子树上的最左孩子
            while (rightChild->left)
                rightChild = rightChild->left;
            return rightChild;
        }
        // 若不存在右子树，寻找第一个右父亲
        while (pNode->next) {
            if (pNode->next->left == pNode) 
                return pNode->next; 
            pNode = pNode->next;
        }
        return NULL;
    }
};
```
## 面试题9：[用两个栈实现队列](https://leetcode-cn.com/problems/yong-liang-ge-zhan-shi-xian-dui-lie-lcof/)
```c++
class CQueue {
public:
    CQueue() {
    }
    
    void appendTail(int value) {
        st1.push(value);
    }
    
    int deleteHead() {
        if(st1.empty()) return -1;
        while(!st1.empty())
        {
            st2.push(st1.top());
            st1.pop();
        }
        int res=st2.top();
        st2.pop();
        while(!st2.empty())
        {
            st1.push(st2.top());
            st2.pop();
        }
        return res;
    }
public:
    stack<int> st1;
    stack<int> st2;
};
```
## 面试题10-I：[斐波那契数列](https://leetcode-cn.com/problems/fei-bo-na-qi-shu-lie-lcof/)
```c++
class Solution {
public:
int fib(int n) {
        if(n<=1)
            return n;
        int dp[2]={0,1};
        for(int i=2;i<=n;i++)
        {
            long long tmp=dp[0]+dp[1];
            dp[0]=dp[1];
            dp[1]=tmp%1000000007;
        }
        //1000000007是因为题目要求要取模
        return dp[1];
    }
};
```
## 面试题10-II：[青蛙跳台阶问题](https://leetcode-cn.com/problems/qing-wa-tiao-tai-jie-wen-ti-lcof/)
```c++
class Solution {
public:
    int numWays(int n) {
        if(n==0) return 1;
        if(n<3) return n;
        int dp[2]={1,2};
        for(int i=3;i<=n;i++)
        {
            long long tmp=dp[0]+dp[1];
            dp[0]=dp[1];
            dp[1]=tmp%1000000007;
        }
        return dp[1];
    }
};
```
## 面试题11：[旋转数组的最小数字](https://leetcode-cn.com/problems/xuan-zhuan-shu-zu-de-zui-xiao-shu-zi-lcof/)
```c++
class Solution {
public:
    int minArray(vector<int> &numbers)
{
    int left = 0;
    int right = numbers.size() - 1;
    while(left<right)
    {
        int mid=((right-left)>>1)+left;
        if(numbers[mid]<numbers[right])
            right=mid;
        else if(numbers[mid]>numbers[right])
            left=mid+1;
        else
            --right;
    }
    return numbers[left];
}
};
```
## 面试题12：[矩阵中的路径](https://leetcode-cn.com/problems/ju-zhen-zhong-de-lu-jing-lcof/)
```c++
class Solution {
private:
    int ROW, COL, LEN;
    bool backtracking(vector<vector<char>>& board, string& word, int row, int col, int idx) {
        if(idx >= LEN) {
            return true;
        }
        if(row < 0 || row >= ROW || col < 0 || col >= COL || board[row][col] != word[idx]) {
            return false;
        }

        char c = board[row][col];
        board[row][col] = '*';
        if (backtracking(board, word, row - 1, col, idx + 1) ||
            backtracking(board, word, row + 1, col, idx + 1) ||
            backtracking(board, word, row, col - 1, idx + 1) ||
            backtracking(board, word, row, col + 1, idx + 1)) {
                return true;
        }
        board[row][col] = c;
        return false;
    }
public:
    bool exist(vector<vector<char>>& board, string& word) {
        ROW = board.size();
        COL = board[0].size();
        LEN = word.length();

        for(int row = 0; row < ROW; ++row) {
            for(int col = 0; col < COL; ++col) {
                if(backtracking(board, word, row, col, 0)) {
                    return true;
                }
            }
        }

        return false;
    }
};
```
## 面试题13：[机器人的运动范围](https://leetcode-cn.com/problems/ji-qi-ren-de-yun-dong-fan-wei-lcof/)
```c++
//递归法
class Solution {
public:
int getDigitSum(int num)
{
    int sum=0;
    while(num>0)
    {
        sum+=num%10;
        num/=10;
    }
    return sum;
}
int movingCount(int m, int n, int k)
{
    if(k==0) return 1;
    vector<vector<int>> vec(m,vector<int>(n,0));
    int res=1;
    vec[0][0]=1;
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if((i==0&&j==0)||getDigitSum(i)+getDigitSum(j)>k)
                continue;
            if(i>=1)
                vec[i][j]|=vec[i-1][j];//或运算
            if(j>=1)
                vec[i][j]|=vec[i][j-1];
            res+=vec[i][j];
        }
    }
    return res;
}
};
//递归法II
class Solution {
public:
    int getDigitSum(int x)
    {
        int sum=0;
        while(x)
        {
            sum+=x%10;
            x/=10;
        }
        return sum;
    }
    int dfs(vector<vector<int>>& dp,int m,int n,int k,int i,int j)
    {
        //dp[i][j]==true表明该格子要是被访问过就继续
        if(i>=m||j>=n||getDigitSum(i)+getDigitSum(j)>k||dp[i][j])
         return 0;
        dp[i][j]=1;
        return 1+dfs(dp,m,n,k,i+1,j)+dfs(dp,m,n,k,i,j+1);
    }
    int movingCount(int m, int n, int k) {
        vector<vector<int>> dp(m,vector<int>(n,0));
        return dfs(dp,m,n,k,0,0);
    }
};
```
## 面试题14-I：[剪绳子](https://leetcode-cn.com/problems/jian-sheng-zi-lcof/)
```c++
class Solution {
public:
int cuttingRope(int n)
{
    if(n<=3)
        return n-1;
    vector<int> dp(n+1);
    dp[1]=1;
    dp[2]=2;
    dp[3]=3;
    for(int i=4;i<=n;i++)
    {
        int maxValue=0;
        for(int j=1;j<=i/2;j++)
        {
            maxValue=maxValue>dp[j]*dp[i-j]?maxValue:dp[j]*dp[i-j];
        }
        dp[i]=maxValue;
    }
    return dp[dp.size()-1];
}
};
``` 
## 面试题14-II：[剪绳子II](https://leetcode-cn.com/problems/jian-sheng-zi-ii-lcof/)
```c++
//贪心算法：尽可能取3来保证最大
class Solution {
private:
    const long long int mod = 1e9+7;
public:
    int cuttingRope(int n) {
        if(n <= 3) return n - 1;
        long res = 1;
        while(n > 4) {
            res = (res * 3) % mod;
            n -= 3;
        }
        return (res * n) % mod;  
    }
};
```
## 面试题15：[二进制中1的个数](https://leetcode-cn.com/problems/er-jin-zhi-zhong-1de-ge-shu-lcof/)
```c++
class Solution {
public:
int hammingWeight(uint32_t n)
{
    int res=0;
    while(n>0)
    {
        if(n%2)
            res++;
        n/=2;
    }
    return res;
}
};
//微软解法
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int count=0;
        while(n)
        {
            n=n&(n-1);
            count++;
        }
        return count;
    }
};
```
## 面试题16：[数值的整数次方](https://leetcode-cn.com/problems/shu-zhi-de-zheng-shu-ci-fang-lcof/)
```c++
//递归
class Solution {
public:
    double myPow(double x, int n) {
        if(n==0) return 1;
    else if(n==-1) return 1/x;
    //cout<<n<<"\t"<<(n&1)<<endl;
    if(n&1) return myPow(x*x,n>>1)*x;//单数
    else return myPow(x*x,n>>1);//双数
    }
};
```
## 面试题17：[打印从1到最大的n位数](https://leetcode-cn.com/problems/da-yin-cong-1dao-zui-da-de-nwei-shu-lcof/)
```c++
//需要保证不溢出，需要用char或string字符串进行存储
class Solution {
public:
    vector<int> printNumbers(int n) {
        vector<int> res;
        int maxValue=1;
        maxValue=pow(10,n)
        for(int i=1;i<maxValue;i++)
            res.emplace_back(i);
        return res;
    }
};class Solution {
public:
    vector<int> output;
    vector<int> printNumbers(int n) {
        // 以下注释的前提：假设 n = 3
        if(n <= 0) return vector<int>(0);
        string s(n, '0'); // s最大会等于999，即s的长度为n
        while(!overflow(s)) inputNumbers(s);
        return output;
    }
    bool overflow(string& s)
    {
        // 本函数用于模拟数字的累加过程，并判断是否越界（即 999 + 1 = 1000，就是越界情况）
        bool isOverFlow = false;
        int carry = 0; // carry表示进位
        for(int i=s.length()-1; i>=0; --i)
        {
            int current = s[i] - '0' + carry; // current表示当前这次的操作
            if(i == s.length() - 1) current ++; // 如果i此时在个位，current执行 +1 操作
            if(current >= 10)
            {
                // 假如i已经在最大的那一位了，而current++之后>=10，说明循环到头了，即999 + 1 = 1000
                if(i == 0) isOverFlow = true;
                else
                {
                    // 只是普通进位，比如current从9变成10
                    carry = 1;
                    s[i] = current - 10 + '0'; 
                }
            }
            else
            {
                // 如果没有进位，更新s[i]的值，然后直接跳出循环，这样就可以回去执行inputNumbers函数了，即往output里添加元素
                s[i] = current + '0';
                break;
            }
        }
        return isOverFlow;
    }
    void inputNumbers(string s)
    {
        // 本函数用于循环往output中添加符合传统阅读习惯的元素。比如001，我们会添加1而不是001。
        bool isUnwantedZero = true; // 判断是否是不需要添加的0，比如001前面的两个0
        string temp = "";
        for(int i=0; i<s.length(); ++i)
        {
            if(isUnwantedZero && s[i] != '0') isUnwantedZero = false;
            if(!isUnwantedZero) temp += s[i];
        }
        output.push_back(stoi(temp));
    }
};
// 作者：superkakayong
// 链接：https://leetcode-cn.com/problems/da-yin-cong-1dao-zui-da-de-nwei-shu-lcof/solution/fei-zi-jie-ti-ku-jian-17-jian-dan-da-yin-cong-1dao/
```
## 面试题18：[删除链表的节点](https://leetcode-cn.com/problems/shan-chu-lian-biao-de-jie-dian-lcof/)
```c++
class Solution {
public:
    ListNode* deleteNode(ListNode* head, int val) {
ListNode* dummyHead=new ListNode(0);
        dummyHead->next=head;
        ListNode* cur=dummyHead;
        while(cur->next)
        {
            if(cur->next->val==val)
            {
                // ListNode* tmp=cur->next;
                cur->next=cur->next->next;
                // delete tmp;
                break;
            }
            cur=cur->next;
        }
        cur=dummyHead->next;
        delete dummyHead;
        return cur;
    }
};
```
## 面试题19：[正则表达式匹配]([正则表达式匹配](https://leetcode-cn.com/problems/zheng-ze-biao-da-shi-pi-pei-lcof/))
网址推荐：https://leetcode-cn.com/problems/regular-expression-matching/
```c++
//递归解法
class Solution {
public:
    bool isMatch(string s, string p) {
        return isMatch(s.c_str(), p.c_str());
    }
    
    bool isMatch(const char* s, const char* p) {
        if(*p == 0) return *s == 0;
        
        auto first_match = *s && (*s == *p || *p == '.');
        
        if(*(p+1) == '*'){
            return isMatch(s, p+2) || (first_match && isMatch(++s, p));
        }
        else{
            return first_match && isMatch(++s, ++p);
        }
    }
};
//官方题解
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size();
        int n = p.size();

        auto matches = [&](int i, int j) {
            if (i == 0) {
                return false;
            }
            if (p[j - 1] == '.') {
                return true;
            }
            return s[i - 1] == p[j - 1];
        };

        vector<vector<int>> f(m + 1, vector<int>(n + 1));
        f[0][0] = true;
        for (int i = 0; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (p[j - 1] == '*') {
                    f[i][j] |= f[i][j - 2];
                    if (matches(i, j - 1)) {
                        f[i][j] |= f[i - 1][j];
                    }
                }
                else {
                    if (matches(i, j)) {
                        f[i][j] |= f[i - 1][j - 1];
                    }
                }
            }
        }
        return f[m][n];
    }
};
```
## 面试题20：[表示数组的字符串](https://leetcode-cn.com/problems/biao-shi-shu-zhi-de-zi-fu-chuan-lcof/)
```c++
class Solution {
private:
    // 整数的格式可以用[+|-]B表示, 其中B为无符号整数
    bool scanInteger(const string s, int& index){
        if(s[index] == '+' || s[index] == '-')
            ++index;
        return scanUnsignedInteger(s, index);
    }
    bool scanUnsignedInteger(const string s, int& index){
        int befor = index;
        while(index != s.size() && s[index] >= '0' && s[index] <= '9')
            index ++;
        return index > befor;
    }
public:
    // 数字的格式可以用A[.[B]][e|EC]或者.B[e|EC]表示，
    // 其中A和C都是整数（可以有正负号，也可以没有），而B是一个无符号整数
    bool isNumber(string s) {
        if(s.size() == 0)
            return false;
        int index = 0;
        //字符串开始有空格，可以返回true
        while(s[index] == ' ')  //书中代码没有该项测试
            ++index;
        bool numeric = scanInteger(s, index);
        // 如果出现'.'，接下来是数字的小数部分
        if(s[index] == '.'){
            ++index;
            // 下面一行代码用||的原因：
            // 1. 小数可以没有整数部分，例如.123等于0.123；
            // 2. 小数点后面可以没有数字，例如233.等于233.0；
            // 3. 当然小数点前面和后面可以有数字，例如233.666
            numeric = scanUnsignedInteger(s, index) || numeric;
        }
        // 如果出现'e'或者'E'，接下来跟着的是数字的指数部分
        if(s[index] == 'e' || s[index] == 'E'){
            ++index;
            // 下面一行代码用&&的原因：
            // 1. 当e或E前面没有数字时，整个字符串不能表示数字，例如.e1、e1；
            // 2. 当e或E后面没有整数时，整个字符串不能表示数字，例如12e、12e+5.4
            numeric = numeric && scanInteger(s ,index);
        }
         //字符串结尾有空格，可以返回true
        while(s[index] == ' ')
            ++index;
        return numeric && index == s.size();//最后看是否所有部分都符合，如1a3只会检测第一部分是整数然后是a就不会继续检测了，index!=size，所以返回false
    }
};
// 作者：san-he-n
// 链接：https://leetcode-cn.com/problems/biao-shi-shu-zhi-de-zi-fu-chuan-lcof/solution/jian-zhi-offerguan-fang-jie-da-bu-yong-c-e2wd/
```
## 面试题21：[调整数组顺序使奇数位于偶数前面](https://leetcode-cn.com/problems/diao-zheng-shu-zu-shun-xu-shi-qi-shu-wei-yu-ou-shu-qian-mian-lcof/)
```c++
//快慢指针
class Solution {
public:
    vector<int> exchange(vector<int>& nums) {
        int low = 0, fast = 0;
        while (fast < nums.size()) {
            if (nums[fast] & 1) {
                swap(nums[low], nums[fast]);
                low ++;
            }
            fast ++;
        }
        return nums;
    }
};
//首尾指针class Solution {
public:
    vector<int> exchange(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
    while (left < right)
    {
        if ((nums[left] & 1) == 1)
        {
            left++;
            continue;
        }
        if ((nums[right] & 1) == 0)
        {
            right--;
            continue;
        }
        swap(nums[left], nums[right]);
    }
    return nums;
    }
};
```
## 面试题22：[链表中倒数第k个节点](https://leetcode-cn.com/problems/lian-biao-zhong-dao-shu-di-kge-jie-dian-lcof/)
```c++
class Solution {
public:
    ListNode* getKthFromEnd(ListNode* head, int k) {
        ListNode* slow=head,*fast=head;
        while(k--&&fast)
        {
            fast=fast->next;
        }
        while(fast)
        {
            slow=slow->next;
            fast=fast->next;
        }
        return slow;
    }
};
```
## 面试题23：[环形链表II](https://leetcode-cn.com/problems/linked-list-cycle-ii/)
```c++
//快慢指针
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode* fast = head;
        ListNode* slow = head;
        while(fast != NULL && fast->next != NULL) {
            slow = slow->next;
            fast = fast->next->next;
            // 快慢指针相遇，此时从head 和 相遇点，同时查找直至相遇
            if (slow == fast) {
                ListNode* index1 = fast;
                ListNode* index2 = head;
                while (index1 != index2) {
                    index1 = index1->next;
                    index2 = index2->next;
                }
                return index2; // 返回环的入口
            }
        }
        return NULL;
    }
};
```
## 面试题24：[反转链表](https://leetcode-cn.com/problems/fan-zhuan-lian-biao-lcof/)
```c++
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* tmp;
        ListNode* cur=head;
        ListNode* pre=NULL;
        while(cur)
        {
            tmp=cur->next;
            cur->next=pre;
            pre=cur;
            cur=tmp;
        }
        return pre;
    }
};
```
## 面试题25：[合并两个排序的链表](https://leetcode-cn.com/problems/he-bing-liang-ge-pai-xu-de-lian-biao-lcof/)
```c+
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* dummy=new ListNode(0);
        ListNode* ret=dummy;
        while(l1&&l2)
        {
            if(l1->val<l2->val)
            {
                dummy->next=l1;
                l1=l1->next;
            }
            else 
            {
                dummy->next=l2;
                l2=l2->next;
            }
            dummy=dummy->next;
        }
        dummy->next=(l1==NULL)?l2:l1;
        return ret->next;
    }
};
```
## 面试题26：[树的子结构](https://leetcode-cn.com/problems/shu-de-zi-jie-gou-lcof/)
```c++
class Solution {
public:
    bool hasSubStructure(TreeNode*A, TreeNode*B)
    {
        if(!B)   
            return true;
        if(!A)
            return false;
        if(A->val!=B->val)
            return false;
        return hasSubStructure(A->left, B->left) && hasSubStructure(A->right, B->right); 
    }
    bool isSubStructure(TreeNode* A, TreeNode* B) 
    {
         if (!A || !B)
         {
             //特殊判断
             return false;
         }   
        // 根节点相同的话直接进入比较，根节点不相同看B是不是A的左/右子树的子结构
        return hasSubStructure(A, B) || isSubStructure(A->left, B) || isSubStructure(A->right, B);
    }
};
```
## 面试题27：[二叉树的镜像](https://leetcode-cn.com/problems/er-cha-shu-de-jing-xiang-lcof/)
```c++
class Solution {
public:
    TreeNode* mirrorTree(TreeNode* root) {
        if (root == nullptr) {
            return nullptr;
        }
        TreeNode* left = mirrorTree(root->left);
        TreeNode* right = mirrorTree(root->right);
        root->left = right;
        root->right = left;
        return root;
    }
};
```
## 面试题28：[对称的二叉树](https://leetcode-cn.com/problems/dui-cheng-de-er-cha-shu-lcof/)
```c++
class Solution {
public:
    bool traversal(TreeNode* A,TreeNode* B)
    {
        if(!A&&!B) return true;
        else if(!A&&B) return false;
        else if(A&&!B) return false;
        else if(A->val!=B->val) return false;
        else 
            return traversal(A->left,B->right)&&traversal(A->right,B->left);
    }
    bool isSymmetric(TreeNode* root) {
        if(!root) return true;
        return traversal(root->left,root->right);
    }
};
```
## 面试题29：[顺时针打印矩阵](https://leetcode-cn.com/problems/shun-shi-zhen-da-yin-ju-zhen-lcof/)
类似题型：[54.螺旋矩阵](#54)
```c++
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if(matrix.empty()) return vector<int>{};
        int up=0,left=0,right=matrix[0].size()-1,down=matrix.size()-1;
        vector<int> res;
        while(true)
        {
            for(int j=left;j<=right;j++)
            {
                res.emplace_back(matrix[up][j]);
            }
            if(++up>down) break;
            for(int i=up;i<=down;i++)
            {
                res.emplace_back(matrix[i][right]);
            }
            if(--right<left) break;
            for(int j=right;j>=left;j--)
            {
                res.emplace_back(matrix[down][j]);
            }
            if(--down<up) break;
            for(int i=down;i>=up;i--)
            {
                res.emplace_back(matrix[i][left]);
            }
            if(++left>right) break;
        }
        return res;
    }
};
```
## 面试题30：[包含min函数的栈](https://leetcode-cn.com/problems/bao-han-minhan-shu-de-zhan-lcof/)
```c++
class MinStack {
    public:
        stack<int> st;
        stack<int> minSt;
public:
    /** initialize your data structure here. */
    MinStack() {

    }
    
    void push(int x) {
        st.push(x);
        if(minSt.empty())
            minSt.push(x);
        else
            minSt.push(std::min(minSt.top(),x));
    }
    
    void pop() {
        st.pop();
        minSt.pop();
    }
    
    int top() {
        return st.top();
    }
    
    int min() {
       return minSt.top();
    }
};
```
## 面试题31：[栈的压入、弹出序列](https://leetcode-cn.com/problems/zhan-de-ya-ru-dan-chu-xu-lie-lcof/)
```c++
class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
    int len=pushed.size();
    if(len==0) return true;
    stack<int> st;
    int indexPush=0,indexPop=0;
    while(true)
    {
        if(st.empty()&&indexPush<len)
        {
            st.push(pushed[indexPush++]);
        }
        if(popped[indexPop]==st.top())
        {
            st.pop();
            if(++indexPop==len)
                break;
        }
        else
        {
            if(indexPush<len)
            {
                st.push(pushed[indexPush++]);
            }
            else
            {
                break;
            }
        }
    }
    if(indexPush==len&&indexPop==len) return true;
    return false;
    }
};
```

## 面试题32：[从上到下打印二叉树](https://leetcode-cn.com/problems/cong-shang-dao-xia-da-yin-er-cha-shu-ii-lcof/)
相同题目：[二叉树的层序遍历](#102)
```c++
class Solution {
public:
void traversal(TreeNode* root,int depth,vector<vector<int>>& rs)
{
    if(!root) return;
    if(depth==rs.size())
        rs.emplace_back(vector<int>{});
    if(depth>rs.size())
        return;
    rs[depth].emplace_back(root->val);
    traversal(root->left,depth+1,rs);
    traversal(root->right,depth+1,rs);
}
vector<vector<int>> levelOrder(TreeNode *root)
{
    vector<vector<int>> rs;
    traversal(root,0,rs);
    return rs;
}
};
```
## 面试题32-III：[从上到下打印二叉树II](https://leetcode-cn.com/problems/cong-shang-dao-xia-da-yin-er-cha-shu-iii-lcof/)
```c++
 class Solution{
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if(root == NULL){
            return ans;
        }
        queue<TreeNode*> q;
        q.push(root);
        bool isLeft = false;
        while(!q.empty()){
            int rowLen = q.size();
            vector<int> temp;
            for(int i = 0; i < rowLen; ++i){
                TreeNode* curNode = q.front();
                q.pop();
                if(curNode != NULL){
                    temp.push_back(curNode->val);
                    if(curNode->left)q.push(curNode->left);
                    if(curNode->right)q.push(curNode->right);
                }
            }
            isLeft = !isLeft;
            if(!isLeft){
                ans.push_back(vector<int>(temp.rbegin(), temp.rend()));
            }else{
                ans.push_back(temp);
            }
        }
        return ans;
 }
};
```
## 面试题33：[二叉搜索树的后序遍历序列](https://leetcode-cn.com/problems/er-cha-sou-suo-shu-de-hou-xu-bian-li-xu-lie-lcof/)
```c++
//递归法
class Solution {
public:
    bool traversal(const vector<int>& postorder,int left,int right)
{
    if(left>=right) return true;
    int rootVal=postorder[right];
    int start=left;
    while(start<right&&postorder[start]<rootVal) ++start;
    for(int i=start;i<right;++i)
    {
        if(postorder[i]<=rootVal)
            return false;
    }
    return traversal(postorder,left,start-1)&&traversal(postorder,start,right-1);
}
bool verifyPostorder(vector<int> &postorder)
{
    return traversal(postorder,0,postorder.size()-1);
} 
};

//辅助栈
class Solution {
public:
    bool verifyPostorder(vector<int>& postorder) {
        stack<int> st;
        int rootVal=INT_MAX;
        for(auto it=postorder.rbegin();it!=postorder.rend();++it)
        {
            //左子树大于root值，所以返回false
            if(*it>rootVal)
                return false;
            //压入root的右节点树
            //*it<st.top()表示是root->right的左树节点
            //排空root->right->right的右树节点
            while(!st.empty()&&*it<st.top())
            {
                rootVal=st.top();
                st.pop();
            }
            //更新根节点的值为root->right->val
            st.push(*it);//压入
        }
        return true;
    }
};
```
## 面试题34：[二叉树中和为某一值的路径](https://leetcode-cn.com/problems/er-cha-shu-zhong-he-wei-mou-yi-zhi-de-lu-jing-lcof/)
```c++
//递归
class Solution {
public:
    vector<vector<int>> res;
    vector<int> vec;
    void dfs(TreeNode* root,int target)
    {
        if(!root) return;
        vec.push_back(root->val);
        target-=root->val;
        if(!root->left&&!root->right&&target==0)
        {
            res.push_back(vec);
        }
        dfs(root->left,target);
        dfs(root->right,target);
        vec.pop_back();
    }
    vector<vector<int>> pathSum(TreeNode *root, int target)
    {
        dfs(root,target);
        return res;
    }
};
```
## 面试题35：[复杂链表的复制](https://leetcode-cn.com/problems/fu-za-lian-biao-de-fu-zhi-lcof/)
```c++
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(head == nullptr) return nullptr;
        Node* cur = head;
        unordered_map<Node*, Node*> map;
        // 3. 复制各节点，并建立 “原节点 -> 新节点” 的 Map 映射
        while(cur != nullptr) {
            map[cur] = new Node(cur->val);
            cur = cur->next;
        }
        cur = head;
        // 4. 构建新链表的 next 和 random 指向
        while(cur != nullptr) {
            map[cur]->next = map[cur->next];
            map[cur]->random = map[cur->random];
            cur = cur->next;
        }
        // 5. 返回新链表的头节点
        return map[head];
    }
};
```
## 面试题36：[二叉搜索树和双向链表](https://leetcode-cn.com/problems/er-cha-sou-suo-shu-yu-shuang-xiang-lian-biao-lcof/)
```c++
class Solution {
public:
    Node *pre, *head;
    Node* treeToDoublyList(Node* root) {
        if(root==NULL) return NULL;
        dfs(root);
        head->left=pre;
        pre->right=head;
        return head;
    }

    void dfs(Node* cur){
        if(cur==NULL) return;
        dfs(cur->left);
        if(pre!=NULL) pre->right=cur;
        else head=cur;
        cur->left=pre;
        pre=cur; 
        dfs(cur->right);
    }
};
```
## 面试题37：[序列化二叉树](https://leetcode-cn.com/problems/xu-lie-hua-er-cha-shu-lcof/)
```c++
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string data;
        queue<TreeNode*> que;
        if (root) que.push(root);
        
        while (!que.empty()) {
            auto curr = que.front();
            que.pop();
            
            if (curr) {
                data += to_string(curr->val) + ',';
                que.push(curr->left);
                que.push(curr->right);
            } else {
                data += "null,";
            }
        }
        
        if (!data.empty()) data.pop_back();
        return data;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        unique_ptr<TreeNode> dummy(new TreeNode(0));
        queue<TreeNode*> que;
        que.push(dummy.get());
        size_t beg = 0, end = 0;
        bool left_side = false;
        
        while (beg < data.size()) {
            while (end < data.size() && data[end] != ',') ++end;
            auto str = data.substr(beg, end - beg);
            TreeNode *node = nullptr;
            if (str != "null") node = new TreeNode(atoi(str.c_str()));
            
            auto curr = que.front();
            if (left_side) {
                curr->left = node;
            } else {
                curr->right = node;
                que.pop();
            }
            
            if (node) que.push(node);
            left_side = !left_side;
            beg = ++end;
        }
        
        return dummy->right;
    }
};
```
## 面试题38：[字符串的排列](https://leetcode-cn.com/problems/zi-fu-chuan-de-pai-lie-lcof/)
```c++
class Solution {
public:
    vector<string> res;
    string path="";
    void dfs(const string& s,vector<bool>& used,int index) 
    {
        if(path.size()==s.size())
        {
            res.emplace_back(path);
            return;
        }
        for(int i=0;i<s.size();i++)
        {
            if(used[i]==true)
            {
                continue;
            }
            if(i>0&&used[i-1]==false&&s[i]==s[i-1])
            {
                continue;
            }
            used[i]=true;
            path+=s[i];
            dfs(s,used,index+1);
            path.pop_back();
            used[i]=false;
        }
    }
    vector<string> permutation(string s) {
        if(s.size()==0) return res;
        vector<bool> used(s.size(),false);
        sort(s.begin(),s.end());
        dfs(s,used,0);
        return res;
    }
};
```
## 面试题39：[数组中出现次数超过一半的数字](https://leetcode-cn.com/problems/shu-zu-zhong-chu-xian-ci-shu-chao-guo-yi-ban-de-shu-zi-lcof/)
```c++
//摩尔投票法
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int x = 0, votes = 0;
        for(int num : nums){
            if(votes == 0) x = num;
            votes += num == x ? 1 : -1;
        }
        return x;
    }
};
//链接：https://leetcode-cn.com/problems/shu-zu-zhong-chu-xian-ci-shu-chao-guo-yi-ban-de-shu-zi-lcof/solution/mian-shi-ti-39-shu-zu-zhong-chu-xian-ci-shu-chao-3/
```
## 面试题40：[最小的k个数](https://leetcode-cn.com/problems/zui-xiao-de-kge-shu-lcof/)
```c++
//自定义快排
class Solution {
public:
 vector<int> getLeastNumbers(vector<int>& arr, int k) 
{
    mySort(arr,0,arr.size()-1);
    vector<int> res;
    res.assign(arr.begin(),arr.begin()+k);
    return res;
}
private:
    void mySort(vector<int>& arr,int left,int right)
{
    if(left>=right) return;
    int i=left,j=right;
    while(i<j)
    {
        while(i<j&&arr[j]>=arr[left]) --j;
        while(i<j&&arr[i]<=arr[left]) ++i;
        swap(arr[i],arr[j]);
    }
    swap(arr[i],arr[left]);//此时i=j
    mySort(arr,left,i-1);
    mySort(arr,i+1,right);
}
};
//小顶堆
class Solution {
public:
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        vector<int> res;
        if(k==0) return res;
        priority_queue<int,vector<int>,greater<int>> que;
        for(auto i:arr)
        {
            que.push(i);
        }
        for(int i=0;i<k;i++)
        {
            res.emplace_back(que.top());
            que.pop();
        }
        return res;
    }
};
```
## 面试题41：[数据流中的中位数](https://leetcode-cn.com/problems/shu-ju-liu-zhong-de-zhong-wei-shu-lcof/)
```c++
class MedianFinder {
private:
    priority_queue<int,vector<int>,less<int>> small;//存储最小一半，使用大顶堆(堆顶为中位数)
    priority_queue<int,vector<int>,greater<int>> big;//存储最大一半，使用小顶堆(堆顶为中位数)
    int n=0;//n为数量
public:
    /** initialize your data structure here. */
    MedianFinder() {}
    
    void addNum(int num) {
        if(small.empty())
        {
            small.push(num);
            ++n;
            return;
        }
        if(num<=small.top())//num比中位数小，放到small堆里
        {
            small.push(num);
            ++n;
        }
        else
        {
            big.push(num);
            ++n;
        }
        //small和big相差2个数字，需要重新排序
        if(small.size()-big.size()==2)
        {
            big.push(small.top());
            small.pop();
        }
        if(big.size()-small.size()==2)
        {
            small.push(big.top());
            big.pop();
        }
    }
    
    double findMedian() {
        if(n%2)
        {
            if(small.size()>big.size()) return small.top();
            return big.top();
        }
        else
        {
            return ((long long)small.top() + big.top()) * 0.5;
    }
    }
};
```
## 面试题42：[连续子数组的最大和](https://leetcode-cn.com/problems/lian-xu-zi-shu-zu-de-zui-da-he-lcof/)
```c++
//动态规划
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
    if(nums.size()<=1) return nums[0];
    vector<int> dp(2,0);
    dp[0]=nums[0];
    int ret=dp[0];
    for(int i=1;i<nums.size();i++)
    {
        dp[1]=max(dp[0]+nums[i],nums[i]);
        ret=max(ret,dp[1]);
        dp[0]=dp[1];
    }
    return ret;
    }
};
```
## 面试题43：[1~n整数中1出现的次数](https://leetcode-cn.com/problems/1nzheng-shu-zhong-1chu-xian-de-ci-shu-lcof/)
```c++
class Solution {
public:
    int countDigitOne(int n) {
       int count = 0;
       long i = 1;//指向遍历的位数，如i=1即个位，i=10即十位，...，因为n可以有31位，所以10^31用long存储
       while(n/i!=0){
           //n/i控制遍历的次数，将所有的位数都遍历完毕
            long high = n/(10*i);//将当前位之前的所有高位都存在high中
            long cur = (n/i)%10;//将当前位记录在cur中，即我们每次都需要统计当前位上1出现的次数
            long low = n-(n/i)*i;
            if(cur == 0){
                count += high * i;
            } else if(cur == 1){
                count += high * i + low + 1;
            } else {
                count += high * i + i;
            }
            i = i * 10;//准备遍历下一位
       }
       return count;
    }
};
// 作者：lu-yang-shan-yu
// 链接：https://leetcode-cn.com/problems/1nzheng-shu-zhong-1chu-xian-de-ci-shu-lcof/solution/c-cong-ge-wei-bian-li-dao-zui-gao-wei-yi-ci-qiu-ji/
```
## 面试题44：[数字序列中某一位数字](https://leetcode-cn.com/problems/shu-zi-xu-lie-zhong-mou-yi-wei-de-shu-zi-lcof/)
```c++
class Solution {
public:
    int findNthDigit(int n) {
    int digit=1;//记录数字位数
    long long start=1;//记录n所在数字
    long long count=9;//记录数位个数
    while(n>count)
    {
        n-=count;
        start*=10;
        digit++;
        count=9*start*digit;
    }
    int num=start+(n-1)/digit;
    string num_s=to_string(num);
    int index=(n-1)%digit;
    return num_s[index]-'0';
    }
};
//参考网址：https://leetcode-cn.com/problems/shu-zi-xu-lie-zhong-mou-yi-wei-de-shu-zi-lcof/solution/mian-shi-ti-44-shu-zi-xu-lie-zhong-mou-yi-wei-de-6/
```
## 面试题45：[把数组排成最小的数](https://leetcode-cn.com/problems/ba-shu-zu-pai-cheng-zui-xiao-de-shu-lcof/)
```c++
class Solution {
public:
    void quickSort(vector<string>& strs,int left,int right)
{
    if(left>=right) return;
    int i=left,j=right;
    while(i<j)
    {
        while(strs[j]+strs[left]>=strs[left]+strs[j]&&i<j) --j;
        while(strs[i]+strs[left]<=strs[left]+strs[i]&&i<j) ++i;
        swap(strs[i],strs[j]);
    }
    swap(strs[left],strs[i]);
    quickSort(strs,left,i-1);
    quickSort(strs,i+1,right);
}
string minNumber(vector<int>& nums)
{
    vector<string> strs;
    string res;
    for(int i=0;i<nums.size();i++)
    {
        strs.emplace_back(to_string(nums[i]));
    }
    quickSort(strs,0,strs.size()-1);
    for(string s:strs)
        res+=s;
    return res;
}
};
//lambda表达式
class Solution {
public:
    struct cmp{
        bool operator()(string s1, string s2){
            return s1 + s2 < s2 + s1;
        }
    };
    string minNumber(vector<int>& nums) {
        vector<string> strs;
        string ans;
        for(int i = 0; i < nums.size(); i++){
            strs.push_back(to_string(nums[i]));
        }

        sort(strs.begin(), strs.end(), cmp());

        for(int i = 0; i < strs.size(); i++){
            ans += strs[i];
        }

        return ans;
    }
};
```

## 面试题46：[把数字翻译为字符串](https://leetcode-cn.com/problems/ba-shu-zi-fan-yi-cheng-zi-fu-chuan-lcof/)
```c++
class Solution {
public:
int translateNum(int num)
{
    if(num<10) return 1;
    //0-25编号一共26个英文字母
    if(num%100<10||num%100>25)//表示只能单字符
        return translateNum(num/10);
    else
        return translateNum(num/10)+translateNum(num/100);
}
};
//参考网址：https://leetcode-cn.com/problems/ba-shu-zi-fan-yi-cheng-zi-fu-chuan-lcof/solution/cjian-ji-dai-ma-shuang-bai-by-orangeman/
//动态规划
class Solution {
public:
    int translateNum(int num) {
        // 0 - 25;
        //类似于跳台阶，只能一步或者两步跳
        string s = to_string(num);
        int n = s.size();
        vector<int>dp (n + 1, 1);
        //dp[0]无意义，dp[1]表示第一个数字字符
        for(int i = 2; i <= n; i++){
            int sum = (s[i - 2] - '0') * 10 + s[i - 1] - '0';
            if(sum >= 10 && sum <= 25) dp[i] = dp[i - 1] + dp[i - 2];
            else dp[i] = dp[i - 1];
        }
        return dp[n];
    }
};
```
## 面试题47：[礼物的最大价值](https://leetcode-cn.com/problems/li-wu-de-zui-da-jie-zhi-lcof/)
```c++
//滑动窗口
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
    if (s.empty())
        return 0;
    if (s.size() == 1)
        return 1;
    int res = 0, left = -1;
    unordered_map<char, int> hash;
    for (int i = 0; i < s.length(); i++)
    {
        if (hash.find(s[i]) != hash.end())
        {
            left = max(hash[s[i]], left);
        }
        hash[s[i]] = i;
        res = max(res, i - left);
    }
    return res;
    }
};
```
## 面试题48：[最长不含重复字符的子字符串](https://leetcode-cn.com/problems/zui-chang-bu-han-zhong-fu-zi-fu-de-zi-zi-fu-chuan-lcof/)
```c++
//滑动窗口
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
int len=s.size();
    int start(0),end(0),res(0),length(0);
    while(end<len)
    {
        char tmp=s[end];
        for(int index=start;index<end;index++)
        {
            if(tmp==s[index])
            {
                start=index+1;
                length=end-start;
                break;
            }
        }
        end++;
        length++;
        res=max(res,length);
    }
    return res;
    }
};
```
## 面试题49：[丑数](https://leetcode-cn.com/problems/chou-shu-lcof/)
```c++
class Solution {
public:
int min(int a,int b,int c)
{
    a=a>b?b:a;
    return a>c?c:a;
}
int nthUglyNumber(int n)
{
    vector<int> dp(n,1);
    int a(0),b(0),c(0);
    for(int i=1;i<n;i++)
    {
        dp[i]=min(dp[a]*2,dp[b]*3,dp[c]*5);
        if(dp[i]==(dp[a]*2)) ++a;
        if(dp[i]==(dp[b]*3)) ++b;
        if(dp[i]==(dp[c]*5)) ++c;
    }
    return dp[n-1];
}
};
```
## 面试题50：[第一个只出现一次的字符](https://leetcode-cn.com/problems/di-yi-ge-zhi-chu-xian-yi-ci-de-zi-fu-lcof/)
```c++
class Solution {
public:
    char firstUniqChar(string s) {
    unordered_map<char,int> umap;
    for(char i:s)
    {
        umap[i]++;
    }
    for(int i=0;i<s.size();i++)
    {
        if(umap[s[i]]==1)
            return s[i];
    }
    return ' ';
    }
};
```
## 面试题51：[数组中的逆序对](https://leetcode-cn.com/problems/shu-zu-zhong-de-ni-xu-dui-lcof/)
```c++
//参考网址：https://leetcode-cn.com/problems/shu-zu-zhong-de-ni-xu-dui-lcof/solution/jian-zhi-offer-51-shu-zu-zhong-de-ni-xu-pvn2h/
class Solution {
public:
    int merge_sort(int left, int right, vector<int> &nums, vector<int> &saveNums)
{
    if (left >= right)
        return 0;
    int mid = (left + right) >> 1;
    int res = merge_sort(left, mid, nums, saveNums) + merge_sort(mid + 1, right, nums, saveNums);
    //保存数组
    for (int i = left; i <= right; i++)
    {
        saveNums[i] = nums[i];
    }
    int i = left;    //左集合的起点
    int j = mid + 1; //右集合的起点
    for (int k = left; k <= right; k++)
    {
        if (i == mid + 1) //右集合使用完毕
        {
            nums[k] = saveNums[j++];
        }
        //左集合使用完毕或在左集合小于右集合
        else if (j == right + 1 || saveNums[i] <= saveNums[j])
        {
            nums[k] = saveNums[i++];
        }
        else //右集合大于左集合
        {
            nums[k] = saveNums[j++];
            res += mid - i + 1;
        }
    }
    return res;
}
int reversePairs(vector<int> &nums)
{
    vector<int> vec(nums.size());
    return merge_sort(0, nums.size() - 1, nums, vec);
}
};
```
## 面试题52：[两个链表的第一个公共节点](https://leetcode-cn.com/problems/liang-ge-lian-biao-de-di-yi-ge-gong-gong-jie-dian-lcof/)
```c++
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *node1 = headA;
        ListNode *node2 = headB;
        
        while (node1 != node2) {
            node1 = node1 != NULL ? node1->next : headB;
            node2 = node2 != NULL ? node2->next : headA;
        }
        return node1;
    }
};
```
## 面试题53：[在排序数组中查找数字I](https://leetcode-cn.com/problems/zai-pai-xu-shu-zu-zhong-cha-zhao-shu-zi-lcof/)
```c++
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left=0,right=nums.size()-1;
        if(nums.empty()) return 0;
        int pos=-1;
        while(left<=right)
        {
            int mid=left+((right-left)>>1);
            if(nums[mid]>target)
            {
                right=mid-1;
            }
            else if(nums[mid]<target)
            {
                left=mid+1;
            }
            else
            {
                pos=mid;
                break;
            }
        }
        if(pos==-1) return 0;
        int i=pos,j=pos;
        while(i>=0&&nums[i]==target) i--;
        while(j<nums.size()&&nums[j]==target) j++;
        return j-i-1;
    }
};
```
## 面试题53-II：[0~n-1中缺失的数字](https://leetcode-cn.com/problems/que-shi-de-shu-zi-lcof/)
```c++
//二分法
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int left=0,right=nums.size()-1;
        while(left<=right)
        {
            int mid=left+((right-left)>>1);
            if(nums[mid]==mid)
            {
                left=mid+1;
            }
            else if(nums[mid]>mid)
            {
                right=mid-1;
            }
        }
        return left;
    }
};
//最佳写法
class Solution {
public:
     int missingNumber(vector<int>& nums) {
        if (nums[0]==1) return 0;
        for (int i = 0;i<nums.size();i++){
            if (nums[i]!=i) return i;
        }
        return nums.size();
    }
};
```
## 面试题54：[二叉搜索树的第K大节点](https://leetcode-cn.com/problems/er-cha-sou-suo-shu-de-di-kda-jie-dian-lcof/)
```c++
class Solution {
public:
    int res;
    void dfs(TreeNode* root,int &k)
    {
        if(!root) return;
        dfs(root->right,k);
        --k;
        if(k==0) 
        {
            res=root->val;
            return;
        }
        dfs(root->left,k);
    }
    int kthLargest(TreeNode* root, int k) {
        dfs(root,k);
        return res;
    }
};
```
## 面试题55-I：[二叉树的深度](https://leetcode-cn.com/problems/er-cha-shu-de-shen-du-lcof/)
```c++
//递归
class Solution {
public:
    int getDepth(TreeNode* node)
    {
        if(!node) return 0;
        int leftDepth=getDepth(node->left);
        int rightDepth=getDepth(node->right);
        int depth=1+max(leftDepth,rightDepth);
        return depth;
    }
    int maxDepth(TreeNode* root) {
        return getDepth(root);
    }
};
```
## 面试题55-II：[平衡二叉树](https://leetcode-cn.com/problems/ping-heng-er-cha-shu-lcof/)
```c++
class Solution {
public:
    int getDepth(TreeNode* root)
    {
        if(!root) return 0;
        int left=getDepth(root->left);
        if(left==-1) return -1;
        int right=getDepth(root->right);
        if(right==-1) return -1;
        return abs(left-right)>1?-1:1+max(left,right);
    }
    bool isBalanced(TreeNode* root) {
        return getDepth(root)==-1?false:true;
    }
};
```
## 面试题56-I：[数组中数字出现的次数](https://leetcode-cn.com/problems/shu-zu-zhong-shu-zi-chu-xian-de-ci-shu-lcof/)
```c++
class Solution {
public:
    vector<int> singleNumbers(vector<int>& nums) {
        int a=0,b=0;
        int a_b=0,aDifb=1;
        //0^(异或)任何数都为原来的数
        //a^a=0
        //a_b表示最后剩下a异或b的值
        //aDifb表示在某一位置上a和b异或为1，及a和b在某一位置上不同，作为分界线
        for(int num:nums)
            a_b^=num;
        while((a_b&aDifb)==0)
            aDifb<<=1;//找到为1的位置
        for(int num:nums)
        {
            if(num&aDifb)
                a^=num;
            else
                b^=num;
        }
        return vector<int>{a,b};
    }
};
```
## 面试题56-II：[数组中数字出现的次数II](https://leetcode-cn.com/problems/shu-zu-zhong-shu-zi-chu-xian-de-ci-shu-ii-lcof/)
```c++
class Solution
{
public:
    int singleNumber(vector<int> &nums)
    {
        int bits[32] = {0};
        for (int i = 0; i < nums.size(); i++)
        {
            int j = 0;
            while (nums[i])
            {
                bits[j++] += nums[i] % 2;
                nums[i] >>= 1;
            }
        }
        //得到二进制上各位数之和
        int ans = 0;
        //二进制装十进制并%n位数
        for (int i = 0; i < 32; i++)
        {
            ans+=(1<<i)*(bits[i]%3);
        }
        return ans;
    }
};
```
## 面试题57：[和为s的两个数字](https://leetcode-cn.com/problems/he-wei-sde-liang-ge-shu-zi-lcof/)
```c++
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int left=0,right=nums.size()-1;
        while(left<right)
        {
            if(target-nums[left]<nums[right])
            {
                right--;
            }
            else if(target-nums[left]>nums[right])
            {
                left++;
            }
            else
            {
                return {nums[left],nums[right]};
            }
        }
        return vector<int>{};
    }
};
```
## 面试题57-II：[和为s的连续正数序列](https://leetcode-cn.com/problems/he-wei-sde-lian-xu-zheng-shu-xu-lie-lcof/)
```c++
class Solution {
public:
    vector<vector<int>> findContinuousSequence(int target) {
       vector<vector<int>> res;
       int left=1,right=1;
       int saveTarget=target;
        while(left<=(saveTarget>>1))
        {
            if(target>0)
            {
                target-=right++;
            }
            else if(target<0)
            {
                target+=left++;
            }
            else
            {
                vector<int> tmp;
                for(int i=left;i<right;i++)
                {
                    tmp.emplace_back(i);
                }
                res.emplace_back(tmp);
                target+=left++;
            }
        }
        return res;
    }
};
```

## 面试题58-I：[翻转单词顺序](https://leetcode-cn.com/problems/fan-zhuan-dan-ci-shun-xu-lcof/)
```c++
//头文件<sstream>
//stringstream的使用
class Solution {
public:
    string reverseWords(string s) {
       stringstream istr(s);
       string res,word;
       while(istr>>word)
       {
           res=word+" "+res;
       }
       res.pop_back();
       return res;
    }
};
//双指针用法
class Solution {
public:
    string reverseWords(string s) {
        int left=s.size()-1;
        int right=left;
        string res;
        while(left>=0)
        {
            while(s[left]==' ')
            {
                --left;
                right=left;
                if(left<0) break;
            }
            if(left<0) break;
            while(s[left]!=' ')
            {
                --left;
                if(left<0) break;
            }
            res+=s.substr(left+1,right-left)+" ";
            right=left;
        }
        return res.substr(0,res.size()-1);
    }
};
```
## 面试题58-II：[左旋转字符串](https://leetcode-cn.com/problems/zuo-xuan-zhuan-zi-fu-chuan-lcof/)
```c++
class Solution {
public:
    string reverseLeftWords(string s, int n) {
        for(int i=0;i<n;i++){
            s.push_back(s[i]);
        }
        s.erase(0,n);
        return s;
    }
};
```
## 面试题59-I：[滑动窗口的最大值](https://leetcode-cn.com/problems/hua-dong-chuang-kou-de-zui-da-zhi-lcof/)
```c++
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    int n = nums.size();
	priority_queue<pair<int, int>> q;
	for (int i = 0; i < k; ++i)
		q.emplace(nums[i], i);
	vector<int> ans = { q.top().first };
	for (int i = k; i < n; ++i)
	{
		q.emplace(nums[i], i);
		while (q.top().second <= i - k)
			q.pop();
		ans.push_back(q.top().first);
	}
	return ans;
    }
};
```
## 面试题59-II：[队列的最大值](https://leetcode-cn.com/problems/dui-lie-de-zui-da-zhi-lcof/)
```c++
class MaxQueue
{
    queue<int> que;
    deque<int> deq;
public:
    MaxQueue(){}
    int max_value()
    {
        if(deq.empty()) return -1;
        return deq.front();
    }
    void push_back(int value)
    {
        que.emplace(value);
        while(!deq.empty()&&deq.back()<value)
        {
            deq.pop_back();
        }
        deq.push_back(value);
    }
    int pop_front()
    {
        if(que.empty()) return -1;
        int ret=que.front();
        que.pop();
        if(ret==deq.front())
            deq.pop_front();
        return ret;
    }
};
```
## 面试题60：[n个骰子的点数](https://leetcode-cn.com/problems/nge-tou-zi-de-dian-shu-lcof/)
```c++
class Solution {
public:
    vector<double> dicesProbability(int n) {
        int dp[70]={0};//骰子点数和的可能方案数
        for(int i=1;i<=6;i++)
            dp[i]++;
        //从第二个骰子开始
        for(int i=2;i<=n;i++)
        {
            //从点数和最大的开始
            for(int j=6*i;j>=i;j--)
            {
                dp[j]=0;
                //一个骰子的点数
                //所有点数和范围j：[i,6*j]
                //除去第一个骰子后j的范围：[i-1,6*j-6]
                //所以下面需要判断让剩余点数(点数和-当前点数，即j-cur)<i-1
                for(int cur=1;cur<=6;cur++)
                {
                    if(j-cur<i-1) break;
                    dp[j]+=dp[j-cur];
                }
            }
        }
        int all=pow(6,n);
        vector<double> ret;
        for(int i=n;i<=6*n;i++)
            ret.emplace_back(dp[i]*1.0/all);
        return ret;
    }
};
```
## 面试题61：[扑克牌中的顺子](https://leetcode-cn.com/problems/bu-ke-pai-zhong-de-shun-zi-lcof/)
```c++
class Solution {
public:
    bool isStraight(vector<int>& nums) {
        bool card[15]={false};
        int minVal=14,maxVal=0;
        for(int num:nums)
        {
            if(num==0) continue;
            if(card[num]) return false;
            card[num]=true;
            minVal=min(minVal,num);
            maxVal=max(maxVal,num);
        }
        return maxVal-minVal<5;
    }
};
```
## 面试题62：[圆圈中最后剩下的数字](https://leetcode-cn.com/problems/yuan-quan-zhong-zui-hou-sheng-xia-de-shu-zi-lcof/)
```c++
//参考网站：https://blog.csdn.net/u011500062/article/details/72855826
class Solution {
public:
    int lastRemaining(int n, int m) {
        //dp[i]：表示最后胜利的人位置，i表示当前人数
        int dp[n+1];
        //初始化dp，当人数为1时，获胜的人位置为0
        dp[1]=0;
        for(int i=2;i<=n;i++)
        {
            //参考网址：https://blog.csdn.net/u011500062/article/details/72855826
            //解释：当人数为2时，相当于将人数为1时获胜位置0向右移动m位，
            //此时胜利位置为(人数为0时的胜利位置)0+m(移动位数)，
            //但是为了防止数组越界，需要对人数取余(%i)
            //综上所述，dp[i]=(dp[i-1]+m)%i
            dp[i]=(dp[i-1]+m)%i;
        }
        return dp[n];
    }
};
```
## 面试题63：[股票的最大利润](https://leetcode-cn.com/problems/gu-piao-de-zui-da-li-run-lcof/)
```c+
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len=prices.size();
        if(len<=1) return 0;
        //dp[0][0]表示持有股票，dp[0][1]表示未持有股票
        vector<vector<int>> dp(2,vector<int>(2,0));
        dp[0][0]=-prices[0];
        for(int i=1;i<len;i++)
        {
            dp[i%2][0]=max(dp[(i-1)%2][0],-prices[i]);
            dp[(i%2)][1]=max(dp[(i-1)%2][1],dp[(i-1)%2][0]+prices[i]);
        }
        return dp[(len-1)%2][1];
    }
};
```
## 面试题64：[求1+2+...+n](https://leetcode-cn.com/problems/qiu-12n-lcof/)
```c++
class Solution {
public:
    int sumNums(int n) {
        //如果n为0返回0，然后从1开始计算
        n && (n += sumNums(n-1));
        return n;
    }
};
```
## 面试题65：[不用加减乘除做加法](https://leetcode-cn.com/problems/bu-yong-jia-jian-cheng-chu-zuo-jia-fa-lcof/)
```c++
class Solution {
public:
    int add(int a, int b) {
        if (a == 0 || b == 0) {
            return a == 0 ? b : a;
        }

        int sum = 0, carry = 0;

        while (b != 0) { // 当没有进位的时候退出循环
            sum = a ^ b; 
            carry = (unsigned int) (a & b) << 1; // C++ 不允许负数进行左移操作，故要加 unsigned int

            a = sum;
            b = carry;
        }

        return a;
    }
}
// 链接：https://leetcode-cn.com/problems/bu-yong-jia-jian-cheng-chu-zuo-jia-fa-lcof/solution/zi-jie-ti-ku-jian-65-jian-dan-bu-yong-ji-5k3q/
```
## 面试题66：[构建乘积数组](https://leetcode-cn.com/problems/gou-jian-cheng-ji-shu-zu-lcof/)
```c++
class Solution {
public:
    vector<int> constructArr(vector<int>& a) {
        int n = a.size();
        vector<int> ret(n, 1);
        int left = 1;
        for (int i = 0; i < n; i ++) {
            ret[i] = left;
            left = left * a[i];
        } 
        int right = 1;
        for (int i = n-1; i >= 0; i --) {
            ret[i] *= right;
            right *= a[i];
        }
        return ret;
    }
};
//链接：https://leetcode-cn.com/problems/gou-jian-cheng-ji-shu-zu-lcof/solution/gou-jian-cheng-ji-shu-zu-dui-cheng-bian-li-by-huwt/
```
## 面试题67：[把字符串变为整数](https://leetcode-cn.com/problems/ba-zi-fu-chuan-zhuan-huan-cheng-zheng-shu-lcof/)
```c++
class Solution {
public:
    int strToInt(string str) {
        int i = 0, flag = 1;
        int res=0;
        while (str[i] == ' ') i ++;
        if (str[i] == '-') flag = -1;
        if (str[i] == '-' || str[i] == '+') i ++;
        for (; i < str.size(); i++)  {
            if(str[i]<'0'||str[i]>'9') break;
            if(res>INT_MAX/10||(res==INT_MAX/10&&str[i]-'0'>7))
                return flag==1?INT_MAX:INT_MIN;
            res = res * 10 + (str[i] - '0');
        } 
        return flag * res;
    }
};
```
## 面试题68-I：[二叉搜索树的最近公共祖先](https://leetcode-cn.com/problems/er-cha-sou-suo-shu-de-zui-jin-gong-gong-zu-xian-lcof/)
```c++
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* ancestor = root;
        while (true) {
            if (p->val < ancestor->val && q->val < ancestor->val) {
                ancestor = ancestor->left;
            }
            else if (p->val > ancestor->val && q->val > ancestor->val) {
                ancestor = ancestor->right;
            }
            else {
                break;
            }
        }
        return ancestor;
    }
};
```
## 面试题69-II：[二叉树的最近公共祖先](https://leetcode-cn.com/problems/er-cha-shu-de-zui-jin-gong-gong-zu-xian-lcof/)
```c++
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root==NULL||p==root||q==root)
        {
            return root;
        }
        TreeNode* left=lowestCommonAncestor(root->left,p,q);
        TreeNode* right=lowestCommonAncestor(root->right,p,q);
        if(!left&&!right) return NULL;
        if(!left) return right;
        if(!right) return left;
        return root;
        // return left==NULL?right:(right==NULL?left:root);
    }
};
```
