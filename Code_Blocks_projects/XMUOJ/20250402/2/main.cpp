/*
最大物资
描述

在《三角洲行动》的世界中，你作为一名特战干员，需要在敌方占领的街区执行秘密搜刮任务。街区中的每个建筑物都储藏着一定的物资，但相邻建筑之间设有联动警报系统。如果你在同一时间进入相邻的两座建筑，警报系统将被触发，导致任务失败。

任务目标：
在不触发警报系统的前提下，计算你一夜之间能够获取的最大物资量。


输入

一个整数数组nums，其中nums[i]表示第i座建筑内储藏的物资量，且nums[i]为非负整数。


输出

一个整数，表示在不触发警报的情况下，能够获取的最大物资量。

示例 1：

输入：[1,2,3,1]
输出：4
解释：偷窃 1 号房屋 (金额 = 1) ，然后偷窃 3 号房屋 (金额 = 3)。
     偷窃到的最高金额 = 1 + 3 = 4 。
示例 2：

输入：[2,7,9,3,1]
输出：12
解释：偷窃 1 号房屋 (金额 = 2), 偷窃 3 号房屋 (金额 = 9)，接着偷窃 5 号房屋 (金额 = 1)。
     偷窃到的最高金额 = 2 + 9 + 1 = 12 。

输入样例 1

1 2 3 1
输出样例 1

4
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long valT;

inline valT getMax_nAdjSum(const vector<valT> &A)
{
    valT Sum=0;
    if(!A.empty())
    {
        vector<valT> Tmp(A.size());
        auto it2=Tmp.begin();
        for(auto it1=A.begin(); it1<A.end(); ++it1,++it2)
            if(it1==A.begin())
                *it2=*it1;
            else if(it1==A.begin()+1)
                *it2=max(*it1,*(it1-1));
            else
                *it2=max(*(it2-1),*(it2-2)+*it1);
        Sum=Tmp.back();
    }
    return Sum;
}

int main()
{
    valT val=0;
    vector<valT> A;
    while(cin>>val)
        A.push_back(val);
    cout<<getMax_nAdjSum(A)<<endl;
    return 0;
}
