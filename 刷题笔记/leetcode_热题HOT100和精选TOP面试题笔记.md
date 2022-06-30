# [Leetcode����HOT 100](https://leetcode-cn.com/problem-list/2cktkvj/)
## [75.��ɫ����](https://leetcode-cn.com/problems/sort-colors/)
```c++
//���α���
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int n=nums.size();
        int p=0;
        for(int i=0;i<n;i++)
        {
            if(nums[i]==0)
                swap(nums[i],nums[p++]);
        }
        for(int i=p;i<n;i++)
            if(nums[i]==1)
                swap(nums[i],nums[p++]);
    }
};
//�Զ������
class Solution {
public:
    void mySort(int left,int right,vector<int>& nums)
    {
        if(left>=right)
            return;
        int i=left,j=right;
        int base=nums[left];
        while(i<j)
        {
            while(nums[j]>=base&&i<j) --j;//�ҵ��ұߵ�һ��С��base����
            while(nums[i]<=base&&i<j) ++i;//�ҵ���ߵ�һ������base����
            if(i<j) swap(nums[i],nums[j]);
        }
        //i=j
        swap(nums[left],nums[i]);
        mySort(left,i-1,nums);
        mySort(i+1,right,nums);
    }
    void sortColors(vector<int>& nums) {
        mySort(0,nums.size()-1,nums);
    }
};
//˫ָ��
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int zero = -1;            // ��֤�±� 0 �� zero ��Ӧ��Ԫ�ض�Ϊ 0 
        int two = nums.size();    // ��֤�±� two �� numsSize - 1 ��Ӧ��Ԫ�ض�Ϊ 2
        // ���ڵ���������Ԫ��Ϊ 2 ʱ��ֻ��Ҫ�����±� two - 1 ��Ӧ��Ԫ�����������Ԫ�أ����� for ������治д i++
        for (int i = 0; i < two;) {  
            // ֱ�ӽ���������Ԫ�� 1 ���뵽���� 1 �Ĳ��֣�i ���Ƽ�������
            if (nums[i] == 1) {          
                i++;
            } else if (nums[i] == 2) {
                //  �����±�Ϊ two ǰ��һ���±��Ӧ��Ԫ�����������Ԫ�� 2 ������������Ԫ�� 2 ���뵽���� 2 �Ĳ��֣�two ����
                swap(nums[i], nums[--two]);
            } else {                 
                //  �����±�Ϊ zero ����һ���±��Ӧ��Ԫ�����������Ԫ�� 0 ������������Ԫ�� 0 ���뵽���� 0 �Ĳ��֣�zero �� i ����
                swap(nums[++zero], nums[i++]);
            }
        }
    }
};
//���ӣ�https://leetcode-cn.com/problems/sort-colors/solution/75-yan-se-fen-lei-san-lu-kuai-pai-by-din-84w8/
```
## [146.LRU����](https://leetcode-cn.com/problems/lru-cache/)
```c++
class LRUCache {
public:
    LRUCache(int capacity):cap(capacity){}
    
    int get(int key) {
        if(map.find(key)==map.end()) return -1;
        //*map[key]��ʾ����map[key]��������ָ���ֵ
        pair<int,int> key_value=*map[key];
        cache.erase(map[key]);
        cache.push_front(key_value);
        map[key]=cache.begin();
        return key_value.second;
    }
    
    void put(int key, int value) {
        if(map.find(key)==map.end())
        {
            //û�ҵ�key���ǣ�����ɾ�����δʹ�ùؼ���
            if(cap==cache.size())
            {
                map.erase(cache.back().first);
                cache.pop_back();
            }
        }
        else
        {
            //�ҵ�key
            cache.erase(map[key]);
        }
        cache.push_front(make_pair(key,value));
        map[key]=cache.begin();
    }
private:
    int cap;
    list<pair<int,int>> cache;
    unordered_map<int,list<pair<int,int>>::iterator> map;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
```
## [152.�˻����������](https://leetcode-cn.com/problems/maximum-product-subarray/)
```c++
//��̬�滮
class Solution {
public:
    int maxThree(const int &a,const int &b,const int &c)
    {
        int res=a<b?b:a;
        return res<c?c:res;
    }
    int minThree(const int& a,const int &b,const int& c)
    {
        int res=a<b?a:b;
        return res<c?res:c;
    }
    int maxProduct(vector<int>& nums) {
        vector<int> maxProduct(nums),minProduct(nums);
        for(int i=1;i<nums.size();i++)
        {
            maxProduct[i]=maxThree(maxProduct[i-1]*nums[i],nums[i],minProduct[i-1]*nums[i]);
            minProduct[i]=minThree(maxProduct[i-1]*nums[i],nums[i],minProduct[i-1]*nums[i]);
        }
        return *max_element(maxProduct.begin(),maxProduct.end());
    }
};
//��������
class Solution {
public:
    int maxThree(const int &a,const int &b,const int &c)
    {
        int res=a<b?b:a;
        return res<c?c:res;
    }
    int minThree(const int& a,const int &b,const int& c)
    {
        int res=a<b?a:b;
        return res<c?res:c;
    }
    int maxProduct(vector<int>& nums) {
        int maxF=nums[0],minF=nums[0],res=nums[0];
        for(int i=1;i<nums.size();i++)
        {
            int maxTmp=maxF,minTmp=minF;
            maxF=maxThree(maxTmp*nums[i],nums[i],minTmp*nums[i]);
            minF=minThree(maxTmp*nums[i],nums[i],minTmp*nums[i]);
            res=max(maxF,res);
        }
        return res;
    }
};
```
## [155.��Сջ](https://leetcode-cn.com/problems/min-stack/)
```c++
//�޸���ջ
/*
����˼·��minValue������Сֵ��st���浱ǰ��ֵ����һ����Сֵ֮���ֵ�������ֵ<0��������ǰ��ֵ��С������minValue�������ֵ>0��minValue���䡣
*/
class MinStack {
    //st��ʾ��ǰֵ����һֵ֮��Ĳ�ֵ��С��0��ʾ��ǰֵ��С������0��ʾ��ǰֵ����
    stack<long long> st;
    long long minValue;
public:
    MinStack() {
        minValue=-1;
    }
    
    void push(int val) {
        if(st.empty())
        {
            //��0��Ϊ��׼����ʱminValue��Ϊpush�����Сֵ
            st.push(0);
            minValue=val;
        }
        else
        {
            long long dif=val-minValue;
            st.push(dif);
            //dif<0��ʾ��ǰֵ��С�����򱣳ֲ���
            minValue=dif<0?val:minValue;
        }
    }
    
    void pop() {
        if(!st.empty())
        {
            long long dif=st.top();
            st.pop();
            minValue=dif<0?minValue-dif:minValue;
        }
    }
    
    int top() {
        long long dif=st.top();
        return dif<0?minValue:minValue+dif;
    }
    
    int getMin() {
        return minValue;
    }
};
//����ջ
class MinStack {
public:
    MinStack() {
        min_stack.push(INT_MAX);
    }
    
    void push(int x) {
        x_stack.push(x);
        min_stack.push(min(min_stack.top(),x));
    }
    
    void pop() {
        x_stack.pop();
        min_stack.pop();
    }
    
    int top() {
        return x_stack.top();
    }
    
    int getMin() {
        return min_stack.top();
    }
private:
    stack<int> x_stack;
    stack<int> min_stack;
};
```
## [169.����Ԫ��](https://leetcode-cn.com/problems/majority-element/)
```c++
//Ħ��ͶƱ��
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int res=0;
        int count=0;
        for(auto num:nums)
        {
            if(count==0)
            {
                count++;
                res=num;
            }
            else if(count>0)
            {
                count=num==res?count+1:count-1;
            }
        }
        return res;
    }
};
```
## [200.��������](https://leetcode-cn.com/problems/number-of-islands/)
```c++
//�������
class Solution {
public:
    void dfs(vector<vector<char>> &grid,int x,int y)
    {
        if(x<0||x>=grid.size()||y<0||y>=grid[0].size()) return;
        if(grid[x][y]=='0') return;
        grid[x][y]='0';
        int di[4]={0,0,1,-1};
        int dj[4]={1,-1,0,0};
        for(int index=0;index<4;index++)
        {
            dfs(grid,x+di[index],y+dj[index]);
        }
    }
    int numIslands(vector<vector<char>>& grid) {
        int res=0;
        for(int i=0;i<grid.size();i++)
        {
            for(int j=0;j<grid[0].size();j++)
            {
                if(grid[i][j]=='1')
                {
                    dfs(grid,i,j);
                    ++res;
                }
            }
        }
        return res;
    }
};
```
## [207.�γ̱�](https://leetcode-cn.com/problems/course-schedule/)
```c++
//��������
class Solution {
public:
   bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
	vector<int> v;
	vector<int> indegree(numCourses,0);
    unordered_multimap<int,int> outdegree;
	for (int i = 0; i < prerequisites.size(); i++)
	{
		indegree[prerequisites[i][0]]++;
        //�����outdegree[����]=����ܺ�
		outdegree.emplace(prerequisites[i][1],prerequisites[i][0]);
	}
	//�����Ϊ0�Ķ������
	queue<int> myqueue;
	for (int i = 0; i < numCourses; i++)
	{
		if (indegree[i] == 0)
			myqueue.push(i);
	}
	int cnt = 0;
	while (!myqueue.empty())
	{
		int temp = myqueue.front();
		myqueue.pop();
		cnt++;
        auto [begin,end]=outdegree.equal_range(temp);
        for(unordered_multimap<int,int>::iterator it=begin;it!=end;it++)
        {
            if(--indegree[it->second]==0)
                myqueue.push(it->second);
        }
	}
	return cnt == numCourses;
}
};
```
## [210.�γ̱�II](https://leetcode-cn.com/problems/course-schedule-ii/)
```c++
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        if(prerequisites.size()==0)
        {
            vector<int> res;
            for(int i=0;i<numCourses;i++)
            {
                res.push_back(i);
            }
            return res;
        }
        int *indegree=new int[numCourses]{0};
		// vector<int> indegree(numCourses,0);
        unordered_multimap<int,int> out;//�洢�ڵ��Ӧ�ĳ���
        for(int i=0;i<prerequisites.size();i++)
        {
            ++indegree[prerequisites[i][0]];
            out.emplace(prerequisites[i][1],prerequisites[i][0]);
        }
        queue<int> que;
        //�������Ϊ0�Ľڵ�
        vector<int> course;
        for(int i=0;i<numCourses;i++)
        {
            if(indegree[i]==0)
            {
                que.push(i);
            }
        }
        while(!que.empty())
        {
            int classNumber=que.front();
            que.pop();
            course.push_back(classNumber);
            auto [begin,end]=out.equal_range(classNumber);
            for(auto it=begin;it!=end;it++)
            {
                if(--indegree[it->second]==0)
                    que.push(it->second);
            }
        }
        return numCourses==course.size()?course:vector<int>{};
    }
};
```
## [208.ʵ��ǰ׺��](https://leetcode-cn.com/problems/implement-trie-prefix-tree/)
```c++
class Trie
{
private:
	bool isWord;//�Ƿ�����������Ϊ��β�ĵ���
	// vector<Trie*> son(26,NULL);
	Trie* son[26];

public:
	Trie()
	{
		isWord = false;
		for (int i = 0; i < 26; i++)
			son[i] = NULL;
	}
	~Trie()
	{
		for (int i = 0; i < 26; i++)
		{
			if (son[i])
				delete son[i];
		}
	}

	void insert(string word)
	{
		Trie *root = this;
		for (char x : word)
		{
			int index = x - 'a';
			if (!root->son[index])
				root->son[index] = new Trie;
			root = root->son[index];
		}
		root->isWord = true;
	}

	bool search(string word)
	{
		Trie *root = this;
		for (char x : word)
		{
			int index = x - 'a';
			if (root->son[index] == NULL)
				return false;
			root = root->son[index];
		}
		return root->isWord;
	}

	bool startsWith(string prefix)
	{
		Trie *root = this;
		for (char x : prefix)
		{
			int index = x - 'a';
			if (root->son[index] == NULL)
				return false;
			root = root->son[index];
		}
		return true;
	}
};
```
## [215.�����е�K������Ԫ��](https://leetcode-cn.com/problems/kth-largest-element-in-an-array/)
```c++
//����
class Solution
{
public:
	int findKthLargest(vector<int> &nums, int k)
	{
		int len=nums.size();
		int left=0,right=len-1;
		while(left<=right)
		{
			int mid=quickSort(nums,left,right);
			if(mid==len-k) return nums[mid];
			else if(mid<len-k) left=mid+1;
			else right=mid-1;
		}
		return -1;
	}
	int quickSort(vector<int>& nums,int left,int right)
	{
		int base=nums[left];
		int i=left,j=right;
		while(i<j)
		{
			while(i<j&&nums[j]>=base) --j;
			while(i<j&&nums[i]<=base) ++i;
			swap(nums[i],nums[j]);
		}
		swap(nums[i],nums[left]);
		return i;
	}
};
```
## [221.���������](https://leetcode-cn.com/problems/maximal-square/)
```c++
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if(matrix.empty()||matrix[0].empty()) return 0;
		int rows=matrix.size();
		int cols=matrix[0].size();
		int maxLen=0;
		//dp[i][j]����i��jΪ���½ǵ������α߳�
		vector<vector<int>> dp(rows,vector<int>(cols,0));
		//��ʼ����һ��
		for(int i=0;i<rows;i++)
		{
			dp[i][0]=matrix[i][0]-'0';
			if(maxLen<dp[i][0]) maxLen=dp[i][0];
		}
		//��ʼ����һ��
		for(int j=0;j<cols;j++)
		{
			dp[0][j]=matrix[0][j]-'0';
			if(maxLen<dp[0][j]) maxLen=dp[0][j];
		}
		for(int i=1;i<rows;++i)
		{
			for(int j=1;j<cols;++j)
			{
				if(matrix[i][j]=='0') continue;
				int len1=dp[i-1][j];//�Ϸ�����
				int len2=dp[i][j-1];//�󷽾���
				int len3=dp[i-1][j-1];//���Ͼ���
				dp[i][j]=min(min(len1,len2),len3)+1;
				maxLen=max(dp[i][j],maxLen);
			}
		}
		return maxLen*maxLen;
    }
};
//������ӣ�https://leetcode-cn.com/problems/maximal-square/solution/dong-tai-gui-hua-c-by-zhengjingwei/
```
## [238.���������������ĳ˻�](https://leetcode-cn.com/problems/product-of-array-except-self/)
```c++
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int len=nums.size();
        vector<int> leftPro(len,0),rightPro(len,0);
        vector<int> res(len,0);
        leftPro[0]=1;
        for(int i=1;i<len;i++)
            leftPro[i]=leftPro[i-1]*nums[i-1];
        rightPro[len-1]=1;
        for(int i=len-2;i>=0;i--)
            rightPro[i]=rightPro[i+1]*nums[i+1];
        for(int i=0;i<len;i++)
            res[i]=leftPro[i]*rightPro[i];
        return res;
    }
};
//�ռ��Ż�
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int len=nums.size();
        vector<int> res(len);
        //res[i]��ʾ�������Ԫ�صĳ˻�
        res[0]=1;
        for(int i=1;i<len;i++)
        {
            res[i]=res[i-1]*nums[i-1];
        }
        int R=1;
        for(int i=len-1;i>=0;i--)
        {
            res[i]=res[i]*R;
            R*=nums[i];
        }
        return res;
    }
};
```
## [240.������ά����II](https://leetcode-cn.com/problems/search-a-2d-matrix-ii/)
```c++
class Solution
{
public:
    bool searchMatrix(vector<vector<int>> &matrix, int target)
    {
        int rows = matrix.size();
        int cols = matrix[0].size();
        if(rows==0||cols==0) return false;
        int i=0,j=cols-1;
        while(i<rows&&j>=0)
        {
            if(target>matrix[i][j]) i++;
            else if(target<matrix[i][j]) j--;
            else return true;
        }
        return false;
    }
};
```
## [338.����λ����](https://leetcode-cn.com/problems/counting-bits/)
```c++
//��λ��Ч��
class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> dp(n+1,0);
        for(int i=1;i<=n;i++)
        {
            //dp[i]Ϊi/2λ�õ�1����+����
            //������ָ������Ҫ+1��ż������Ҫ+1
            dp[i]=dp[i>>1]+(i&1);
        }
        return dp;
    }
};
//��λ��Ч��
class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> dp(n+1,0);
        int highBits=0;
        for(int i=1;i<=n;i++)
        {
            //��i&(i-1)=0����ʱΪ2����������
            if((i&(i-1))==0)
                highBits=i;
            dp[i]=dp[i-highBits]+1;
        }
        return dp;
    }
};
//Brian Kernighan �㷨
class Solution {
public:
    int countOnes(int x)
    {
        int ones=0;
        while(x>0)
        {
            x&=x-1;
            ones++;
        }
        return ones;
    }
    vector<int> countBits(int n) {
        vector<int> dp(n+1,0);
        for(int i=0;i<=n;i++)
        {
            dp[i]=countOnes(i);
        }
        return dp;
    }
};
```
## [394.�ַ�������](https://leetcode-cn.com/problems/decode-string/)
```c++
//����ջ
class Solution
{
public:
    string decodeString(string s)
    {
        string res = "";
        stack<int> nums;
        stack<string> strs;
        int num = 0;
        int len = s.size();
        for (int i = 0; i < len; i++)
        {
            if (s[i] >= '0' && s[i] <= '9')
            {
                num = num * 10 + s[i] - '0';
            }
            else if (s[i] == '[')
            {
                nums.push(num);
                num = 0;
                strs.push(res);
                res="";
            }
            else if (s[i] == ']')
            {
                int times = nums.top();
                nums.pop();
                for (int j = 0; j < times; j++)
                {
                    strs.top() += res;
                }
                res = strs.top();
                strs.pop();
            }
            else
            {
                res += s[i];
            }
        }
        return res;
    }
};
//���ݷ�
class Solution
{
public:
    string analysis(string s,int& index)
    {
        string res;
        int num=0;
        string tmp;
        while(index<s.size())
        {
            if(isdigit(s[index]))
            {
                num=10*num+s[index]-'0';
            }
            else if('['==s[index])
            {
                tmp=analysis(s,++index);
                for(int i=0;i<num;i++)
                {
                    res+=tmp;
                }
                num=0;
            }
            else if(']'==s[index]) break;
            else res+=s[index];
            index++;
        }
        return res;
    }
    string decodeString(string s)
    {
       int index=0;
       return analysis(s,index);
    }
};
```
## [399.������ֵ](https://leetcode-cn.com/problems/evaluate-division/)
```c++
//�����㷨
class Solution {
public:
    unordered_map<string, string> father; // father[x] ��¼�ڵ� x �����Ƚڵ㣬����˳��ָ�Ӵ�С������
    unordered_map<string, double> distance; // distance[x] ��¼�ڵ� x �����Ƚڵ�ľ��루�� x / root��
    string find(string x) {
        if(father[x] != x) {
            string t = find(father[x]);
            distance[x] *= distance[father[x]];
            father[x] = t;
        }
        return father[x];
    }
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        // ��ʼ�����нڵ�
        for(int i = 0; i < equations.size(); i++) {
            string dividend = equations[i][0], divisor = equations[i][1];
            father[dividend] = dividend, father[divisor] = divisor;
            distance[dividend] = 1, distance[divisor] = 1;
        }
        // ���Ϻϲ�
        for(int i = 0; i < equations.size(); i++) {
            string dividend = equations[i][0], divisor = equations[i][1];
            string t1 = find(dividend); // �ҵ������������Ƚڵ�
            //����ڵ���ɻ�����Ҫ����
            string t2=find(divisor);
            if(t1==t2) continue;
            // ���� t1 �ڵ�
            father[t1] = divisor; 
            distance[t1] = values[i] / distance[dividend];
        }
        vector<double> res;
        for(auto q : queries) {
            string dividend = q[0], divisor = q[1];
            // ���divisor��dividend����ͬһ���ϻ��Զ���� distance[divisor]��distance[dividend]
            //���divisor��dividend�����ڣ�����divisor��dividend�����Ƚڵ㲻һ��(˵������֮�����κ���ϵ)
            //��Ϊ���Ϻϲ���һ����׼ȷ��Ӧ���ڵ�֮���ϵ�����Ǿ�����Դ����׼ȷ������
            if(!father.count(dividend) || !father.count(divisor)||find(dividend)!=find(divisor)) res.push_back(-1.0);
            else {
                res.push_back(distance[dividend] / distance[divisor]);
            }
        }
        return res;
    }
};
//floyd�㷨
class Solution
{
public:
    //graph[i][j]��ʾ��i/j��ֵ
    vector<vector<double>> graph;
    unordered_map<string,int> h;
    int n=0;
    void floyd()
    {
        //��ÿ���ڵ����ѭ��
        for(int k=0;k<n;k++)
        {
            for(int i=0;i<n;i++)
            {
                for(int j=0;j<n;j++)
                {
                    //ֻ�е�graph[i][k],graph[k][j]���ߵ�ʱ����ܽ��и���g[i][j]
                    //��ʽ��ʾi/j=(i/k)*(k/j)
                    if(graph[i][k]>=0&&graph[k][j]>=0)
                        graph[i][j]=graph[i][k]*graph[k][j];
                }
            }
        }
    }
    vector<double> calcEquation(vector<vector<string>> &equations, vector<double> &values, vector<vector<string>> &queries)
    {
        //���ַ���ӳ�䵽�����±�
        for(int i=0;i<equations.size();i++)
        {
            string a=equations[i][0],b=equations[i][1];
            if(!h.count(a)) h[a]=n++;
            if(!h.count(b)) h[b]=n++;
        }
        //��ʾ���ܵ���
        graph=vector<vector<double>>(n,vector<double>(n,-1));
        //�ԽǴ���ʼ��Ϊ1
        for(int i=0;i<n;i++)
        {
            graph[i][i]=1;
        }
        for(int i=0;i<equations.size();i++)
        {
            string a=equations[i][0],b=equations[i][1];
            graph[h[a]][h[b]]=values[i];
            graph[h[b]][h[a]]=1/values[i];
        }
        vector<double> res;
        floyd();
        for(auto q:queries)
        {
            string a=q[0],b=q[1];
            if(!h.count(a)||!h.count(b)||graph[h[a]][h[b]]==-1)
            {
                res.push_back(-1.0);
            }        
            else
            {
                res.push_back(graph[h[a]][h[b]]);
            }
        }
        return res;
    }
};
```
## [990.��ʽ���̵Ŀ�������](https://leetcode-cn.com/problems/satisfiability-of-equality-equations/)
```c++
class Solution
{
public:
    bool equationsPossible(vector<string> &equations)
    {
        int len = equations.size();
        //ֻ��һ����ʽ��ʱ�򲻻Ὠͼ
        if (1 == len)
        {
            if (equations[0][0] == equations[0][3] && equations[0][1] == '=')
                return true;
            else if (equations[0][0] != equations[0][3] && equations[0][1] == '!')
                return true;
            else return false;
        }
        int n=0;
        unordered_map<char,int> umap;//��¼�ַ����
        for(int i=0;i<len;i++)
        {
            char c1=equations[i][0],c2=equations[i][3];
            if(umap.count(c1)==0) umap[c1]=n++;
            if(umap.count(c2)==0) umap[c2]=n++;
        }
        vector<vector<bool>> graph(n,vector<bool>(n,false));
        vector<int> notEqual;
        for(int i=0;i<len;i++)
        {
            int m=umap[equations[i][0]];
            int n=umap[equations[i][3]];
            char flag=equations[i][1];
            if('='==flag)
            {
                graph[m][n]=true;
                graph[n][m]=true;
            }
            else
            {
                notEqual.push_back(i);
            }
        }
        for(int k=0;k<n;k++)
        {
            for(int i=0;i<n;i++)
            {
                for(int j=0;j<n;j++)
                {
                    if(graph[i][k]&&graph[k][j])
                        graph[i][j]=true;
                }
            }
        }
        for(int i=0;i<notEqual.size();i++)
        {
            int id=notEqual[i];
            int m=umap[equations[id][0]];
            int n=umap[equations[id][3]];
            if(n==m||graph[m][n])
                return false;
        }
        return true;
    }
};
```
## [448.�ҵ�������������ʧ������](https://leetcode-cn.com/problems/find-all-numbers-disappeared-in-an-array/)
```c++
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        vector<int> res;
        if(nums.empty()) return nums;
        int len=nums.size();
        for(int i=0;i<len;i++)
        {
            //indexΪӦ�ó��ֵ�λ��
            //nums[index]��ʾ��λ�ó����ˣ�+n��������ж�>len��ʾ��λ�ó��ֹ�
            //%len��Ϊ�˷�ֹ��ǰλ���Ѿ�+n
            int index=(nums[i]-1)%len;
            nums[index]+=len;
        }
        for(int i=0;i<len;i++)
        {
            if(nums[i]<=len)
                res.push_back(i+1);
        }
        return res;
    }
};
```
## [581.�����������������](https://leetcode-cn.com/problems/shortest-unsorted-continuous-subarray/)
```c++
class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int len = nums.size();
        int min = nums[len-1];
        int max = nums[0];
        int begin = 0, end = -1;
        //����
        for(int i = 0; i < len; i++){
            //������Ӧ���������ҵ�������������λ��
            if(nums[i] < max){
                end = i;
            }else{
                max = nums[i];
            }
            //���ҵ���Ӧ���ǽ����ҵ����ǽ�������һ��λ��
            if(nums[len-i-1] > min){
                begin = len-i-1;
            }else{
                min = nums[len-i-1];
            }            
        }
        return end-begin+1;
    }
};
```
## [621.���������](https://leetcode-cn.com/problems/task-scheduler/)
```c++
//˼·���ӣ�https://leetcode-cn.com/problems/task-scheduler/solution/tong-zi-by-popopop/
//˼·���ܣ������������Ͱ����Ϊ���������һ��Ͱ���û����ͬ����������Ͱ����ʱ��tһ��Ϊ1(�����ڵȴ�ʱ��)��
//���ȴ�ʱ��һ���Ƕ�����Ҫ�ȴ�ʱ�䣬�ܼ�ʱ��tasks.size()������һ������Ҫ�ȴ�ʱ��(���Ͱ��-1)*(n+1)+���ʣ���ʱ��t������(n+1)��ʾ����������һ��ʱ��
class Solution
{
public:
    int leastInterval(vector<char> &tasks, int n)
    {
        unordered_map<char, int> umap;
        for (char &ch : tasks)
        {
            umap[ch]++;
        }
        //Ͱ���������ʣ�������
        int nums = 0, remain = 0;
        for (auto pair : umap)
        {
            //�ҵ����Ͱ��
            if (nums < pair.second)
            {
                nums = pair.second;
                //���һ��Ͱһ����1���������ͬ�������������++
                remain = 1;
            }
            else if (pair.second == nums)
            {
                remain++;
            }
        }
        int nums1 = tasks.size();
        int nums2 = (nums - 1) * (n + 1) + remain;
        return max(nums1,nums2);
    }
};
```
## [560.��ΪK��������](https://leetcode-cn.com/problems/subarray-sum-equals-k/)
```c++
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int,int> umap;
        umap[0]=1;
        int res=0,pre=0;
        for(const int& num:nums)
        {
            pre+=num;
            if(umap.count(pre-k)>0)
            {
                res+=umap[pre-k];
            }
            umap[pre]++;
        }
        return res;
    }
};
```
# [LeetCode ��ѡ TOP ������](https://leetcode-cn.com/problem-list/2ckc81c/)
## [1.����֮��](https://leetcode-cn.com/problems/two-sum/)
```c++
class Solution {
public:
    vector<int> twoSum(vector<int> &nums, int target)
{
    unordered_map<int,int> umap;
    for(int i=0;i<nums.size();i++)
    {
        unordered_map<int,int>::iterator iter=umap.find(target-nums[i]);
        if(iter!=umap.end())
            return {iter->second,i};
        umap[nums[i]]=i;
    }
    return {};
}
};
```
## [2.�������](https://leetcode-cn.com/problems/add-two-numbers/)
```c++
//������
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* dummyHead=new ListNode(0);
        ListNode *cur=dummyHead;
        int sum=0;
        while(l1||l2||sum)
        {
            if(l1) sum+=l1->val;
            if(l2) sum+=l2->val;
            ListNode* tmp=new ListNode(sum%10);
            cur->next=tmp;
            cur=cur->next;
            if(l1) l1=l1->next;
            if(l2) l2=l2->next;
            sum/=10;
        }
        return dummyHead->next;
    }
};
```
## [3.���ظ��ַ�����Ӵ�](https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/)
```c++
//��������
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int left=0,right=0;
        int res=0,curLen=0;
        int len=s.size();
        while(right<len)
        {
            char tmp=s[right];
            for(int i=left;i<right;i++)
            {
                if(tmp==s[i])
                {
                    left=i+1;
                    curLen=right-left;
                    break;
                }
            }
            right++;
            res=res>++curLen?res:curLen;
        }
        return res;
    }
};
//��ϣ��
class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        int left = 0, right = 0;
        int len = 0, res = 0;
        int sSize = s.size();
        unordered_map<char, int> umap;
        while (right < sSize)
        {
            char tmp = s[right];
            if (umap.count(tmp)!=0&&umap[tmp]>=left)
            {
                left=umap[tmp]+1;
                len=right-left;
            }
            umap[tmp]=right++;
            res=max(res,++len);
        }
        return res;
    }
};
```
## [4.Ѱ�����������������λ��](https://leetcode-cn.com/problems/median-of-two-sorted-arrays/)
```c++
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m=nums1.size(),n=nums2.size();
        int i=0,j=0;
        //����ֻ����left���أ�ż����᷵��left��right��һ��
        int left=0,right=0;
        int xSize=(m+n)>>1;
        for(int x=0;x<=xSize;x++)
        {
            left=right;
            if(i<m&&j>=n)//��ʾ����2�������
            {
                right=nums1[i++];
            }
            else if(i>=m&&j<n)//��ʾ����1�������
            {
                right=nums2[j++];
            }
            else
            {
                right=nums1[i]<nums2[j]?nums1[i++]:nums2[j++];
            }
        }
        return (m+n)&1?right:(left+right)/2.0;
    }
};
```
## [5.������Ӵ�](https://leetcode-cn.com/problems/longest-palindromic-substring/)
```c++
class Solution {
public:
    int left=0;
    int right=0;
    int maxLen=0;
    string longestPalindrome(string s) {
        for(int i=0;i<s.size();i++)
        {
            extend(s,i,i,s.size());
            extend(s,i,i+1,s.size());
        }
        return s.substr(left,maxLen);
    }
    void extend(const string& s,int i,int j,int n)
    {
        while(i>=0&&j<n&&s[i]==s[j])
        {
            if(j-i+1>maxLen)
            {
                left=i;
                right=j;
                maxLen=j-i+1;
            }
            --i,++j;
        }
    }
};
```
## [7.������ת](https://leetcode-cn.com/problems/reverse-integer/)
```c++
class Solution {
public:
    int reverse(int x) {
        int res=0;
        while(x)
        {
            if(res<INT_MIN/10||res>INT_MAX/10) return 0;
            res=res*10+x%10;
            x/=10;
        }
        return res;
    }
};
```
## [8.�ַ���ת������(stoi)](https://leetcode-cn.com/problems/string-to-integer-atoi/)
```c++
class Solution {
public:
    int myAtoi(string s) {
        int i=0;
        int flag=1;
        int len=s.size();
        while(i<len&&s[i]==' ') i++;
        if(len==i||(!isdigit(s[i])&&s[i]!='+'&&s[i]!='-'))
            return 0;
        if(s[i]=='-'||s[i]=='+')
        {
            flag=s[i++]=='-'?-1:1;
        }
        long num=0;
        while(i<len&&isdigit(s[i]))
        {
            char curChar=s[i++];
            if(num>INT_MAX/10||(num==INT_MAX/10&&(curChar-'0')>INT_MAX%10)) return INT_MAX;
            else if(num<INT_MIN/10||(num==INT_MIN/10&&(curChar-'0')>-(INT_MIN%10))) return INT_MIN;
            else
            {
                num=num*10+flag*(curChar-'0');
            }
        }
        return num;
    }
};
```
## [11.ʢ���ˮ������](https://leetcode-cn.com/problems/container-with-most-water/)
```c++
class Solution {
public:
    int maxArea(vector<int>& height) {
        int len=height.size();
        int maxV=0;
        int left=0,right=len-1;
        while(left<right)
        {
            maxV=max(min(height[left],height[right])*(right-left),maxV);
            if(height[left]<height[right])
            {
                left++;
            }
            else right--;
        }
        return maxV;
    }
};
```
## [12.����ת��������](https://leetcode-cn.com/problems/integer-to-roman/)
```c++
//13����Ϊ��������ֻ�涨��6�����������ԭ����7�����
class Solution {
public:
    const pair<int,string> valueSymbols[13]={
        {1000,"M"},{900,"CM"},{500,"D"},
        {400,"CD"},{100,"C"},{90,"XC"},
        {50,"L"},{40,"XL"},{10,"X"},
        {9,"IX"},{5,"V"},{4,"IV"},{1,"I"}
    };
    string intToRoman(int num) {
        string roman="";
        for(const auto& [val,symbol]:valueSymbols)
        {
            while(num>=val)
            {
                num-=val;
                roman+=symbol;
            }
            if(num==0) break;
        }
        return roman;
    }
};
```
## [13.��������ת����](https://leetcode-cn.com/problems/roman-to-integer/)
```c++
//����
class Solution {
public:
    unordered_map<char, int> symbolValues = {
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D', 500},
        {'M', 1000},
    };
    int romanToInt(string s) {
        int num=0;
        int len=s.size();
        for(int i=len-1;i>=0;i--)
        {
            char curChar=s[i];
            if(i+1<len&&symbolValues[curChar]<symbolValues[s[i+1]])
                num-=symbolValues[curChar];
            else num+=symbolValues[curChar];
        }
        return num;
    }
};
//˳��
class Solution {
public:
    unordered_map<char, int> symbolValues = {
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D', 500},
        {'M', 1000},
    };
    int romanToInt(string s) {
        int num=0;
        int len=s.size();
        for(int i=0;i<len;i++)
        {
            int value=symbolValues[s[i]];
            if(i+1<len&&value<symbolValues[s[i+1]])
                num-=value;
            else num+=value;
        }
        return num;
    }
};
```
## [14.�����ǰ׺](https://leetcode-cn.com/problems/longest-common-prefix/)
```c++
//���αȽ�
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string res=strs[0];
        if(strs.size()==1) return res;
        for(int i=1;i<strs.size();i++)
        {
            int right=0;
            while(right<res.size()&&right<strs[i].size()&&res[right]==strs[i][right]) right++;
            res=res.substr(0,right);
        }
        return res;
    }
};
//����
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.size()==1) return strs[0];
        sort(strs.begin(),strs.end());
        int index=0;
        while(index<strs[0].size()&&index<strs.back().size())
        {
            if(strs[0][index]!=strs.back()[index])
            {
                break;
            }
            index++;
        }
        return strs[0].substr(0,index);
    }
};
```
## [15.����֮��](https://leetcode-cn.com/problems/3sum/)
```c++
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int len=nums.size();
        sort(nums.begin(),nums.end());
        vector<vector<int>> res;
        for(int i=0;i<nums.size();i++)
        {
            if(nums[i]>0)  return res;
            if(i-1>=0&&nums[i]==nums[i-1]) continue;
            int left=i+1,right=len-1;
            while(left<right)
            {
                int sum=nums[i]+nums[right]+nums[left];
                if(sum>0) right--;
                else if(sum<0) left++;
                else 
                {
                    res.push_back(vector<int>{nums[i],nums[left],nums[right]});
                    while(left<right&&nums[right]==nums[right-1]) --right;
                    while(left<right&&nums[left]==nums[left+1]) ++left;
                    --right,++left;
                }
            }
        }
        return res;
    }
};
```
## [17.�绰�������ĸ���](https://leetcode-cn.com/problems/letter-combinations-of-a-phone-number/)
```c++
class Solution {
public:
    unordered_map<int,string> phone={
        {0,""},{1,""},
        {2,"abc"},{3,"def"},{4,"ghi"},{5,"jkl"},
        {6,"mno"},{7,"pqrs"},{8,"tuv"},{9,"wxyz"}
    };
    vector<string> res;
    string path;
    void backTrack(const string&digits,int index)
    {
        if(index>=digits.size())
        {
            res.push_back(path);
            return;
        }
        int digit=digits[index]-'0';
        string word=phone[digit];
        for(int i=0;i<word.size();i++)
        {
            path.push_back(word[i]);
            backTrack(digits,index+1);
            path.pop_back();
        }
    }
    vector<string> letterCombinations(string digits) {
        if(digits.size()==0) return res;
        backTrack(digits,0);
        return res;
    }
};
```
## [19.ɾ������ĵ�����N���ڵ�](https://leetcode-cn.com/problems/remove-nth-node-from-end-of-list/)
```c++
//˫ָ��
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        //fast����n��
        if(!head||!head->next) return NULL;
        ListNode *fast=head,*slow=head;
        while(n--)
        {
           fast=fast->next;
        }
        if(!fast) return head->next;//���fastΪ�գ���ʾɾ����һ��Ԫ��
        while(fast->next&&slow->next)
        {
            fast=fast->next;
            slow=slow->next;
        }
        ListNode* node=slow->next;
        slow->next=slow->next->next;
        delete node;
        return head;
    }
};
//�ݹ�
class Solution {
public:
    int cur=0;
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if(!head) return NULL;
        head->next=removeNthFromEnd(head->next,n);
        if(n==++cur) return head->next;
        return head;
    }
};
```
## [20.��Ч������](https://leetcode-cn.com/problems/valid-parentheses/)
```c++
class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        for(int i=0;i<s.size();i++)
        {
            if(s[i]=='(')  st.push(')');
            else if(s[i]=='[') st.push(']');
            else if(s[i]=='{') st.push('}');
            else if(st.empty()||st.top()!=s[i]) return false;
            else st.pop();
        }
        return st.empty();
    }
};
```
## [22.��������](https://leetcode-cn.com/problems/generate-parentheses/)
```c++
class Solution {
public:
    vector<string> res;
    void dfs(string path,int n,int left,int right)
    {
        if(right>left) return;
        if(right==n&&right==left)
        {
            res.push_back(path);
            return;
        }
        if(left<n) dfs(path+'(',n,left+1,right);
        if(right<n) dfs(path+')',n,left,right+1);
    }
    vector<string> generateParenthesis(int n) {
        dfs("",n,0,0);
        return res;
    }
};
```
## [29.�������](https://leetcode-cn.com/problems/divide-two-integers/)
```c++
class Solution
{
public:
    int divide(int dividend, int divisor)
    {
        if (dividend == INT_MIN && divisor == -1)
            return INT_MAX;
        if(divisor==1) return dividend;
        int res = 0;
        long m = abs(dividend), n = abs(divisor);
        bool sign = (dividend > 0 && divisor > 0) || (dividend < 0 && divisor < 0) ? true : false;
        while (m >= n)
        {
            long d = n, c = 1; //����n�ı���d������c����ʾc������d��
            while (m-d>= d)
            {
                d <<= 1;
                c <<= 1;
            }
            res += c;//��ʾ��c*d������������+c
            m -= d;
        }
        return sign ? res : -res;
    }
};
```
## [36.��Ч������](https://leetcode-cn.com/problems/valid-sudoku/)
```c++
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        int row[9][10] = {0};// ��ϣ��洢ÿһ�е�ÿ�����Ƿ���ֹ���Ĭ�ϳ�ʼ����£�ÿһ��ÿһ������û�г��ֹ�
        // ����board��9�У��ڶ�ά��ά��10��Ϊ�����±���9���������е�����9��Ӧ��
        int col[9][10] = {0};// �洢ÿһ�е�ÿ�����Ƿ���ֹ���Ĭ�ϳ�ʼ����£�ÿһ�е�ÿһ������û�г��ֹ�
        int box[9][10] = {0};// �洢ÿһ��box��ÿ�����Ƿ���ֹ���Ĭ�ϳ�ʼ����£���ÿ��box�У�ÿ������û�г��ֹ�������board��9��box��
        for(int i=0; i<9; i++){
            for(int j = 0; j<9; j++){
                // ��������i�е�j�е��Ǹ���,����Ҫ�ж�������������ڵ�����û�г��ֹ���
                // ͬʱ�ж�������������ڵ�����û�г��ֹ�
                // ͬʱ�ж�������������ڵ�box����û�г��ֹ�
                if(board[i][j] == '.') continue;
                int curNumber = board[i][j]-'0';
                if(row[i][curNumber]) return false; 
                if(col[j][curNumber]) return false;
                if(box[j/3 + (i/3)*3][curNumber]) return false;

                row[i][curNumber] = 1;// ֮ǰ��û���ֹ������ڳ����ˣ��͸�����Ϊ1���´����������ܹ�ֱ�ӷ���false�ˡ�
                col[j][curNumber] = 1;
                box[j/3 + (i/3)*3][curNumber] = 1;
            }
        }
        return true;
    }
};
//https://leetcode-cn.com/problems/valid-sudoku/solution/36-jiu-an-zhao-cong-zuo-wang-you-cong-shang-wang-x/
```
## [88.�ϲ�������������](https://leetcode-cn.com/problems/merge-sorted-array/)
```c++
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i=nums1.size()-1;
        m--,n--;
        while(n>=0)
        {
            while(m>=0&&nums1[m]>nums2[n])
                swap(nums1[i--],nums2[m--]);
            swap(nums1[i--],nums2[n--]);
        }
    }
};
```
## [91.���뷽��](https://leetcode-cn.com/problems/decode-ways/)
```c++
//��������̨�׵Ķ�̬�滮
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
```
## [38.�������](https://leetcode-cn.com/problems/count-and-say/)
```c++
class Solution {
public:
    string countAndSay(int n) {
        if(1==n) return "1";
        string s=countAndSay(n-1);
        string res="";
        for(int i=0,j=0;i<s.size();)
        {
            char c=s[i];
            while(i<s.size()&&s[i]==c) ++i;
            string cnt=to_string(i-j);
            res+=cnt+c;
            j=i;
        }
        return res;
    }
};
```
## [41.ȱʧ�ĵ�һ������](https://leetcode-cn.com/problems/first-missing-positive/)
```c++
class Solution
{
public:
    int firstMissingPositive(vector<int> &nums)
    {
        int n = nums.size();
        for(int& num:nums)
        {
            if(num<=0) num=n+1;
        }
        for(int i=0;i<n;i++)
        {
            int num=abs(nums[i]);
            if(num-1<n)
            {
                nums[num-1]=-abs(nums[num-1]);
            }
        }
        for(int i=0;i<n;i++)
        {
            if(nums[i]>0) return i+1;
        }
        return n+1;
    }
};
```
## [66.��һ](https://leetcode-cn.com/problems/plus-one/)
```c++
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int n = digits.size();
        while(n && ++digits[--n] == 10) digits[n] = 0;
        if(digits[0] == 0) digits.insert(begin(digits), 1);
        return digits;
    }
};
```
## [73.��������](https://leetcode-cn.com/problems/set-matrix-zeroes/)
```c++
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int rows=matrix.size();
        int cols=matrix[0].size();
        bool row_flag=false;//true��ʾ��һ����0
        bool col_flag=false;//true��ʾ��һ����0
        for(int i=0;i<rows;i++)
        {
            if(matrix[i][0]==0)
            {
                col_flag=true;
                break;
            }
        }
        for(int j=0;j<cols;j++)
        {
            if(matrix[0][j]==0)
            {
                row_flag=true;
                break;
            }
        }

        for(int i=1;i<rows;i++)
        {
            for(int j=1;j<cols;j++)
            {
                if(matrix[i][j]==0)
                {
                    matrix[i][0]=matrix[0][j]=0;
                }
            }
        }
        //�����һ����0���򽫸���ȫ��Ϊ0
        for(int j=1;j<cols;j++)
        {
            if(matrix[0][j]==0)
            {
                for(int i=1;i<rows;i++)
                    matrix[i][j]=0;
            }
        }
        //�����һ����0���򽫸���ȫ��Ϊ0
        for(int i=1;i<rows;i++)
        {
            if(matrix[i][0]==0)
            {
                for(int j=1;j<cols;j++)
                {
                    matrix[i][j]=0;
                }
            }
        }
        if(row_flag)
            for(int j=0;j<cols;j++)
                matrix[0][j]=0;
        if(col_flag)
            for(int i=0;i<rows;i++)
                matrix[i][0]=0;
    }
};
```
## [118.�������](https://leetcode-cn.com/problems/pascals-triangle/)
```c++
class Solution
{
public:
    vector<vector<int>> generate(int numRows)
    {
        vector<vector<int>> res(numRows);
        res[0].push_back(1);
        for (int i = 1; i < numRows; i++)
        {
            res[i].push_back(1);
            for(int k=1;k<i;k++)
            {
                res[i].push_back(res[i-1][k-1]+res[i-1][k]);
            }
            res[i].push_back(1);
        }
        return res;
    }
};
```
## [44.ͨ���ƥ��](https://leetcode-cn.com/problems/wildcard-matching/)
```c++
//̰���㷨
class Solution
{
public:
    bool isMatch(string s, string p)
    {
        int si=0,pi=0,sStar=-1,pStar=-1,m=s.size(),n=p.size();
        while(si<m)
        {
            if(pi<n&&(s[si]==p[pi]||p[pi]=='?'))
            {
                ++si,++pi;
            }
            else if(pi<n&&p[pi]=='*')
            {
                sStar=si;//��¼s�ж�Ӧλ��
                pStar=pi++;//��¼p��*��λ��
            }
            else if(sStar>=0)
            {
                si=++sStar;//����ǰ���*��ƥ�䲻�ɹ���*ƥ����ַ�����+1
                pi=pStar+1;
            }
            else return false;
        }
        while(pi<n&&p[pi]=='*') ++pi;
        return pi==n;
        }
};
//˼·���ӣ�https://leetcode-cn.com/problems/wildcard-matching/solution/44-tong-pei-fu-pi-pei-shuang-zhi-zhen-by-guohaodin/

//��̬�滮
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.length(), n = p.length();

        // ״̬���壺dp[i][j] ��ʾ s ��ǰ i ���ַ��� p ��ǰ j ���ַ��Ƿ�ƥ��
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));

        // ״̬��ʼ��
        // 1. ���ַ����Ϳ��ַ�����ƥ���
        dp[0][0] = true;
        for (int i = 1; i <= n; i++) {
            // 3. ���ַ����� * ��ƥ���
            if (dp[0][i - 1] && p[i - 1] == '*') {
                dp[0][i] = true;
            }
        }

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s[i - 1] == p[j - 1] || p[j - 1] == '?') {
                    dp[i][j] = dp[i - 1][j - 1];
                } else if(p[j - 1] == '*') {
                    //��ʹ��*��ʹ��*
                    dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
                }
            }
        }

        return dp[m][n];
    }
};
//https://leetcode-cn.com/problems/wildcard-matching/solution/tong-pei-fu-pi-pei-by-leetcode-solution/
```
## [125.��֤���Ĵ�](https://leetcode-cn.com/problems/valid-palindrome/)
```c++
//˫ָ��
class Solution {
public:
    bool isPalindrome(string s) {
        int n=s.size();
        int left=0,right=n-1;
        while(left<right)
        {
            while(left<right&&!isalnum(s[left])) left++;
            while(left<right&&!isalnum(s[right])) right--;
            if(left<right)
            {
                if(tolower(s[left])!=tolower(s[right]))
                {
                    return false;
                }
                ++left,--right;
            }
        }
        return true;
    }
};
```
## [127.���ʽ���](https://leetcode-cn.com/problems/word-ladder/)
```c++
//�������
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> words(wordList.begin(), wordList.end());
        if ( words.empty() || words.find(endWord) == words.end() ) return 0;
        words.erase(beginWord);
        queue<string> que;
        que.push(beginWord);
        //depth�൱�����Ĳ���
        int depth = 1;
        while ( !que.empty() ) {
            // �ҵ�û�б����ʹ�, �����ܹ��ɵ�ǰ����ת�����ɵĵ���
            int n = que.size();
            //��һ���while������ʾ�������+1
            while ( n-- ) {
                string curWord = que.front();
                que.pop();
                // ��ǰ���ʵ�ÿ���ַ����滻��������25���ַ�, Ȼ���ڵ��ʱ��в�ѯ
                for ( int i = 0; i < curWord.size(); ++i ) {
                    char originalChar = curWord[i];
                    for ( int j = 0; j < 26; ++j ) {
                        if ( char('a' + j) == originalChar ) continue;
                        curWord[i] = 'a' + j;
                        //������ʱ��д�����δ�����ʹ�
                        if ( words.find(curWord) != words.end()) {
                            if ( curWord == endWord ) return depth + 1;
                            else {
                                que.push(curWord);
                                //����ҵ�����ֱ�����ַ�����ɾ��
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
//���ӣ�https://leetcode-cn.com/problems/word-ladder/solution/by-jjkhl-s9kq/

```

## [130.��Χ�Ƶ�����](https://leetcode-cn.com/problems/surrounded-regions/)
```c++
//�������
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
        //�Ա��ϵ�'O'���б���Լ���ͨ����
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

## [138.���ƴ����ָ�������](https://leetcode-cn.com/problems/copy-list-with-random-pointer/)
```c++
//��ϣ��
class Solution {
public:
    unordered_map<Node*,Node*> umap;
    Node* dfs(Node *head)
    {
        if(!head) return NULL;
        if(umap.count(head)) return umap[head];
        Node *node=new Node(head->val);
        umap[head]=node;//Դ�ڵ㵽�ֽڵ��ӳ��
        node->next=dfs(head->next);
        node->random=dfs(head->random);
        return node;
    }
    Node* copyRandomList(Node* head) {
        if(head==NULL) return NULL;
        return dfs(head);
    }
};
//ԭ�ظ���
class Solution {
public:
    Node* copyRandomList(Node* head) {
        for(auto cur = head; cur; cur = cur->next->next)  //����ÿ���ڵ㣬����ԭ����͸�����������һ��
        {
            auto node = new Node(cur->val);
            node->next = cur->next;
            cur->next = node;
        }

        for(auto cur = head; cur; cur = cur->next->next)   //����randomָ��
        {
            if(cur->random)
              cur->next->random = cur->random->next;
        }

        //���������������ԭԭ����
        auto dummy = new Node(-1), copy = dummy; 
        for(auto cur = head; cur; cur = cur->next)
        {
            auto copy_node = cur->next;
            // copy = copy->next = copy_node;
            copy->next=copy_node;
            copy=copy->next;
            cur->next = copy_node->next;
        }

        return dummy->next;
    }
};
```
## [821.�ַ�����̾���](https://leetcode-cn.com/problems/shortest-distance-to-a-character/)
```c++
class Solution {
public:
    int maxArea(vector<int>& height) {
        int len=height.size();
        int maxV=0;
        int left=0,right=len-1;
        while(left<right)
        {
            maxV=max(min(height[left],height[right])*(right-left),maxV);
            if(height[left]<height[right])
            {
                left++;
            }
            else right--;
        }
        return maxV;
    }
};
```
## [166.������С��](https://leetcode-cn.com/problems/fraction-to-recurring-decimal/)
```c++
class Solution
{
    using ll=long long;
public:
    string fractionToDecimal(int numerator, int denominator)
    {
        ll n = abs(numerator), d = abs(denominator);
        string res;
        //�����ж�
        if ((numerator > 0 && denominator < 0) || (numerator < 0 && denominator > 0))
            res += '-';

        ll a = n / d;
        res += to_string(a);

        //����С������
        n %= d;
        if(n==0) return res;
        res+='.';
        unordered_map<int,int> umap;
        string path;
        int index=0;
        while(n&&!umap.count(n))
        {
            //��ʾĿǰС������λ��
            umap[n]=index++;
            n*=10;
            path.push_back('0'+n/d);
            n%=d;
        }
        //����ѭ��
        if(n!=0)
        {
            res+=path.substr(0,umap[n])+"("+path.substr(umap[n])+")";
        }
        else
        {
            res+=path;
        }
        return res;
    }
};
```
## [162.Ѱ�ҷ�ֵ](https://leetcode-cn.com/problems/find-peak-element/)
```c++
//��Ϊnums[-1]=nums[n]=-�ޣ�����ֻҪ���ŵ��������ҷ�ֵһ�����ҵ���
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int left=0,right=nums.size()-1;
        while(left<right)
        {
            int mid=left+((right-left)>>1);
            if(nums[mid]>nums[mid+1])
                right=mid;//nums[mid]����Ϊ��ֵ
            else
                left=mid+1;//nums[mid]һ����Ϊ��ֵ
        }
        return left;
    }
};
```
## [171.Excel��������](https://leetcode-cn.com/problems/excel-sheet-column-number/)
```c++
class Solution {
public:
    int titleToNumber(string columnTitle) {
        int sum=0;
        for(const char& ch:columnTitle)
        {
            sum=sum*26+(ch-'A'+1);
        }
        return sum;
    }
};
```
## [172.�׳˺����](https://leetcode-cn.com/problems/factorial-trailing-zeroes/)
```c++
//10=2*5��100=2*5*2*5��1000=2*5*2*5*2*5
//2���ִ���һ������5������ֻ��Ҫ��5���ִ�������
// ��130Ϊ�����ֵ�����
// ��һ�Σ�5��10��15������130�����ٰ���1��5����Ϊ26��
// �ڶ��Σ�25��50��75��100��125�����ٰ���2��5��������5��
// �����Σ�125�������ٰ���3��5����ʵҲֻ����3��5��
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
## [179.�����](https://leetcode-cn.com/problems/largest-number/)
```c++
//string��������
class Solution {
public:
    string largestNumber(vector<int>& nums) {
        string res="";
        int n=nums.size();
        vector<string> num_str(n);
        for(int i=0;i<n;i++)
        {
            num_str[i]=to_string(nums[i]);
        }
        //ֻ����a+b>b+a����ֹ{0,0,0,0,0}�ĳ���
        sort(num_str.begin(),num_str.end(),[](const string&a,const string&b){return a+b>b+a;});
        if(num_str[0]=="0") return "0";
        for(const auto& str:num_str) res+=str;
        return res;
    }
};
//STL��׼�⺯��
class Solution {
public:
    string largestNumber(vector<int>& nums) 
    {
        if (all_of(nums.begin(), nums.end(), [](int x) { return x == 0; })) {
            return string("0");
        }
        vector<string> strNums(nums.size());
        std::transform(nums.begin(), nums.end(), strNums.begin(), [](int x) {
            return std::to_string(x);
        });

        std::sort(strNums.begin(), strNums.end(), [](const string& x, const string& y) {
            /* xΪ����Ԫ�أ�yΪǰ��Ԫ�أ�return true��x�ƶ���ǰ�� */
            return x + y >= y + x;//�˴�Ҳ����Ϊx+y>y+x
        });

        return std::accumulate(strNums.begin(), strNums.end(), string());
    }
};


// ���ӣ�https://leetcode-cn.com/problems/largest-number/solution/c-4ms-by-harold-15/

```
## [190.�ߵ�������λ](https://leetcode-cn.com/problems/reverse-bits/)
```c++
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t res = 0;
        //32��Ϊ�˷�ֹǰ����0
        //|�����൱��λ����ļӷ�
        for (int i = 0; i < 32; ++i) {
            res = (res << 1) | (n & 1);
            n >>= 1;
        }
        return res;
    }
};
```

## [189.��ת����](https://leetcode-cn.com/problems/rotate-array/)
```c++
//��ת��
class Solution
{
public:
    void reverseNums(vector<int>& nums,int start,int end)
    {
        while(start<end)
        {
            swap(nums[start++],nums[end--]);
        }
    }
    void rotate(vector<int> &nums, int k)
    {
        int n = nums.size();
        k%=n;
        reverseNums(nums,0,n-1);
        reverseNums(nums,0,k-1);
        reverseNums(nums,k,n-1);
    }
};
//�������鷨
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n=nums.size();
        vector<int> copy(n);
        for(int i=0;i<n;i++)
        {
            copy[(i+k)%n]=nums[i];
        }
        nums=copy;
    }
};
```

## [204.��������](https://leetcode-cn.com/problems/count-primes/)
```c++
//�ο���ַ��https://leetcode-cn.com/problems/count-primes/solution/ji-shu-zhi-shu-bao-li-fa-ji-you-hua-shai-fa-ji-you/
//��������ɸ��
class Solution {
public:
    int countPrimes(int n) {
        int count=0;
        vector<bool> signs(n,true);
        for(int i=2;i<n;i++)
        {
            if(signs[i])
            {
                ++count;
                for(int j=i+i;j<n;j+=i)
                {
                    signs[j]=false;
                }
            }
        }
        return count;
    }
};
```

## [212.��������II](https://leetcode.cn/problems/word-search-ii/)
```c++
//�ֵ���
struct TrieNode {
    vector<TrieNode*> children;
    bool isWord;

    TrieNode() {
        children = vector<TrieNode*>(26, NULL);
        isWord = false;
    }
};

class Solution {
public:
    vector<int> dx = {1, -1, 0, 0};
    vector<int> dy = {0, 0, 1, -1};
    int rows = 0;
    int cols = 0;
    vector<string> ans;
    unordered_set<string> unique;

    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        // build trie tree
        TrieNode* root = new TrieNode();
        for (auto word: words) {
            TrieNode* p = root;
            for (auto c: word) {
                int index = c - 'a';
                if (p->children[index] == NULL) {
                    p->children[index] = new TrieNode();
                }
                p = p->children[index];
            }
            p->isWord = true;
        }

        rows = board.size();
        cols = board[0].size();
        string word = "";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                dfs(i, j, board, root, word);
            }
        }

        for (auto s: unique) {
            ans.push_back(s);
        }

        return ans;
    }

    void dfs(int i, int j, vector<vector<char>>& board, TrieNode* root, string& word) {
        char c = board[i][j];
        int index = c - 'a';
        //�ֵ�����û��������
        if (root->children[index] == NULL) return;
        //'0'��ʾ�ѷ��ʹ�������
        if (c == '0') return;

        board[i][j] = '0';
        word += c;
        if (root->children[index]->isWord) 
            unique.insert(word);
        for (int d = 0; d < 4; d++) {
            int y = i + dy[d];
            int x = j + dx[d];
            if (x < 0 || y < 0 || x >= cols || y >= rows) continue;
            if (board[y][x] == '0') continue;
            dfs(y, x, board, root->children[index], word);
        }
        word.pop_back();
        board[i][j] = c;
    }
};

//���ӣ�https://leetcode.cn/problems/word-search-ii/solution/wei-rao-li-lun-dfsbao-sou-triejian-zhi-b-pqwr/

```