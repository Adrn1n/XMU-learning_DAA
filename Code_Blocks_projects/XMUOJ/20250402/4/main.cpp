/*
最大物资2
描述

在《三角洲行动》的世界中，​你作为一名特战干员，需要在敌方占领的环形基地中执行秘密搜刮任务。​基地中的每个建筑物都储藏着一定的物资，但相邻建筑之间设有联动警报系统。​由于基地呈环形布局，第一个和最后一个建筑也是相邻的。​如果你在同一时间进入相邻的两座建筑，警报系统将被触发，导致任务失败。​

任务目标：
在不触发警报系统的前提下，计算你一夜之间能够获取的最大物资量。


输入

一个整数数组nums，其中nums[i]表示第i座建筑内储藏的物资量，且nums[i]为非负整数。


输出

一个整数，表示在不触发警报的情况下，能够获取的最大物资量。

示例 1：

输入：nums = [2,3,2]
输出：3
解释：你不能先偷窃 1 号房屋（金额 = 2），然后偷窃 3 号房屋（金额 = 2）, 因为他们是相邻的。
示例 2：

输入：nums = [1,2,3,1]
输出：4
解释：你可以先偷窃 1 号房屋（金额 = 1），然后偷窃 3 号房屋（金额 = 3）。
     偷窃到的最高金额 = 1 + 3 = 4 。
示例 3：

输入：nums = [1,2,3]
输出：3

输入样例 1

2 3 2
输出样例 1

3
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long valT;
typedef vector<valT> valVec;

inline valT getMax_nAdjCircSum(const valVec &A)
{
    valT Sum=0;
    auto len=A.size();
    if(len>2)
    {
        vector<valVec> Tmp(2,valVec(len));
        auto it2=Tmp[0].begin(),it3=Tmp[1].begin();
        for(auto it1=A.begin(); it1<A.end(); ++it1,++it2,++it3)
            if(it1==A.begin())
                *it2=*it1;
            else if(it1==A.begin()+1)
                *it2=max(*it1,*(it1-1)),*it3=*it1;
            else
            {
                *it2=max(*(it2-1),*(it2-2)+*it1);
                if(it1==A.begin()+2)
                    *it3=max(*it1,*(it1-1));
                else
                    *it3=max(*(it3-1),*(it3-2)+*it1);
            }
        Sum=max(Tmp[0][len-2],A.back()+Tmp[1][len-3]);
    }
    else if(!A.empty())
        Sum=*max_element(A.begin(),A.end());
    return Sum;
}

int main()
{
    valT val=0;
    valVec A;
    while(cin>>val)
        A.push_back(val);
    cout<<getMax_nAdjCircSum(A)<<endl;
    return 0;
}
