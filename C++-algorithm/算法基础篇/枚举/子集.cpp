//题目网址https://leetcode.cn/problems/TVdhkn/description/

#include<iostream>
#include<vector>

using namespace std;


class Solution {
public:
//采用二进制枚举
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> vv;
        int n=nums.size();
        for(int i=0;i<(1<<n);i++)
        {
            vector<int> v;
            for(int j=0;j<n;j++)
            {
                //循环遍历i逐位对比是否是1
                if((1<<j)&i) v.push_back(nums[j]);
            }
            vv.push_back(v);
        }
        return vv;
    }
};


void test()
{
	vector<int> nums={1,2,3,4};
	Solution s;
	vector<vector<int>> vv=s.subsets(nums);

	for(int i=0;i<vv.size();i++)
	{
		cout<<"[";
		for(int j=0;j<vv[i].size();j++)
		{
			cout<<vv[i][j]<<" ";
		}
		cout<<"]";
		cout<<endl;
	}

}

int main()
{
	test();
	return 0;
}