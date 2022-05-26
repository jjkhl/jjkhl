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