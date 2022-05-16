# [程序员面试金典（第 6 版）](https://leetcode.cn/problem-list/xb9lfcwi/)

## [01.判断字符是否唯一](https://leetcode.cn/problems/is-unique-lcci/)
```c++
//位运算来表示26位字母，如果该位置&x=1，表示已有该字母
class Solution {
public:
    bool isUnique(string astr) {
        int x=0;
        for(char ch:astr)
        {
            if(x&(1<<(ch-'a'))) return false;
            x|=(1<<(ch-'a'));
        }
        return true;
    }
};
```
## [02.判定是否互为字符重排](https://leetcode.cn/problems/check-permutation-lcci/)
```c++
class Solution {
public:
    bool CheckPermutation(string s1, string s2) {
    int *record=new int[26]();
        for (int i = 0; i < s1.size(); i++) {
            // 并不需要记住字符a的ASCII，只要求出一个相对数值就可以了
            record[s1[i] - 'a']++;
        }
        for (int i = 0; i < s2.size(); i++) {
            record[s2[i] - 'a']--;
        }
        for (int i = 0; i < 26; i++) {
            if (record[i] != 0) {
                // record数组如果有的元素不为零0，说明字符串s和t 一定是谁多了字符或者谁少了字符。
                return false;
            }
        }
        // record数组所有元素都为零0，说明字符串s和t是字母异位词
        delete [] record;
        return true;
    }
};
```
## [03.URL化](https://leetcode.cn/problems/string-to-url-lcci/)
**该题同**[剑指offer05](https://leetcode.cn/problems/ti-huan-kong-ge-lcof/)
```c++
//注意题目假定该字符串尾部有足够的空间存放新增字符，并且知道字符串的“真实”长度。
//双指针法
class Solution {
public:
    string replaceSpaces(string S, int length) {
        int i=length-1,j=S.size()-1;
        while(i>=0)
        {
            if(' '==S[i])
            {
                S[j--]='0';
                S[j--]='2';
                S[j--]='%';
            }
            else S[j--]=S[i];
            i--;
        }
        return S.substr(j+1);
    }
};
```
## [04.回文子串](https://leetcode.cn/problems/palindrome-permutation-lcci/)
```c++
class Solution {
public:
    bool canPermutePalindrome(string s) {
        unordered_map<char,int> umap;
        int num=0;
        for(char ch:s)
        {
            if(umap[ch]>0)
            {
                umap[ch]--;
                num--;
            }
            else if(umap[ch]==0)
            {
                umap[ch]++;
                num++;
            }
        }
        if(num==0||num==1) return true;
        return false;
    }
};
```

## [05.一次编辑](https://leetcode.cn/problems/one-away-lcci/)
```c++
//双指针法
class Solution {
public:
    bool oneEditAway(string first, string second) {
        int len1=first.size(),len2=second.size();
        if(abs(len1-len2)>1) return false;
        //保证len1>=len2
        if(len2==len1+1) return oneEditAway(second,first);

        int i=0,j=0;
        int diff=0;
        bool size_diff=(len2==len1)?false:true;
        while(i<len1&&j<len2)
        {
            if(first[i]!=second[j])
            {
                if(++diff>=2) return false;
                //如果first大小比second大且不相同，则first需要比second多出一个身位
                if(size_diff) j--;
            }
            ++i,++j;
        }
        return true;
    }
};
//双向遍历法
//参考思路：https://leetcode.cn/problems/one-away-lcci/solution/c-by-zi-bu-yu-mf-052b/
class Solution {
public:
    bool oneEditAway(const string& first, const string& second) {
        auto pos1 = mismatch(first.cbegin(), first.cend(), second.cbegin(), second.cend());
        auto pos2 = mismatch(first.crbegin(), first.crend(), second.crbegin(), second.crend());
        ptrdiff_t dis[4]{ first.cend() - pos1.first, second.cend() - pos1.second,pos2.first - first.crbegin(),pos2.second - second.crbegin() };
        return (int)dis[0] - dis[2] < 2 && (int)dis[1] - dis[3] < 2;
    }
};
```
## [06.字符串压缩](https://leetcode.cn/problems/compress-string-lcci/)
```c++
class Solution {
public:
    string compressString(string S) {
        string res="";
        int left=0,right=0;
        int count=0;
        while(right<S.size())
        {
            if(S[left]==S[right])
            {
                right++;
                count++;
            }
            else
            {
                res=res+S[left]+to_string(count);
                left=right;
                count=0;
            }
        }
        res=res+S[left]+to_string(count);
        return res.size()>=S.size()?S:res;
    }
};
```

## [07.旋转矩阵](https://leetcode.cn/problems/rotate-matrix-lcci/)
```c++
//先沿主对角线翻转，再沿竖直方向上的对称轴翻转
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int rows=matrix.size();
        int cols=matrix[0].size();
        for(int i=0;i<rows;i++)
        {
            for(int j=0;j<cols;j++)
            {
                if(i<j)
                {
                    swap(matrix[i][j],matrix[j][i]);
                }
            }
        }
        for(int i=0;i<rows;i++)
        {
            for(int j=0;j<cols/2;j++)
            {
                swap(matrix[i][j],matrix[i][cols-j-1]);
            }
        }
    }
};
```