# C++基础知识点
* 定义一个空的类型，里面没有任何成员变量和成员函数，对该类型求sizeof，得到的结果是**1**，因为空类型的实例中不包含任何信息，但是当我们声明该类型的实例时，它必须在内存中占有一定的空间。在Visual Studio中，每个空类型的实例占用1字节空间。此外，构造函数和析构函数只需要知道函数地址即可，即这些函数的地址只与类型相关，而与类型的实例无关，所以此时得到的结果还是**1**。但是将析构函数标记为虚函数后，c++编译器就会为该类型生成虚函数表，并在该类型的每一个实例中添加一个直线虚函数表的指针，在32位机器上，一个指针占4字节，此时sizeof=**4**;在64位机器上，一个指针占8字节，此时sizeof=**8**。
* 
* 
# 剑指OFFER
## 第二章
### 面试题1：复制运算函数
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
[测试代码](CodingInterviewChinese2/01_AssignmentOperator/AssignmentOperator.cpp)
# [代码随想录](https://programmercarl.com/)
## [数组](https://programmercarl.com/0704.%E4%BA%8C%E5%88%86%E6%9F%A5%E6%89%BE.html#%E6%80%9D%E8%B7%AF)
数组是存放在连续空间上的相同类型数据的集合，可以方便的通过下标索引的方式获取到下标下对应的数据。c++中二维数组在地址空间上也是连续的。
### 二分查找
#### [704.二分法查找](https://leetcode-cn.com/problems/binary-search/submissions/)
二分法第一种写法，条件`[left,right]`，注意点：
* while(left<=right)要用<=，因为left==right有意义
* if(nums[middle]>target)时right要赋值为middle-1，因为翻墙这个nums[middle]不一定是target，接下来要查找middle-1
```c++
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1; // 定义target在左闭右闭的区间里，[left, right]
        while (left <= right) { // 当left==right，区间[left, right]依然有效，所以用 <=
            int middle = left + ((right - left) / 2);// 防止溢出 等同于(left + right)/2
            if (nums[middle] > target) {
                right = middle - 1; // target 在左区间，所以[left, middle - 1]
            } else if (nums[middle] < target) {
                left = middle + 1; // target 在右区间，所以[middle + 1, right]
            } else { // nums[middle] == target
                return middle; // 数组中找到目标值，直接返回下标
            }
        }
        // 未找到目标值
        return -1;
    }
};
```
二分法第二种写法，条件[left,right)，注意点：
* while(left<right>)，因为此时left==right无意义
* if(nums[middle]>target)时right更新为middle，因为当前nums[middle]不等于target，需要去作曲奖继续寻找，即下一个查询区间不会去比较nums[middle]
```c++
// 版本二
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size(); // 定义target在左闭右开的区间里，即：[left, right)
        while (left < right) { // 因为left == right的时候，在[left, right)是无效的空间，所以使用 <
            int middle = left + ((right - left) >> 1);
            if (nums[middle] > target) {
                right = middle; // target 在左区间，在[left, middle)中
            } else if (nums[middle] < target) {
                left = middle + 1; // target 在右区间，在[middle + 1, right)中
            } else { // nums[middle] == target
                return middle; // 数组中找到目标值，直接返回下标
            }
        }
        // 未找到目标值
        return -1;
    }
};
```
#### [35.搜索插入位置](https://leetcode-cn.com/problems/search-insert-position/)
```c++
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int left=0;
    int right=nums.size()-1;
    int mid=0;
    while(left<=right)
    {
        mid=left+((right-left)>>1);
        if(nums[mid]>target)
            right=mid-1;
        else if(nums[mid]<target)
            left=mid+1;
        else
            return mid;
    }
    return right+1;
    }
};
```
#### [34.在排序数组中查找元素的第一个和最后一个位置](https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array/)
解题思路：先用二分法找到目标元素，然后找到开始位置和结束位置
```c++
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target)
{
    int len=nums.size();
    if(len==0)
        return vector<int>{-1,-1};
    vector<int> res(2,-1);
    int left=0;
    int right=len-1;
    int mid=0;
    bool is_existed=false;
    while(left<=right)
    {
        mid=left+((right-left)>>1);
        if(nums[mid]>target)
            right=mid-1;
        else if(nums[mid]<target)
            left=mid+1;
        else
        {
            is_existed=true;
            break;
        }
    }
    if(!is_existed)
        return res;
    //找到最小位置
    int l_mid=mid;
    int r_mid=mid;
    while(l_mid>=0&&nums[l_mid]==target)
    {
        --l_mid;
    }
    while(r_mid<len&&nums[r_mid]==target)
    {
        ++r_mid;
    }
    res.at(0)=l_mid+1;
    res.at(1)=r_mid-1;
    return res;
}
};
```
#### [69.x的平方根](https://leetcode-cn.com/problems/sqrtx/)
```c++
class Solution {
public:
    int mySqrt(int x) {
         int l = 0, r = x;
    while (l <= r) {
        int mid = l+r>>1;
        if ((long long)mid * mid <= x) {
            l = mid + 1;
        }
        else {
            r = mid - 1;
        }
    }
    return r;
    }
};
```
#### [267.有效的完全平方数](https://leetcode-cn.com/problems/valid-perfect-square/)
```c++
class Solution {
public:
    bool isPerfectSquare(int num) {
long long left = 0;
	long long right = num;
	while (left <= right)
	{
		long long mid = left + right >> 1;
		if (mid * mid == num)
			return true;
		else if (mid * mid < num)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return false;
    }
};
```
### 移除元素-双指针法
#### [27.移除元素](https://leetcode-cn.com/problems/remove-element/)
方法一(双指针法)：
```c++
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
    int len=nums.size();
    int slow=0,fast=0;
   while(fast<len)
   {
       if(nums[fast]==val)
       {
           fast++;
           continue;
       }
       nums[slow]=nums[fast];
       slow++;
       fast++;
   }
   return slow;
    }
};
```
方法二：[一行代码](http://c.biancheng.net/view/429.html#:~:text=%E5%8F%AF%E4%BB%A5%E9%80%9A%E8%BF%87%E4%BD%BF%E7%94%A8%20vector%20%E7%9A%84%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0,clear%20%28%29%20%E6%9D%A5%E5%88%A0%E9%99%A4%E6%89%80%E6%9C%89%E7%9A%84%E5%85%83%E7%B4%A0%E3%80%82)
```c++
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
            nums.erase(remove(nums.begin(), nums.end(), val), nums.end());
        return nums.size();
    }
};
```
remove函数返回最后一个空元素迭代器位置，erase函数删除范围内的所有元素
![](picture/move函数示意图.jpg)
#### [26.删除排序数组中的重复项](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-array/)
```c++
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
    int t = 0;
	for (int i = 0; i < nums.size(); i++) {
		if (i == 0 || nums[i] != nums[i - 1]) 
			nums[t++] = nums[i];
	}
	return t;
    }
};
```
#### [283.移动零](https://leetcode-cn.com/problems/move-zeroes/)
```c++
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
int t=0;
    for(int i=0;i<nums.size();i++)
    {
        if(nums[i]!=0)
            nums[t++]=nums[i];
    }
    for(int i=t;i!=nums.size();i++)
        nums[i]=0;
    }
};
```
#### [844.比较含退格的字符串](https://leetcode-cn.com/problems/backspace-string-compare/)
```c++
class Solution {
public:
    bool backspaceCompare(string s, string t) {
    int sp = s.size() - 1;
    int tp = t.size() - 1;
    int s_pass = 0;
    int t_pass = 0;
    while (1)
    {
        while (sp >= 0)
        {
            if (s[sp] == '#')
            {
                s_pass++;
            }
            else
            {
                if(s_pass>0)
                    s_pass--;
                else
                    break;
            }
            sp--;
        }
        while (tp >= 0)
        {
            if (t[tp] == '#')
            {
                t_pass++;
            }
            else
            {
                if(t_pass>0)
                    t_pass--;
                else
                    break;
            }
            tp--;
        }
        if(sp<0||tp<0) break;//跳出循环
        if(s[sp--]!=t[tp--])
            return false;
    }
    //sp和tp同时为-1表示最后字符串长度相同
    if(sp==-1&&tp==-1)
        return true;
    return false;
    }
};
```
string标准库版本
```c++
class Solution {
public:
 string build(string str)
    {
        string ret;
        for(char ch:str)
        {
            if(ch!='#')
            ret.push_back(ch);
            else
            if(!ret.empty())
            ret.pop_back();
        }
        return ret;
    }
    bool backspaceCompare(string s, string t) {
       return build(s)==build(t);
    }
   
};
```
正则表达式版本
```c++
class Solution {
public:
    bool backspaceCompare(string s, string t) {
    regex  re{"(^|[a-z])#"};
    while (regex_search(s, re))
    {
        s = regex_replace(s, re, "");
    }
    while(regex_search(t,re))
    {
        t=regex_replace(t,re,"");
    }
    if(s==t)
        return true;
    return false;
    }
};
```
#### [977.有序数组的平方](https://leetcode-cn.com/problems/squares-of-a-sorted-array/)
```c++
class Solution {
public:
    vector<int> sortedSquares(vector<int> &nums)
    {
    int left = 0, right = nums.size() - 1;
    vector<int> res(right + 1.0);
    int i = right;
    while (left < right)
    {
        if (abs(nums[left]) > abs(nums[right]))
        {
            res[i--] = (nums[left] * nums[left]);
            left++;
        }
        else if (abs(nums[left]) < abs(nums[right]))
        {
            res[i--] = (nums[right] * nums[right]);
            right--;
        }
        else
        {
            res[i--]=(nums[right]*nums[right]);
            res[i--]=(nums[left]*nums[left]);
            left++;
            right--;
        }
    }
    res[0]=(nums[left] * nums[left]);
    return res;
  }
};
```
#### [209.长度最小的子数组](https://leetcode-cn.com/problems/minimum-size-subarray-sum/)
滑动窗口解法
```c++
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
    int len=nums.size();
    int left=0,right=0;
    int sum=0;
    int subLen=0;
    int res=INT_MAX;
    for(;right<len;right++)
    {
         sum+=nums[right];
        while (sum>=target)
        {
            subLen=right-left+1;
            res=res<subLen?res:subLen;
            sum-=nums[left++];
        }     
    }
    return res==INT_MAX?0:res;
    }
};
```
#### [904.水果成篮](https://leetcode-cn.com/problems/fruit-into-baskets/)
```c++
class Solution {
public:
    int totalFruit(vector<int>& tree) {
      int res = 0;
	int left = 0, right = 1;
	int a = tree[0], b ;
	int len = tree.size();
	while (right < len && tree[right] == a)
		++right;
    if(right==len) return len;
    b=tree[right++];
    while(right<len)
    {
        if(tree[right]!=a&&tree[right]!=b)
        {
            res=max(res,right-left);
            a=tree[right-1];
            b=tree[right];
            left = right - 1;
  		    while (tree[left - 1] == a)
			    --left;
        }
  		++right;
    }
	return max(res, right - left);
    }
};
```
#### [76.最小覆盖子串](https://leetcode-cn.com/problems/minimum-window-substring/)
```c++
class Solution
{
public:
    string minWindow(string s,string t)
    {
    vector<int> need(128, 0);
    for (char c : t)
    {
        need[c]++;
    }
    int count = t.size();
    int len_s = s.size();
    int left = 0, right = 0, start = 0, size = INT_MAX;
    while (right < len_s)
    {
        char c = s[right];
        if (need[c] > 0)
            count--;
        need[c]--;      //先把右边的字符加入窗口
        if (count == 0) //窗口中已经包含所需的全部字符
        {
            while (left < right && need[s[left]] < 0) //缩减窗口
            {
                need[s[left++]]++;
            }                            //此时窗口符合要求
            if (right - left + 1 < size) //更新答案
            {
                size = right - left + 1;
                start = left;
            }
            need[s[left]]++; //左边界右移之前需要释放need[s[left]]
            left++;
            count++;
        }
        right++;
    }
    return size == INT_MAX ? "" : s.substr(start, size);
    }
};
```
#### [59.螺旋矩阵II](https://leetcode-cn.com/problems/spiral-matrix-ii/)
```c++
class Solution
{
public:
    vector<vector<int>> generateMatrix(int n)
    {
    //左闭右开原则
    vector<vector<int>> res(n, vector<int>(n, 0));
    int startX=0,startY=0;
    int num=1;
    int i,j;
    int loop=n/2;
    int boundary=1;
    while(loop--)
    {
        i=startX;
        j=startY;
        while(j<startY+n-boundary)
        {
            res[startX][j++]=num++;
        }
        while(i<startX+n-boundary)
        {
            res[i++][j]=num++;
        }
        while(j>startY)
        {
            res[i][j--]=num++;
        }
        while(i>startX)
        {
            res[i--][j]=num++;
        }
        //更改下一圈的起点和边界
        startX++;
        startY++;
        boundary+=2;
    }
    if(n%2)
    {
        res[n/2][n/2]=num;
    }
    return res;
    }
};
```
#### [54.螺旋矩阵](https://leetcode-cn.com/problems/spiral-matrix/)
```c++
class Solution{
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix)
    {
        vector<int> res;
        int startX=0,startY=0;
        int row=matrix.size();//row=3
        int column=matrix[0].size();//col=4
        int countdown=row*column;//总个数，用来结束循环
        int up=0,down=row-1,left=0,right=column-1;
        while(1)
        {
            for(int j=left;j<=right;j++)
            {
                res.push_back(matrix[up][j]);
            }
            if(++up>down) break;
            for(int i=up;i<=down;i++)
            {
                res.push_back(matrix[i][right]);
            }
            if(--right<left) break;

            for(int j=right;j>=left;j--)
            {
                res.push_back(matrix[down][j]);
            }
            if(--down<up) break;
            for(int i=down;i>=up;i--)
            {
                res.push_back(matrix[i][left]);
            }
            if(++left>right) break;
        }
        return res;
    }
};
```
方式二：
![](picture/按照形状模拟示意图1.png)
```c++
class Solution{
public:
vector<int> spiralOrder(vector<vector<int>> &matrix)
{
    int row = matrix.size();
    int col = matrix[0].size();
    int left = 0, right = col - 1, up = 0, down = row - 1;
    vector<int> res;
    while (true)
    {
        if (left > right || up > down)
            break;
        //只有一行时，按行遍历
        if (up == down)
        {
            for (int j = left; j <= right; j++)
                res.push_back(matrix[up][j]);
            break;
        }
        //只有一列时，按列遍历
        if (left == right)
        {
            for (int i = up; i <= down; i++)
                res.push_back(matrix[i][left]);
            break;
        }
        //遍历当前的一圈
        for (int j = left; j < right; j++)
            res.push_back(matrix[up][j]);
        for (int i = up; i < down; i++)
            res.push_back(matrix[i][right]);
        for (int j = right; j > left; j--)
            res.push_back(matrix[down][j]);
        for (int i = down; i > up; i--)
            res.push_back(matrix[i][left]);
        left++;
        right--;
        up++;
        down--;
    }
    return res;
}
};
```
## 链表
* 链表在内存中不是连续分布的，它是通过指针域的指针来链接内存中的各个节点。
链表常用方式
```c++
// 单链表
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
//数组方式初始化链表
vector<int> v={1,2,6,3,4,5,6};
    ListNode *head=new ListNode();
    ListNode *prehead=head;
    for(const decltype(v[0])& i:v)
    {
        prehead->next=new ListNode(i);
        prehead=prehead->next;
    }
    head=head->next;
};
```
### [203.移除链表元素](https://leetcode-cn.com/problems/remove-linked-list-elements/)
```c++
//虚拟头结点方式
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode* dummyHead = new ListNode(0); // 设置一个虚拟头结点
        dummyHead->next = head; // 将虚拟头结点指向head，这样方面后面做删除操作
        ListNode* cur = dummyHead;
        while (cur->next != NULL) {
            if(cur->next->val == val) {
                ListNode* tmp = cur->next;
                cur->next = cur->next->next;
                delete tmp;
            } else {
                cur = cur->next;
            }
        }
        head = dummyHead->next;
        delete dummyHead;
        return head;
    }
};

//直接使用原来的链表
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        // 删除头结点
        while (head != NULL && head->val == val) { // 注意这里不是if
            ListNode* tmp = head;
            head = head->next;
            delete tmp;
        }

        // 删除非头结点
        ListNode* cur = head;
        while (cur != NULL && cur->next!= NULL) {
            if (cur->next->val == val) {
                ListNode* tmp = cur->next;
                cur->next = cur->next->next;
                delete tmp;
            } else {
                cur = cur->next;
            }
        }
        return head;
    }
};
```
### [707.设计链表](https://leetcode-cn.com/problems/design-linked-list/)
```c++
class MyLinkedList {
public:
    // 定义链表节点结构体
    struct Node {
        int val;
        Node* next;
        Node(int val):val(val), next(nullptr){}
    };

    // 初始化链表
    MyLinkedList() {
        dummyhead = new Node(0); // 这里定义的头结点 是一个虚拟头结点，而不是真正的链表头结点
        size = 0;
    }

    // 获取到第index个节点数值，如果index是非法数值直接返回-1， 注意index是从0开始的，第0个节点就是头结点
    int get(int index) {
        if (index > (size - 1) || index < 0) {
            return -1;
        }
        Node* cur = dummyhead->next;
        while(index--){ // 如果--index 就会陷入死循环
            cur = cur->next;
        }
        return cur->val;
    }

    // 在链表最前面插入一个节点，插入完成后，新插入的节点为链表的新的头结点
    void addAtHead(int val) {
        Node* newNode = new Node(val);
        newNode->next = dummyhead->next;
        dummyhead->next = newNode;
        size++;
    }

    // 在链表最后面添加一个节点
    void addAtTail(int val) {
        Node* newNode = new Node(val);
        Node* cur = dummyhead;
        while(cur->next != nullptr){
            cur = cur->next;
        }
        cur->next = newNode;
        size++;
    }

    // 在第index个节点之前插入一个新节点，例如index为0，那么新插入的节点为链表的新头节点。
    // 如果index 等于链表的长度，则说明是新插入的节点为链表的尾结点
    // 如果index大于链表的长度，则返回空
    void addAtIndex(int index, int val) {
        if (index > size) {
            return;
        }
        Node* newNode = new Node(val);
        Node* cur = dummyhead;
        while(index--) {
            cur = cur->next;
        }
        newNode->next = cur->next;
        cur->next = newNode;
        size++;
    }

    // 删除第index个节点，如果index 大于等于链表的长度，直接return，注意index是从0开始的
    void deleteAtIndex(int index) {
        if (index >= size || index < 0) {
            return;
        }
        Node* cur = dummyhead;
        while(index--) {
            cur = cur ->next;
        }
        Node* tmp = cur->next;
        cur->next = cur->next->next;
        delete tmp;
        size--;
    }

    // 打印链表
    void printLinkedList() {
        Node* cur = dummyhead;
        while (cur->next != nullptr) {
            cout << cur->next->val << " ";
            cur = cur->next;
        }
        cout << endl;
    }
private:
    int size;
    Node* dummyhead;

};
```
### [206.反转链表](https://leetcode-cn.com/problems/reverse-linked-list/)
```c++
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* temp; // 保存cur的下一个节点
        ListNode* cur = head;
        ListNode* pre = NULL;
        while(cur) {
            temp = cur->next;  // 保存一下 cur的下一个节点，因为接下来要改变cur->next
            cur->next = pre; // 翻转操作
            // 更新pre 和 cur指针
            pre = cur;
            cur = temp;
        }
        return pre;
    }
};
```
### [19.删除链表的倒数第N个节点](https://leetcode-cn.com/problems/remove-nth-node-from-end-of-list/)
```c++
//递归法
class Solution {
public:
    int cur=0;
    ListNode* removeNthFromEnd(ListNode* head, int n) {
       if(!head) return NULL;
       head->next = removeNthFromEnd(head->next,n);
       cur++;
       if(n==cur) return head->next;
       return head;
    }
};
//虚拟头结点+双指针
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummyHead = new ListNode(0);
        dummyHead->next = head;
        ListNode* slow = dummyHead;
        ListNode* fast = dummyHead;
        while(n-- && fast != NULL) {
            fast = fast->next;
        }
        fast = fast->next; // fast再提前走一步，因为需要让slow指向删除节点的上一个节点
        while (fast != NULL) {
            fast = fast->next;
            slow = slow->next;
        }
        slow->next = slow->next->next;
        return dummyHead->next;
    }
};
//双指针
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if(!head | !head -> next) return NULL;
        ListNode * fast = head, *slow = head;
        for(int i = 0; i < n; i++){
            fast = fast -> next;
        }
        if(!fast){
            return head -> next;    
        }
        
        while(fast -> next){
            fast = fast -> next;
            slow = slow -> next;
        }
        slow -> next = slow -> next -> next;
        return head;
    }
};
```
### [24.两两交换链表中的节点](https://leetcode-cn.com/problems/swap-nodes-in-pairs/)
```c++
//虚拟头结点
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode* dummyHead = new ListNode(0); // 设置一个虚拟头结点
        dummyHead->next = head; // 将虚拟头结点指向head，这样方面后面做删除操作
        ListNode* cur = dummyHead;
        while(cur->next != nullptr && cur->next->next != nullptr) {
            ListNode* tmp = cur->next; // 记录临时节点
            ListNode* tmp1 = cur->next->next->next; // 记录临时节点

            cur->next = cur->next->next;    // 步骤一
            cur->next->next = tmp;          // 步骤二
            cur->next->next->next = tmp1;   // 步骤三

            cur = cur->next->next; // cur移动两位，准备下一轮交换
        }
        return dummyHead->next;
    }
};
//递归法，只看2个元素
ListNode swapPairs(ListNode head)
{
	 if(head == null || head.next == null){
            return head;
        }
        ListNode next = head.next;
        head.next = swapPairs(next.next);
        next.next = head;
        return next;
}
```
![](picture/24.两两交换链表中的节点.png)

### [面试题 02.07. 链表相交](https://leetcode-cn.com/problems/intersection-of-two-linked-lists-lcci/)
```c++
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *A = headA, *B = headB;
        while (A != B) {
            A = A != nullptr ? A->next : headB;
            B = B != nullptr ? B->next : headA;
        }
        return A;
    }
};
作者：jyd
链接：https://leetcode-cn.com/problems/intersection-of-two-linked-lists-lcci/solution/mian-shi-ti-0207-lian-biao-xiang-jiao-sh-b8hn/
```

### [142.环形链表II](https://leetcode-cn.com/problems/linked-list-cycle-ii/)
```c++
//链表地址判断法
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        while(head) {
            if(!less<ListNode *>()(head, head->next)) {
                return head->next;
            }
            head = head->next;
        }
        return nullptr;
    }
};
```
参考网址：https://programmercarl.com/0142.%E7%8E%AF%E5%BD%A2%E9%93%BE%E8%A1%A8II.html#%E6%80%9D%E8%B7%AF
![](picture/142.环形链表快慢指针.png)

```c++
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode* slow=head,*fast=head;
	while(fast&&fast->next)
	{
		fast=fast->next->next;
		slow=slow->next;
		if(fast==slow)
		{
			ListNode* left=head;
			ListNode* right=fast;
			while(left!=right)
			{
				left=left->next;
				right=right->next;
			}
			return left;
		}
	}
	return NULL;
    }
};
```
## 哈希表
### [242.有效的字母异位词](https://leetcode-cn.com/problems/valid-anagram/)
```c++
class Solution {
public:
    bool isAnagram(string s, string t) {
        int record[26] = {0};
        for (int i = 0; i < s.size(); i++) {
            // 并不需要记住字符a的ASCII，只要求出一个相对数值就可以了
            record[s[i] - 'a']++;
        }
        for (int i = 0; i < t.size(); i++) {
            record[t[i] - 'a']--;
        }
        for (int i = 0; i < 26; i++) {
            if (record[i] != 0) {
                // record数组如果有的元素不为零0，说明字符串s和t 一定是谁多了字符或者谁少了字符。
                return false;
            }
        }
        // record数组所有元素都为零0，说明字符串s和t是字母异位词
        return true;
    }
};
```
### [383.赎金信](https://leetcode-cn.com/problems/ransom-note/)
```c++
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
    int a[26] = { 0 };
	for (int i = 0; i < magazine.size(); i++)
		++a[magazine[i] - 'a'];
	for (int i = 0; i < ransomNote.size(); i++)
	{
		--a[ransomNote[i] - 'a'];
		if (a[ransomNote[i] - 'a'] < 0)
			return false;
	}
	return true;
    }
};
```
### [49.字母异位词分组](https://leetcode-cn.com/problems/group-anagrams/)
```c++
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs)
{
	vector<vector<string>> res;
	map<string,vector<string>> s_map;
	for(int i=0;i<strs.size();i++)
	{
		string key=strs[i];
		sort(key.begin(),key.end());
		s_map[key].push_back(strs[i]);
	}
	for(auto iter=s_map.begin();iter!=s_map.end();iter++)
	{
		res.push_back(iter->second);
	}
	return res;
}
};
```
### [438.找到字符串中所有字母异位词](https://leetcode-cn.com/problems/find-all-anagrams-in-a-string/)
```c++
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> res; /* 存放这些子串的起始索引startPos */
        int restCount = p.size(); /* 维护一个固定长度的窗口, 长度= len(p), restCount: 剩下的待匹配字符的数量 */
        int pFreq[26]; /* 模拟一个计数哈希表 */
        memset(pFreq, 0, sizeof(pFreq));
        for (int i = 0; i < p.size(); i++)
            pFreq[p[i] - 'a']++;
        int sFreq[26]; /* 模拟一个计数哈希表, sFreq: s中处于滑动窗口内的字符的频次 */
        memset(sFreq, 0, sizeof(sFreq));        
        for (int i = 0; i < s.size(); i++)
        {
            char c = s[i];
            sFreq[c - 'a']++;
            if (sFreq[c - 'a'] <= pFreq[c - 'a']) /* 匹配到了一个待匹配的字符 */
                restCount--;
            if (i >= p.size()) /* 删除最前面的1个字符 */
            {
                char h = s[i - p.size()];
                sFreq[h - 'a']--;
                if (sFreq[h - 'a'] < pFreq[h - 'a'])
                    restCount++;
            }
            // check is anagram
            if (restCount == 0) /* i - startPos + 1 = len(p) => startPos = i - len(p) + 1 */
                res.push_back(i - p.size() + 1);
        }
        return res;
    }
};
```
### [349. 两个数组的交集](https://leetcode-cn.com/problems/intersection-of-two-arrays/)
```c++
//unordered_set版本
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    unordered_set<int> res_set;
	unordered_set<int> uset(nums1.begin(),nums1.end());
	for(const int& num:nums2)
	{
		if(uset.find(num)!=uset.end())
			res_set.emplace(num);
	}
	return vector<int>(res_set.begin(),res_set.end());
    }
};
//int数组版本，时间更短，内存更小
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
vector<int> ans;
	int f1[1000] = { 0 };
	int f2[1000] = { 0 };
	for (int i = 0; i < nums1.size(); i++)
		f1[nums1[i]]++;
	for (int i = 0; i < nums2.size(); i++)
		f2[nums2[i]]++;
	for (int i = 0; i < 1000; i++)
	{
		if (f1[i]&&f2[i])
			ans.push_back(i);
	}
	return ans;
    }
};
```
### [350.两个数组的交集II](https://leetcode-cn.com/problems/intersection-of-two-arrays-ii/)
```c++
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
    vector<int> res;
	int a[1001]={0};
	for(int i=0;i<nums1.size();i++)
		a[nums1[i]]++;
	for(int j=0;j<nums2.size();j++)
	{
		if(a[nums2[j]]>0)
		{
			res.emplace_back(nums2[j]);
			a[nums2[j]]--;
		}
	}
	return res;
    }
};
```
### [202.快乐数](https://leetcode-cn.com/problems/happy-number/)
```c++
//参考英文网站热评第一。这题可以用快慢指针的思想去做，有点类似于检测是否为环形链表那道题
//如果给定的数字最后会一直循环重复，那么快的指针（值）一定会追上慢的指针（值），也就是
//两者一定会相等。如果没有循环重复，那么最后快慢指针也会相等，且都等于1。
class Solution {
public:
    int squareSum(int m)
{
	int res = 0;
	while (m > 0)
	{
		res += (m % 10) * (m % 10);
		m /= 10;
	}
	return res;
}
bool isHappy(int n)
{
	int fast = n;
	int slow = n;
	do
	{
		slow = squareSum(slow);
		fast = squareSum(fast);
		fast = squareSum(fast);
	} while (slow != fast);
	if (fast == 1)
		return true;
	return false;
}
};
```
### [287.寻找重复数](https://leetcode-cn.com/problems/find-the-duplicate-number/)
```c++
//数组中存在环
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
    int len=nums.size();
	int slow=0,fast=0;
	while(true)
	{
		fast=nums[nums[fast]];
		slow=nums[slow];
		if(slow==fast)
		{
			fast=0;
			while(nums[slow]!=nums[fast])
			{
				fast=nums[fast];
				slow=nums[slow];
			}
			return nums[fast];
		}
	}
}
};
```
### [1两数之和](https://leetcode-cn.com/problems/two-sum/)
```c++
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        std::unordered_map <int,int> map;
        for(int i = 0; i < nums.size(); i++) {
            auto iter = map.find(target - nums[i]);
            if(iter != map.end()) {
                return {iter->second, i};
            }
            map[nums[i]]=i;
        }
        return {};
    }
};
```
### [454.四数相加II](https://leetcode-cn.com/problems/4sum-ii/)
```c++
class Solution {
public:
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
int result=0;
	unordered_map<int,int> umap;
	for (int a : nums1)
		for (int b : nums2)
			umap[a + b]++;
	for (int c : nums3)
		for (int d : nums4)
			if (umap.find(0 - (c + d)) != umap.end())
				result += umap[0 - (c + d)];
	return result;
    }
};
```
### [383. 赎金信](https://leetcode-cn.com/problems/ransom-note/)
```c++
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
    int a[26] = { 0 };
	for (int i = 0; i < magazine.size(); i++)
		++a[magazine[i] - 'a'];
	for (int i = 0; i < ransomNote.size(); i++)
	{
		--a[ransomNote[i] - 'a'];
		if (a[ransomNote[i] - 'a'] < 0)
			return false;
	}
	return true;
    }
};
```
### [15.三数之和](https://leetcode-cn.com/problems/3sum/)
```c++
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
    int len=nums.size();
	sort(nums.begin(),nums.end());
	vector<vector<int>> res;
	for(int i=0;i<nums.size();i++)
	{
		if(nums[i]>0)
			return res;
		if(i>0&&nums[i]==nums[i-1])
			continue;
		int left=i+1;
		int right=len-1;
		while(right>left)
		{
			if(nums[i]+nums[left]+nums[right]>0)
				--right;
			else if(nums[i]+nums[left]+nums[right]<0)
				++left;
			else
			{
				res.emplace_back(vector<int>{nums[i],nums[left],nums[right]});
				while(right>left&&nums[right]==nums[right-1]) --right;
				while(left<right&&nums[left]==nums[left+1]) ++left;
				--right;
				++left;
			}
		}
	}
	return res;
    }
};
```