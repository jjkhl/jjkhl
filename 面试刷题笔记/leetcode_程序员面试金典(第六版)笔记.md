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