/*
战场选点

描述

在王者荣耀的世界中，战场上的每一处战略要地都至关重要。现有 N 个区域，每个区域都用闭区间 [aᵢ, bᵢ] 表示——这些区域可能隐藏着敌人的伏击或是关键的资源点。作为主帅，你需要在战场上布置你的英雄，确保每个区域都有至少一名英雄驻守（英雄驻守在区域边界也同样有效）。

你的任务：
在保证每个区域至少有一名英雄守护的前提下，使用尽可能少的英雄完成布阵。

请你计算并输出所需的最少英雄数量，为胜利制定最优战略！

输入

第一行包含整数N，表示区间数。

接下来N行，每行包含两个整数ai,bi，表示一个区间的两个端点。

输出

输出一个整数，表示所需的点的最小数量。

输入样例 1

5
1 3
2 5
4 6
7 9
8 10

输出样例 1

3


*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef int idxT;
typedef long long valT;
typedef pair<valT,valT> PVV;

idxT getN_mostCommon(vector<PVV> A)
{
    idxT res=0;
    if(!A.empty())
    {
        bool flag=true;
        for(const auto &a:A)
            if(a.first>a.second)
            {
                flag=false;
                break;
            }
        if(flag)
        {
            sort(A.begin(),A.end(),[](const PVV &a,const PVV &b)
            {
                return a.first<b.first;
            });
            for(auto it1=A.begin(); it1!=A.end(); ++res)
            {
                auto it2=it1+1;
                for(; (it2!=A.end())&&((*it2).first<=(*it1).second); ++it2);
                it1=it2;
            }
        }
    }
    return res;
}

int main()
{
    idxT N=0;
    cin>>N;
    if(N>0)
    {
        vector<PVV> A(N);
        for(auto &a:A)
        {
            cin>>a.first>>a.second;
            if(a.first>a.second)
                swap(a.first,a.second);
        }
        cout<<getN_mostCommon(A)<<endl;
    }
    else
        cout<<"ERROR"<<endl;
    return 0;
}
