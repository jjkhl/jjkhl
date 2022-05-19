# [����Ա���Խ�䣨�� 6 �棩](https://leetcode.cn/problem-list/xb9lfcwi/)

## [0101.�ж��ַ��Ƿ�Ψһ](https://leetcode.cn/problems/is-unique-lcci/)
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
## [0102.�ж��Ƿ�Ϊ�ַ�����](https://leetcode.cn/problems/check-permutation-lcci/)
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
## [0103.URL��](https://leetcode.cn/problems/string-to-url-lcci/)
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
## [0104.�����Ӵ�](https://leetcode.cn/problems/palindrome-permutation-lcci/)
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

## [0105.һ�α༭](https://leetcode.cn/problems/one-away-lcci/)
```c++
//˫ָ�뷨
class Solution {
public:
    bool oneEditAway(string first, string second) {
        int len1=first.size(),len2=second.size();
        if(abs(len1-len2)>1) return false;
        //��֤len1>=len2
        if(len2==len1+1) return oneEditAway(second,first);

        int i=0,j=0;
        int diff=0;
        bool size_diff=(len2==len1)?false:true;
        while(i<len1&&j<len2)
        {
            if(first[i]!=second[j])
            {
                if(++diff>=2) return false;
                //���first��С��second���Ҳ���ͬ����first��Ҫ��second���һ����λ
                if(size_diff) j--;
            }
            ++i,++j;
        }
        return true;
    }
};
//˫�������
//�ο�˼·��https://leetcode.cn/problems/one-away-lcci/solution/c-by-zi-bu-yu-mf-052b/
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
## [0106.�ַ���ѹ��](https://leetcode.cn/problems/compress-string-lcci/)
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

## [0107.��ת����](https://leetcode.cn/problems/rotate-matrix-lcci/)
```c++
//�������Խ��߷�ת��������ֱ�����ϵĶԳ��ᷭת
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

## [0108.�����](https://leetcode.cn/problems/zero-matrix-lcci/)
ͬ[73.��������](https://leetcode-cn.com/problems/set-matrix-zeroes/)
```c++
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int rows=matrix.size(),cols=matrix[0].size();
        int row_flag=false;//true��ʾ��һ����0
        int col_flag=false;//true��ʾ��һ����0

        for(int i=0;i<rows;i++)
        {
            if(0==matrix[i][0])
            {
                col_flag=true;
                break;
            }
        }
        for(int j=0;j<cols;j++)
        {
            if(0==matrix[0][j])
            {
                row_flag=true;
                break;
            }
        }

        for(int i=1;i<rows;i++)
        {
            for(int j=1;j<cols;j++)
            {
                if(0==matrix[i][j])
                {
                    matrix[i][0]=matrix[0][j]=0;
                }
            }
        }

        for(int j=1;j<cols;j++)
        {
            if(0==matrix[0][j])
            {
                for(int i=1;i<rows;i++)
                    matrix[i][j]=0;
            }
        }

        for(int i=1;i<rows;i++)
        {
            if(0==matrix[i][0])
            {
                for(int j=1;j<cols;j++)
                    matrix[i][j]=0;
            }
        }

        if(row_flag)
        {
            for(int j=0;j<cols;j++)
                matrix[0][j]=0;
        }

        if(col_flag)
        {
            for(int i=0;i<rows;i++)
                matrix[i][0]=0;
        }
    }
};
```

## [0109.�ַ�����ת](https://leetcode.cn/problems/string-rotation-lcci/)
```c++
//һ������
class Solution {
public:
    bool isFlipedString(string s1, string s2) {
        return s1.length() == s2.length() && (s2 + s2).find(s1) != -1;
    }
};
//˫ָ�뷨
class Solution {
public:
    bool isFlipedString(string s1, string s2) {
        int len1=s1.size();
        int len2=s2.size();
        if(len1!=len2) return false;
        int index1=0,index2=0;
        while(index1<len1&&index2<len2)
        {
            if(s1[index1++]!=s2[index2++])
            {
                index2--;
            }
        }
        if(index2==len2&&index1!=len1)
        {
            index2=0;
            while(index1<len1)
            {
                if(s1[index1++]!=s2[index2++])
                    return false;
            }
        }
        else if(index1==len1&&index2!=len2)
        {
            index1=0;
            while(index2<len2)
            {
                if(s1[index1++]!=s2[index2++])
                    return false;
            }
        }
        return true;
    }
};
```

## [0201�Ƴ��ظ��ڵ�](https://leetcode.cn/problems/remove-duplicate-node-lcci/)
```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* removeDuplicateNodes(ListNode* head) {
        if(head==NULL)
            return head;
        unordered_set<int> occurred={head->val};
        ListNode* pos=head;
        //ö��ǰ���ڵ�
        while(pos->next)
        {
            //��ǰ����ɾ���Ľڵ�
            ListNode* cur=pos->next;
            if(!occurred.count(cur->val))
            {
                occurred.insert(cur->val);
                pos=pos->next;
            }
            else
            {
                pos->next=pos->next->next;
            }
        }
        pos->next=NULL;
        return head;
    }
};
```

## [0202.���ص�����K���ڵ�](https://leetcode.cn/problems/kth-node-from-end-of-list-lcci/)
```c++
class Solution {
public:
    int kthToLast(ListNode* head, int k) {
        ListNode *slow=head,*fast=head;
        while(k--)
        {
            fast=fast->next;
        }
        while(fast)
        {
            slow=slow->next;
            fast=fast->next;
        }
        return slow->val;
    }
};
```

## [0203.ɾ���м�ڵ�](https://leetcode.cn/problems/delete-middle-node-lcci/)
```c++
class Solution {
public:
    void deleteNode(ListNode* node) {
        node->val=node->next->val;
        node->next=node->next->next;
    }
};
```

