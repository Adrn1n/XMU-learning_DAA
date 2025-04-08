/*
连击能量
描述

在《王者荣耀》的世界里，每位英雄在战斗中会获得连击能量，能量的多少取决于连续的攻击伤害。

已知nums数组表示一名英雄在连续攻击中的伤害值（可能为正、负或零），你需要找出英雄造成的最大连击伤害（即乘积最大的连续子数组），并返回这个最大值。

规则：

连续攻击不能被中断（即子数组必须是连续的）。

伤害值可以是正数（有效伤害）、负数（反噬伤害）、零（攻击被打断）。

计算英雄在某段连击中的最大伤害乘积。


输入

一个整数数组


输出

一个整数

示例 1:

输入: nums = [2,3,-2,4]
输出: 6
解释: 子数组 [2,3] 有最大乘积 6。
示例 2:

输入: nums = [-2,0,-1]
输出: 0
解释: 结果不能为 2, 因为 [-2,-1] 不是子数组。

输入样例 1

2 3 -2 4
输出样例 1

6
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long valT;
typedef vector<valT> valVec;

inline valT getMax_cntusMultiply(const valVec &A)
{
    valT res=0;
    if(!A.empty())
    {
        vector<valVec> Tmp(2,valVec(A.size()));
        for(auto it=A.begin(); it<A.end(); ++it)
            if(it==A.begin())
                if(*it>0)
                    Tmp[0][0]=res=*it;
                else
                    Tmp[1][0]=res=*it;
            else
            {
                auto idx=it-A.begin();
                auto val0=Tmp[0][idx-1],val1=Tmp[1][idx-1];
                if(*it>0)
                {
                    if(!val0)
                        val0=1;
                }
                else
                {
                    swap(val0,val1);
                    if(!val1)
                        val1=1;
                }
                Tmp[0][idx]=*it*val0,Tmp[1][idx]=*it*val1,res=max(res,Tmp[0][idx]);
            }
    }
    return res;
}

int main()
{
    valT val=0;
    valVec A;
    while(cin>>val)
        A.push_back(val);
    cout<<getMax_cntusMultiply(A)<<endl;
    return 0;
}
