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
## [435.���ص�����](https://leetcode.cn/problems/non-overlapping-intervals/)
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