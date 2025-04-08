/*
羁绊效果
描述

在《金铲铲之战》中，你正在研究英雄的羁绊效果。羁绊的强度可以用杨辉三角来模拟，每一行代表不同阶段的羁绊层数，每个数字代表当前层级的英雄协同强度。

你的任务是：给定一个非负整数rowIndex（表示羁绊的层数，从0开始），请你计算并返回杨辉三角的第rowIndex行，以帮助你制定最佳的阵容搭配策略！

杨辉三角规则
第i行的元素个数为i + 1。
每一行的第一个和最后一个数都是1。
其他位置的数等于上一行的左右相邻两个数之和。
0:     [1]

1:    [1, 1]

2:   [1, 2, 1]

3:  [1, 3, 3, 1]


输入

一个整数rowIndex，表示要获取的羁绊层数（0 ≤ rowIndex ≤ 33）。


输出

该行的列表形式，表示羁绊强度数值。


输入样例 1

3
输出样例 1

1 3 3 1
输入样例 2

0
输出样例 2

1
*/

#include <iostream>
#include <vector>

using namespace std;

typedef short idxT;
typedef long long valT;
typedef vector<valT> valVec;

inline idxT build_PascalTriangle(valVec &A)
{
    idxT idx=0;
    if(!A.empty())
    {
        valVec B(A.size());
        vector<valVec *> Tmp(2);
        if(A.size()%2)
            Tmp[0]=&A,Tmp[1]=&B;
        else
            Tmp[0]=&B,Tmp[1]=&A;
        for(; (size_t)idx<A.size(); ++idx)
            for(auto i=0; i<=idx; ++i)
                if(i)
                    if(i==idx)
                        (*Tmp[idx%2])[idx]=1;
                    else
                        (*Tmp[idx%2])[i]=(*Tmp[(idx+1)%2])[i-1]+(*Tmp[(idx+1)%2])[i];
                else
                    (*Tmp[idx%2])[0]=1;
    }
    return idx;
}

int main()
{
    idxT rowIndex=0;
    cin>>rowIndex;
    if(rowIndex>=0)
    {
        valVec A(rowIndex+1);
        build_PascalTriangle(A);
        for(auto &a:A)
            cout<<a<<' ';
        cout<<endl;
    }
    else
        cout<<"ERROR!"<<endl;
    return 0;
}
