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
## <span id="435">[435.无重叠区间](https://leetcode.cn/problems/non-overlapping-intervals/)</span>
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

# 二分查找
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

## [34.在排序数组中查找元素的第一个和最后一个位置](https://leetcode.cn/problems/find-first-and-last-position-of-element-in-sorted-array/)
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

# 排序算法系列
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
/*    int d = 1; //保存最大的位数
    int p = 10;
    for(int i = 0; i < n; ++i)
    {
        while(data[i] >= p)
        {
            p *= 10;
            ++d;
        }
    }
    return d;*/
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