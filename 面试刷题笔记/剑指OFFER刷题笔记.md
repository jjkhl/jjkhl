# ��ָOFFER
## �ڶ���
### ������1����ֵ���㺯��
ΪCMyString��������Ӹ�ֵ���������
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
����һ��
```c++
CMyString& CMyString::operator=(const CMyString& str)
	{
		if(this==&str)
			return *this;//this��str����Ϊͬһ��ʵ��������ǰ�ռ�ᱻdelete
		delete[] m_pData;
		m_pData=nullptr;

		m_pData=new char[strlen(m_pData)+1];//����ʧ���׳��쳣��ô��
		strcpy(m_pData,str.m_pData);

		return *this;
	}
```
��ѷ������ȴ���һ����ʱʵ�����ڽ�����ʱʵ����ԭ��ʵ����
```c++
CMyString& CMyString::operator=(const CMyString& str)
{
    //��һ��������temp��ʱ������temp.m_pDataָ��str.m_pData�ĵ�ַ(A)
    //�ڶ���������data_t��ʱ����(��ַB)������ָ��temp.m_pData�ĵ�ַ(A)
    //���������õ�ַA(temp.m_pData��ַ)ָ��m_pData�ĵ�ַ(C)
    //��ʱ��data_t(��ַA,str�ĵ�ַ)��temp.mpData(��ַC,ԭthisָ���ַ),m_pData(��ַB,ԭdata_t�ĵ�ַ,ָ��str.m_pData)
    //������ʱ����ʱ���󶼻ᱻ�ͷŵ�������ַC��delete����ַC��Ϊ��ֻ�����Զ��޷����в�����
    if(this!=&str)
    {
        CMyString temp(str);
        char* data_t=temp.m_pData;//�൱��new�ռ�
        temp.m_pData=m_pData;//�൱��delete[] m_pData;
        m_pData=data_t;
    }
    return *this;
}
```
## ������2��ʵ��[Singletonģʽ](https://www.cnblogs.com/sunchaothu/p/10389842.html#%E4%B8%80%E4%BB%80%E4%B9%88%E6%98%AF%E5%8D%95%E4%BE%8B)
����1:��ȱ�ݵ�����ʽ
���ݣ�ֻ��ʹ��ʱ��ʵ������������������þͲ���ռ���ڴ�
���⣺
1.�̰߳�ȫ�����������
2.�ڴ�й©����delete���󡪡�ʹ�ù���ָ��
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
//������:constructor called!
```
����2���̰߳�ȫ���ڴ氲ȫ������ʽ����
���⣺ʹ������ָ���Ҫ���û�Ҳ��ʹ������ָ�룬�Ǳ�Ҫ��Ӧ���������Լ��; ʹ����Ҳ�п���; ͬʱ������Ҳ�����ˣ�ʵ��������ϣ��Խ��Խ�á����и������ص����⣬��ĳЩƽ̨�����������ָ��ܹ��йأ���˫������ʧЧ��
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
//�����constructor called!
//     destructor called!
```
����3���ֲ���̬����
���ͣ�����������ڳ�ʼ����ʱ�򣬲���ͬʱ����������䣬�����߳̽��������ȴ���ʼ��������������֤�˲����߳��ڻ�ȡ��̬�ֲ�������ʱ��һ���ǳ�ʼ�����ģ���<strong style="color:red">ֻ��һ�γ�ʼ��</strong>�����Ծ����̰߳�ȫ�ԣ���c++��̬�������������Ǵ����������������
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
    static Singleton& get_instance(){//�������ò��ܻ�ȡ����
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
//�����constructor called!
//     destructor called!
```
## ������3��[�������ظ�������](https://leetcode-cn.com/problems/shu-zu-zhong-zhong-fu-de-shu-zi-lcof/)
[˼·��ַ](https://leetcode-cn.com/problems/shu-zu-zhong-zhong-fu-de-shu-zi-lcof/solution/mian-shi-ti-03-shu-zu-zhong-zhong-fu-de-shu-zi-yua/)
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
## ������4��[��ά�����еĲ���](https://leetcode-cn.com/problems/er-wei-shu-zu-zhong-de-cha-zhao-lcof/)
```c++
//���½ǲ���
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
//���Ͻǲ���
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
## ������5��[�滻�ո�](https://leetcode-cn.com/problems/ti-huan-kong-ge-lcof/)
```c++
//�⺯����ʹ��
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
//ԭ����Ķ�
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
## ������6��[��ͷ��β��ӡ����](https://leetcode-cn.com/problems/cong-wei-dao-tou-da-yin-lian-biao-lcof/)
```c++
//ʱ�任�ռ䣺�ȷ�ת����
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
//ջ��ʹ��/**
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

## ������7��[�ؽ�������](https://leetcode-cn.com/problems/zhong-jian-er-cha-shu-lcof/)
```c++
//ǰ�����������ع�������
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
## ������8��[����������һ�����](https://www.nowcoder.com/practice/9023a0c988684a53960365b889ceaf5e?tpId=13&tqId=23451&ru=/practice/6fe361ede7e54db1b84adc81d09d8524&qru=/ta/coding-interviews/question-ranking)
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
//next��ʾ���ڵ�
class Solution {
public:
    TreeLinkNode* GetNext(TreeLinkNode* pNode) {
        if (!pNode)
            return NULL;
        // ���ý�����������
        if (pNode->right) {
            TreeLinkNode* rightChild = pNode->right; 
            // Ѱ���������ϵ�������
            while (rightChild->left)
                rightChild = rightChild->left;
            return rightChild;
        }
        // ����������������Ѱ�ҵ�һ���Ҹ���
        while (pNode->next) {
            if (pNode->next->left == pNode) 
                return pNode->next; 
            pNode = pNode->next;
        }
        return NULL;
    }
};
```
## ������9��[������ջʵ�ֶ���](https://leetcode-cn.com/problems/yong-liang-ge-zhan-shi-xian-dui-lie-lcof/)
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
## ������10-I��[쳲���������](https://leetcode-cn.com/problems/fei-bo-na-qi-shu-lie-lcof/)
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
        //1000000007����Ϊ��ĿҪ��Ҫȡģ
        return dp[1];
    }
};
```
## ������10-II��[������̨������](https://leetcode-cn.com/problems/qing-wa-tiao-tai-jie-wen-ti-lcof/)
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
## ������11��[��ת�������С����](https://leetcode-cn.com/problems/xuan-zhuan-shu-zu-de-zui-xiao-shu-zi-lcof/)
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
## ������12��[�����е�·��](https://leetcode-cn.com/problems/ju-zhen-zhong-de-lu-jing-lcof/)
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
## ������13��[�����˵��˶���Χ](https://leetcode-cn.com/problems/ji-qi-ren-de-yun-dong-fan-wei-lcof/)
```c++
//�ݹ鷨
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
                vec[i][j]|=vec[i-1][j];//������
            if(j>=1)
                vec[i][j]|=vec[i][j-1];
            res+=vec[i][j];
        }
    }
    return res;
}
};
//�ݹ鷨II
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
        //dp[i][j]==true�����ø���Ҫ�Ǳ����ʹ��ͼ���
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
## ������14-I��[������](https://leetcode-cn.com/problems/jian-sheng-zi-lcof/)
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
## ������14-II��[������II](https://leetcode-cn.com/problems/jian-sheng-zi-ii-lcof/)
```c++
//̰���㷨��������ȡ3����֤���
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
## ������15��[��������1�ĸ���](https://leetcode-cn.com/problems/er-jin-zhi-zhong-1de-ge-shu-lcof/)
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
//΢��ⷨ
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
## ������16��[��ֵ�������η�](https://leetcode-cn.com/problems/shu-zhi-de-zheng-shu-ci-fang-lcof/)
```c++
//�ݹ�
class Solution {
public:
    double myPow(double x, int n) {
        if(n==0) return 1;
    else if(n==-1) return 1/x;
    //cout<<n<<"\t"<<(n&1)<<endl;
    if(n&1) return myPow(x*x,n>>1)*x;//����
    else return myPow(x*x,n>>1);//˫��
    }
};
```
## ������17��[��ӡ��1������nλ��](https://leetcode-cn.com/problems/da-yin-cong-1dao-zui-da-de-nwei-shu-lcof/)
```c++
//��Ҫ��֤���������Ҫ��char��string�ַ������д洢
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
        // ����ע�͵�ǰ�᣺���� n = 3
        if(n <= 0) return vector<int>(0);
        string s(n, '0'); // s�������999����s�ĳ���Ϊn
        while(!overflow(s)) inputNumbers(s);
        return output;
    }
    bool overflow(string& s)
    {
        // ����������ģ�����ֵ��ۼӹ��̣����ж��Ƿ�Խ�磨�� 999 + 1 = 1000������Խ�������
        bool isOverFlow = false;
        int carry = 0; // carry��ʾ��λ
        for(int i=s.length()-1; i>=0; --i)
        {
            int current = s[i] - '0' + carry; // current��ʾ��ǰ��εĲ���
            if(i == s.length() - 1) current ++; // ���i��ʱ�ڸ�λ��currentִ�� +1 ����
            if(current >= 10)
            {
                // ����i�Ѿ���������һλ�ˣ���current++֮��>=10��˵��ѭ����ͷ�ˣ���999 + 1 = 1000
                if(i == 0) isOverFlow = true;
                else
                {
                    // ֻ����ͨ��λ������current��9���10
                    carry = 1;
                    s[i] = current - 10 + '0'; 
                }
            }
            else
            {
                // ���û�н�λ������s[i]��ֵ��Ȼ��ֱ������ѭ���������Ϳ��Ի�ȥִ��inputNumbers�����ˣ�����output�����Ԫ��
                s[i] = current + '0';
                break;
            }
        }
        return isOverFlow;
    }
    void inputNumbers(string s)
    {
        // ����������ѭ����output����ӷ��ϴ�ͳ�Ķ�ϰ�ߵ�Ԫ�ء�����001�����ǻ����1������001��
        bool isUnwantedZero = true; // �ж��Ƿ��ǲ���Ҫ��ӵ�0������001ǰ�������0
        string temp = "";
        for(int i=0; i<s.length(); ++i)
        {
            if(isUnwantedZero && s[i] != '0') isUnwantedZero = false;
            if(!isUnwantedZero) temp += s[i];
        }
        output.push_back(stoi(temp));
    }
};
// ���ߣ�superkakayong
// ���ӣ�https://leetcode-cn.com/problems/da-yin-cong-1dao-zui-da-de-nwei-shu-lcof/solution/fei-zi-jie-ti-ku-jian-17-jian-dan-da-yin-cong-1dao/
```
## ������18��[ɾ������Ľڵ�](https://leetcode-cn.com/problems/shan-chu-lian-biao-de-jie-dian-lcof/)
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
## ������19��[������ʽƥ��]([������ʽƥ��](https://leetcode-cn.com/problems/zheng-ze-biao-da-shi-pi-pei-lcof/))
��ַ�Ƽ���https://leetcode-cn.com/problems/regular-expression-matching/
```c++
//�ݹ�ⷨ
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
//�ٷ����
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
## ������20��[��ʾ������ַ���](https://leetcode-cn.com/problems/biao-shi-shu-zhi-de-zi-fu-chuan-lcof/)
```c++
class Solution {
private:
    // �����ĸ�ʽ������[+|-]B��ʾ, ����BΪ�޷�������
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
    // ���ֵĸ�ʽ������A[.[B]][e|EC]����.B[e|EC]��ʾ��
    // ����A��C���������������������ţ�Ҳ����û�У�����B��һ���޷�������
    bool isNumber(string s) {
        if(s.size() == 0)
            return false;
        int index = 0;
        //�ַ�����ʼ�пո񣬿��Է���true
        while(s[index] == ' ')  //���д���û�и������
            ++index;
        bool numeric = scanInteger(s, index);
        // �������'.'�������������ֵ�С������
        if(s[index] == '.'){
            ++index;
            // ����һ�д�����||��ԭ��
            // 1. С������û���������֣�����.123����0.123��
            // 2. С����������û�����֣�����233.����233.0��
            // 3. ��ȻС����ǰ��ͺ�����������֣�����233.666
            numeric = scanUnsignedInteger(s, index) || numeric;
        }
        // �������'e'����'E'�����������ŵ������ֵ�ָ������
        if(s[index] == 'e' || s[index] == 'E'){
            ++index;
            // ����һ�д�����&&��ԭ��
            // 1. ��e��Eǰ��û������ʱ�������ַ������ܱ�ʾ���֣�����.e1��e1��
            // 2. ��e��E����û������ʱ�������ַ������ܱ�ʾ���֣�����12e��12e+5.4
            numeric = numeric && scanInteger(s ,index);
        }
         //�ַ�����β�пո񣬿��Է���true
        while(s[index] == ' ')
            ++index;
        return numeric && index == s.size();//����Ƿ����в��ֶ����ϣ���1a3ֻ�����һ����������Ȼ����a�Ͳ����������ˣ�index!=size�����Է���false
    }
};
// ���ߣ�san-he-n
// ���ӣ�https://leetcode-cn.com/problems/biao-shi-shu-zhi-de-zi-fu-chuan-lcof/solution/jian-zhi-offerguan-fang-jie-da-bu-yong-c-e2wd/
```
## ������21��[��������˳��ʹ����λ��ż��ǰ��](https://leetcode-cn.com/problems/diao-zheng-shu-zu-shun-xu-shi-qi-shu-wei-yu-ou-shu-qian-mian-lcof/)
```c++
//����ָ��
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
//��βָ��class Solution {
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
## ������22��[�����е�����k���ڵ�](https://leetcode-cn.com/problems/lian-biao-zhong-dao-shu-di-kge-jie-dian-lcof/)
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
## ������23��[��������II](https://leetcode-cn.com/problems/linked-list-cycle-ii/)
```c++
//����ָ��
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode* fast = head;
        ListNode* slow = head;
        while(fast != NULL && fast->next != NULL) {
            slow = slow->next;
            fast = fast->next->next;
            // ����ָ����������ʱ��head �� �����㣬ͬʱ����ֱ������
            if (slow == fast) {
                ListNode* index1 = fast;
                ListNode* index2 = head;
                while (index1 != index2) {
                    index1 = index1->next;
                    index2 = index2->next;
                }
                return index2; // ���ػ������
            }
        }
        return NULL;
    }
};
```
## ������24��[��ת����](https://leetcode-cn.com/problems/fan-zhuan-lian-biao-lcof/)
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
## ������25��[�ϲ��������������](https://leetcode-cn.com/problems/he-bing-liang-ge-pai-xu-de-lian-biao-lcof/)
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
## ������26��[�����ӽṹ](https://leetcode-cn.com/problems/shu-de-zi-jie-gou-lcof/)
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
             //�����ж�
             return false;
         }   
        // ���ڵ���ͬ�Ļ�ֱ�ӽ���Ƚϣ����ڵ㲻��ͬ��B�ǲ���A����/���������ӽṹ
        return hasSubStructure(A, B) || isSubStructure(A->left, B) || isSubStructure(A->right, B);
    }
};
```
## ������27��[�������ľ���](https://leetcode-cn.com/problems/er-cha-shu-de-jing-xiang-lcof/)
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
## ������28��[�ԳƵĶ�����](https://leetcode-cn.com/problems/dui-cheng-de-er-cha-shu-lcof/)
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
## ������29��[˳ʱ���ӡ����](https://leetcode-cn.com/problems/shun-shi-zhen-da-yin-ju-zhen-lcof/)
�������ͣ�[54.��������](#54)
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
## ������30��[����min������ջ](https://leetcode-cn.com/problems/bao-han-minhan-shu-de-zhan-lcof/)
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
## ������31��[ջ��ѹ�롢��������](https://leetcode-cn.com/problems/zhan-de-ya-ru-dan-chu-xu-lie-lcof/)
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

## ������32��[���ϵ��´�ӡ������](https://leetcode-cn.com/problems/cong-shang-dao-xia-da-yin-er-cha-shu-ii-lcof/)
��ͬ��Ŀ��[�������Ĳ������](#102)
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
## ������32-III��[���ϵ��´�ӡ������II](https://leetcode-cn.com/problems/cong-shang-dao-xia-da-yin-er-cha-shu-iii-lcof/)
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
## ������33��[�����������ĺ����������](https://leetcode-cn.com/problems/er-cha-sou-suo-shu-de-hou-xu-bian-li-xu-lie-lcof/)
```c++
//�ݹ鷨
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

//����ջ
class Solution {
public:
    bool verifyPostorder(vector<int>& postorder) {
        stack<int> st;
        int rootVal=INT_MAX;
        for(auto it=postorder.rbegin();it!=postorder.rend();++it)
        {
            //����������rootֵ�����Է���false
            if(*it>rootVal)
                return false;
            //ѹ��root���ҽڵ���
            //*it<st.top()��ʾ��root->right�������ڵ�
            //�ſ�root->right->right�������ڵ�
            while(!st.empty()&&*it<st.top())
            {
                rootVal=st.top();
                st.pop();
            }
            //���¸��ڵ��ֵΪroot->right->val
            st.push(*it);//ѹ��
        }
        return true;
    }
};
```
## ������34��[�������к�Ϊĳһֵ��·��](https://leetcode-cn.com/problems/er-cha-shu-zhong-he-wei-mou-yi-zhi-de-lu-jing-lcof/)
```c++
//�ݹ�
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
## ������35��[��������ĸ���](https://leetcode-cn.com/problems/fu-za-lian-biao-de-fu-zhi-lcof/)
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
        // 3. ���Ƹ��ڵ㣬������ ��ԭ�ڵ� -> �½ڵ㡱 �� Map ӳ��
        while(cur != nullptr) {
            map[cur] = new Node(cur->val);
            cur = cur->next;
        }
        cur = head;
        // 4. ����������� next �� random ָ��
        while(cur != nullptr) {
            map[cur]->next = map[cur->next];
            map[cur]->random = map[cur->random];
            cur = cur->next;
        }
        // 5. �����������ͷ�ڵ�
        return map[head];
    }
};
```
## ������36��[������������˫������](https://leetcode-cn.com/problems/er-cha-sou-suo-shu-yu-shuang-xiang-lian-biao-lcof/)
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
## ������37��[���л�������](https://leetcode-cn.com/problems/xu-lie-hua-er-cha-shu-lcof/)
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
## ������38��[�ַ���������](https://leetcode-cn.com/problems/zi-fu-chuan-de-pai-lie-lcof/)
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
## ������39��[�����г��ִ�������һ�������](https://leetcode-cn.com/problems/shu-zu-zhong-chu-xian-ci-shu-chao-guo-yi-ban-de-shu-zi-lcof/)
```c++
//Ħ��ͶƱ��
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
//���ӣ�https://leetcode-cn.com/problems/shu-zu-zhong-chu-xian-ci-shu-chao-guo-yi-ban-de-shu-zi-lcof/solution/mian-shi-ti-39-shu-zu-zhong-chu-xian-ci-shu-chao-3/
```
## ������40��[��С��k����](https://leetcode-cn.com/problems/zui-xiao-de-kge-shu-lcof/)
```c++
//�Զ������
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
    swap(arr[i],arr[left]);//��ʱi=j
    mySort(arr,left,i-1);
    mySort(arr,i+1,right);
}
};
//С����
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
## ������41��[�������е���λ��](https://leetcode-cn.com/problems/shu-ju-liu-zhong-de-zhong-wei-shu-lcof/)
```c++
class MedianFinder {
private:
    priority_queue<int,vector<int>,less<int>> small;//�洢��Сһ�룬ʹ�ô󶥶�(�Ѷ�Ϊ��λ��)
    priority_queue<int,vector<int>,greater<int>> big;//�洢���һ�룬ʹ��С����(�Ѷ�Ϊ��λ��)
    int n=0;//nΪ����
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
        if(num<=small.top())//num����λ��С���ŵ�small����
        {
            small.push(num);
            ++n;
        }
        else
        {
            big.push(num);
            ++n;
        }
        //small��big���2�����֣���Ҫ��������
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
## ������42��[���������������](https://leetcode-cn.com/problems/lian-xu-zi-shu-zu-de-zui-da-he-lcof/)
```c++
//��̬�滮
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
## ������43��[1~n������1���ֵĴ���](https://leetcode-cn.com/problems/1nzheng-shu-zhong-1chu-xian-de-ci-shu-lcof/)
```c++
class Solution {
public:
    int countDigitOne(int n) {
       int count = 0;
       long i = 1;//ָ�������λ������i=1����λ��i=10��ʮλ��...����Ϊn������31λ������10^31��long�洢
       while(n/i!=0){
           //n/i���Ʊ����Ĵ����������е�λ�����������
            long high = n/(10*i);//����ǰλ֮ǰ�����и�λ������high��
            long cur = (n/i)%10;//����ǰλ��¼��cur�У�������ÿ�ζ���Ҫͳ�Ƶ�ǰλ��1���ֵĴ���
            long low = n-(n/i)*i;
            if(cur == 0){
                count += high * i;
            } else if(cur == 1){
                count += high * i + low + 1;
            } else {
                count += high * i + i;
            }
            i = i * 10;//׼��������һλ
       }
       return count;
    }
};
// ���ߣ�lu-yang-shan-yu
// ���ӣ�https://leetcode-cn.com/problems/1nzheng-shu-zhong-1chu-xian-de-ci-shu-lcof/solution/c-cong-ge-wei-bian-li-dao-zui-gao-wei-yi-ci-qiu-ji/
```
## ������44��[����������ĳһλ����](https://leetcode-cn.com/problems/shu-zi-xu-lie-zhong-mou-yi-wei-de-shu-zi-lcof/)
```c++
class Solution {
public:
    int findNthDigit(int n) {
    int digit=1;//��¼����λ��
    long long start=1;//��¼n��������
    long long count=9;//��¼��λ����
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
//�ο���ַ��https://leetcode-cn.com/problems/shu-zi-xu-lie-zhong-mou-yi-wei-de-shu-zi-lcof/solution/mian-shi-ti-44-shu-zi-xu-lie-zhong-mou-yi-wei-de-6/
```
## ������45��[�������ų���С����](https://leetcode-cn.com/problems/ba-shu-zu-pai-cheng-zui-xiao-de-shu-lcof/)
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
//lambda���ʽ
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

## ������46��[�����ַ���Ϊ�ַ���](https://leetcode-cn.com/problems/ba-shu-zi-fan-yi-cheng-zi-fu-chuan-lcof/)
```c++
class Solution {
public:
int translateNum(int num)
{
    if(num<10) return 1;
    //0-25���һ��26��Ӣ����ĸ
    if(num%100<10||num%100>25)//��ʾֻ�ܵ��ַ�
        return translateNum(num/10);
    else
        return translateNum(num/10)+translateNum(num/100);
}
};
//�ο���ַ��https://leetcode-cn.com/problems/ba-shu-zi-fan-yi-cheng-zi-fu-chuan-lcof/solution/cjian-ji-dai-ma-shuang-bai-by-orangeman/
//��̬�滮
class Solution {
public:
    int translateNum(int num) {
        // 0 - 25;
        //��������̨�ף�ֻ��һ������������
        string s = to_string(num);
        int n = s.size();
        vector<int>dp (n + 1, 1);
        //dp[0]�����壬dp[1]��ʾ��һ�������ַ�
        for(int i = 2; i <= n; i++){
            int sum = (s[i - 2] - '0') * 10 + s[i - 1] - '0';
            if(sum >= 10 && sum <= 25) dp[i] = dp[i - 1] + dp[i - 2];
            else dp[i] = dp[i - 1];
        }
        return dp[n];
    }
};
```
## ������47��[���������ֵ](https://leetcode-cn.com/problems/li-wu-de-zui-da-jie-zhi-lcof/)
```c++
//��������
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
## ������48��[������ظ��ַ������ַ���](https://leetcode-cn.com/problems/zui-chang-bu-han-zhong-fu-zi-fu-de-zi-zi-fu-chuan-lcof/)
```c++
//��������
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
## ������49��[����](https://leetcode-cn.com/problems/chou-shu-lcof/)
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
## ������50��[��һ��ֻ����һ�ε��ַ�](https://leetcode-cn.com/problems/di-yi-ge-zhi-chu-xian-yi-ci-de-zi-fu-lcof/)
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
## ������51��[�����е������](https://leetcode-cn.com/problems/shu-zu-zhong-de-ni-xu-dui-lcof/)
```c++
//�ο���ַ��https://leetcode-cn.com/problems/shu-zu-zhong-de-ni-xu-dui-lcof/solution/jian-zhi-offer-51-shu-zu-zhong-de-ni-xu-pvn2h/
class Solution {
public:
    int merge_sort(int left, int right, vector<int> &nums, vector<int> &saveNums)
{
    if (left >= right)
        return 0;
    int mid = (left + right) >> 1;
    int res = merge_sort(left, mid, nums, saveNums) + merge_sort(mid + 1, right, nums, saveNums);
    //��������
    for (int i = left; i <= right; i++)
    {
        saveNums[i] = nums[i];
    }
    int i = left;    //�󼯺ϵ����
    int j = mid + 1; //�Ҽ��ϵ����
    for (int k = left; k <= right; k++)
    {
        if (i == mid + 1) //�Ҽ���ʹ�����
        {
            nums[k] = saveNums[j++];
        }
        //�󼯺�ʹ����ϻ����󼯺�С���Ҽ���
        else if (j == right + 1 || saveNums[i] <= saveNums[j])
        {
            nums[k] = saveNums[i++];
        }
        else //�Ҽ��ϴ����󼯺�
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
## ������52��[��������ĵ�һ�������ڵ�](https://leetcode-cn.com/problems/liang-ge-lian-biao-de-di-yi-ge-gong-gong-jie-dian-lcof/)
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
## ������53��[�����������в�������I](https://leetcode-cn.com/problems/zai-pai-xu-shu-zu-zhong-cha-zhao-shu-zi-lcof/)
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
## ������53-II��[0~n-1��ȱʧ������](https://leetcode-cn.com/problems/que-shi-de-shu-zi-lcof/)
```c++
//���ַ�
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
//���д��
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
## ������54��[�����������ĵ�K��ڵ�](https://leetcode-cn.com/problems/er-cha-sou-suo-shu-de-di-kda-jie-dian-lcof/)
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
## ������55-I��[�����������](https://leetcode-cn.com/problems/er-cha-shu-de-shen-du-lcof/)
```c++
//�ݹ�
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
## ������55-II��[ƽ�������](https://leetcode-cn.com/problems/ping-heng-er-cha-shu-lcof/)
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
## ������56-I��[���������ֳ��ֵĴ���](https://leetcode-cn.com/problems/shu-zu-zhong-shu-zi-chu-xian-de-ci-shu-lcof/)
```c++
class Solution {
public:
    vector<int> singleNumbers(vector<int>& nums) {
        int a=0,b=0;
        int a_b=0,aDifb=1;
        //0^(���)�κ�����Ϊԭ������
        //a^a=0
        //a_b��ʾ���ʣ��a���b��ֵ
        //aDifb��ʾ��ĳһλ����a��b���Ϊ1����a��b��ĳһλ���ϲ�ͬ����Ϊ�ֽ���
        for(int num:nums)
            a_b^=num;
        while((a_b&aDifb)==0)
            aDifb<<=1;//�ҵ�Ϊ1��λ��
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
## ������56-II��[���������ֳ��ֵĴ���II](https://leetcode-cn.com/problems/shu-zu-zhong-shu-zi-chu-xian-de-ci-shu-ii-lcof/)
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
        //�õ��������ϸ�λ��֮��
        int ans = 0;
        //������װʮ���Ʋ�%nλ��
        for (int i = 0; i < 32; i++)
        {
            ans+=(1<<i)*(bits[i]%3);
        }
        return ans;
    }
};
```
## ������57��[��Ϊs����������](https://leetcode-cn.com/problems/he-wei-sde-liang-ge-shu-zi-lcof/)
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
## ������57-II��[��Ϊs��������������](https://leetcode-cn.com/problems/he-wei-sde-lian-xu-zheng-shu-xu-lie-lcof/)
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

## ������58-I��[��ת����˳��](https://leetcode-cn.com/problems/fan-zhuan-dan-ci-shun-xu-lcof/)
```c++
//ͷ�ļ�<sstream>
//stringstream��ʹ��
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
//˫ָ���÷�
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
## ������58-II��[����ת�ַ���](https://leetcode-cn.com/problems/zuo-xuan-zhuan-zi-fu-chuan-lcof/)
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
## ������59-I��[�������ڵ����ֵ](https://leetcode-cn.com/problems/hua-dong-chuang-kou-de-zui-da-zhi-lcof/)
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
## ������59-II��[���е����ֵ](https://leetcode-cn.com/problems/dui-lie-de-zui-da-zhi-lcof/)
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
## ������60��[n�����ӵĵ���](https://leetcode-cn.com/problems/nge-tou-zi-de-dian-shu-lcof/)
```c++
class Solution {
public:
    vector<double> dicesProbability(int n) {
        int dp[70]={0};//���ӵ����͵Ŀ��ܷ�����
        for(int i=1;i<=6;i++)
            dp[i]++;
        //�ӵڶ������ӿ�ʼ
        for(int i=2;i<=n;i++)
        {
            //�ӵ��������Ŀ�ʼ
            for(int j=6*i;j>=i;j--)
            {
                dp[j]=0;
                //һ�����ӵĵ���
                //���е����ͷ�Χj��[i,6*j]
                //��ȥ��һ�����Ӻ�j�ķ�Χ��[i-1,6*j-6]
                //����������Ҫ�ж���ʣ�����(������-��ǰ��������j-cur)<i-1
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
## ������61��[�˿����е�˳��](https://leetcode-cn.com/problems/bu-ke-pai-zhong-de-shun-zi-lcof/)
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
## ������62��[ԲȦ�����ʣ�µ�����](https://leetcode-cn.com/problems/yuan-quan-zhong-zui-hou-sheng-xia-de-shu-zi-lcof/)
```c++
//�ο���վ��https://blog.csdn.net/u011500062/article/details/72855826
class Solution {
public:
    int lastRemaining(int n, int m) {
        //dp[i]����ʾ���ʤ������λ�ã�i��ʾ��ǰ����
        int dp[n+1];
        //��ʼ��dp��������Ϊ1ʱ����ʤ����λ��Ϊ0
        dp[1]=0;
        for(int i=2;i<=n;i++)
        {
            //�ο���ַ��https://blog.csdn.net/u011500062/article/details/72855826
            //���ͣ�������Ϊ2ʱ���൱�ڽ�����Ϊ1ʱ��ʤλ��0�����ƶ�mλ��
            //��ʱʤ��λ��Ϊ(����Ϊ0ʱ��ʤ��λ��)0+m(�ƶ�λ��)��
            //����Ϊ�˷�ֹ����Խ�磬��Ҫ������ȡ��(%i)
            //����������dp[i]=(dp[i-1]+m)%i
            dp[i]=(dp[i-1]+m)%i;
        }
        return dp[n];
    }
};
```
## ������63��[��Ʊ���������](https://leetcode-cn.com/problems/gu-piao-de-zui-da-li-run-lcof/)
```c+
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len=prices.size();
        if(len<=1) return 0;
        //dp[0][0]��ʾ���й�Ʊ��dp[0][1]��ʾδ���й�Ʊ
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
## ������64��[��1+2+...+n](https://leetcode-cn.com/problems/qiu-12n-lcof/)
```c++
class Solution {
public:
    int sumNums(int n) {
        //���nΪ0����0��Ȼ���1��ʼ����
        n && (n += sumNums(n-1));
        return n;
    }
};
```
## ������65��[���üӼ��˳����ӷ�](https://leetcode-cn.com/problems/bu-yong-jia-jian-cheng-chu-zuo-jia-fa-lcof/)
```c++
class Solution {
public:
    int add(int a, int b) {
        if (a == 0 || b == 0) {
            return a == 0 ? b : a;
        }

        int sum = 0, carry = 0;

        while (b != 0) { // ��û�н�λ��ʱ���˳�ѭ��
            sum = a ^ b; 
            carry = (unsigned int) (a & b) << 1; // C++ ���������������Ʋ�������Ҫ�� unsigned int

            a = sum;
            b = carry;
        }

        return a;
    }
}
// ���ӣ�https://leetcode-cn.com/problems/bu-yong-jia-jian-cheng-chu-zuo-jia-fa-lcof/solution/zi-jie-ti-ku-jian-65-jian-dan-bu-yong-ji-5k3q/
```
## ������66��[�����˻�����](https://leetcode-cn.com/problems/gou-jian-cheng-ji-shu-zu-lcof/)
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
//���ӣ�https://leetcode-cn.com/problems/gou-jian-cheng-ji-shu-zu-lcof/solution/gou-jian-cheng-ji-shu-zu-dui-cheng-bian-li-by-huwt/
```
## ������67��[���ַ�����Ϊ����](https://leetcode-cn.com/problems/ba-zi-fu-chuan-zhuan-huan-cheng-zheng-shu-lcof/)
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
## ������68-I��[�����������������������](https://leetcode-cn.com/problems/er-cha-sou-suo-shu-de-zui-jin-gong-gong-zu-xian-lcof/)
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
## ������69-II��[�������������������](https://leetcode-cn.com/problems/er-cha-shu-de-zui-jin-gong-gong-zu-xian-lcof/)
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
