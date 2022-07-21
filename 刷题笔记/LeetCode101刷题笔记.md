github地址：https://github.com/changgyhub/leetcode_101/

**算法部分**

# 第二章 贪心算法

## [455.分发饼干](https://leetcode.cn/problems/assign-cookies/)
```c++
class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(),g.end());
        sort(s.begin(),s.end());
        int child=0,cookie=0;
        while(child<g.size()&&cookie<s.size())
        {
            if(g[child]<=s[cookie]) ++child;
            ++cookie;
        }
        return child;
    }
};
```
## [135.分发糖果](https://leetcode.cn/problems/candy/)
```c++
//双向遍历
class Solution {
public:
    int candy(vector<int>& ratings) {
       int len=ratings.size();
       vector<int> candys(len,1);
       //方向：左→右，当右边优先度大于左边，candys+1
       for(int i=1;i<len;i++)
       {
           if(ratings[i]>ratings[i-1])//右>左
           {
               candys[i]=candys[i-1]+1;
           }
       }
       //方向：右→左，当左边优先度大于右边，candys+1
       for(int i=len-1;i>0;i--)
       {
           if(ratings[i-1]>ratings[i])//左>右
           {
               candys[i-1]=max(candys[i-1],candys[i]+1);
           }
       }
       return std::accumulate(candys.begin(),candys.end(),0);
    }
};
//数组法
class Solution
{
public:
    int candy(vector<int> &ratings)
    {
        int len = ratings.size();
        int *candys=new int[len];
        //memset不能用来初始化1
        fill(candys,candys+len,1);
        //方向：左→右，当右边优先度大于左边，candys+1
        for (int i = 1; i < len; i++)
        {
            if (ratings[i] > ratings[i - 1]) //右>左
            {
                candys[i] = candys[i - 1] + 1;
            }
        }
        //方向：右→左，当左边优先度大于右边，candys+1
        for (int i = len - 1; i > 0; i--)
        {
            if (ratings[i - 1] > ratings[i]) //左>右
            {
                candys[i - 1] = max(candys[i - 1], candys[i] + 1);
            }
        }
        int result = 0;
        for (int i = 0; i < len; i++)
            result += candys[i];
        return result;
    }
};
```
## <span id="435"> [435.无重叠区间](https://leetcode.cn/problems/non-overlapping-intervals/) 
</span>

```c++
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if(0==intervals.size()) return 0;
        sort(intervals.begin(),intervals.end(),[](vector<int> &a,vector<int> &b){
            // if(a[1]==b[1]) return a[0]<b[0];
            return a[1]<b[1];
        });
        int removed=0,prev=intervals[0][1];
        for(int i=1;i<intervals.size();i++)
        {
            if(intervals[i][0]<prev)
            {
                ++removed;
            }
            else
            {
                prev=intervals[i][1];
            }
        }
        return removed;
    }
};
```

## [605.种花问题](https://leetcode.cn/problems/can-place-flowers/)
```c++
class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        int len=flowerbed.size();
        for(int i=0;i<len;i++)
        {
            if(flowerbed[i]==0&&(i==0||!flowerbed[i-1])&&(i==len-1||!flowerbed[i+1]))
            {
                n--;
                flowerbed[i]=1;
            }
            if(n<=0) return true;
        }
        return false;
    }
};

//跳两格
class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        int len=flowerbed.size();
        for(int i=0;i<len;i+=2)
        {
            //当前为空地
            if(flowerbed[i]==0)
            {
                //如果是最后一格或下一个为空
                if(i==len-1||flowerbed[i+1]==0)
                {
                    n--;
                }
                else i++;
            }
            if(n<=0) return true;
        }
        return false;
    }
};
//首尾加0
class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        flowerbed.insert(flowerbed.begin(),0);
        flowerbed.insert(flowerbed.end(),0);
        int len=flowerbed.size();
        for(int i=1;i<len-1;i++)
        {
            if(flowerbed[i]==0)
            {
                if(flowerbed[i-1]==0&&flowerbed[i+1]==0)
                {
                    flowerbed[i]=1;
                    n--;
                }
            }
            if(n<=0) return true;
        }
        return false;
    }
};
```
## [452.用最少的箭引爆气球](https://leetcode.cn/problems/minimum-number-of-arrows-to-burst-balloons/)
和[435无重叠区间](#435)相似
```c++
//方式一
class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        sort(points.begin(),points.end(),[](const vector<int>&a,const vector<int>&b){return a[1]<b[1];});
        int prevBorder=points[0][1];
        int count=1;
        for(int i=1;i<points.size();i++)
        {
            if(prevBorder<points[i][0])
            {
                count++;
                prevBorder=points[i][1];
            }
        }
        return count;
    }
};

//方式二
class Solution {
private:
    static bool cmp(const vector<int>& a, const vector<int>& b) {
        return a[0] < b[0];
    }
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        if (points.size() == 0) return 0;
        sort(points.begin(), points.end(), cmp);

        int result = 1; // points 不为空至少需要一支箭
        for (int i = 1; i < points.size(); i++) {
            if (points[i][0] > points[i - 1][1]) {  // 气球i和气球i-1不挨着，注意这里不是>=
                result++; // 需要一支箭
            }
            else {  // 气球i和气球i-1挨着
                points[i][1] = min(points[i - 1][1], points[i][1]); // 更新重叠气球最小右边界
            }
        }
        return result;
    }
};
```
## [763.划分字母区间](https://leetcode.cn/problems/partition-labels/)
```c++
class Solution {
public:
    vector<int> partitionLabels(string S) {
        int *hash = new int[27]{0}; // i为字符，hash[i]为字符出现的最后位置
        for (int i = 0; i < S.size(); i++) { // 统计每一个字符最后出现的位置
            hash[S[i] - 'a'] = i;
        }
        vector<int> result;
        int left = 0;
        int right = 0;
        for (int i = 0; i < S.size(); i++) {
            right = max(right, hash[S[i] - 'a']); // 找到字符出现的最远边界
            if (i == right) {
                result.push_back(right - left + 1);
                left = i + 1;
            }
        }
        delete []hash;
        return result;
    }
};
```

## [122.买卖股票得最佳时机](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii/)
```c++
//贪心算法
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len=prices.size();
        int sum=0;
        for(int i=0;i<len-1;i++)
        {
            if(prices[i]<prices[i+1])
            {
                sum+=prices[i+1]-prices[i];
            }
        }
        return sum;
    }
};
//动态规划
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int dp[2]={-prices[0],0};//持有，未持有
        for(int i=0;i<prices.size();i++)
        {
            int lastHold=dp[0];
            //持有不动，未持有买入
            dp[0]=max(dp[0],dp[1]-prices[i]);
            //未持有不动，持有卖出
            dp[1]=max(dp[1],lastHold+prices[i]);
        }
        return max(dp[0],dp[1]);
    }
};
```

## [406.根据身高重建队列](https://leetcode.cn/problems/queue-reconstruction-by-height/)
```c++
//使用list比vector插入效率高
class Solution {
public:
    // 身高从大到小排（身高相同k小的站前面）
    static bool cmp(const vector<int> a, const vector<int> b) {
        if (a[0] == b[0]) return a[1] < b[1];
        return a[0] > b[0];
    }
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        sort (people.begin(), people.end(), cmp);
        list<vector<int>> que; // list底层是链表实现，插入效率比vector高的多
        for (int i = 0; i < people.size(); i++) {
            int position = people[i][1]; // 插入到下标为position的位置
            std::list<vector<int>>::iterator it = que.begin();
            while (position--) { // 寻找在插入位置
                it++; 
            }
            que.insert(it, people[i]); 
        }
        return vector<vector<int>>(que.begin(), que.end());
    }
};
```
## [665.非递归数列](https://leetcode.cn/problems/non-decreasing-array/)
```c++
/*
  这道题给了我们一个数组，说我们最多有1次修改某个数字的机会，
  问能不能将数组变为非递减数组。题目中给的例子太少，不能覆盖所有情况，我们再来看下面三个例子：
	4，2，3
	-1，4，2，3
	2，3，3，2，4
我们通过分析上面三个例子可以发现，当我们发现后面的数字小于前面的数字产生冲突后，
[1]有时候需要修改前面较大的数字(比如前两个例子需要修改4)，
[2]有时候却要修改后面较小的那个数字(比如前第三个例子需要修改2)，
那么有什么内在规律吗？是有的，判断修改那个数字其实跟再前面一个数的大小有关系，
首先如果再前面的数不存在，比如例子1，4前面没有数字了，我们直接修改前面的数字为当前的数字2即可。
而当再前面的数字存在，并且小于当前数时，比如例子2，-1小于2，我们还是需要修改前面的数字4为当前数字2；
如果再前面的数大于当前数，比如例子3，3大于2，我们需要修改当前数2为前面的数3。

//题解思路：https://leetcode.cn/problems/non-decreasing-array/comments/
*/
class Solution {
public:
    bool checkPossibility(vector<int>& nums) { 
        if(nums.empty() || nums.size() <= 1)
        return true;
        int cnt = 0;
        for(int i = 1; i < nums.size() && cnt <2; i++)
        {
            if(nums[i-1] <= nums[i])
                continue;
            cnt++;
            if(i-2>=0 && nums[i-2] >nums[i])
                nums[i] = nums[i-1];  //修改当前数字     2 3 3 2 4  ->  2 3 3 3 4 
            else    
                nums[i-1] = nums[i];   //修改前面的数字  -1 4 2 3 ->  -1 2 2 3
        }
        return cnt<=1;
    }
};
```

# 第三章 双指针
指针函数和函数指针
```c++
//指针函数返回类型是指针
int *add(int a,int b)
{
    int *sum=new int(a+b);
    return sum;
}

//函数指针，指向函数的指针
int add1(int a,int b)
{
    return a+b;
}
int (*m)(int,int)=add1;
```

## [167.两数之和II-输入有序数组](https://leetcode.cn/problems/two-sum-ii-input-array-is-sorted/)
```c++
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int left=0,right=numbers.size()-1;
        while(left<right)
        {
            if(numbers[left]+numbers[right]>target) --right;
            else if(numbers[left]+numbers[right]<target) ++left;
            else break;
        }
        return {left+1,right+1};
    }
};
```

## [88.合并两个有序数组](https://leetcode.cn/problems/merge-sorted-array/)
```c++
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int pos=-1+m--+n--;
        while(m>=0&&n>=0)
        {
            nums1[pos--]=nums1[m]>nums2[n]?nums1[m--]:nums2[n--];
        }
        while(n>=0)
        {
            nums1[pos--]=nums2[n--];
        }
    }
};
```

## [142.环形列表](https://leetcode.cn/problems/linked-list-cycle-ii/)
```c++
//地址法
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode *cur=head;
        unordered_set<ListNode*> uset;
        while(cur)
        {
            if(uset.count(cur))
            {
                return cur;
            }
            uset.insert(cur);
            cur=cur->next;
        }
        return NULL;
    }
};
//快慢指针
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode *slow=head,*fast=head;
        do
        {
            if(!fast||!fast->next) return NULL;
            slow=slow->next;
            fast=fast->next->next;
        }while(slow!=fast);
        slow=head;
        while(fast!=slow)
        {
            fast=fast->next;
            slow=slow->next;
        }
        return fast;
    }
};
```

## [76.最小覆盖字串](https://leetcode.cn/problems/minimum-window-substring/)
```c++
class Solution
{
public:
    string minWindow(string s,string t)
    {
        int *need=new int[128]{0};
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
            if (need[c]--> 0)
                count--;
            //need[c]--;      //先把右边的字符加入窗口
            if (count == 0) //窗口中已经包含所需的全部字符
            {
                while (left < right && need[s[left]] < 0) //缩减窗口，不能有重复的字母存在
                {
                    need[s[left++]]++;
                }                            //此时窗口符合要求
                if (right - left + 1 < size) //更新答案
                {
                    size = right - left + 1;
                    start = left;
                }
                need[s[left++]]++; //左边界右移之前需要释放need[s[left]]
                count++;
            }
            right++;
        }
        delete []need;
        return size == INT_MAX ? "" : s.substr(start, size);
    }
};
```

## [633.平方数之和](https://leetcode.cn/problems/sum-of-square-numbers/)
```c++
class Solution {
public:
    bool judgeSquareSum(int c) {
        long left = 0;
        long right = (int)sqrt(c);
        while (left <= right) {
            long sum = left * left + right * right;
            if (sum == c) {
                return true;
            } else if (sum > c) {
                right--;
            } else {
                left++;
            }
        }
        return false;
    }
};
```

## [680.验证回文字符串II](https://leetcode.cn/problems/valid-palindrome-ii/)
```c++
class Solution {
public:
    bool isPalindrome(const string& s,int left,int right)
    {
        while(left<right)
        {
            if(s[left++]!=s[right--])
                return false;
        }
        return true;
    }
    bool validPalindrome(string s) {
        int left=0,right=s.size()-1;
        while(left<right)
        {
            if(s[left]==s[right])
            {
                left++,right--;
            }
            else
            {
                return isPalindrome(s,left,right-1)||isPalindrome(s,left+1,right);
            }
        }
        return true;
    }
};
```

## [524.通过删除字母匹配带字典里最长单词](https://leetcode.cn/problems/longest-word-in-dictionary-through-deleting/)
```c++
class Solution {
public:
    bool isSub(string s,string t)
    {
        int n=s.size(),m=t.size();

        if(m>n) return false;

        int index=0;
        for(char ch:t)
        {
            while(index<n&&s[index]!=ch) index++;
            if(index>=n) return false;
            index++;
        }
        return true;
    }
    string findLongestWord(string s, vector<string>& dictionary) {
        sort(dictionary.begin(),dictionary.end(),[&](string &a,string &b)
        {
            if(a.size()==b.size()) return a<b;
            return a.size()>b.size();
        });
        for(string& t:dictionary)
        {
            if(isSub(s,t)) return t;
        }
        return "";
    }
};
//思路：https://leetcode.cn/problems/longest-word-in-dictionary-through-deleting/solution/suan-fa-xiao-ai-shuang-zhi-zhen-xiang-ji-6rey/
```

# 第四章 二分查找
## [69.x的平方根](https://leetcode.cn/problems/sqrtx/)
```c++
class Solution {
public:
    int mySqrt(int x) {
    int left=0,right=x;
    if(1==x||0==x) return x;
    while(left<right)
    {
        int mid=left+((right-left)>>1);
        if(mid<x/mid)
        {
            left=mid+1;
        }
        else if(mid>x/mid) right=mid;
        else return mid;
    }
    return right-1;
    }
};
```

## <span id="34"> [34.在排序数组中查找元素的第一个和最后一个位置](https://leetcode.cn/problems/find-first-and-last-position-of-element-in-sorted-array/)
</span>
```c++
//库函数
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        auto border=equal_range(nums.begin(),nums.end(),target);
        if(border.first==border.second) return {-1,-1};
        return {(int)(border.first-nums.begin()),(int)(border.second-nums.begin()-1)};
    }
};
//左闭右开
class Solution {
private:
int lower_bound(vector<int>& nums,int target)
{
    int left=0,right=nums.size(),mid;
    while(left<right)
    {
        mid=left+(right-left)/2;
        if(nums[mid]>=target)
        {
            right=mid;
        }
        else
        {
            left=mid+1;
        }
    }   
    return left;
}
int upper_bound(vector<int>& nums,int target)
{
    int left=0,right=nums.size(),mid;
    while(left<right)
    {
        mid=left+(right-left)/2;
        if(nums[mid]<=target)
        {
            left=mid+1;
        }
        else
        {
            right=mid;
        }
    }
    return left-1;
}
public:

    vector<int> searchRange(vector<int>& nums, int target) {
        if(nums.size()==0) return {-1,-1};
        int lower=lower_bound(nums,target);
        int upper=upper_bound(nums,target);
        if(lower==nums.size()||nums[lower]!=target)
        {
            return {-1,-1};
        }
        return {lower,upper};
    }
};
```

## [81.搜索旋转排序数组II](https://leetcode.cn/problems/search-in-rotated-sorted-array-ii/)
```c++
//左闭右闭
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int left=0,right=nums.size()-1;
        while(left<=right)
        {
            int mid=left+(right-left)/2;
            if(nums[mid]==target) return true;
            //无法判断[left,mid]升序还是降序
            if(nums[mid]==nums[left])
            {
                ++left;
            }
            //[mid,right]升序
            else if(nums[mid]<=nums[right])
            {
                if(target>nums[mid]&&target<=nums[right])
                {
                    left=mid+1;
                }
                else
                {
                    right=mid-1;
                }
            }
            //[left,mid]升序
            else
            {
                if(target>=nums[left]&&target<nums[mid])
                {
                    right=mid-1;
                }
                else
                {
                    left=mid+1;
                }
            }
        }
        return false;
        
    }
};
```

## [153.寻找旋转排序数组中的最小值](https://leetcode.cn/problems/find-minimum-in-rotated-sorted-array/)
```c++
/*
    情况1：左值<中值<右值，无旋转，最小值在左边界
    情况2：左值>中值，中值<右值，最小值在左半边
    情况3：左值<中值，中值>右值，最小值在右半边
    情况4：左值>中值>右值，单调递减，不可能出现

    归总：
    1.中值<右值，最小值在左半边
    2.中值>右值，最小值在右半边

    参考网址：https://leetcode.cn/problems/find-minimum-in-rotated-sorted-array/solution/er-fen-cha-zhao-wei-shi-yao-zuo-you-bu-dui-cheng-z/
*/
class Solution {
public:
    int findMin(vector<int>& nums) {
        int left=0,right=nums.size()-1,mid;
        while(left<=right)
        {
            mid=left+(right-left)/2;
            if(nums[mid]<nums[right])
            {
                right=mid;//不取mid-1是因为mid可能也是最小值
            }
            else
            {
                left=mid+1;
            }
        }
        return nums[right];
    }
};

//找最大值
class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;
        while (left < right) {
            int mid = left + (right - left + 1) / 2;   /* 先加一再除，mid更靠近右边的right */
            if (nums[left] < nums[mid]) {
                left = mid;                            /* 向右移动左边界 */
            } else if (nums[left] > nums[mid]) {
                right = mid - 1;                       /* 向左移动右边界 */
            }
        }
        return nums[(right + 1) % nums.size()];    /* 最大值向右移动一位就是最小值了（需要考虑最大值在最右边的情况，右移一位后对数组长度取余） */
    }
};
```
## [154.寻找旋转排序数组中的最小值II](https://leetcode.cn/problems/find-minimum-in-rotated-sorted-array-ii/)
```c++
class Solution {
public:
    int findMin(vector<int>& nums) {
        int left=0,right=nums.size()-1,mid;
        while(left<=right)
        {
            mid=left+(right-left)/2;
            if(nums[mid]>nums[right])
            {
                left=mid+1;
            }
            else if(nums[mid]<nums[right])
            {
                right=mid;
            }
            else
            {
                right--;
            }
        }
        return nums[left];
    }
};
```

## [540.有序数组中的单一元素](https://leetcode.cn/problems/single-element-in-a-sorted-array/)
```c++
/*
成对元素中的第一个所对应的下标必然是偶数，成对元素中的第二个所对应的下标必然是奇数。
参考思路：https://leetcode.cn/problems/single-element-in-a-sorted-array/solution/gong-shui-san-xie-er-duan-xing-fen-xi-yu-17nv/
*/
//异或二分法
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int n = nums.size();
        int l = 0, r = n - 1;
        while (l < r) {
            int mid = l + r >> 1;
            //mid为奇数,mid^1为偶数；mid为偶数，mid^1为奇数
            if (nums[mid] == nums[mid ^ 1]) l = mid + 1;
            else r = mid;
        }
        return nums[r];
    }
};

//二分法
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int n=nums.size();
        int left=0,right=n,mid;
        while(left<right)
        {
            mid=left+(right-left>>1);
            if(mid%2==0)
            {
                if(mid+1<n&&nums[mid]==nums[mid+1]) left=mid+1;
                else right=mid;
            }
            else
            {
                if(mid-1>=0&&nums[mid-1]==nums[mid]) left=mid+1;
                else right=mid;
            }
        }
        return nums[right];
    }
};
```
## [4.寻找两个正序数组的中位数](https://leetcode.cn/problems/median-of-two-sorted-arrays/)
```c++
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int tot = nums1.size() + nums2.size();
        if (tot % 2 == 0) {
            int left = find(nums1, 0, nums2, 0, tot / 2);
            int right = find(nums1, 0, nums2, 0, tot / 2 + 1);
            return (left + right) / 2.0;
        } else {
            return find(nums1, 0, nums2, 0, tot / 2 + 1);
        }
    }

    int find(vector<int>& nums1, int i, vector<int>& nums2, int j, int k) {
        int n1=nums1.size(),n2=nums2.size();
        if (n1 - i > n2 - j) return find(nums2, j, nums1, i, k);
        if (k == 1) {
            //递归找到k=1时，表示找到了该k位数
            if (n1 == i) return nums2[j];
            else return min(nums1[i], nums2[j]);
        }
        if (n1 == i) return nums2[j + k - 1];
        int si = min(n1, i + k / 2), sj = j + k - k / 2;
        //通过比较nums1[si-1]和nums[sj-1]，可以删除最小的部分
        if (nums1[si - 1] > nums2[sj - 1])
        //nums2左侧数据全部抛弃(都比两个数小)，剩下数组查找第k-(sj-j)位数
            return find(nums1, i, nums2, sj, k - (sj - j));
        else
        //nums1左侧数据全部抛弃(都比两个数小)，剩下数组查找第k-(si-i)位数
            return find(nums1, si, nums2, j, k - (si - i));
    }
};
// 链接：https://leetcode.cn/problems/median-of-two-sorted-arrays/solution/di-gui-si-lu-zui-qing-xi-yi-dong-de-ti-j-19yt/
```

# 第五章 排序算法系列
---
动图参考：https://blog.csdn.net/weixin_57095511/article/details/119795137
代码参考：https://github.com/changgyhub/leetcode_101/
代码参考2：https://www.runoob.com/w3cnote/ten-sorting-algorithm.html
代码完整参考：https://blog.csdn.net/mengyujia1234/article/details/90179896


---
算法稳定是指两个相等的数的相对位置排序前后不变。
常用排序：
|排序算法|平均复杂度|最好情况|最坏情况|空间复杂度|稳定性|
|:--:|:--:|:--:|:--:|:--:|:--:|
|冒泡排序|O(n<sup>2</sup>)|O(n<sup>2</sup>)|O(n<sup>2</sup>)|O(1)|稳定|
|插入排序|O(n<sup>2</sup>)|O(n)|O(n<sup>2</sup>)|O(1)|稳定|
|归并排序|O(nlogn)|O(nlogn)|O(nlogn)|O(n+logn)|稳定|
|桶排序|O(n+k)|O(n+k)|O(n<sup>2</sup>)|O(n+k)|稳定|
|计数排序|O(n+k)|O(n+k)|O(n+k)|O(k)|稳定|
|基数排序|O(n×m)|O(n×m)|O(n×m)|O(n+m)|稳定|
|快速排序|O(nlogn)|O(nlogn)|O(n<sup>2</sup>)|O(logn)|不稳定|
|选择排序|O(n<sup>2</sup>)|O(n<sup>2</sup>)|O(n<sup>2</sup>)|O(1)|不稳定|
|希尔排序|O(nlogn)|O(n<sup>1.3</sup>)|O(n<sup>2</sup>)|O(1)|不稳定|
|堆排序|O(nlogn)|O(nlogn)|O(nlogn)|O(1)|不稳定|

* 冒泡排序
```c++
void bubbleSort(vector<int> &nums)
{
    for(int i=nums.size()-1;i>0;i--)
    {
        bool flag=true;
        for(int j=0;j<i;j++)
        {
            if(nums[j]>nums[j+1])
            {
                swap(nums[j],nums[j+1]);
                flag=false;
            }
        }
        if(flag) break;
    }
}
```
* 插入排序
```c++
/*
每一步将一个待排序的数据插入到前面已经排好序的有序序列中，直到插完所有元素为止。
*/
void insertionSort(vector<int> &nums)
{
    for(int i=0;i<nums.size();++i)
    {
        for(int j=i;j>0&&nums[j]<nums[j-1];--j)
        {
            swap(nums[j],nums[j-1]);
        }
    }
}
```
* 归并排序
```c++
/*
    是利用归并的思想实现的排序方法，该算法采用经典的分治（divide-and-conquer）策略将问题分成一些小的问题然后递归求解
*/
//1.左闭右开
//初始化条件：right=nums.size(),left=0
void mergeSort(vector<int> &nums, int left, int right)
{
    if (left + 1 >= right) return;
    // divide
    int mid = left + (right - left) / 2;
    mergeSort(nums, left, mid);
    mergeSort(nums, mid, right);
    // conquer
    static vector<int> temp=nums;
    int p = left, q = mid, i = left;
    while (p < mid || q < right)
    {
        if (q >= right || (p < mid && nums[p] <= nums[q]))
        {
            temp[i++] = nums[p++];
        }
        else
        {
            temp[i++] = nums[q++];
        }
    }
    for (i = left; i < right; ++i)
    {
        nums[i] = temp[i];
    }
}

//2. 左闭右闭
void mergeSort(vector<int> &nums, int left, int right)
{
    if (left  >= right) return;
    // divide
    int mid = left + (right - left) / 2;
    mergeSort(nums, left, mid);
    mergeSort(nums, mid+1, right);
    // conquer
    static vector<int> temp=nums;
    int p = left, q = mid+1, i = left;
    //p∈[left,mid]
    //q∈[mid+1,right]
    while (p <=mid || q <=right)
    {
        if (q > right || (p <= mid && nums[p] <= nums[q]))
        {
            temp[i++] = nums[p++];
        }
        else
        {
            temp[i++] = nums[q++];
        }
    }
    for (i = left; i <= right; ++i)
    {
        nums[i] = temp[i];
    }
}
```
* 桶排序
```c++
void bucketSort(vector<int> &nums,int n)
{
    vector<int> bucket(100,0);
    for(auto num:nums)
        bucket[num]++;
    for(int i=0,j=0;i<bucket.size();i++)
    {
        while(bucket[i]>0)
        {
            nums[j++]=i;
            bucket[i]--;
        }
    }
}

//链表法
const int BUCKET_NUM = 10;

struct ListNode{
        explicit ListNode(int i=0):mData(i),mNext(NULL){}
        ListNode* mNext;
        int mData;
};

ListNode* insert(ListNode* head,int val){
        ListNode dummyNode;
        ListNode *newNode = new ListNode(val);
        ListNode *pre,*curr;
        dummyNode.mNext = head;
        pre = &dummyNode;
        curr = head;
        while(NULL!=curr && curr->mData<=val){
                pre = curr;
                curr = curr->mNext;
        }
        newNode->mNext = curr;
        pre->mNext = newNode;
        return dummyNode.mNext;
}


ListNode* Merge(ListNode *head1,ListNode *head2){
        ListNode dummyNode;
        ListNode *dummy = &dummyNode;
        while(NULL!=head1 && NULL!=head2){
                if(head1->mData <= head2->mData){
                        dummy->mNext = head1;
                        head1 = head1->mNext;
                }else{
                        dummy->mNext = head2;
                        head2 = head2->mNext;
                }
                dummy = dummy->mNext;
        }
        if(NULL!=head1) dummy->mNext = head1;
        if(NULL!=head2) dummy->mNext = head2;
       
        return dummyNode.mNext;
}

void BucketSort(int n,int arr[]){
        vector<ListNode*> buckets(BUCKET_NUM,(ListNode*)(0));
        for(int i=0;i<n;++i){
                int index = arr[i]/BUCKET_NUM;
                ListNode *head = buckets.at(index);
                buckets.at(index) = insert(head,arr[i]);
        }
        ListNode *head = buckets.at(0);
        for(int i=1;i<BUCKET_NUM;++i){
                head = Merge(head,buckets.at(i));
        }
        for(int i=0;i<n;++i){
                arr[i] = head->mData;
                head = head->mNext;
        }
}
```
* [计数排序](https://blog.csdn.net/YF_Li123/article/details/76930121)
```c++
/*
（1）找出待排序的数组中最大和最小的元素
（2）统计数组中每个值为i的元素出现的次数，存入数组C的第i项
（3）对所有的计数累加（从C中的第一个元素开始，每一项和前一项相加）
（4）反向填充目标数组：将每个元素i放在新数组的第C(i)项，每放一个元素就将C(i)减去1
*/
void countingSort(vector<int> &nums,int maxVal)
{
    int len=nums.size();
    if(len<=1) return;
    vector<int> count(maxVal+1,0);
    vector<int> tmp(nums);
    for(auto x:nums)
        count[x]++;
    for(int i=1;i<count.size();i++)
    {
        count[i]+=count[i-1];
    }
    for(int i=len-1;i>=0;i--)
    {
        //a是指数字tmp[i]在count数组中的位置
        int a=tmp[i]-1;
        //b是指当前数的需要放置的位置
        int b=count[a];
        nums[b]=tmp[i];
        count[tmp[i]]--;
    } 
}
```
* [基数排序](https://www.runoob.com/w3cnote/radix-sort.html)
```c++
/*
基数排序是一种非比较型整数排序算法，其原理是将整数按位数切割成不同的数字，然后按每个位数分别比较。
由于整数也可以表达字符串（比如名字或日期）和特定格式的浮点数，所以基数排序也不是只能使用于整数。
*/
int maxbit(int data[], int n) //辅助函数，求数据的最大位数
{
    int maxData = data[0];              ///< 最大数
    /// 先求出最大数，再求其位数，这样有原先依次每个数判断其位数，稍微优化点。
    for (int i = 1; i < n; ++i)
    {
        if (maxData < data[i])
            maxData = data[i];
    }
    int d = 1;
    int p = 10;
    while (maxData >= p)
    {
        //p *= 10; // Maybe overflow
        maxData /= 10;
        ++d;
    }
    return d;
}
void radixSort(int data[], int n) //基数排序
{
    int d = maxbit(data, n);
    int *tmp = new int[n];
    int *count = new int[10]; //计数器
    int i, j, k;
    int radix = 1;
    for(i = 1; i <= d; i++) //进行d次排序
    {
        for(j = 0; j < 10; j++)
            count[j] = 0; //每次分配前清空计数器
        for(j = 0; j < n; j++)
        {
            k = (data[j] / radix) % 10; //统计每个桶中的记录数
            count[k]++;
        }
        //下面一段类似于计数排序
        for(j = 1; j < 10; j++)
            count[j] = count[j - 1] + count[j]; //将tmp中的位置依次分配给每个桶
        for(j = n - 1; j >= 0; j--) //将所有桶中记录依次收集到tmp中
        {
            k = (data[j] / radix) % 10;
            tmp[count[k] - 1] = data[j];
            count[k]--;
        }
        for(j = 0; j < n; j++) //将临时数组的内容复制到data中
            data[j] = tmp[j];
        radix = radix * 10;
    }
    delete []tmp;
    delete []count;
}
```
* [快速排序](https://blog.csdn.net/qq_28584889/article/details/88136498)
```c++
//左闭右闭
void quickSort(vector<int> &nums,int left,int right)
{
    if(left>=right) return;
    int i,j,base,tmp;
    i=left,j=right;
    while(i<j)
    {
        while(nums[j]>=nums[left]&&i<j) j--;
        while(nums[i]<=nums[left]&&i<j) i++;
        if(i<j)
        {
            swap(nums[i],nums[j]);
            //交换操作可以使用异或运算
            /*
                nums[i]=nums[i]^nums[j];
                nums[j]=nums[i]^nums[j];
                nums[i]=nums[i]^nums[j];
            */
        }
    }
    swap(nums[left],nums[i]);
    quickSort(nums,left,i-1);
    quickSort(nums,i+1,right);
}
```
* 选择排序
```c++
/*
首先在未排序序列中找到最小（大）元素，存放到排序序列的起始位置。
再从剩余未排序元素中继续寻找最小（大）元素，然后放到已排序序列的末尾。
重复第二步，直到所有元素均排序完毕。
*/
void selectionSort(vector<int>& nums)
{
    int min;
    for(int i=0;i<nums.size()-1;i++)
    {
        min=i;
        for(int j=i+1;j<nums.size();j++)
        {
            if(nums[j]<nums[min])
                min=j;
        }
        swap(nums[i],nums[min]);
    }
}
```
* [希尔排序](https://www.runoob.com/w3cnote/shell-sort.html)
```c++
/*
先将整个待排序的记录序列分割成为若干子序列分别进行直接插入排序，
待整个序列中的记录"基本有序"时，再对全体记录进行依次直接插入排序
*/
void shellSort(vector<int>&nums,int len)
{
    int h=1;
    while(h<len/3)
    {
        h=3*h+1;
    }
    while(h>=1)
    {
        for(int i=h;i<len;++i)
        {
            for(int j=i;j>=h&&nums[j]<nums[j-h];j-=h)
                swap(nums[j],nums[j-h]);
        }
        h/=3;
    }
}
```
* [堆排序](https://blog.csdn.net/lzuacm/article/details/52853194?utm_medium=distribute.pc_relevant.none-task-blog-2~default~baidujs_baidulandingword~default-0-52853194-blog-83504950.pc_relevant_default&spm=1001.2101.3001.4242.1&utm_relevant_index=3)
```c++
/*
建堆(初始化+调整堆, 时间复杂度为O(n));

拿堆的根节点和最后一个节点交换(siftdown, 时间复杂度为O(n*log n) )
*/
void adjust(vector<int> &nums, int len, int index)
{
    int left = 2*index + 1;
    int right = 2*index + 2;
    int maxIdx = index;
    if(left<len && nums[left] > nums[maxIdx]) maxIdx = left;
    if(right<len && nums[right] > nums[maxIdx]) maxIdx = right;  // maxIdx是3个数中最大数的下标
    if(maxIdx != index)                 // 如果maxIdx的值有更新
    {
        swap(nums[maxIdx], nums[index]);
        adjust(nums, len, maxIdx);       // 递归调整其他不满足堆性质的部分
    }
}
void heapSort(vector<int> &nums, int size)
{
    // 对每一个非叶结点进行堆调整(从最后一个非叶结点开始)
    for(int i=size/2 - 1; i >= 0; i--)  
    {
        adjust(nums, size, i);
    }
    //不断的循环，将最大值放置到数组末尾
    for(int i = size - 1; i >= 1; i--)
    {
        swap(nums[0], nums[i]);
        // 将未完成排序的部分继续进行堆排序      
        adjust(nums, i, 0);
    }
}
```

## [215.数组中的第K个最大元素](https://leetcode.cn/problems/kth-largest-element-in-an-array/)
```c++
class Solution {
public:
    int quickSelection(vector<int>& nums,int left,int right)
    {
        int i=left,j=right;
        int base=nums[left];
        while(i<j)
        {
            while(i<j&&nums[j]>=base) j--;
            while(i<j&&nums[i]<=base) i++;
            if(i<j)
            {
                swap(nums[i],nums[j]);
            }
        }
        swap(nums[left],nums[i]);
        return i;
    }
    int findKthLargest(vector<int>& nums, int k) {
        int left=0,right=nums.size()-1;
        int target=nums.size()-k;
        while(left<right)
        {
            int cur=quickSelection(nums,left,right);
            if(cur==target)
            {
                return nums[cur];
            }
            else if(cur<target)
            {
                left=cur+1;
            }
            else if(cur>target)
            {
                right=cur-1;
            }
        }
        return nums[left];
    }
};
```

## [347.前K个高频元素](https://leetcode.cn/problems/top-k-frequent-elements/)
```c++
//2次快排
class Solution
{
public:
    vector<int> topKFrequent(vector<int> &nums, int k)
    {
        if(nums.size()==k) return nums;
        vector<pair<int,int>> vp;
        vp.push_back({});
        int count=1;
        sort(nums.begin(),nums.end());
        for(int i=0;i<nums.size()-1;i++)
        {
            vp.back().second=nums[i];
            if(nums[i+1]==nums[i])
            {
                ++count;
            }
            else
            {
                vp.back().first=count;
                count=1;
                vp.push_back({1,nums[i+1]});
            }
        }
        if(count>1) vp.back().first=count;
        sort(vp.rbegin(),vp.rend());
        vector<int> res(k,0);
        int index;
        for(index=0;index<k;index++)
        {
            res[index]=vp[index].second;
        }
        return res;
    }
};
//桶排序
class Solution
{
public:
    vector<int> topKFrequent(vector<int> &nums, int k)
    {
        unordered_map<int, int> counts;
        int max_count = 0;
        for (const int &num : nums)
        {
            max_count = max(max_count, ++counts[num]);
        }

        vector<vector<int>> buckets(max_count + 1);
        for (const auto &p : counts)
        {
            buckets[p.second].push_back(p.first);
        }

        vector<int> ans;
        for (int i = max_count; i >= 0 && ans.size() < k; --i)
        {
            for (const int &num : buckets[i])
            {
                ans.push_back(num);
                if (ans.size() == k)
                {
                    break;
                }
            }
        }
        return ans;
    }
};
```

## [451.根据字符出现频率排序](https://leetcode.cn/problems/sort-characters-by-frequency/)
```c++
//桶排序
class Solution
{
public:
    string frequencySort(string s)
    {
        int len = s.size();
        int max_count = 0;
        if (len <= 2)
            return s;
        unordered_map<char, int> umap;
        for (auto ch : s)
        {
            max_count = max(max_count, ++umap[ch]);
        }
        vector<vector<char>> buckets(max_count + 1);
        for (const auto &p : umap)
        {
            buckets[p.second].push_back(p.first);
        }
        string res = "";
        for (int i = max_count; i >= 0; i--)
        {
            int len1=buckets[i].size();
            if(len1==0) continue;
            for (int j = 0; j < len1; j++)
            {
                int count = i;
                while (count--)
                {
                    res += buckets[i][j];
                }
            }
        }
        return res;
    }
};
//2次快排
class Solution
{
public:
    string frequencySort(string s)
    {
        int len = s.size();
        int count = 1;
        if (len <= 2)
            return s;
        string ret = "";
        sort(s.begin(), s.end());
        vector<pair<int, char>> vp;
        vp.push_back({});
        for (int i = 0; i < len - 1; i++)
        {
            vp.back().second = s[i];
            if (s[i + 1] == s[i])
            {
                ++count;
            }
            else
            {
                vp.back().first=count;
                count=1;
                vp.push_back({1,s[i+1]});
            }
        }
        if(count>1) vp.back().first=count;
        sort(vp.rbegin(),vp.rend());
        for(const pair<int,char> &p:vp)
        {
            count=p.first;
            while(count--)
                ret+=p.second;
        } 
        return ret;
    }
};
```

## [75.颜色分类](https://leetcode.cn/problems/sort-colors/)
```c++
//双指针
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int zero=0;
        int two=nums.size()-1;
        for(int i=0;i<=two;)
        {
            if(nums[i]==1)
                i++;
            else if(nums[i]==2)
                swap(nums[i],nums[two--]);
            else if(nums[i]==0)
                swap(nums[i++],nums[zero++]);
        }
    }
};
```

# 第六章 一切皆可搜索
* 深度优先搜索(DFS)
 * 搜索到一个新的节点时，立即对该新节点进行遍历
 * 使用先入后出的栈实现，也可以通过与栈等价的递归实现
* 广度优先搜索(BFS)

## [695.岛屿的最大面积](https://leetcode.cn/problems/max-area-of-island/)
```c++
//栈
class Solution {
public:
    int *dir=new int[5]{-1,0,1,0,-1};
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int rows=grid.size();
        if(rows==0) return 0;
        int cols=grid[0].size();
        int x,y,local_area,area=0;
        for(int i=0;i<rows;i++)
        {
            for(int j=0;j<cols;j++)
            {
                if(1==grid[i][j])
                {
                    local_area=1;
                    stack<pair<int,int>> island;
                    grid[i][j]=0;
                    island.push({i,j});
                    while(!island.empty())
                    {
                        pair<int,int> p=island.top();
                        island.pop();
                        for(int k=0;k<4;k++)
                        {
                            x=p.first+dir[k];
                            y=p.second+dir[k+1];
                            if(x>=0&&x<rows&&y>=0&&y<cols&&grid[x][y]==1)
                            {
                                grid[x][y]=0;
                                ++local_area;
                                island.push({x,y});
                            }
                        }
                    }
                    area=max(area,local_area);
                }
            }
        }
        delete []dir;
        return area;
    }
};
//递归法
class Solution {
public:
    const int *dir=new int[5]{-1,0,1,0,-1};
    int dfs(vector<vector<int>>& grid,int x,int y)
    {
        if(grid[x][y]==0) return 0;
        grid[x][y]=0;
        int newX,newY,area=1;
        for(int i=0;i<4;i++)
        {
            newX=x+dir[i];
            newY=y+dir[i+1];
            if(newX>=0&&newX<grid.size()&&newY>=0&&newY<grid[0].size())
                area+=dfs(grid,newX,newY);
        }
        return area;
    }
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        if(grid.empty()||grid[0].empty()) return 0;
        int max_area=0;
        int m=grid.size(),n=grid[0].size();
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(1==grid[i][j])
                {
                    max_area=max(max_area,dfs(grid,i,j));
                }
            }
        }
        delete []dir;
        return max_area;
    }
};
```

## [547.省份数量](https://leetcode.cn/problems/number-of-provinces/)
```c++
//并查集
class Solution {
private:
    int father[210];
    int n;

    void init()
    {
        for(int i=0;i<n;++i)
            father[i]=i;
    }

    int find(int x)
    {
        return father[x]==x?x:find(father[x]);
    }

    void join(int x1,int x2)
    {
        father[find(x1)]=find(x2);
    }

    bool same(int x1,int x2)
    {
        return find(x1)==find(x2);
    }
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        n=isConnected.size();
        init();
        for(int i=0;i<n;i++)
        {
            for(int j=i+1;j<n;j++)
            {
                if(isConnected[i][j])
                    join(i,j);
            }
        }

        unordered_set<int> uset;
        for(int i=0;i<n;i++)
        {
            uset.insert(find(i));
        }
        return uset.size();
    }
};
/*
参考思路1：https://leetcode.cn/problems/number-of-provinces/solution/547-sheng-fen-shu-liang-bing-cha-ji-ji-c-qcj6/

参考思路2：https://www.jianshu.com/p/fc17847b0a31
*/

//深度优先
class Solution {
public:
    void dfs(vector<vector<int>>& isConnected,int i,vector<bool>& visited)
    {
        visited[i]=true;
        for(int k=0;k<isConnected.size();k++)
        {
            if(isConnected[i][k]==1&&!visited[k])
            {
                dfs(isConnected,k,visited);
            }
        }
    }
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n=isConnected.size(),count=0;
        vector<bool> visited(n,false);
        for(int i=0;i<n;++i)
        {
            if(!visited[i])
            {
                dfs(isConnected,i,visited);
                count++;
            }
        }
        return count;
    }
};
```

## [417.太平洋大西洋水流问题](https://leetcode.cn/problems/pacific-atlantic-water-flow/)
```c++
class Solution {
public:
    int dir[5]={-1,0,1,0,-1};
    void dfs(const vector<vector<int>>& heights,vector<vector<bool>>& can_reach,int r,int c)
    {
        if(can_reach[r][c]) return;
        can_reach[r][c]=true;
        int x,y;
        for(int i=0;i<4;i++)
        {
            x=r+dir[i];
            y=c+dir[i+1];
            if(x>=0&&x<heights.size()&&y>=0&&y<heights[0].size()&&heights[x][y]>=heights[r][c])
                dfs(heights,can_reach,x,y);
        }
    }
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        if(heights.size()==0||heights[0].size()==0) return {};
        int m=heights.size();
        int n=heights[0].size();
        vector<vector<int>> res;
        vector<vector<bool>> toPac(m,vector<bool>(n,false));
        vector<vector<bool>> toAtl(m,vector<bool>(n,false));
        for(int i=0;i<m;i++)
        {
            dfs(heights,toPac,i,0);
            dfs(heights,toAtl,i,n-1);
        }
        for(int j=0;j<n;j++)
        {
            dfs(heights,toPac,0,j);
            dfs(heights,toAtl,m-1,j);
        }
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(toPac[i][j]&&toAtl[i][j])
                    res.push_back({i,j});
            }
        }
        return res;
    }
};
```

## [46.全排列](https://leetcode.cn/problems/permutations/)
```c++
class Solution
{
private:
    vector<vector<int>> ans;
    vector<int> path;
    int *used = new int[21]{0};

public:
    void backtrack(vector<int> &nums)
    {
        if (path.size() == nums.size())
        {
            ans.emplace_back(path);
            return;
        }
        for (int i = 0; i < nums.size(); i++)
        {
            if (used[i])
                continue;
            path.emplace_back(nums[i]);
            used[i] = 1;
            backtrack(nums);
            used[i] =0;
            path.pop_back();
        }
    }
    vector<vector<int>> permute(vector<int> &nums)
    {
        backtrack(nums);
        delete[] used;
        return ans;
    }
};
//方式2
class Solution
{
private:
    vector<vector<int>> ans;
    vector<int> path;
    int *used = new int[21]{0};

public:
    // 主函数
    vector<vector<int>> permute(vector<int> &nums)
    {
        vector<vector<int>> ans;
        backtracking(nums, 0, ans);
        return ans;
    }
    // 辅函数
    void backtracking(vector<int> &nums, int level, vector<vector<int>> &ans)
    {
        if (level == nums.size() - 1)
        {
            ans.push_back(nums);
            return;
        }
        for (int i = level; i < nums.size(); i++)
        {
            swap(nums[i], nums[level]);         // 修改当前节点状态
            backtracking(nums, level + 1, ans); // 递归子节点
            swap(nums[i], nums[level]);         // 回改当前节点状态
        }
    }
};
```

## [77.组合](https://leetcode.cn/problems/combinations/)
```c++
class Solution {
public:
    vector<vector<int>> res;
    vector<int> path;
    void backtrack(int index,int n,int k)
    {
        if(path.size()==k)
        {
            res.emplace_back(path);
            return;
        }
        //k-path.size()：剩余数字数量
        //+1：从1开始
        //n-(k-path.size())+1：表示当前索引最多能到的位置
        for(int i=index;i<=n-(k-path.size())+1;i++)
        {
            path.emplace_back(i);
            backtrack(i+1,n,k);
            path.pop_back();
        }
    }
    vector<vector<int>> combine(int n, int k) {
        backtrack(1,n,k);
        return res;
    }
};
//固定空间解法
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res;
        vector<int> comb(k,0);
        int count=0;
        backtrack(res,comb,0,1,n,k);
        return res;
    }
    void backtrack(vector<vector<int>>& ans,vector<int>&comb,int count,int pos,int n,int  k)
    {
        if(count==k)
        {
            ans.emplace_back(comb);
            return;
        }
        for(int i=pos;i<=n;i++)
        {
            comb[count]=i;
            backtrack(ans,comb,count+1,i+1,n,k);
        }
    }

};
```

## [79.单词搜索](https://leetcode.cn/problems/word-search/)
```c++
class Solution {
public:
    int dir[5]={-1,0,1,0,-1};
    bool dfs(vector<vector<char>>& board,string word,int index,int x,int y)
    {
        if(board[x][y]!=word[index]) return false;
        if(index==word.size()-1) return true;
        char t=board[x][y];
        board[x][y]='0';
        int newX,newY;
        for(int i=0;i<4;i++)
        {
            newX=dir[i]+x;
            newY=dir[i+1]+y;
            if(newX<0||newX>=board.size()||newY<0||newY>=board[0].size()) continue;
            if(dfs(board,word,index+1,newX,newY)) return true;
        }   
        board[x][y]=t;
        return false;
    }
    bool exist(vector<vector<char>>& board, string word) {
        for(int i=0;i<board.size();i++)
        {
            for(int j=0;j<board[0].size();j++)
            {
                if(word[0]==board[i][j])
                {
                    if(dfs(board,word,0,i,j))
                        return true;
                }
            }
        }
        return false;
    }
};

//方式2
class Solution
{
public:
    // 主函数
    bool exist(vector<vector<char>> &board, string word)
    {
        if (board.empty())
            return false;
        int m = board.size(), n = board[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        bool find = false;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                backtracking(i, j, board, word, find, visited, 0);
            }
        }
        return find;
    }
    // 辅函数
    void backtracking(int i, int j, vector<vector<char>> &board, string &word, bool &find, vector<vector<bool>> &visited, int pos)
    {
        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size())
        {
            return;
        }
        if (visited[i][j] || find || board[i][j] != word[pos])
        {
            return;
        }
        if (pos == word.size() - 1)
        {
            find = true;
            return;
        }
        visited[i][j] = true; // 修改当前节点状态
        // 递归子节点
        backtracking(i + 1, j, board, word, find, visited, pos + 1);
        backtracking(i - 1, j, board, word, find, visited, pos + 1);
        backtracking(i, j + 1, board, word, find, visited, pos + 1);
        backtracking(i, j - 1, board, word, find, visited, pos + 1);
        visited[i][j] = false; // 回改当前节点状态
    }
};
```

## [51.N皇后](https://leetcode-cn.com/problems/n-queens/)
```c++
class Solution
{
public:
    vector<vector<string>> res;
    void backTrack(int n, int row, vector<string> &chessboard)
    {
        if (n == row)
        {
            res.emplace_back(chessboard);
            return;
        }
        for (int col = 0; col < n; col++)
        {
            if(isValid(row,col,chessboard,n))
            {
                chessboard[row][col]='Q';
                backTrack(n,row+1,chessboard);
                chessboard[row][col]='.';
            }
        }
    }
    bool isValid(int row, int col, vector<string> &chessboard, int n)
    {
        int count = 0;
        //检查列
        for (int i = 0; i < row; i++)
            if (chessboard[i][col] == 'Q')
                return false;
        // 45°角
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
            if (chessboard[i][j] == 'Q')
                return false;
        //135°角
        for(int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++)
            if(chessboard[i][j]=='Q')
                return false;
        return true;
    }
    vector<vector<string>> solveNQueens(int n)
    {
        vector<string> chessBoard(n,string(n,'.'));
        backTrack(n,0,chessBoard);
        return res;
    }
};
```
## [934.最短的桥](https://leetcode.cn/problems/shortest-bridge/)
```c++
class Solution {
public:
    int dir[5]={-1,0,1,0,-1};
    //存储边界0的位置
    queue<pair<int,int>> points;
    //将1的位置变为2，将0的位置存储
    void dfs(vector<vector<int>>& grid,int m,int n,int x,int y)
    {
        if(x<0||y<0||x>=m||y>=n||grid[x][y]==2)
            return;
        if(grid[x][y]==0)
        {
            points.push(make_pair(x,y));
            return;
        }
        grid[x][y]=2;
        for(int d=0;d<4;d++)
        {
            dfs(grid,m,n,x+dir[d],y+dir[d+1]);
        }
    }
    int shortestBridge(vector<vector<int>>& grid) {
        int m=grid.size(),n=grid[0].size();
        //找到第一个岛屿位置并全部置2
        int flag=false;
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(grid[i][j]==1)
                {
                    dfs(grid,m,n,i,j);
                    flag=true;
                    break;
                }
            }
            if(flag) break;
        }

        //找第二个岛屿，一旦找到就结束
        int x,y,level=0;
        while(!points.empty())
        {
            ++level;
            int len=points.size();
            while(len--)
            {
                auto [r,c]=points.front();
                grid[r][c]=2;
                points.pop();
                for(int d=0;d<4;d++)
                {
                    x=r+dir[d],y=c+dir[d+1];
                    if(x>=0&&y>=0&&x<m&&y<n)
                    {
                        if(2==grid[x][y])
                            continue;
                        if(1==grid[x][y])
                            return level;
                            points.push({x,y});
                            grid[x][y]=2;
                    }
                }
            }
        }
        return 0;
    }
};
```

## [130.被围绕的区域](https://leetcode.cn/problems/surrounded-regions/)
```c++
class Solution {
public:
    int rows, cols;

    void dfs(vector<vector<char>>& board, int x, int y) {
        if (x < 0 || x >= rows || y < 0 || y >= cols || board[x][y] != 'O') {
            return;
        }
        board[x][y] = 'A';
        dfs(board, x + 1, y);
        dfs(board, x - 1, y);
        dfs(board, x, y + 1);
        dfs(board, x, y - 1);
    }

    void solve(vector<vector<char>>& board) {
        rows = board.size();
        if (rows == 0) {
            return;
        }
        cols = board[0].size();
        //对边上的'O'进行标记
        for (int i = 0; i < rows; i++) {
            dfs(board, i, 0);
            dfs(board, i, cols - 1);
        }
        for (int i = 1; i < cols - 1; i++) {
            dfs(board, 0, i);
            dfs(board, rows - 1, i);
        }
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (board[i][j] == 'A') {
                    board[i][j] = 'O';
                } else if (board[i][j] == 'O') {
                    board[i][j] = 'X';
                }
            }
        }
    }
};
```

## [127.单词接龙](https://leetcode.cn/problems/word-ladder/)
```c++
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> words(wordList.begin(), wordList.end());
        if ( words.empty() || words.find(endWord) == words.end() ) return 0;
        words.erase(beginWord);
        queue<string> que;
        que.push(beginWord);
        //depth相当于树的层数
        int depth = 1;
        while ( !que.empty() ) {
            // 找到没有被访问过, 而且能够由当前单词转换而成的单词
            int n = que.size();
            //下一层的while结束表示树的深度+1
            while ( n-- ) {
                string curWord = que.front();
                que.pop();
                // 当前单词的每个字符都替换成其他的25个字符, 然后在单词表中查询
                for ( int i = 0; i < curWord.size(); ++i ) {
                    char originalChar = curWord[i];
                    for ( int j = 0; j < 26; ++j ) {
                        if ( char('a' + j) == originalChar ) continue;
                        curWord[i] = 'a' + j;
                        //如果单词表中存在且未被访问过
                        if ( words.find(curWord) != words.end()) {
                            if ( curWord == endWord ) return depth + 1;
                            else {
                                que.push(curWord);
                                //如果找到，则直接在字符表中删除
                                words.erase(curWord);
                            }
                        }
                    }
                    curWord[i] = originalChar;
                }
            }
            ++depth;
        }
        return 0;
    }
};
//参考思路：https://leetcode-cn.com/problems/word-ladder/solution/yan-du-you-xian-bian-li-shuang-xiang-yan-du-you-2/
```

## [126.单词接龙II](https://leetcode.cn/problems/word-ladder-ii/)
```c++
class Solution
{
public:
   vector<vector<string>> findLadders(string beginWord, string endWord, vector<string> &wordList)
   {
      vector<vector<string>> res;
      unordered_set<string> words{wordList.begin(), wordList.end()};
      unordered_set<string> visited;
      queue<vector<string>> que;
      words.erase(beginWord);
      que.push({beginWord});
      while (!que.empty())
      {
         int n = que.size();
         while (n--)
         {
            vector<string> curPath = que.front();
            que.pop();
            string curWord = curPath.back();
            for (int i = 0; i < curWord.size(); i++)
            {
               char originChar = curWord[i];
               for(char c='a';c<='z';c++)
               {
                  curWord[i]=c;
                  //替换后成功在单词表中找到
                  if(words.count(curWord)==1)
                  {
                     vector<string> newPath=curPath;
                     newPath.push_back(curWord);
                     //标记该单词
                     visited.insert(curWord);
                     if(curWord!=endWord)
                     {
                        que.push(newPath);
                     }
                     else
                     {
                        res.push_back(newPath);
                     }
                  }
               }
               curWord[i]=originChar;
            }
         }
         for(auto &str:visited)
          words.erase(str);
      }
      return res;
   }
};
```

## [157.二叉树的所有路径](https://leetcode.cn/problems/binary-tree-paths/)
```c++
//迭代法
class Solution {
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        if(!root) return{};
        stack<TreeNode*> st;
        stack<string> pathst;
        vector<string> res;
        st.push(root);
        pathst.push(to_string(root->val));
        while(!st.empty())
        {
            TreeNode *node=st.top();
            st.pop();
            string path=pathst.top();
            pathst.pop();
            if(!node->left&&!node->right)
            {
                res.push_back(path);
            }
            if(node->left)
            {
                st.push(node->left);
                pathst.push(path+"->"+to_string(node->left->val));
            }
            if(node->right)
            {
                st.push(node->right);
                pathst.push(path+"->"+to_string(node->right->val));
            }
        }
        return res;
    }
};
//递归法
class Solution {
public:
    void dfs(TreeNode* cur,string path,vector<string>& res)
    {
        path+=to_string(cur->val);
        if(!cur->left&&!cur->right)
        {
            res.push_back(path);
            return;
        }
        if(cur->left) dfs(cur->left,path+"->",res);
        if(cur->right) dfs(cur->right,path+"->",res);
    }
    vector<string> binaryTreePaths(TreeNode* root) {
        if(!root) return {};
        vector<string> res;
        dfs(root,"",res);
        return res;
    }
};
```

## [40.组合总和II](https://leetcode.cn/problems/combination-sum-ii/)
```c++
class Solution
{
public:
    vector<vector<int>> res;
    vector<int> path;
    void backTrack(vector<int> &candidates, int target, int start)
    {
        if(target==0)
        {
            res.push_back(path);
            return;
        }
        for(int i=start;i<candidates.size();i++)
        {
            if(i>start&&candidates[i]==candidates[i-1])
            {
                continue;
            }
            if(candidates[i]>target) break;
            path.emplace_back(candidates[i]);
            backTrack(candidates,target-candidates[i],i+1);
            path.pop_back();
        }
    }
    vector<vector<int>> combinationSum2(vector<int> &candidates, int target)
    {
        sort(candidates.begin(),candidates.end());
        backTrack(candidates,target,0);
        return res;
    }
};
```

## [47.全排列II](https://leetcode.cn/problems/permutations-ii/)
```c++
class Solution {
private:
    vector<vector<int>> res;
    vector<int> path;
    void dfs(const vector<int>& nums,bool* used)
    {
        if(path.size()==nums.size())
        {
            res.push_back(path);
            return;
        }
        for(int i=0;i<nums.size();i++)
        {
            if(i>0&&nums[i-1]==nums[i]&&!used[i-1])
                continue;
            if(!used[i])
            {
                used[i]=true;
                path.push_back(nums[i]);
                dfs(nums,used);
                path.pop_back();
                used[i]=false;
            }
        }
    }
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(),nums.end(),less<int>());
        bool *used=new bool[nums.size()]{false};
        dfs(nums,used);
        delete[]used;
        return res;
    }
};
```

## [37.解数独](https://leetcode.cn/problems/sudoku-solver/)
```c++
class Solution
{
private:
    bool backtracking(vector<vector<char>> &board)
    {
        for (int i = 0; i < board.size(); i++)
        { // 遍历行
            for (int j = 0; j < board[0].size(); j++)
            { // 遍历列
                if (board[i][j] != '.')
                    continue;
                for (char k = '1'; k <= '9'; k++)
                { // (i, j) 这个位置放k是否合适
                    if (isValid(i, j, k, board))
                    {
                        board[i][j] = k; // 放置k
                        if (backtracking(board))
                            return true;   // 如果找到合适一组立刻返回
                        board[i][j] = '.'; // 回溯，撤销k
                    }
                }
                return false; // 9个数都试完了，都不行，那么就返回false
            }
        }
        return true; // 遍历完没有返回false，说明找到了合适棋盘位置了
    }
    bool isValid(int row, int col, char val, vector<vector<char>> &board)
    {
        for (int i = 0; i < 9; i++)
        { // 判断行里是否重复
            if (board[row][i] == val||board[i][col]==val)
            {
                return false;
            }
        }
        int startRow = (row / 3) * 3;
        int startCol = (col / 3) * 3;
        for (int i = startRow; i < startRow + 3; i++)
        { // 判断9方格里是否重复
            for (int j = startCol; j < startCol + 3; j++)
            {
                if (board[i][j] == val)
                {
                    return false;
                }
            }
        }
        return true;
    }

public:
    void solveSudoku(vector<vector<char>> &board)
    {
        backtracking(board);
    }
};
```

## [310.最小高度树](https://leetcode.cn/problems/minimum-height-trees/)
```c++
/*
总体思路：
1. 找到从下往上的最外面一层的节点，这些节点度为1，将这些节点置于队列q
2.将q中的节点自身对应的度-1，将q中节点的相邻节点对应的度-1，并将新的度为1的节点放入队列q
3.当q中无数据时，表示ans中的节点都可以作为根标签
*/
class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if (n == 1) {
            return {0};
        }
        vector<int> degree(n);// 每个节点对应的度数，因为是无向图，所以出入度一起统计
        vector<vector<int>> mp(n);// 每个节点的邻接表
        vector<int> ans;// 返回值
        //统计每个节点和其邻接表
        for (int i = 0; i < edges.size(); i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            degree[u]++;
            degree[v]++;
            mp[u].emplace_back(v);
            mp[v].emplace_back(u);
        }
        queue<int> q;
        for (int i = 0; i < n; i++) {
            //度为1，一定为从下往上看最外面一层的叶子节点
            if (degree[i] == 1) {
                q.push(i); // 把叶子节点（度为1）入队列
            }
        }
        //只有当q为空，则表示得到头节点
        //while循环的次数+1=最小的高度
        while (!q.empty()) {
            //清空为了保存新的层
            ans.clear();
            int sz = q.size();
            for (int i = 0; i < sz; i++) {
                int node = q.front();
                q.pop();
                ans.emplace_back(node);
                //node节点的度-1
                degree[node]--;
                //node节点的相邻节点的度都-1，同时再次放入度为1的节点
                for(int j : mp[node]) {
                    degree[j]--;
                    if(degree[j] == 1) {
                        q.push(j);//新的度为1的节点加入队列
                    }
                }
            }
        }
        return ans;
    }
};
//参考思路：https://leetcode.cn/problems/minimum-height-trees/comments/1488770
```

# 第七章 动态规划
动态规划和其他遍历算法(如dfs、dfs)都是将原问题拆成多个子问题然后求解，但是**动态规划保存子问题的解，避免重复计算**。
## [70.爬楼梯](https://leetcode.cn/problems/climbing-stairs/)
```c++
class Solution {
public:
    int climbStairs(int n) {
        if(n<=2) return n;
        int dp[3]={1,2,3};
        for(int i=2;i<n;i++)
        {
            dp[2]=dp[1]+dp[0];
            dp[0]=dp[1];
            dp[1]=dp[2];
        }
        return dp[2];
    }
};
```

## [198.打家劫舍](https://leetcode.cn/problems/house-robber/)
```c++
class Solution {
public:
    int rob(vector<int>& nums) {
        int n=nums.size();
        if(n==1) return nums[0];
        //dp:最高持有金额
        int dp[3]={nums[0],max(nums[0],nums[1]),max(nums[0],nums[1])};
        for(int i=2;i<n;i++)
        {
            dp[2]=max(dp[0]+nums[i],dp[1]);
            dp[0]=dp[1];
            dp[1]=dp[2];
        }
        return dp[2];
    }
};
```
## [413.等差数列划分](https://leetcode.cn/problems/arithmetic-slices/)
```c++
class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        int n=nums.size();
        if(n<3) return 0;
        vector<int> dp(n,0);
        for(int i=2;i<n;i++)
        {
            if(nums[i]-nums[i-1]==nums[i-1]-nums[i-2])
                dp[i]=dp[i-1]+1;
        }
        return accumulate(dp.begin(),dp.end(),0,[](int x,int y){return x+y;});
    }
};
```

## [64.最小路径和](https://leetcode.cn/problems/minimum-path-sum/)
```c++
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int rows=grid.size(),cols=grid[0].size();
        vector<int> dp(cols,0);
        dp[0]=grid[0][0];
        for(int j=1;j<cols;j++)
        {
            dp[j]=dp[j-1]+grid[0][j];
        }
        for(int i=1;i<rows;i++)
        {
            dp[0]+=grid[i][0];
            for(int j=1;j<cols;j++)
            {
                dp[j]=min(dp[j],dp[j-1])+grid[i][j];
            }
        }
        return dp.back();
    }
};
```

## [542.01矩阵](https://leetcode.cn/problems/01-matrix/)
```c++
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        if(mat.empty()) return{};
        int m=mat.size();
        int n=mat[0].size();
        vector<vector<int>> dp(m,vector<int>(n,INT_MAX-1));
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(0==mat[i][j])
                {
                    dp[i][j]=0;
                }
                else
                {
                    if(j>0)
                        dp[i][j]=min(dp[i][j],dp[i][j-1]+1);
                    if(i>0)
                        dp[i][j]=min(dp[i][j],dp[i-1][j]+1);
                }
            }
        }

        for(int i=m-1;i>=0;i--)
        {
            for(int j=n-1;j>=0;j--)
            {
                if(mat[i][j])
                {
                    if(j<n-1)
                        dp[i][j]=min(dp[i][j],dp[i][j+1]+1);
                    if(i<m-1)
                        dp[i][j]=min(dp[i][j],dp[i+1][j]+1);
                }
            }
        }
        return dp;
    }
};
```

## [221.最大正方形](https://leetcode.cn/problems/maximal-square/)
```c++
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int m=matrix.size(),n=matrix[0].size();
        vector<vector<int>> dp(m,vector<int>(n,0));
        int maxEdge=0;
        for(int i=0;i<m;i++)
            if(matrix[i][0]=='1')
                dp[i][0]=maxEdge=1;
        for(int j=0;j<n;j++)
            if(matrix[0][j]=='1')
                dp[0][j]=maxEdge=1;
        
        for(int i=1;i<m;++i)
        {
            for(int j=1;j<n;++j)
            {
                if(matrix[i][j]=='0') continue;
                int len1=dp[i-1][j];
                int len2=dp[i][j-1];
                int len3=dp[i-1][j-1];
                dp[i][j]=min(min(len1,len2),len3)+1;
                maxEdge=max(maxEdge,dp[i][j]);
            }
        }
        return maxEdge*maxEdge;
    }
};
```

## [279.完全平方数](https://leetcode.cn/problems/perfect-squares/)
```c++
//01背包
class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n+1,INT_MAX);
        dp[0]=0;
        for(int i=0;i<=n;i++)//背包
        {
            for(int j=1;j*j<=i;j++)//物品
                dp[i]=min(dp[i],dp[i-j*j]+1);
        }
        return dp.back();
    }
};
```

## [91.解码方法](https://leetcode.cn/problems/decode-ways/)
```c++
//类似于跳台阶的动态规划
class Solution {
public:
    int numDecodings(string s) {
        int n=s.size();
        if(s[0]=='0') return 0;
        vector<int> dp(n+1,0);
        dp[0]=1;
        dp[1]=1;
        for(int i=2;i<dp.size();i++)
        {
            if(s[i-1]!='0') dp[i]=dp[i-1];
            int t=(s[i-2]-'0')*10+s[i-1]-'0';
            if(t>=10&&t<=26) dp[i]+=dp[i-2];
        }
        return dp.back();
    }
};

//方式二
class Solution {
public:
    int numDecodings(string s) {
        if(s[0]=='0') return 0;
        int n=s.size();
        //dp[i]标识s[i-1]目前状态
        vector<int> dp(n+1,0);
        dp[0]=dp[1]=1;
        for(int i=2;i<=n;i++)
        {
            if(s[i-1]=='0')
            {
                if(s[i-2]=='1'||s[i-2]=='2')
                    dp[i]=dp[i-2];
                //如果不是20或10，其余比如30、40等拆开也是不能解码的，
                else
                    return 0;
            }
            else if(s[i-2]=='1'||(s[i-2]=='2'&&s[i-1]>='1'&&s[i-1]<='6'))
                dp[i]=dp[i-2]+dp[i-1];
            else
                dp[i]=dp[i-1];
        }
        return dp[n];
    }
};
```

## [139.单词拆分](https://leetcode.cn/problems/word-break/)
```c++
//直接动态规划
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int n=s.size();
        vector<bool> dp(n+1,false);
        dp[0]=true;
        for(int i=1;i<=n;++i)
        {
            for(const string &word:wordDict)
            {
                int len=word.size();
                if(i>=len&&s.substr(i-len,len)==word)
                {
                    dp[i]=dp[i]||dp[i-len];
                }
            }
        }
        return dp[n];
    }
};
//集合辅助动态规划
class Solution {
public:
    bool wordBreak(string& s, vector<string>& wordDict) {
        const int len = s.length();
        vector<bool> flag(len + 1, false);
        set<string> buf(wordDict.begin(), wordDict.end());
        
        int minlen = 0, maxlen = 0;
        //找到最小的字符长度和最大的字符长度
        for (auto& str : wordDict) {
            const int tl = str.length();
            maxlen = max(maxlen, tl);
            if (minlen == 0 || tl < minlen)
                minlen = tl;
        }
     
        flag[0] = true;
        //i不用从1开始，只要从wordDict字符串的最小长度开始
        //j也不用从0开始，只要从i-maxWordLength开始搜索
        for (int i = minlen; i <= len; ++i) {
            for (int j = max(0, i - maxlen); j < i; ++j) {
                if (flag[j] && buf.count(s.substr(j, i-j))) {
                    flag[i] = true;
                    break;
                }
            }
        }
        
        return flag[len];
    }
};
```

## [300.最长递增子序列](https://leetcode.cn/problems/longest-increasing-subsequence/)
lower_bound写法参考[leetcode 34](#34)
```c++
//最佳写法
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> minnums;
        for(int v : nums)
        {
            //在minnums找到大于等于v的第一个数的位置
            auto pos = lower_bound(minnums.begin(), minnums.end(), v);
            //没找到，所以可以添加数字v
            if(pos == minnums.end()) {
                minnums.push_back(v);
            } 
            //找到了，则将minnums对应位置的数替换为v
            else {
                *pos = v;
            }
        }
        return minnums.size();
    }
};
//动态规划
//时间复杂度O(n^2)
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n=nums.size();
        int res=INT_MIN;
        vector<int> dp(n,1);
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<i;j++)
            {
                if(nums[i]>nums[j])
                {
                    dp[i]=max(dp[i],dp[j]+1);
                    res=max(dp[i],res);
                }
            }
        }
        return res;
    }
};
```

## [1143.最长公共子序列](https://leetcode.cn/problems/longest-common-subsequence/)
```c++
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int len1=text1.size();
        int len2=text2.size();
        int **dp=new int*[len1+1];
        for(int i=0;i<=len1;i++)
            dp[i]=new int[len2+1]{0};
        for(int i=1;i<=len1;i++)
        {
            for(int j=1;j<=len2;j++)
            {
                if(text1[i-1]==text2[j-1])
                {
                    dp[i][j]=dp[i-1][j-1]+1;
                }
                else
                {
                    dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
                }
            }
        }
        int res=dp[len1][len2];
        for(int i=0;i<=len1;i++)
            delete[] dp[i];
        delete[] dp;
        return res;
    }
};
```

## [416.分割等和子集](https://leetcode.cn/problems/partition-equal-subset-sum/)
```c++
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum=accumulate(nums.begin(),nums.end(),0);
        if(sum&1) return false;
        int target=sum>>1, n=nums.size();
        int *dp=new int[target+1]{0};
        dp[0]=true;
        for(int i=1;i<=n;i++)
        {
            for(int j=target;j>=nums[i-1];j--)
            {
                //或操作保证如何满足条件就一直满足条件
                dp[j]=dp[j]||dp[j-nums[i-1]];
            }
        }
        bool res=dp[target]?true:false;
        delete[] dp;
        return res;
    }
};
```

## [474.一和零](https://leetcode.cn/problems/ones-and-zeroes/)
```c++
class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        //2个01背包
        //dp[i][j]：最多有i个0和j个1的strs的最大子集的大小
        vector<vector<int>> dp(m + 1, vector<int> (n + 1, 0)); // 默认初始化0
        for (string str : strs) { // 遍历物品
            int oneNum = 0, zeroNum = 0;
            for (char c : str) {
                if (c == '0') zeroNum++;
                else oneNum++;
            }
            for (int i = m; i >= zeroNum; i--) { // 遍历背包容量且从后向前遍历！
                for (int j = n; j >= oneNum; j--) {
                    dp[i][j] = max(dp[i][j], dp[i - zeroNum][j - oneNum] + 1);
                }
            }
        }
        return dp[m][n];
    }
};
```

## [322.零钱兑换](https://leetcode.cn/problems/coin-change/)
```c++
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        if(coins.empty()) return -1;
        vector<int> dp(amount+1,amount+1);
        dp[0]=0;
        for(int i=1;i<=amount;i++)
        {
            for(const int &coin:coins)
            {
                if(i>=coin)
                {
                    dp[i]=min(dp[i],dp[i-coin]+1);
                }
            }
        }
        return dp[amount]==amount+1?-1:dp[amount];
        
    }
};

//先物品后背包
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount+1,INT_MAX);
        dp[0]=0;
        for(int i=0;i<coins.size();i++)//物品
            for(int j=coins[i];j<=amount;j++)//背包
                if(dp[j-coins[i]]!=INT_MAX)
                    dp[j]=min(dp[j],dp[j-coins[i]]+1);
        return dp.back()==INT_MAX?-1:dp.back();
    }
};
```

## [72.编辑距离](https://leetcode.cn/problems/edit-distance/)
```c++
class Solution {
public:
    int minDistance(string word1, string word2) {
        vector<vector<int>> dp(word1.size()+1,vector<int>(word2.size()+1,0));
        for(int i=0;i<dp.size();i++) dp[i][0]=i;
        for(int j=0;j<dp[0].size();j++) dp[0][j]=j;
        for(int i=1;i<dp.size();i++)
        {
            for(int j=1;j<dp[0].size();j++)
            {
                if(word1[i-1]==word2[j-1])
                {
                    dp[i][j]=dp[i-1][j-1];
                }
                else
                    //替换 word1删除(word2插入) word2删除(word1插入)
                    dp[i][j]=min({dp[i-1][j-1],dp[i-1][j],dp[i][j-1]})+1;
            }
        }
        return dp.back().back();
    }
};
```

## [650.只有两个键的键盘](https://leetcode.cn/problems/2-keys-keyboard/)
```c++
class Solution {
public:
    int minSteps(int n) {
        vector<int> dp(n+1,0);
        for(int i=2;i<=n;i++)
        {
            dp[i]=i;
            for(int j=2;j*j<=i;j++)
            {
                if(i%j==0)
                {
                    dp[i]=dp[j]+dp[i/j];
                    break;
                }
            }
        }
        return dp[n];
    }
};
```

## [121.买卖股票的最佳时机](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/)
```c++ 
//贪心算法
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int low = INT_MAX;
        int result = 0;
        for (int i = 0; i < prices.size(); i++) {
            low = min(low, prices[i]);  // 取最左最小价格
            result = max(result, prices[i] - low); // 直接取最大区间利润
        }
        return result;
    }
};

//动态规划
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int dp[2]={-prices[0],0};
        for(int i=1;i<prices.size();i++)
        {
            //dp数组：持有，未持有
            dp[1]=max(dp[1],prices[i]+dp[0]);
            dp[0]=max(-prices[i],dp[0]);
        }
        return dp[1];
    }
};
```

## [122.买卖股票最佳时机II](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii/)
```c++
//贪心算法
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n=prices.size();
        int res=0;
        for(int i=1;i<n;i++)
        {
            if(prices[i-1]<prices[i])
            {
                res+=prices[i]-prices[i-1];
            }
        }
        return res;
    }
};
//动态规划
```
## [123.买卖股票最佳时机III](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-iii/)
```c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.size()<=1) return 0;
        //第i天所持有的最大金额
        //0：无操作，恒等于0
        //1：第一次持有股票
        //2：第一次未持有股票
        //3：第二次持有股票
        //4：第二次未持有股票
        int dp[5]={0};
        dp[1]=-prices[0];
        dp[3]=-prices[0];
        for(int i=1;i<prices.size();i++)
        {
            dp[4]=max(dp[4],dp[3]+prices[i]);
            dp[3]=max(dp[3],dp[2]-prices[i]);
            dp[2]=max(dp[2],dp[1]+prices[i]);
            dp[1]=max(dp[1],-prices[i]);
        }
        return dp[4];
    }
};
```
## [188.买卖股票最佳时机IV](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-iv/)
```c++
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        if(prices.size()<=1) return 0;
        //单数买入，双数卖出
        int n=prices.size();
        vector<int> dp(2*k+1,0);
        for(int i=1;i<dp.size();i+=2)
        {
            dp[i]=-prices[0];
        }
        for(int i=1;i<n;i++)
        {
            for(int j=0;j+2<dp.size();j+=2)
            {
                dp[j+2]=max(dp[j+2],dp[j+1]+prices[i]);
                dp[j+1]=max(dp[j+1],dp[j]-prices[i]);
            }
        }
        return dp[2*k];
    }
};
```
## [309.买卖股票最佳时机含冷冻期](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-with-cooldown/)
```c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n=prices.size();
        if(n<=1) return 0;
        //不持有(一直不持有+冷冻期) 持有 进入冷冻期(卖出)
        int dp[3]={0};
        dp[1]=-prices[0];
        for(int i=1;i<n;i++)
        {
            int preDp1=dp[1];
            dp[1]=max(dp[1],dp[0]-prices[i]);
            dp[0]=max(dp[0],dp[2]);
            dp[2]=preDp1+prices[i];
        }
        return max(dp[0],dp[2]);
    }
};
```
## [714.买卖股票最佳时机含手续费](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/)
```c++
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int n=prices.size();
        if(n<=1) return 0;
        // 持有 未持有(一直未持有或卖出(手续费))
        int dp[2]={-prices[0],0};
        for(int i=1;i<n;i++)
        {
            int tmp=dp[0];
            dp[0]=max(dp[0],dp[1]-prices[i]);
            dp[1]=max(dp[1],tmp+prices[i]-fee);
        }
        return dp[1];
    }
};
```
## [213.打家劫舍II](https://leetcode.cn/problems/house-robber-ii/)
```c++
class Solution {
public:
    int maxMoney(const vector<int>& nums,int begin, int end)
    {
        if(begin==end) return nums[begin];
        int dp[3]={0};
        dp[0]=nums[begin];
        dp[1]=max(nums[begin],nums[begin+1]);
        for(int i=begin+2;i<=end;i++)
        {
            dp[2]=max(dp[0]+nums[i],dp[1]);
            dp[0]=dp[1];
            dp[1]=dp[2];
        }
        return max({dp[0],dp[1],dp[2]});
    }
    int rob(vector<int>& nums) {
        if(nums.size()==1) return nums[0];
        return max(maxMoney(nums,1,nums.size()-1),maxMoney(nums,0,nums.size()-2));
    }
};
```

## [53.最大子数组和](https://leetcode.cn/problems/maximum-subarray/)
```c++
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n=nums.size();
        if(n==0) return 0;
        vector<int> dp(n,0);
        dp[0]=nums[0];
        int res=dp[0];
        for(int i=1;i<n;i++)
        {
            dp[i]=max(dp[i-1]+nums[i],nums[i]);
            res=max(res,dp[i]);
        }
        return res;
    }
};
```

## [343.整数拆分](https://leetcode.cn/problems/integer-break/)
```c++
class Solution {
public:
    int integerBreak(int n) {
        vector<int> dp(n+1,0);
        dp[2]=1;
        for(int i=3;i<=n;i++)
        {
            for(int j=1;j<i-1;j++)
            {
                dp[i]=max({dp[i],(i-j)*j,dp[i-j]*j});
            }
        }
        return dp[n];
    }
};
```

## [583.两个字符串的删除操作](https://leetcode.cn/problems/delete-operation-for-two-strings/)
```c++
//最长序列动态规划
class Solution {
public:
    int minDistance(string word1, string word2) {
        int len1=word1.size();
        int len2=word2.size();
        if(len1<len2) return minDistance(word2,word1);
        vector<vector<int>> dp(len1+1,vector<int>(len2+1,0));
        for(int i=1;i<=len1;i++)
        {
            for(int j=1;j<=len2;j++)
            {
                if(word1[i-1]==word2[j-1])
                {
                    dp[i][j]=dp[i-1][j-1]+1;
                }
                else
                {
                    dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
                }
                if(dp[i][j]>len1) dp[i][j]=len1;
            }
        }
        return len1+len2-2*dp[len1][len2];
    }
};
```
## [646.最长数对链](https://leetcode.cn/problems/maximum-length-of-pair-chain/)
```c++
//参考思路：https://leetcode.cn/problems/maximum-length-of-pair-chain/solution/c-dong-tai-gui-hua-by-da-li-wang-35/
//一般动规，时间复杂度有O(n^2)，但是可以通过二分法快速查找
class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        sort(pairs.begin(),pairs.end(),[](const auto& a,const auto& b)
                        {return (a[0]<b[0])||(a[0]==b[0]&&a[1]<b[1]);});
        int n=pairs.size();
        //dp[i]：前i(从0开始计数)个数形成的最长数对数
        vector<int> dp(n,0);
        //pairs[0]加入，初始化dp[0]=1
        dp[0]=1;
        for(int i=1;i<n;i++)
        {
            dp[i]=dp[i-1];
            int j=i-1;
            //寻找pairs[i][0]的插入位置
            while(j>=0&&pairs[j][1]>=pairs[i][0]) --j;
            //此时j为满足数对i且距离i最近的一个数对下标
            if(j>=0) dp[i]=max(dp[i],dp[j]+1);
        }
        return dp[n-1];
    }
};
//动规+二分
//参考思路：https://leetcode.cn/problems/maximum-length-of-pair-chain/solution/cdong-tai-gui-hua-er-fen-fa-tan-xin-fa-yi-ti-duo-j/
class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        if(pairs.empty()) return 0;
        sort(pairs.begin(),pairs.end(),[](const vector<int>& a,const vector<int>& b)
                                     {return (a[0]<b[0])||(a[0]==b[0]&&a[1]<b[1]);});
        vector<vector<int>> dp;
        for(auto &p:pairs)
        {
            //二分法找到大于等于p[0]的最小值dp[i][1]
            //左闭右开
            int left=0,right=dp.size();
            while(left<right)
            {
                int mid=left+((right-left)>>1);
                if(dp[mid][1]>=p[0]) right=mid;
                else left=mid+1;
            }
            //如果dp末尾的数字都小于p，则插入新p
            if(left>=dp.size()) dp.emplace_back(p);
            //如果p在dp中间，则寻找最小的dp[1]
            else if(dp[left][1]>p[1]) dp[left]=p;
        }
        return dp.size();
    }
};
```
## [376.摆动序列](https://leetcode.cn/problems/wiggle-subsequence/)
```c++
//参考网站：https://leetcode.cn/problems/wiggle-subsequence/solution/tan-xin-si-lu-qing-xi-er-zheng-que-de-ti-jie-by-lg/
class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        int n=nums.size();
        if(n<=1) return n;
        int down=1,up=1;
        for(int i=1;i<n;i++)
        {
            if(nums[i]-nums[i-1]>0)
                up=down+1;
            else if(nums[i]-nums[i-1]<0)
                down=up+1;
        }
        return max(down,up);
    }
};
```
## [494.目标和](https://leetcode.cn/problems/target-sum/)
```c++
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum=accumulate(nums.begin(),nums.end(),0);
        if(((sum+target)&1)||abs(target)>sum) return 0;
        int bagSize=(sum+target)>>1;
        vector<int> dp(bagSize+1,0);
        dp[0]=1;
        for(int i=0;i<nums.size();i++)
        {
            for(int j=bagSize;j>=nums[i];j--)
            {
                dp[j]+=dp[j-nums[i]];
            }
        }
        return dp[bagSize];
    }
};
```

# 第八章 化繁为简的分治法
主定理：
设T(n)表示处理一个长度为n的数组的时间复杂度，则归并排序复杂度递推公式为`T(n)=2T(n/2)+O(n)`。其中O(n)表示合并两个长度为n/2数组的时间复杂度。

考虑T(n)=aT(n/b)+f(n)，定义k=log~b~a,
如果存在c≥0满足f(n)=O(n^k^log^c^n)，那么T(n)=O(n^k^log^c+1^n)

所以归并排序时间复杂度是O(nlogn)

## [241.为运算表达式设计优先度](https://leetcode.cn/problems/different-ways-to-add-parentheses/)
```c++
/*
动态规划算法
链接：https://leetcode.cn/problems/different-ways-to-add-parentheses/solution/by-jjkhl-xv5a/
*/
class Solution
{
public:
    vector<int> diffWaysToCompute(string input)
    {
        vector<int> data;
        vector<char> ops;
        int num = 0;
        char op = ' ';
        //“+”是为了保持ss的一致性
        istringstream ss(input + "+");
        while (ss >> num && ss >> op)
        {
            data.push_back(num);
            ops.push_back(op);
        }
        int n = data.size();
        //dp[i][j]：第i个数字到第j个数字(从0开始计数)范围内的表达式的所有解
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>()));
        //data[i]后面紧接着就是ops[i]，所以能判断i到j内的所有符号
        for (int i = 0; i < n; ++i)
        {
            for (int j = i; j >= 0; --j)
            {
                //表示只有一个数字，即数字data[i]
                if (i == j)
                {
                    dp[j][i].push_back(data[i]);
                }
                /*
                [j,i]区间内的计算
                数字有data[j]到data[i]
                符号有ops[j]到ops[i]
                */
                else
                {
                    //k是[j,i]区间的分割点，但是k可以取0但是不能为i，相当于ops[i]符号默认省略
                    for (int k = j; k < i; k ++)
                    {
                        for (auto left : dp[j][k])
                        {
                            for (auto right : dp[k + 1][i])
                            {
                                int val = 0;
                                switch (ops[k])
                                {
                                case '+':
                                    val = left + right;
                                    break;
                                case '-':
                                    val = left - right;
                                    break;
                                case '*':
                                    val = left * right;
                                    break;
                                }
                                dp[j][i].push_back(val);
                            }
                        }
                    }
                }
            }
        }
        return dp[0][n - 1];
    }
};

//归并算法
class Solution {
public:
    vector<int> diffWaysToCompute(string expression) {
        vector<int> res;
        int len=expression.size();
        if(2==len||1==len)
        {
            res.emplace_back(stoi(expression));
            return res;
        }
        for(int i=0;i<len;i++)
        {
            char ch=expression[i];
            if(ch=='+'||ch=='-'||ch=='*')
            {
                vector<int> left=diffWaysToCompute(expression.substr(0,i));
                vector<int> right=diffWaysToCompute(expression.substr(i+1));
                for(const int &l:left)
                {
                    for(const int& r:right)
                    {
                        switch(ch)
                        {
                            case '+': res.emplace_back(l+r);break;
                            case '-': res.emplace_back(l-r);break;
                            case '*': res.emplace_back(l*r);break;
                        }
                    }
                }
            }
        }
        return res;
    }
};
```

## [932.漂亮数组](https://leetcode.cn/problems/beautiful-array/)
```c++
//思路链接：https://leetcode.cn/problems/beautiful-array/solution/by-jjkhl-de63/
class Solution {
public:
    vector<int> beautifulArray(int n) {
        if(n==1) return {1};
        //1到N的奇数个数：(n+1)/2
        //1到N的偶数个数：n/2
        //分治
        vector<int> left=beautifulArray((n+1)/2);
        vector<int> right=beautifulArray(n/2);
        vector<int> ans;
        //合并
        for(auto &c:left) ans.push_back(2*c-1);
        for(auto &c:right) ans.push_back(2*c);
        return ans;
    }
};
```

## [312.戳气球](https://leetcode.cn/problems/burst-balloons/)
```c++
class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int sum=0;
        nums.insert(nums.begin(),1);
        nums.push_back(1);
        int len=nums.size();
        //dp[i][j]表示开区间(i,j)之间编号的最高分数,所以dp[i][i]=0
        //k表示只剩下i和j两个气球时的最后戳破的气球
        vector<vector<int>> dp(len,vector<int>(len,0));
        /*
        i=len-1时，只有dp[len-1][len-1]=0，所以忽略从len-2开始
        */
        //从下往上
        for(int i=len-2;i>=0;i--)
        {
            //从左往右
            for(int j=i+1;j<len;j++)
            {
                //[i+1,j-1]依次遍历取最大值，
                for(int k=i+1;k<j;k++)
                    dp[i][j]=max(dp[i][j],dp[i][k]+dp[k][j]+nums[i]*nums[j]*nums[k]);
            }
        }
        return dp[0].back();
    }
};
//参考思路：https://leetcode-cn.com/problems/burst-balloons/solution/tu-jie-dong-tai-gui-hua-jie-jue-chuo-qi-cx18h/
```

# 第九章 巧解数学问题
## [204.计数质数](https://leetcode.cn/problems/count-primes/)
```c++
//埃式筛选
class Solution {
public:
    int countPrimes(int n) {
        if(n<=2) return 0;
        vector<bool> prime(n,true);
        //去掉不是质数的1
        int count=n-2;
        for(int i=2;i<n;i++)
        {
            if(prime[i])
            {
                for(int j=2*i;j<n;j+=i)
                {
                    if(prime[j])
                    {
                        prime[j]=false;
                        --count;
                    }
                }
            }
        }
        return count;
    }
};
//优化版埃式筛选——奇数筛
class Solution {
public:
    int countPrimes(int n) {
        if(n<3) return 0;
        vector<bool> prime(n+1,true);
        for(int i=3;i*i<n;i+=2)//+2保证一直为奇数
        {
            if(prime[i])
            {
                for(int j=i;j*i<=n;j+=2)
                    prime[j*i]=false;
            }
        }
        int count=1;
        for(int i=3;i<n;i+=2)
        {
            count+=prime[i];
        }
        return count;
    }
};
```

## [504.七进制数](https://leetcode.cn/problems/base-7/)
```c++
class Solution {
public:
    string convertToBase7(int num) {
        if(num==0) return "0";
        string res="";
        bool flag=true;
        if(num<0) flag=false,num=-num;;
        while(num)
        {
            res=to_string(num%7)+res;
            num/=7;
        }
        return flag==true?res:"-"+res;
    }
};
```
## [172.阶乘后的零](https://leetcode.cn/problems/factorial-trailing-zeroes/)
```c++
class Solution {
public:
    int trailingZeroes(int n) {
        int count=0;
        while(n)
        {
            n/=5;
            count+=n;
        }
        return count;
    }
};
```
## [415.字符串相加](https://leetcode.cn/problems/add-strings/)
```c++
class Solution {
public:
    string addStrings(string num1, string num2) {
        string res="";
        int cur=0,i=num1.size()-1,j=num2.size()-1;
        while(i>=0||j>=0||cur!=0)
        {
            if(i>=0) cur+=num1[i--]-'0';
            if(j>=0) cur+=num2[j--]-'0';
            res+=to_string(cur%10);
            cur/=10;
        }
        reverse(res.begin(),res.end());
        return res;
    }
};
```

## [326.3的幂](https://leetcode.cn/problems/power-of-three/)
```c++
class Solution {
public:
    bool isPowerOfThree(int n) {
        int maxNum=pow(3,19);
        return n>0&&maxNum%n==0;
    }
};
```

## [384.打乱数组](https://leetcode.cn/problems/shuffle-an-array/)
```c++
class Solution {
private:
    vector<int> nums;
    vector<int> orig;

public:
    Solution(vector<int>& nums) {
        this->nums = nums;
        orig=nums;
        // orig.resize(nums.size());
        // copy(nums.begin(), nums.end(), orig.begin());
    }
    
    vector<int> reset() {
        // copy(orig.begin(), orig.end(), nums.begin());

        // return nums;
        nums=orig;
        return nums;
    }
    
    vector<int> shuffle() {
        for (int i = 0; i < nums.size(); ++i) {
            int j = i + rand() % (nums.size() - i);
            swap(nums[i], nums[j]);
        }

        return nums;
    }
};
```
## [528.按权重随机选择](https://leetcode.cn/problems/random-pick-with-weight/)
```c++
class Solution {
private:
    vector<int> w;
public:
    Solution(vector<int>& W) {
        w.push_back(W[0]);
        for(int i=1;i<W.size();i++)
        {
            w.push_back(w.back()+W[i]);
        }
    }
    
    int pickIndex() {
        int weight=rand()%w.back();
        return upper_bound(w.begin(),w.end(),weight)-w.begin();
    }
};
//参考思路：https://leetcode.cn/problems/random-pick-with-weight/solution/cer-fen-xiang-jie-by-xiaohu9527-nsns/
```

## [382.链表随机节点](https://leetcode.cn/problems/linked-list-random-node/)
```c++
//模拟法
class Solution {
private:
    vector<int> list;
public:
    Solution(ListNode* head) {
        while(head)
        {
            list.push_back(head->val);
            head=head->next;
        }
    }
    
    int getRandom() {
        return list[rand()%list.size()];
    }
};
//水塘抽样，针对数据流
class Solution {
    ListNode *head;
public:
    Solution(ListNode* head) {
        this->head=head;
    }
    
    int getRandom() {
        int i=1,ans=0;
        for(auto node=head;node;node=node->next)
        {
            if(rand()%i==0)
            {
                ans=node->val;
            }
            ++i;
        }
        return ans;
    }
};
```

## [168.Excel表列名称](https://leetcode.cn/problems/excel-sheet-column-title/)
```c++
class Solution {
public:
    string convertToTitle(int columnNumber) {
        string res="";
        while(columnNumber>0)
        {
            int curNum=(columnNumber-1)%26;
            columnNumber=(columnNumber-1)/26;
            char ch='A'+curNum;
            res+=ch;
        }
        reverse(res.begin(),res.end());
        return res;
    }
};
```

## [67.二进制求和](https://leetcode.cn/problems/add-binary/)
```c++
class Solution {
public:
    string addBinary(string a, string b) {
        if(a.size()<b.size()) return addBinary(b,a);
        int carry=0;
        int lenA=a.size(),lenB=b.size();
        string tmp(lenA-lenB,'0');
        b.insert(0,tmp);
        for(int i=lenA-1;i>=0;i--)
        {
            int sum=a[i]-'0'+b[i]-'0'+carry;
            a[i]=(sum)%2+'0';
            carry=sum>>1;
        }
        if(carry>0)
            a.insert(0,"1");
        return a;
    }
};
```


## [238.除自身以外数组的乘积](https://leetcode.cn/problems/product-of-array-except-self/)
```c++
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n=nums.size();
        vector<int> res(n,1);
        for(int i=1;i<n;i++)
        {
            res[i]=res[i-1]*nums[i-1];
        }
        int R=nums[n-1];
        for(int i=n-2;i>=0;i--)
        {
            res[i]=res[i]*R;
            R*=nums[i];
        }
        return res;
    }
};
```
## [462.最少移动次数使数组元素相等II](https://leetcode.cn/problems/minimum-moves-to-equal-array-elements-ii/)
```c++
//参考思路：https://leetcode.cn/problems/minimum-moves-to-equal-array-elements-ii/solution/by-fuxuemingzhu-13z3/
class Solution {
public:
    int minMoves2(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        const int n=nums.size();
        int mid=nums[n>>1];
        int res=0;
        for(int i:nums)
        {
            res+=abs(i-mid);
        }
        return res;
    }
};
```

## [168.多数元素](https://leetcode.cn/problems/majority-element/)
```c++
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int res=0,count=0;
        for(int num:nums)
        {
            if(0==count)
            {
                count++;
                res=num;
            }
            else if(count>0)
            {
                if(num==res) count++;
                else count--;
            }
        }
        return res;
    }
};
```
## [470.用Rand7()实现Rand100()](https://leetcode.cn/problems/implement-rand10-using-rand7/)
```c++
class Solution {
public:
    int rand10() {
        int a=rand7(),b=rand7();
        while(a==7) a=rand7();//a不能为7，必须为[1,6]才能保证奇偶各一半
        while(b>5) b=rand7();//b不为5及其以上，保证a取最大值6时，a+b还在10范围内
        return ((a&1)==0?0:5)+b;
    }
};
```

## [202.快乐数](https://leetcode.cn/problems/happy-number/)
```c++
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

# 第十章 位运算

常用的位运算符号包括：“∧”按位异或、“&”按位与、“|”按位或、“∼”取反、“<<”
算术左移和“>>”算术右移。以下是一些常见的位运算特性，其中 0s 和 1s 分别表示只由 0 或 1
构成的二进制数字。

```
x ^ 0s = x 			x & 0s = 0 			x | 0s = x
x ^ 1s = ~x 		x & 1s = x 			x | 1s = 1s
x ^ x = 0 			x & x = x 			x | x = x
```

* n & (n - 1)为0表示是2得n次方；可以找到最低位
* n & (-n) 可以得到 n 的位级表示中最低的那一位

## [461.汉明距离](https://leetcode.cn/problems/hamming-distance/)

```c++
class Solution {
public:
    int hammingDistance(int x, int y) {
        int res=0;
        int diff=x^y;
        while(diff)
        {
            res+=diff&1;
            diff>>=1;
        }
        return res;
    }
};
```
## [190.颠倒二进制位](https://leetcode.cn/problems/reverse-bits/)

```c++
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t res=0;
        for(int i=0;i<32;i++)
        {
            res=(res<<1)+(n&1);
            n>>=1;
        }
        return res;
    }
};
```
## [136.只出现一次的数字](https://leetcode.cn/problems/single-number/)
```c++
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res=0;
        for(int num:nums)
        {
            res^=num;
        }
        return res;
    }
};
```
## [342.4的幂](https://leetcode.cn/problems/power-of-four/)
```c++
//递归模拟
class Solution {
public:
    bool isPowerOfFour(int n) {
        while(n!=1&&n%4==0&&n!=0)
        {
            n>>=2;
        }
        return n==1;
    }
};
//位运算
class Solution {
public:
    //0x5 = 0101b
    bool isPowerOfFour(int num) {
        //num&(num-1)=0，表示是2的次方
        if (num < 0 || num & (num-1)){//check(is or not) a power of 2.
            return false;
        }
        return num & 0x55555555;//check 1 on odd bits
    }
};
```
## [318.最大单词长度乘积](https://leetcode.cn/problems/maximum-product-of-word-lengths/)
```c++
// 链接：https://leetcode.cn/problems/maximum-product-of-word-lengths/solution/acmjin-pai-ti-jie-zhuang-tai-ya-suo-bian-biqp/
class Solution {
public:
    int mask[1000];
    int maxProduct(vector<string>& words) {
        for (int i = 0; i < words.size(); i++) {
            for (int j = 0; j < words[i].size(); j++) {
                mask[i] |= (1 << (words[i][j] - 'a'));
            }
        }
        int ans = 0;
        for (int i = 0; i < words.size(); i++) {
            for (int j = i + 1; j < words.size(); j++) {
                if (!(mask[i] & mask[j])) {
                    ans = max(ans, int(words[i].size() * words[j].size()));
                }
            }
        }
        return ans;
    }
};

```
## [338.比特位计数](https://leetcode.cn/problems/counting-bits/)

```c++
class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> res(n+1,0);
        for(int i=1;i<=n;i++)
        {
            // res[i]=i&1?res[i-1]+1:res[i>>1];
            res[i]=res[i&(i-1)]+1;
        }
        return res;
    }
};
```
## [268.丢失的数字](https://leetcode.cn/problems/missing-number/)

```c++
//相当于两个数组异或，相同的数异或为0，任何数字异或0=原数。
//异或法
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n=nums.size();
        int res=n;
        for(int i=0;i<n;i++) res^=i^nums[i];
        return res;
    }
};
```

## [693.交替位二进制数](https://leetcode.cn/problems/binary-number-with-alternating-bits/)

```c++
class Solution {
public:
    bool hasAlternatingBits(int n) {
        int pre=n&1;
        int cur;
        while(n)
        {
            n>>=1;
            cur=n&1;
            if(cur==pre) return false;
            pre=cur;
        }
        return true;
    }
};
//异或位运算
class Solution {
public:
    bool hasAlternatingBits(int n) {
        // 如 010101 右移一位得到 001010
        // 二者异或之后得到011111  (这一步是关键,只有交替出现01，异或后才能得到结果0111111...11)
        // 为了判断 异或后的结果是否满足(0111111...11)类型的结果
        // 可以用如下方法，比如
        // 011111 加上1 为100000
        // 011111 与 100000按位相与 结果为000000 ， 也就是0;
        long m = n ^ (n >> 1);
        return (m & (m + 1)) == 0;
    }
};
```



## [476.数字的补数](https://leetcode.cn/problems/number-complement/)

```c++
class Solution {
public:
    int findComplement(int num) {
        int tmp=num,c=0;
        while(tmp>0)
        {
            tmp>>=1;
            c=(c<<1)+1;
        }
        return num^c;
    }
};
```



## [260.只出现一次的数字III](https://leetcode.cn/problems/single-number-iii/)

```c++
//参考思路：https://leetcode.cn/problems/single-number-iii/solution/gong-shui-san-xie-yi-ti-shuang-jie-ha-xi-zgi4/
/*
主要思路：
1. 对所有数字进行异或，最后肯定是2个只出现一次的元素异或的结果
2. 以异或值最后一个二进制位为1作为分界线mask，如果是0则为一个数组，是1则为另外一个数组。
3. 上面的两个数组一定是只出现一次的元素各在一个，所以再取异或即可
*/
class Solution
{
public:
    vector<int> singleNumber(vector<int> &nums)
    {
        int aux = 0;
        for (auto num : nums)
            aux ^= num;

        int ans = 0, tmp = aux;
        //找到异或为1的最近一位
        aux = aux & (~(unsigned)aux + 1);
        for (auto num : nums)
            if (num & aux)
                ans ^= num;

        return {ans, ans ^ tmp};
    }
};
```

# 第十一章 妙用数据结构

## [448.找到所有数组中消失的数字](https://leetcode.cn/problems/find-all-numbers-disappeared-in-an-array/)

```c++
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        int n=nums.size();
        if(n==0) return nums;
        vector<int> res;
        for(const int& num:nums)
        {
            int index=abs(num)-1;
            if(nums[index]>0)
                nums[index]=-nums[index];
        }
        for(int i=0;i<n;i++)
        {
            if(nums[i]>0)
                res.emplace_back(i+1);
        }
        return res;
    }
};
```

## [48.旋转图像](https://leetcode.cn/problems/rotate-image/)
```c++
//翻转法
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n=matrix.size();
        for(int i=0;i<n/2;i++)
        {
            for(int j=0;j<(n+1)/2;j++)
            {
                int temp=matrix[i][j];
                matrix[i][j]=matrix[n-j-1][i];
                matrix[n-j-1][i]=matrix[n-i-1][n-j-1];
                matrix[n-i-1][n-j-1]=matrix[j][n-i-1];
                matrix[j][n-i-1]=temp;
            }
        }
    }   
};
//替换法
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n=matrix.size();
        for(int i=0;i<n/2;i++)
        {
            for(int j=0;j<n;j++)
            {
                swap(matrix[i][j],matrix[n-1-i][j]);
            }
        }
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<i;j++)
            {
                swap(matrix[i][j],matrix[j][i]);
            }
        }
    }
};
```
## [240.搜索二维矩阵II](https://leetcode.cn/problems/search-a-2d-matrix-ii/)
```c++
//右上角搜索类比搜索树
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m=matrix.size(),n=matrix[0].size();
        if(m==0||n==0) return false;
        int i=0,j=n-1;
        while(i<m&&j>=0)
        {
            if(target>matrix[i][j]) i++;
            else if(target<matrix[i][j]) j--;
            else return true;
        }
        return false;
    }
};
```
## [769.最多能完成排序的快](https://leetcode.cn/problems/max-chunks-to-make-sorted/)
```c++
/*
    通过cur_max找到数组位置，通过循环找到左侧比它小的数组，这时说明这一块数组需要进行排序。
    通俗来说，有3个规律
    1：若区间内有升有降，则找拐点，以拐点为分界线升序排序左侧数组
    2.若区间内只有升序，则每个数字都可以单独作为分区
    3.若区间内只有降序，则只存在一个分区
    比如{1,0,2,3,4}
    当i=0，得到cur_max=1，i!=cur_max，所以继续循环
    当i=1,得到cur_max=1,i==cur_max，此时说明左侧数组需要排序，且{arr[0],arr[1]}需要进行升序排序
    当i=2，cur_max=2=i，说明其左侧数组需要排序，但因为上一步已将{arr[0],arr[1]}进行了升序排序，则只需要进行{arr[2]}的排序就行
    同理，对i=3和i=4进行相同顺序的排序
*/
class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        int chunks=0,cur_max=0;
        for(int i=0;i<arr.size();i++)
        {
            cur_max=max(cur_max,arr[i]);
            if(cur_max==i)
                chunks++;
        }
        return chunks;
    }
};
```
## [232.用栈实现队列](https://leetcode.cn/problems/implement-queue-using-stacks/)
```c++
class MyQueue {
private:
    stack<int> in,out;
public:
    MyQueue() {

    }
    
    void push(int x) {
        in.push(x);
    }
    
    int pop() {
        in2out();
        int res=out.top();
        out.pop();
        return res;
    }
    
    int peek() {
        in2out();
        return out.top();
    }
    
    bool empty() {
        return in.empty()&&out.empty();
    }
    void in2out()
    {
        if(out.empty())
        {
            while(!in.empty())
            {
                out.push(in.top());
                in.pop();
            }
        }
    }
};
```
## [155.最小栈](https://leetcode.cn/problems/min-stack/)
```c++
//辅助栈
class MinStack {
private:
    stack<int> st;
    stack<int> minst;
public:
    MinStack() {

    }
    
    void push(int val) {
        st.push(val);
        if(minst.empty()||minst.top()>=val) minst.push(val);
    }
    
    void pop() {
        int val=st.top();
        st.pop();
        if(minst.top()==val) minst.pop();
    }
    
    int top() {
        return st.top();
    }
    
    int getMin() {
        return minst.top();
    }
};
```

## [20.有效队列](https://leetcode.cn/problems/valid-parentheses/)
```c++
class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        for(const char& ch:s)
        {
            if(ch=='(') st.push(')');
            else if(ch=='[') st.push(']');
            else if(ch=='{') st.push('}');
            else if(st.empty()||st.top()!=ch) return false;
            else st.pop();
        }
        return st.empty();
    }
};
```
## [739.每日温度](https://leetcode.cn/problems/daily-temperatures/)
```c++
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        stack<int> st;
        int n=temperatures.size();
        vector<int> res(n,0);
        for(int i=0;i<n;i++)
        {
            if(st.empty())
            {
                st.push(i);
                continue;
            }
            while(!st.empty()&&temperatures[st.top()]<temperatures[i])
            {
                res[st.top()]=i-st.top();
                st.pop();
            }
            st.push(i);
        }
        return res;
    }
};
```
## [23.合并K个升序链表](https://leetcode.cn/problems/merge-k-sorted-lists/)
```c++
 struct cmp{
     bool operator()(ListNode* l1,ListNode* l2)
     {
         return l1->val>l2->val;
     }
 };
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.empty()) return NULL;
        int k=lists.size();
        priority_queue<ListNode*,vector<ListNode*>,cmp> que;
        for(ListNode* list:lists)
        {
            if(list)
                que.push(list);
        }
        ListNode* dummy=new ListNode(0);
        ListNode* cur=dummy;
        while(!que.empty())
        {
            cur->next=que.top();
            que.pop();
            cur=cur->next;
            if(cur->next)//如果合并的结点还有其余顺序结点，则继续合并
            {
                que.push(cur->next);
            }
        }
        return dummy->next;
    }
};
```
## [218.天际线问题](https://leetcode.cn/problems/the-skyline-problem/)
```c++
class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings)
    {
        vector<pair<int,long>> sortedBuildings;
        for(auto & building: buildings)
        {
            int left = building[0];
            int right = building[1];
            long height = building[2];
            sortedBuildings.push_back(make_pair(left,-height));
            sortedBuildings.push_back(make_pair(right,height));
        }

        std::sort(sortedBuildings.begin(),sortedBuildings.end(),[](auto &left,auto &right){return left.first < right.first || (left.first == right.first && left.second < right.second);});
       
        multiset<int,greater<int>> pq;//降序排序
        pq.insert(0);
        vector<vector<int>> ans;
        for(auto & build: sortedBuildings)
        {
            int x = build.first;
            long y = build.second;
            int top = *(pq.begin());//取第一个元素，即最大元素
            if(y < 0)//左边界,只需要找到最高的边
            {
                y = -y;
                if(y > top)
                {
                    ans.push_back({x,(int)y});
                }
                pq.insert(y);
            }
            else //右边界，只找最低的边
            {
                pq.erase(pq.find(y));//表示高度y已到右边界，所以删除转折点
                int tmp = *(pq.begin());
                if(top > tmp)
                {
                    ans.push_back({x,tmp});
                }
            }
        }
        return ans;
    }
};
//参考思路：https://leetcode.cn/problems/the-skyline-problem/solution/gong-shui-san-xie-sao-miao-xian-suan-fa-0z6xc/
```
## [239.滑动窗口最大值](https://leetcode.cn/problems/sliding-window-maximum/)
```c++
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
	int n=nums.size();
	deque<int> q;
	for (int i = 0; i < k; i++)
	{
		while (!q.empty() && nums[i] >= nums[q.back()])
			q.pop_back();
		q.push_back(i);
	}
	vector<int> ans = { nums[q.front()] };
	for (int i = k; i < n; ++i) {
		while (!q.empty() && nums[i] >= nums[q.back()]) {
			q.pop_back();
		}
		q.push_back(i);
		while (q.front() <= i - k) {
			q.pop_front();
		}
		ans.push_back(nums[q.front()]);
	}
	return ans;
    }
};
```
## [1.两数之和](https://leetcode.cn/problems/two-sum/)
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
## [128.最长连续序列](https://leetcode.cn/problems/longest-consecutive-sequence/)

```c++
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> hash;
        for(const int& num:nums) hash.insert(num);
        int ans=0;
        while(!hash.empty())
        {
            int cur=*(hash.begin());
            hash.erase(cur);
            int next=cur+1,pre=cur-1;
            while(hash.count(next))
            {
                hash.erase(next++);
            }
            while(hash.count(pre))
            {
                hash.erase(pre--);
            }
            ans=max(ans,next-pre-1);
        }
        return ans;
    }
};
```



## [149.直线上最多的点数](https://leetcode.cn/problems/max-points-on-a-line/)

```c++
class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        unordered_map<double,int> hash;
        int max_count=0,same_y=1;
        int n=points.size();
        for(int i=0;i<n;i++)
        {
            same_y=1;
            for(int j=i+1;j<n;j++)
            {
				//因为斜率dy!=0，所以需要单独提出
                if(points[i][1]==points[j][1])
				{
					//表示与i点水平
					++same_y;
				}
				else
				{
					double dx=points[i][0]-points[j][0];
					double dy=points[i][1]-points[j][1];
					++hash[dx/dy];				
				}
            }
			max_count=max(max_count,same_y);
			for(auto item:hash)
			{
                //item.second表示当前斜率下的除i点以外的点，所以计算数量时要+1
				max_count=max(max_count,1+item.second);
			}
			hash.clear();
        }
		return max_count;
    }
};
```



## [332.重新安排行程](https://leetcode.cn/problems/reconstruct-itinerary/)
```c++
class Solution
{
private:
    //unordered_map<出发机场, map<到达机场,航班次数>> targets;
    unordered_map<string, map<string, int>> targets;
    bool backtrack(int tickeNum,vector<string>& res)
    {
        if(res.size()>tickeNum)
            return true;
        for(pair<const string,int>& target:targets[res.back()])
        {
            //如果还没有飞过
            if(target.second>0)
            {
                res.push_back(target.first);
                target.second--;
                if(backtrack(tickeNum,res)) return true;
                res.pop_back();
                target.second++;
            }
        }
        return false;
    }
public:
    vector<string> findItinerary(vector<vector<string>> &tickets)
    {
        vector<string> res;
        for(const vector<string>& t:tickets)
            targets[t[0]][t[1]]++;//记录映射关系
        res.push_back("JFK");
        backtrack(tickets.size(),res);
        return res;
    }
};
```
## [303.区域和检索-数组不变](https://leetcode.cn/problems/range-sum-query-immutable/)
```c++
class NumArray {
    vector<int> psum;
public:
    NumArray(vector<int>& nums):psum(nums.size()+1,0) {
        partial_sum(nums.begin(),nums.end(),psum.begin()+1);
    }
    
    int sumRange(int left, int right) {
        return psum[right+1]-psum[left];
    }
};
```
## [304.二维区域和检索-矩阵不变](https://leetcode.cn/problems/range-sum-query-2d-immutable/)
```c++
class NumMatrix {
    vector<vector<int>> integral;
public:
    NumMatrix(vector<vector<int>>& matrix) {
        int m=matrix.size(),n=m>0?matrix[0].size() : 0;
        integral=vector<vector<int>>(m+1,vector<int>(n+1,0));
        for(int i=1;i<=m;i++)
        {
            for(int j=1;j<=n;j++)
            {
                integral[i][j]=matrix[i-1][j-1]+integral[i-1][j]+integral[i][j-1]-integral[i-1][j-1];            
            }
        }
    }
    int sumRegion(int row1, int col1, int row2, int col2) {
        return integral[row2+1][col2+1] - integral[row2+1][col1]-integral[row1][col2+1] + integral[row1][col1];
    }
};
```
## [560.和为K的子数组](https://leetcode.cn/problems/subarray-sum-equals-k/)
```c++
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int count=0,psum=0;
        unordered_map<int,int> hashmap;
        hashmap[0]=1;//表示psum==k，此时count+1
        for(const int& i:nums)
        {
            psum+=i;
            count+=hashmap[psum-k];
            ++hashmap[psum];
        }
        return count;
    }
};
```
## [566.重塑矩阵](https://leetcode.cn/problems/reshape-the-matrix/)
```c++
class Solution {
public:
    vector<vector<int>> matrixReshape(vector<vector<int>>& mat, int r, int c) {
        int m=mat.size(),n=mat[0].size();
        if(m*n!=r*c) return mat;
        vector<vector<int>> res(r,vector<int>(c,0));
        int x=0,y=0;
        for(int i=0;i<r;i++)
        {
            for(int j=0;j<c;j++)
            {
                res[i][j]=mat[x][y];
                if(y++==n-1)
                {
                    x++;
                    y=0;
                }
            }
        }
        return res;
    }
};
```
## [225.用队列实现栈](https://leetcode.cn/problems/implement-stack-using-queues/)
```c++
class MyStack {
    queue<int> que1,que2;
public:
    MyStack() {

    }
    
    void push(int x) {
        que1.push(x);
    }
    
    int pop() {
        int size=que1.size();
        --size;
        while(size--)//将que1导入que2，但需要留下最后一个元素
        {
            que2.push(que1.front());
            que1.pop();
        }

        int res=que1.front();
        que1.pop();
        que1=que2;
        while(!que2.empty())
            que2.pop();
        return res;
    }
    
    int top() {
        return que1.back();
    }
    
    bool empty() {
        return que1.empty();
    }
};
```
## [503.下一个更大元素II](https://leetcode.cn/problems/next-greater-element-ii/)
```c++
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n=nums.size();
		stack<int> st;
		vector<int> res(n,-1);
		for(int i=0;i<2*n;i++)
		{
			while(!st.empty()&&nums[i%n]>nums[st.top()])
			{
				res[st.top()]=nums[i%n];
				st.pop();
			}
			st.push(i%n);
		}
		return res;
    }
};
```
## [217.存在重复元素](https://leetcode.cn/problems/contains-duplicate/)

## [697.数组的度](https://leetcode.cn/problems/degree-of-an-array/)

## [594.最长和谐子序列](https://leetcode.cn/problems/longest-harmonious-subsequence/)

## [287.寻找重复数](https://leetcode.cn/problems/find-the-duplicate-number/)

## [313.超级丑数](https://leetcode.cn/problems/super-ugly-number/)

## [870.优势洗牌](https://leetcode.cn/problems/advantage-shuffle/)

## [307.区域和检索-数组可修改](https://leetcode.cn/problems/range-sum-query-mutable/)