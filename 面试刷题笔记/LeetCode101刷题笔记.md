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

