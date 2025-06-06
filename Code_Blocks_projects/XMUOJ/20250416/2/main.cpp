/*
传送能量

描述

在王者峡谷中，英勇的召唤师初始时站在己方阵地的最前沿。每个位置都有它的传送能量，代表着召唤师能够通过传送进攻的最大距离。召唤师需要快速选择最优的传送路线，以期迅速到达敌方基地并展开作战。

给你一个非负整数数组nums，数组中的每个元素代表在该位置所拥有的最大传送步数。召唤师最初位于数组的第一个下标。

请判断召唤师是否能够借助传送能量到达最后一个下标（即敌方基地）。如果可以，则返回true；否则返回false。

输入

输入为一行由空格分隔的非负整数，表示每个位置的最大传送步数。

输出

输出为一个字符串，若能够到达最后一个下标则输出true，否则输出false。

示例 1：

输入：nums = [2,3,1,1,4]
输出：true
解释：可以先跳 1 步，从下标 0 到达下标 1, 然后再从下标 1 跳 3 步到达最后一个下标。

示例 2：

输入：nums = [3,2,1,0,4]
输出：false
解释：无论怎样，总会到达下标为 3 的位置。但该下标的最大跳跃长度是 0 ， 所以永远不可能到达最后一个下标。

输入样例 1

2 3 1 1 4

输出样例 1

true

来源

xmu

温馨提示

实在搞不定的话，你可以 点此下载测试数据 (./problem_5298_test_cases.zip)
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long idxT;

inline bool isReachable_all(const vector<idxT> &A)
{
    if(A.empty())
        return true;
    else
    {
        auto Start=A.begin(),End=Start+1,maxReach=Start;
        do
        {
            for(auto it=Start; it<End; ++it)
                if(it+(*it)<(A.end()-1))
                    maxReach=max({maxReach,it+(*it),it});
                else
                    return true;
            Start=End,End=maxReach+1;
        }
        while(Start<End);
        return false;
    }
}

int main()
{
    idxT val=0;
    vector<idxT> nums;
    bool flag=true;
    while(cin>>val)
        if(val>=0)
            nums.push_back(val);
        else
            cout<<"ERROR!"<<endl,flag=false;
    if(flag)
    {
        if(isReachable_all(nums))
            cout<<"true"<<endl;
        else
            cout<<"false"<<endl;
    }
    return 0;
}
