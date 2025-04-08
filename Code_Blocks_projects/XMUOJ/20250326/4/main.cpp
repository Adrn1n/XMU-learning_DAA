/*
最大利润
描述

在《无限暖暖》的世界中，暖暖每天都会关注最新的时尚潮流，并且发现商店里某款时装的价格每天都会波动。给定一个数组prices，其中prices[i]表示第i天该款时装的价格。暖暖决定：她只能在某一天买入这款时装，并且在未来的某一天（买入当天除外）卖出。

你的任务是设计一个算法，帮助暖暖计算出从这次交易中她可以获得的最大利润。如果无论如何交易都无法获得利润（例如时装价格一直下跌），则返回0。


输入

一个整数数组prices，其中prices[i]表示第i天时装的价格


输出

一个整数，表示暖暖能够从这笔交易中获得的最大利润。如果没有任何利润可图，返回0。

示例 1：

输入：[7,1,5,3,6,4]
输出：5
解释：在第 2 天的时候买入，在第 5 天的时候卖出，最大利润 = 6-1 = 5 。
     注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格；同时，你不能在买入前卖出股票。
示例 2：

输入：prices = [7,6,4,3,1]
输出：0
解释：在这种情况下, 没有交易完成, 所以最大利润为 0。

输入样例 1

7 1 5 3 6 4
输出样例 1

5
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long valT;

inline valT getMax_delta(const vector<valT> &A)
{
    valT maxDelta=0,minVal=0;
    if(A.size()>1)
    {
        maxDelta=A[1]-A[0],minVal=A.front();
        for(auto it=A.begin()+2; it<A.end(); ++it)
            minVal=min(minVal,*(it-1)),maxDelta=max(maxDelta,*it-minVal);
    }
    return maxDelta;
}

int main()
{
    valT val=0;
    vector<valT> A;
    while(cin>>val)
        A.push_back(val);
    cout<<max(getMax_delta(A),0ll)<<endl;
    return 0;
}
