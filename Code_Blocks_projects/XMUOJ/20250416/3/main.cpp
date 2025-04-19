/*
传送能量2

描述

在王者峡谷的激战中，迅捷的召唤师需要利用传送符文，在战场上迅速发起进攻。现给定一个长度为 n 的整数数组nums，每个位置的数值代表了该位置传送符文的能量——也就是从当前位置向后传送时最多能跨越的格数。召唤师最初立于己方阵地起点nums[0]。

请你帮助召唤师计算从起点出发，最少需要多少次传送才能到达敌方基地（即数组的最后一个下标）。

输入

输入为一行由空格分隔的整数，表示每个位置传送符文的能量值。

输出

输出为一个整数，表示从起点到敌方基地（数组末尾）所需的最小传送次数。

示例 1:

输入: nums = [2,3,1,1,4]
输出: 2
解释: 跳到最后一个位置的最小跳跃数是 2。从下标为 0 跳到下标为 1 的位置，跳 1步，然后跳 3步到达数组的最后一个位置。

示例 2:

输入: nums = [2,3,0,1,4]
输出: 2

输入样例 1

2 3 1 1 4

输出样例 1

2

来源

xmu

温馨提示

实在搞不定的话，你可以 点此下载测试数据 (./problem_5299_test_cases.zip)
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long idxT;

inline idxT getMin_reachLastStep(const vector<idxT> &A)
{
    if(A.size()>1)
    {
        auto Start=A.begin(),End=Start+1,maxReach=Start;
        for(idxT i=1; Start<End; Start=End,End=maxReach+1,++i)
            for(auto it=Start; it<End; ++it)
                if(it+(*it)<(A.end()-1))
                    maxReach=max({maxReach,it+(*it),it});
                else
                    return i;
        return -1;
    }
    else
        return 0;
}

int main()
{
    idxT val=0;
    vector<idxT> nums;
    while(cin>>val)
        nums.push_back(val);
    cout<<getMin_reachLastStep(nums)<<endl;
    return 0;
}
