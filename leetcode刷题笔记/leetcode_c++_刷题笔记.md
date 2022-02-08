ˢ����ַ��https://programmercarl.com/
# [����](https://programmercarl.com/0704.%E4%BA%8C%E5%88%86%E6%9F%A5%E6%89%BE.html#%E6%80%9D%E8%B7%AF)
�����Ǵ���������ռ��ϵ���ͬ�������ݵļ��ϣ����Է����ͨ���±������ķ�ʽ��ȡ���±��¶�Ӧ�����ݡ�c++�ж�ά�����ڵ�ַ�ռ���Ҳ�������ġ�
## ���ֲ���
### [704.���ַ�����](https://leetcode-cn.com/problems/binary-search/submissions/)
���ַ���һ��д��������`[left,right]`��ע��㣺
* while(left<=right)Ҫ��<=����Ϊleft==right������
* if(nums[middle]>target)ʱrightҪ��ֵΪmiddle-1����Ϊ��ǽ���nums[middle]��һ����target��������Ҫ����middle-1
```c++
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1; // ����target������ұյ������[left, right]
        while (left <= right) { // ��left==right������[left, right]��Ȼ��Ч�������� <=
            int middle = left + ((right - left) / 2);// ��ֹ��� ��ͬ��(left + right)/2
            if (nums[middle] > target) {
                right = middle - 1; // target �������䣬����[left, middle - 1]
            } else if (nums[middle] < target) {
                left = middle + 1; // target �������䣬����[middle + 1, right]
            } else { // nums[middle] == target
                return middle; // �������ҵ�Ŀ��ֵ��ֱ�ӷ����±�
            }
        }
        // δ�ҵ�Ŀ��ֵ
        return -1;
    }
};
```
���ַ��ڶ���д��������[left,right)��ע��㣺
* while(left<right>)����Ϊ��ʱleft==right������
* if(nums[middle]>target)ʱright����Ϊmiddle����Ϊ��ǰnums[middle]������target����Ҫȥ����������Ѱ�ң�����һ����ѯ���䲻��ȥ�Ƚ�nums[middle]
```c++
// �汾��
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size(); // ����target������ҿ������������[left, right)
        while (left < right) { // ��Ϊleft == right��ʱ����[left, right)����Ч�Ŀռ䣬����ʹ�� <
            int middle = left + ((right - left) >> 1);
            if (nums[middle] > target) {
                right = middle; // target �������䣬��[left, middle)��
            } else if (nums[middle] < target) {
                left = middle + 1; // target �������䣬��[middle + 1, right)��
            } else { // nums[middle] == target
                return middle; // �������ҵ�Ŀ��ֵ��ֱ�ӷ����±�
            }
        }
        // δ�ҵ�Ŀ��ֵ
        return -1;
    }
};
```
### [35.��������λ��](https://leetcode-cn.com/problems/search-insert-position/)
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
### [34.�����������в���Ԫ�صĵ�һ�������һ��λ��](https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array/)
����˼·�����ö��ַ��ҵ�Ŀ��Ԫ�أ�Ȼ���ҵ���ʼλ�úͽ���λ��
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
    //�ҵ���Сλ��
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
### [69.x��ƽ����](https://leetcode-cn.com/problems/sqrtx/)
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
### [267.��Ч����ȫƽ����](https://leetcode-cn.com/problems/valid-perfect-square/)
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
## �Ƴ�Ԫ��-˫ָ�뷨
### [27.�Ƴ�Ԫ��](https://leetcode-cn.com/problems/remove-element/)
����һ(˫ָ�뷨)��
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
��������[һ�д���](http://c.biancheng.net/view/429.html#:~:text=%E5%8F%AF%E4%BB%A5%E9%80%9A%E8%BF%87%E4%BD%BF%E7%94%A8%20vector%20%E7%9A%84%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0,clear%20%28%29%20%E6%9D%A5%E5%88%A0%E9%99%A4%E6%89%80%E6%9C%89%E7%9A%84%E5%85%83%E7%B4%A0%E3%80%82)
```c++
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
            nums.erase(remove(nums.begin(), nums.end(), val), nums.end());
        return nums.size();
    }
};
```
remove�����������һ����Ԫ�ص�����λ�ã�erase����ɾ����Χ�ڵ�����Ԫ��
![](picture/move����ʾ��ͼ.jpg)
### [26.ɾ�����������е��ظ���](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-array/)
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
### [283.�ƶ���](https://leetcode-cn.com/problems/move-zeroes/)
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
### [844.�ȽϺ��˸���ַ���](https://leetcode-cn.com/problems/backspace-string-compare/)
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
        if(sp<0||tp<0) break;//����ѭ��
        if(s[sp--]!=t[tp--])
            return false;
    }
    //sp��tpͬʱΪ-1��ʾ����ַ���������ͬ
    if(sp==-1&&tp==-1)
        return true;
    return false;
    }
};
```
string��׼��汾
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
������ʽ�汾
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