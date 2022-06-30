# [Leetcode热题HOT 100](https://leetcode-cn.com/problem-list/2cktkvj/)
## [75.颜色分类](https://leetcode-cn.com/problems/sort-colors/)
```c++
//两次遍历
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
//自定义快排
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
            while(nums[j]>=base&&i<j) --j;//找到右边第一个小于base的数
            while(nums[i]<=base&&i<j) ++i;//找到左边第一个大于base的数
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
//双指针
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int zero = -1;            // 保证下标 0 到 zero 对应的元素都为 0 
        int two = nums.size();    // 保证下标 two 到 numsSize - 1 对应的元素都为 2
        // 由于当遍历到的元素为 2 时，只需要交换下标 two - 1 对应的元素与遍历到的元素，所以 for 语句里面不写 i++
        for (int i = 0; i < two;) {  
            // 直接将遍历到的元素 1 纳入到属于 1 的部分，i 右移继续遍历
            if (nums[i] == 1) {          
                i++;
            } else if (nums[i] == 2) {
                //  交换下标为 two 前面一个下标对应的元素与遍历到的元素 2 并将遍历到的元素 2 纳入到属于 2 的部分，two 左移
                swap(nums[i], nums[--two]);
            } else {                 
                //  交换下标为 zero 后面一个下标对应的元素与遍历到的元素 0 并将遍历到的元素 0 纳入到属于 0 的部分，zero 和 i 右移
                swap(nums[++zero], nums[i++]);
            }
        }
    }
};
//链接：https://leetcode-cn.com/problems/sort-colors/solution/75-yan-se-fen-lei-san-lu-kuai-pai-by-din-84w8/
```
## [146.LRU缓存](https://leetcode-cn.com/problems/lru-cache/)
```c++
class LRUCache {
public:
    LRUCache(int capacity):cap(capacity){}
    
    int get(int key) {
        if(map.find(key)==map.end()) return -1;
        //*map[key]表示返回map[key]迭代器所指向的值
        pair<int,int> key_value=*map[key];
        cache.erase(map[key]);
        cache.push_front(key_value);
        map[key]=cache.begin();
        return key_value.second;
    }
    
    void put(int key, int value) {
        if(map.find(key)==map.end())
        {
            //没找到key覆盖，所以删除最久未使用关键字
            if(cap==cache.size())
            {
                map.erase(cache.back().first);
                cache.pop_back();
            }
        }
        else
        {
            //找到key
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
## [152.乘积最大子数组](https://leetcode-cn.com/problems/maximum-product-subarray/)
```c++
//动态规划
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
//滚动数组
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
## [155.最小栈](https://leetcode-cn.com/problems/min-stack/)
```c++
//无辅助栈
/*
总体思路：minValue保存最小值，st保存当前数值与上一个最小值之间差值，如果差值<0，表明当前数值最小，更新minValue；如果差值>0，minValue不变。
*/
class MinStack {
    //st表示当前值与上一值之间的差值，小于0表示当前值更小，大于0表示当前值更大
    stack<long long> st;
    long long minValue;
public:
    MinStack() {
        minValue=-1;
    }
    
    void push(int val) {
        if(st.empty())
        {
            //以0作为基准，此时minValue即为push后的最小值
            st.push(0);
            minValue=val;
        }
        else
        {
            long long dif=val-minValue;
            st.push(dif);
            //dif<0表示当前值更小，否则保持不变
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
//辅助栈
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
## [169.多数元素](https://leetcode-cn.com/problems/majority-element/)
```c++
//摩尔投票法
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
## [200.岛屿数量](https://leetcode-cn.com/problems/number-of-islands/)
```c++
//深度优先
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
## [207.课程表](https://leetcode-cn.com/problems/course-schedule/)
```c++
//拓扑排序
class Solution {
public:
   bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
	vector<int> v;
	vector<int> indegree(numCourses,0);
    unordered_multimap<int,int> outdegree;
	for (int i = 0; i < prerequisites.size(); i++)
	{
		indegree[prerequisites[i][0]]++;
        //存的是outdegree[出边]=入边总和
		outdegree.emplace(prerequisites[i][1],prerequisites[i][0]);
	}
	//将入度为0的顶点入队
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
## [210.课程表II](https://leetcode-cn.com/problems/course-schedule-ii/)
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
        unordered_multimap<int,int> out;//存储节点对应的出边
        for(int i=0;i<prerequisites.size();i++)
        {
            ++indegree[prerequisites[i][0]];
            out.emplace(prerequisites[i][1],prerequisites[i][0]);
        }
        queue<int> que;
        //存入入度为0的节点
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
## [208.实现前缀树](https://leetcode-cn.com/problems/implement-trie-prefix-tree/)
```c++
class Trie
{
private:
	bool isWord;//是否存在以这个点为结尾的单词
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
## [215.数组中第K个最大的元素](https://leetcode-cn.com/problems/kth-largest-element-in-an-array/)
```c++
//快排
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
## [221.最大正方形](https://leetcode-cn.com/problems/maximal-square/)
```c++
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if(matrix.empty()||matrix[0].empty()) return 0;
		int rows=matrix.size();
		int cols=matrix[0].size();
		int maxLen=0;
		//dp[i][j]：以i，j为右下角的最大矩形边长
		vector<vector<int>> dp(rows,vector<int>(cols,0));
		//初始化第一列
		for(int i=0;i<rows;i++)
		{
			dp[i][0]=matrix[i][0]-'0';
			if(maxLen<dp[i][0]) maxLen=dp[i][0];
		}
		//初始化第一行
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
				int len1=dp[i-1][j];//上方矩形
				int len2=dp[i][j-1];//左方矩形
				int len3=dp[i-1][j-1];//左上矩形
				dp[i][j]=min(min(len1,len2),len3)+1;
				maxLen=max(dp[i][j],maxLen);
			}
		}
		return maxLen*maxLen;
    }
};
//题解链接：https://leetcode-cn.com/problems/maximal-square/solution/dong-tai-gui-hua-c-by-zhengjingwei/
```
## [238.除自身以外的数组的乘积](https://leetcode-cn.com/problems/product-of-array-except-self/)
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
//空间优化
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int len=nums.size();
        vector<int> res(len);
        //res[i]表示左侧所有元素的乘积
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
## [240.搜索二维矩阵II](https://leetcode-cn.com/problems/search-a-2d-matrix-ii/)
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
## [338.比特位计数](https://leetcode-cn.com/problems/counting-bits/)
```c++
//低位有效法
class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> dp(n+1,0);
        for(int i=1;i<=n;i++)
        {
            //dp[i]为i/2位置的1个数+余数
            //余数是指奇数需要+1，偶数不需要+1
            dp[i]=dp[i>>1]+(i&1);
        }
        return dp;
    }
};
//高位有效法
class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> dp(n+1,0);
        int highBits=0;
        for(int i=1;i<=n;i++)
        {
            //当i&(i-1)=0，此时为2的正数次幂
            if((i&(i-1))==0)
                highBits=i;
            dp[i]=dp[i-highBits]+1;
        }
        return dp;
    }
};
//Brian Kernighan 算法
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
## [394.字符串解码](https://leetcode-cn.com/problems/decode-string/)
```c++
//辅助栈
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
//回溯法
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
## [399.除法求值](https://leetcode-cn.com/problems/evaluate-division/)
```c++
//回溯算法
class Solution {
public:
    unordered_map<string, string> father; // father[x] 记录节点 x 的祖先节点，祖先顺序指从大到小的排序
    unordered_map<string, double> distance; // distance[x] 记录节点 x 到祖先节点的距离（即 x / root）
    string find(string x) {
        if(father[x] != x) {
            string t = find(father[x]);
            distance[x] *= distance[father[x]];
            father[x] = t;
        }
        return father[x];
    }
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        // 初始化所有节点
        for(int i = 0; i < equations.size(); i++) {
            string dividend = equations[i][0], divisor = equations[i][1];
            father[dividend] = dividend, father[divisor] = divisor;
            distance[dividend] = 1, distance[divisor] = 1;
        }
        // 集合合并
        for(int i = 0; i < equations.size(); i++) {
            string dividend = equations[i][0], divisor = equations[i][1];
            string t1 = find(dividend); // 找到被除数的祖先节点
            //如果节点组成环，需要打破
            string t2=find(divisor);
            if(t1==t2) continue;
            // 更新 t1 节点
            father[t1] = divisor; 
            distance[t1] = values[i] / distance[dividend];
        }
        vector<double> res;
        for(auto q : queries) {
            string dividend = q[0], divisor = q[1];
            // 如果divisor或dividend处于同一集合会自动算出 distance[divisor]和distance[dividend]
            //如果divisor或dividend不存在，或者divisor和dividend的祖先节点不一致(说明二者之间无任何联系)
            //因为集合合并后不一定能准确反应各节点之间关系，但是经过溯源就能准确表达出来
            if(!father.count(dividend) || !father.count(divisor)||find(dividend)!=find(divisor)) res.push_back(-1.0);
            else {
                res.push_back(distance[dividend] / distance[divisor]);
            }
        }
        return res;
    }
};
//floyd算法
class Solution
{
public:
    //graph[i][j]表示：i/j的值
    vector<vector<double>> graph;
    unordered_map<string,int> h;
    int n=0;
    void floyd()
    {
        //对每个节点进行循环
        for(int k=0;k<n;k++)
        {
            for(int i=0;i<n;i++)
            {
                for(int j=0;j<n;j++)
                {
                    //只有当graph[i][k],graph[k][j]能走的时候才能进行更新g[i][j]
                    //下式表示i/j=(i/k)*(k/j)
                    if(graph[i][k]>=0&&graph[k][j]>=0)
                        graph[i][j]=graph[i][k]*graph[k][j];
                }
            }
        }
    }
    vector<double> calcEquation(vector<vector<string>> &equations, vector<double> &values, vector<vector<string>> &queries)
    {
        //将字符串映射到数组下标
        for(int i=0;i<equations.size();i++)
        {
            string a=equations[i][0],b=equations[i][1];
            if(!h.count(a)) h[a]=n++;
            if(!h.count(b)) h[b]=n++;
        }
        //表示不能到达
        graph=vector<vector<double>>(n,vector<double>(n,-1));
        //对角处初始化为1
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
## [990.等式方程的可满足性](https://leetcode-cn.com/problems/satisfiability-of-equality-equations/)
```c++
class Solution
{
public:
    bool equationsPossible(vector<string> &equations)
    {
        int len = equations.size();
        //只有一个等式的时候不会建图
        if (1 == len)
        {
            if (equations[0][0] == equations[0][3] && equations[0][1] == '=')
                return true;
            else if (equations[0][0] != equations[0][3] && equations[0][1] == '!')
                return true;
            else return false;
        }
        int n=0;
        unordered_map<char,int> umap;//记录字符编号
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
## [448.找到所有数组中消失的数字](https://leetcode-cn.com/problems/find-all-numbers-disappeared-in-an-array/)
```c++
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        vector<int> res;
        if(nums.empty()) return nums;
        int len=nums.size();
        for(int i=0;i<len;i++)
        {
            //index为应该出现的位置
            //nums[index]表示该位置出现了，+n方便后续判断>len表示该位置出现过
            //%len是为了防止当前位置已经+n
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
## [581.最短无序连续子数组](https://leetcode-cn.com/problems/shortest-unsorted-continuous-subarray/)
```c++
class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int len = nums.size();
        int min = nums[len-1];
        int max = nums[0];
        int begin = 0, end = -1;
        //遍历
        for(int i = 0; i < len; i++){
            //从左到右应该是升序，找到不是升序的最后位置
            if(nums[i] < max){
                end = i;
            }else{
                max = nums[i];
            }
            //从右到左应该是降序，找到不是降序的最后一个位置
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
## [621.任务调度器](https://leetcode-cn.com/problems/task-scheduler/)
```c++
//思路链接：https://leetcode-cn.com/problems/task-scheduler/solution/tong-zi-by-popopop/
//思路介绍：以最大数量的桶数作为基础，最后一个桶如果没有相同数量的其它桶，则时间t一定为1(不存在等待时间)；
//最大等待时间一种是都不需要等待时间，总计时间tasks.size()，另外一种是需要等待时间(最大桶数-1)*(n+1)+最后剩余的时间t，其中(n+1)表示加上自身后的一行时间
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
        //桶数量，最后剩余的数量
        int nums = 0, remain = 0;
        for (auto pair : umap)
        {
            //找到最大桶数
            if (nums < pair.second)
            {
                nums = pair.second;
                //最后一个桶一定是1，如果有相同的最大数量，再++
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
## [560.和为K的子数组](https://leetcode-cn.com/problems/subarray-sum-equals-k/)
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
# [LeetCode 精选 TOP 面试题](https://leetcode-cn.com/problem-list/2ckc81c/)
## [1.两数之和](https://leetcode-cn.com/problems/two-sum/)
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
## [2.两数相加](https://leetcode-cn.com/problems/add-two-numbers/)
```c++
//新链表
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
## [3.无重复字符的最长子串](https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/)
```c++
//滑动窗口
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
//哈希表
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
## [4.寻找两个正序数组的中位数](https://leetcode-cn.com/problems/median-of-two-sorted-arrays/)
```c++
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m=nums1.size(),n=nums2.size();
        int i=0,j=0;
        //奇数只会有left返回，偶数则会返回left和right的一半
        int left=0,right=0;
        int xSize=(m+n)>>1;
        for(int x=0;x<=xSize;x++)
        {
            left=right;
            if(i<m&&j>=n)//表示数组2遍历完成
            {
                right=nums1[i++];
            }
            else if(i>=m&&j<n)//表示数组1遍历完成
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
## [5.最长回文子串](https://leetcode-cn.com/problems/longest-palindromic-substring/)
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
## [7.整数反转](https://leetcode-cn.com/problems/reverse-integer/)
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
## [8.字符串转换整数(stoi)](https://leetcode-cn.com/problems/string-to-integer-atoi/)
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
## [11.盛最多水的容器](https://leetcode-cn.com/problems/container-with-most-water/)
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
## [12.整数转罗马数字](https://leetcode-cn.com/problems/integer-to-roman/)
```c++
//13是因为减法规则只规定了6种情况，加上原本的7种情况
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
## [13.罗马数字转整数](https://leetcode-cn.com/problems/roman-to-integer/)
```c++
//逆序法
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
//顺序法
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
## [14.最长公共前缀](https://leetcode-cn.com/problems/longest-common-prefix/)
```c++
//依次比较
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
//排序
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
## [15.三数之和](https://leetcode-cn.com/problems/3sum/)
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
## [17.电话号码的字母组合](https://leetcode-cn.com/problems/letter-combinations-of-a-phone-number/)
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
## [19.删除链表的倒数第N个节点](https://leetcode-cn.com/problems/remove-nth-node-from-end-of-list/)
```c++
//双指针
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        //fast先走n步
        if(!head||!head->next) return NULL;
        ListNode *fast=head,*slow=head;
        while(n--)
        {
           fast=fast->next;
        }
        if(!fast) return head->next;//如果fast为空，表示删除第一个元素
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
//递归
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
## [20.有效的括号](https://leetcode-cn.com/problems/valid-parentheses/)
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
## [22.括号生成](https://leetcode-cn.com/problems/generate-parentheses/)
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
## [29.两数相除](https://leetcode-cn.com/problems/divide-two-integers/)
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
            long d = n, c = 1; //除数n的倍数d，计数c（表示c个倍数d）
            while (m-d>= d)
            {
                d <<= 1;
                c <<= 1;
            }
            res += c;//表示有c*d个数，所以商+c
            m -= d;
        }
        return sign ? res : -res;
    }
};
```
## [36.有效的数独](https://leetcode-cn.com/problems/valid-sudoku/)
```c++
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        int row[9][10] = {0};// 哈希表存储每一行的每个数是否出现过，默认初始情况下，每一行每一个数都没有出现过
        // 整个board有9行，第二维的维数10是为了让下标有9，和数独中的数字9对应。
        int col[9][10] = {0};// 存储每一列的每个数是否出现过，默认初始情况下，每一列的每一个数都没有出现过
        int box[9][10] = {0};// 存储每一个box的每个数是否出现过，默认初始情况下，在每个box中，每个数都没有出现过。整个board有9个box。
        for(int i=0; i<9; i++){
            for(int j = 0; j<9; j++){
                // 遍历到第i行第j列的那个数,我们要判断这个数在其所在的行有没有出现过，
                // 同时判断这个数在其所在的列有没有出现过
                // 同时判断这个数在其所在的box中有没有出现过
                if(board[i][j] == '.') continue;
                int curNumber = board[i][j]-'0';
                if(row[i][curNumber]) return false; 
                if(col[j][curNumber]) return false;
                if(box[j/3 + (i/3)*3][curNumber]) return false;

                row[i][curNumber] = 1;// 之前都没出现过，现在出现了，就给它置为1，下次再遇见就能够直接返回false了。
                col[j][curNumber] = 1;
                box[j/3 + (i/3)*3][curNumber] = 1;
            }
        }
        return true;
    }
};
//https://leetcode-cn.com/problems/valid-sudoku/solution/36-jiu-an-zhao-cong-zuo-wang-you-cong-shang-wang-x/
```
## [88.合并两个有序数组](https://leetcode-cn.com/problems/merge-sorted-array/)
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
## [91.解码方法](https://leetcode-cn.com/problems/decode-ways/)
```c++
//类似于跳台阶的动态规划
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
## [38.外观数列](https://leetcode-cn.com/problems/count-and-say/)
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
## [41.缺失的第一个正数](https://leetcode-cn.com/problems/first-missing-positive/)
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
## [66.加一](https://leetcode-cn.com/problems/plus-one/)
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
## [73.矩阵置零](https://leetcode-cn.com/problems/set-matrix-zeroes/)
```c++
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int rows=matrix.size();
        int cols=matrix[0].size();
        bool row_flag=false;//true表示第一行有0
        bool col_flag=false;//true表示第一列有0
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
        //如果第一行有0，则将该列全变为0
        for(int j=1;j<cols;j++)
        {
            if(matrix[0][j]==0)
            {
                for(int i=1;i<rows;i++)
                    matrix[i][j]=0;
            }
        }
        //如果第一列有0，则将该行全变为0
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
## [118.杨辉三角](https://leetcode-cn.com/problems/pascals-triangle/)
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
## [44.通配符匹配](https://leetcode-cn.com/problems/wildcard-matching/)
```c++
//贪心算法
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
                sStar=si;//记录s中对应位置
                pStar=pi++;//记录p中*的位置
            }
            else if(sStar>=0)
            {
                si=++sStar;//表明前面对*的匹配不成功，*匹配的字符数量+1
                pi=pStar+1;
            }
            else return false;
        }
        while(pi<n&&p[pi]=='*') ++pi;
        return pi==n;
        }
};
//思路链接：https://leetcode-cn.com/problems/wildcard-matching/solution/44-tong-pei-fu-pi-pei-shuang-zhi-zhen-by-guohaodin/

//动态规划
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.length(), n = p.length();

        // 状态定义：dp[i][j] 表示 s 的前 i 个字符和 p 的前 j 个字符是否匹配
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));

        // 状态初始化
        // 1. 空字符串和空字符串是匹配的
        dp[0][0] = true;
        for (int i = 1; i <= n; i++) {
            // 3. 空字符串和 * 是匹配的
            if (dp[0][i - 1] && p[i - 1] == '*') {
                dp[0][i] = true;
            }
        }

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s[i - 1] == p[j - 1] || p[j - 1] == '?') {
                    dp[i][j] = dp[i - 1][j - 1];
                } else if(p[j - 1] == '*') {
                    //不使用*和使用*
                    dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
                }
            }
        }

        return dp[m][n];
    }
};
//https://leetcode-cn.com/problems/wildcard-matching/solution/tong-pei-fu-pi-pei-by-leetcode-solution/
```
## [125.验证回文串](https://leetcode-cn.com/problems/valid-palindrome/)
```c++
//双指针
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
## [127.单词接龙](https://leetcode-cn.com/problems/word-ladder/)
```c++
//广度优先
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> words(wordList.begin(), wordList.end());
        if ( words.empty() || words.find(endWord) == words.end() ) return 0;
        words.erase(beginWord);
        queue<string> que;
        que.push(beginWord);
        //depth相当于树的层数
        int depth = 1;
        while ( !que.empty() ) {
            // 找到没有被访问过, 而且能够由当前单词转换而成的单词
            int n = que.size();
            //下一层的while结束表示树的深度+1
            while ( n-- ) {
                string curWord = que.front();
                que.pop();
                // 当前单词的每个字符都替换成其他的25个字符, 然后在单词表中查询
                for ( int i = 0; i < curWord.size(); ++i ) {
                    char originalChar = curWord[i];
                    for ( int j = 0; j < 26; ++j ) {
                        if ( char('a' + j) == originalChar ) continue;
                        curWord[i] = 'a' + j;
                        //如果单词表中存在且未被访问过
                        if ( words.find(curWord) != words.end()) {
                            if ( curWord == endWord ) return depth + 1;
                            else {
                                que.push(curWord);
                                //如果找到，则直接在字符表中删除
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
//链接：https://leetcode-cn.com/problems/word-ladder/solution/by-jjkhl-s9kq/

```

## [130.被围绕的区域](https://leetcode-cn.com/problems/surrounded-regions/)
```c++
//深度优先
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
        //对边上的'O'进行标记以及联通区域
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

## [138.复制带随机指针的链表](https://leetcode-cn.com/problems/copy-list-with-random-pointer/)
```c++
//哈希表
class Solution {
public:
    unordered_map<Node*,Node*> umap;
    Node* dfs(Node *head)
    {
        if(!head) return NULL;
        if(umap.count(head)) return umap[head];
        Node *node=new Node(head->val);
        umap[head]=node;//源节点到现节点的映射
        node->next=dfs(head->next);
        node->random=dfs(head->random);
        return node;
    }
    Node* copyRandomList(Node* head) {
        if(head==NULL) return NULL;
        return dfs(head);
    }
};
//原地复制
class Solution {
public:
    Node* copyRandomList(Node* head) {
        for(auto cur = head; cur; cur = cur->next->next)  //复制每个节点，并将原链表和复制链表连在一起。
        {
            auto node = new Node(cur->val);
            node->next = cur->next;
            cur->next = node;
        }

        for(auto cur = head; cur; cur = cur->next->next)   //复制random指针
        {
            if(cur->random)
              cur->next->random = cur->random->next;
        }

        //拆分两个链表，并复原原链表
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
## [821.字符的最短距离](https://leetcode-cn.com/problems/shortest-distance-to-a-character/)
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
## [166.分数到小数](https://leetcode-cn.com/problems/fraction-to-recurring-decimal/)
```c++
class Solution
{
    using ll=long long;
public:
    string fractionToDecimal(int numerator, int denominator)
    {
        ll n = abs(numerator), d = abs(denominator);
        string res;
        //符号判断
        if ((numerator > 0 && denominator < 0) || (numerator < 0 && denominator > 0))
            res += '-';

        ll a = n / d;
        res += to_string(a);

        //计算小数部分
        n %= d;
        if(n==0) return res;
        res+='.';
        unordered_map<int,int> umap;
        string path;
        int index=0;
        while(n&&!umap.count(n))
        {
            //表示目前小数所处位数
            umap[n]=index++;
            n*=10;
            path.push_back('0'+n/d);
            n%=d;
        }
        //出现循环
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
## [162.寻找峰值](https://leetcode-cn.com/problems/find-peak-element/)
```c++
//因为nums[-1]=nums[n]=-∞，所以只要沿着递增方向找峰值一定能找到。
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int left=0,right=nums.size()-1;
        while(left<right)
        {
            int mid=left+((right-left)>>1);
            if(nums[mid]>nums[mid+1])
                right=mid;//nums[mid]可能为峰值
            else
                left=mid+1;//nums[mid]一定不为峰值
        }
        return left;
    }
};
```
## [171.Excel表列需序](https://leetcode-cn.com/problems/excel-sheet-column-number/)
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
## [172.阶乘后的零](https://leetcode-cn.com/problems/factorial-trailing-zeroes/)
```c++
//10=2*5，100=2*5*2*5，1000=2*5*2*5*2*5
//2出现次数一定大于5，所以只需要求5出现次数即可
// 以130为例出现的数：
// 第一次：5，10，15，…，130，至少包含1个5的数为26个
// 第二次：25，50，75，100，125，至少包含2个5的数有这5个
// 第三次：125，它至少包含3个5（其实也只包含3个5）
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
## [179.最大数](https://leetcode-cn.com/problems/largest-number/)
```c++
//string数组排序法
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
        //只能是a+b>b+a，防止{0,0,0,0,0}的出现
        sort(num_str.begin(),num_str.end(),[](const string&a,const string&b){return a+b>b+a;});
        if(num_str[0]=="0") return "0";
        for(const auto& str:num_str) res+=str;
        return res;
    }
};
//STL标准库函数
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
            /* x为后面元素，y为前面元素，return true则将x移动到前面 */
            return x + y >= y + x;//此处也可以为x+y>y+x
        });

        return std::accumulate(strNums.begin(), strNums.end(), string());
    }
};


// 链接：https://leetcode-cn.com/problems/largest-number/solution/c-4ms-by-harold-15/

```
## [190.颠倒二进制位](https://leetcode-cn.com/problems/reverse-bits/)
```c++
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t res = 0;
        //32是为了防止前面有0
        //|运算相当于位运算的加法
        for (int i = 0; i < 32; ++i) {
            res = (res << 1) | (n & 1);
            n >>= 1;
        }
        return res;
    }
};
```

## [189.轮转数组](https://leetcode-cn.com/problems/rotate-array/)
```c++
//反转法
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
//额外数组法
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

## [204.计数质数](https://leetcode-cn.com/problems/count-primes/)
```c++
//参考地址：https://leetcode-cn.com/problems/count-primes/solution/ji-shu-zhi-shu-bao-li-fa-ji-you-hua-shai-fa-ji-you/
//厄拉多塞筛法
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

## [212.单词搜索II](https://leetcode.cn/problems/word-search-ii/)
```c++
//字典树
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
        //字典树中没有则跳过
        if (root->children[index] == NULL) return;
        //'0'表示已访问过，跳过
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

//链接：https://leetcode.cn/problems/word-search-ii/solution/wei-rao-li-lun-dfsbao-sou-triejian-zhi-b-pqwr/

```