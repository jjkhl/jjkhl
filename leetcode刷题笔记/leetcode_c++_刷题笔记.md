刷题网址：https://programmercarl.com/
# [数组](https://programmercarl.com/0704.%E4%BA%8C%E5%88%86%E6%9F%A5%E6%89%BE.html#%E6%80%9D%E8%B7%AF)
数组是存放在连续空间上的相同类型数据的集合，可以方便的通过下标索引的方式获取到下标下对应的数据。c++中二维数组在地址空间上也是连续的。
## 二分查找
### [704.二分法查找](https://leetcode-cn.com/problems/binary-search/submissions/)
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
### [35.搜索插入位置](https://leetcode-cn.com/problems/search-insert-position/)
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
### [34.在排序数组中查找元素的第一个和最后一个位置](https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array/)
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
### [69.x的平方根](https://leetcode-cn.com/problems/sqrtx/)
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
### [267.有效的完全平方数](https://leetcode-cn.com/problems/valid-perfect-square/)
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
## 移除元素-双指针法
### [27.移除元素](https://leetcode-cn.com/problems/remove-element/)
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
### [26.删除排序数组中的重复项](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-array/)
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
### [283.移动零](https://leetcode-cn.com/problems/move-zeroes/)
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
### [844.比较含退格的字符串](https://leetcode-cn.com/problems/backspace-string-compare/)
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
### [977.有序数组的平方](https://leetcode-cn.com/problems/squares-of-a-sorted-array/)
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
### [209.长度最小的子数组](https://leetcode-cn.com/problems/minimum-size-subarray-sum/)
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
### [904.水果成篮](https://leetcode-cn.com/problems/fruit-into-baskets/)
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
### [76.最小覆盖子串](https://leetcode-cn.com/problems/minimum-window-substring/)
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
### [59.螺旋矩阵II](https://leetcode-cn.com/problems/spiral-matrix-ii/)
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