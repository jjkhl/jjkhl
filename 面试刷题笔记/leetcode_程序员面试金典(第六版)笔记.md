# [����Ա���Խ�䣨�� 6 �棩](https://leetcode.cn/problem-list/xb9lfcwi/)

## [01.�ж��ַ��Ƿ�Ψһ](https://leetcode.cn/problems/is-unique-lcci/)
```c++
//λ��������ʾ26λ��ĸ�������λ��&x=1����ʾ���и���ĸ
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
## [02.�ж��Ƿ�Ϊ�ַ�����](https://leetcode.cn/problems/check-permutation-lcci/)
```c++
class Solution {
public:
    bool CheckPermutation(string s1, string s2) {
    int *record=new int[26]();
        for (int i = 0; i < s1.size(); i++) {
            // ������Ҫ��ס�ַ�a��ASCII��ֻҪ���һ�������ֵ�Ϳ�����
            record[s1[i] - 'a']++;
        }
        for (int i = 0; i < s2.size(); i++) {
            record[s2[i] - 'a']--;
        }
        for (int i = 0; i < 26; i++) {
            if (record[i] != 0) {
                // record��������е�Ԫ�ز�Ϊ��0��˵���ַ���s��t һ����˭�����ַ�����˭�����ַ���
                return false;
            }
        }
        // record��������Ԫ�ض�Ϊ��0��˵���ַ���s��t����ĸ��λ��
        delete [] record;
        return true;
    }
};
```
## [03.URL��](https://leetcode.cn/problems/string-to-url-lcci/)
**����ͬ**[��ָoffer05](https://leetcode.cn/problems/ti-huan-kong-ge-lcof/)
```c++
//ע����Ŀ�ٶ����ַ���β�����㹻�Ŀռ��������ַ�������֪���ַ����ġ���ʵ�����ȡ�
//˫ָ�뷨
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
## [04.�����Ӵ�](https://leetcode.cn/problems/palindrome-permutation-lcci/)
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