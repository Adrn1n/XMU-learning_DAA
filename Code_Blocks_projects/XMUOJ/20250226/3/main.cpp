/*
项目管理计划

描述

一位项目经理正在规划一个重要的系统升级任务。这次升级需要完成N个关键模块的代码重构，每个模块需要重构的代码行数分别为C1、C2……CN行。每重构一行代码都需要消耗相应的工作时间点数。

根据公司的工作制度，每个工作日团队能获得W个工作时间点数。这些工作时间点数必须在当天使用完，不能累积到第二天（未使用的时间点数会在工作日结束时清零）。

同时，为了保证代码的连贯性和质量，每个模块的重构工作必须在同一个工作日内完成（例如，如果某个模块需要80个时间点数来完成重构，而当天只剩50个时间点数，那么这个模块在当天就无法开始重构）。

作为项目管理专家，你需要帮助项目经理制定最优的工作计划，计算出完成所有模块重构所需的最少工作日数。

数据范围：对于100%的数据，1<=N<=18，1<=Ci<=W<=10^8

输入

第一行包含两个用空格隔开的整数，N和W。

接下来N行，每行一个整数，其中第i+1行的整数表示第i个模块需要重构的代码行数Ci。

输出

所有模块重构所需的最少工作日数

输入样例 1

5 1996
1
2
1994
12
29

输出样例 1

2


*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef short idxT;
typedef int valT;

idxT getMax_groupSumLe(vector<valT> A,const valT s_max)
{
    idxT num=0;
    if(!A.empty())
    {
        bool flag=true;
        for(const auto &a:A)
            if(a>s_max)
            {
                flag=false;
                break;
            }
        if(flag)
        {
            sort(A.begin(),A.end(),greater<valT>());
            vector<vector<valT>> Group;
            for(const auto &a:A)
                if(Group.empty())
                    Group.push_back({a,a});
                else
                {
                    auto it=Group.begin();
                    while((it!=Group.end())&&(((*it).front()+a)>s_max))
                        ++it;
                    if(it==Group.end())
                        Group.push_back({a,a});
                    else
                        (*it).front()+=a,(*it).push_back(a);
                }
            num=(idxT)(Group.size());
        }
    }
    return num;
}

int main()
{
    idxT N=0;
    valT W=0;
    cin>>N>>W;
    if(N>0)
    {
        vector<valT> A(N);
        for(auto &a:A)
            cin>>a;
        cout<<getMax_groupSumLe(A,W)<<endl;
    }
    else
        cout<<"ERROR"<<endl;
    return 0;
}
