github��ַ��https://github.com/changgyhub/leetcode_101/

**�㷨����**
# �ڶ��� ̰���㷨
## [455.�ַ�����](https://leetcode.cn/problems/assign-cookies/)
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
## [135.�ַ��ǹ�](https://leetcode.cn/problems/candy/)
```c++
//˫�����
class Solution {
public:
    int candy(vector<int>& ratings) {
       int len=ratings.size();
       vector<int> candys(len,1);
       //��������ң����ұ����ȶȴ�����ߣ�candys+1
       for(int i=1;i<len;i++)
       {
           if(ratings[i]>ratings[i-1])//��>��
           {
               candys[i]=candys[i-1]+1;
           }
       }
       //�����ҡ��󣬵�������ȶȴ����ұߣ�candys+1
       for(int i=len-1;i>0;i--)
       {
           if(ratings[i-1]>ratings[i])//��>��
           {
               candys[i-1]=max(candys[i-1],candys[i]+1);
           }
       }
       return std::accumulate(candys.begin(),candys.end(),0);
    }
};
//���鷨
class Solution
{
public:
    int candy(vector<int> &ratings)
    {
        int len = ratings.size();
        int *candys=new int[len];
        //memset����������ʼ��1
        fill(candys,candys+len,1);
        //��������ң����ұ����ȶȴ�����ߣ�candys+1
        for (int i = 1; i < len; i++)
        {
            if (ratings[i] > ratings[i - 1]) //��>��
            {
                candys[i] = candys[i - 1] + 1;
            }
        }
        //�����ҡ��󣬵�������ȶȴ����ұߣ�candys+1
        for (int i = len - 1; i > 0; i--)
        {
            if (ratings[i - 1] > ratings[i]) //��>��
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
## <span id="435">[435.���ص�����](https://leetcode.cn/problems/non-overlapping-intervals/)</span>
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

## [605.�ֻ�����](https://leetcode.cn/problems/can-place-flowers/)
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

//������
class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        int len=flowerbed.size();
        for(int i=0;i<len;i+=2)
        {
            //��ǰΪ�յ�
            if(flowerbed[i]==0)
            {
                //��������һ�����һ��Ϊ��
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
//��β��0
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
## [452.�����ٵļ���������](https://leetcode.cn/problems/minimum-number-of-arrows-to-burst-balloons/)
��[435���ص�����](#435)����
```c++
//��ʽһ
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

//��ʽ��
class Solution {
private:
    static bool cmp(const vector<int>& a, const vector<int>& b) {
        return a[0] < b[0];
    }
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        if (points.size() == 0) return 0;
        sort(points.begin(), points.end(), cmp);

        int result = 1; // points ��Ϊ��������Ҫһ֧��
        for (int i = 1; i < points.size(); i++) {
            if (points[i][0] > points[i - 1][1]) {  // ����i������i-1�����ţ�ע�����ﲻ��>=
                result++; // ��Ҫһ֧��
            }
            else {  // ����i������i-1����
                points[i][1] = min(points[i - 1][1], points[i][1]); // �����ص�������С�ұ߽�
            }
        }
        return result;
    }
};
```

