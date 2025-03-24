/*
智能机器人

描述

在一个智能机器人训练场中，一个自学习机器人需要完成能量优化任务。训练场被划分为m行n列的网格，每个格子都装有一个能量充电站，含有特定数值的能量单位。

机器人从左上角的起点出发，由于关节设计的限制，它每次只能向右移动或向下移动。它需要通过最优路径到达右下角的终点站。每当机器人经过一个格子，就会自动收集该格子充电站中的能量。

为了达到最佳的训练效果，需要计算出机器人能够积累的最大能量值。

输入

第一行输入两个整数m和n，用空格分隔，分别表示训练场的行数和列数

接下来是一个m*n的矩阵，表示每个格子中充电站的能量值，每行的数字用空格分隔，行与行之间用换行分隔

输出

机器人能够积累的最大能量值

输入样例 1

3 3
1 3 1
1 5 1
4 2 1

输出样例 1

12


*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef int idxT;
typedef long long valT;
typedef vector<valT> val_vec;
typedef pair<idxT,idxT> PII;

valT getMax_matFixedPath(vector<val_vec> A)
{
    valT res=0;
    if(!A.empty())
    {
        idxT n=(idxT)(A.size()),m=(idxT)(A[0].size());
        for(const auto &a:A)
            if(a.size()!=(size_t)m)
                return res;
        queue<PII> que_idx;
        do
        {
            PII idx= {m-1,n-1};
            if(!que_idx.empty())
            {
                idx=que_idx.front(),que_idx.pop();
                valT *p=&A[idx.first][idx.second];
                if(idx.first<m-1)
                    if(idx.second<n-1)
                        *p+=max(A[idx.first+1][idx.second],A[idx.first][idx.second+1]);
                    else
                        *p+=A[idx.first+1][idx.second];
                else
                    *p+=A[idx.first][idx.second+1];
            }
            if(idx.first>0)
                que_idx.emplace(idx.first-1,idx.second);
            if((idx.first==m-1)&&(idx.second>0))
                que_idx.emplace(idx.first,idx.second-1);
        }
        while(!que_idx.empty());
        res=A[0][0];
    }
    return res;
}

int main()
{
    idxT m=0,n=0;
    cin>>m>>n;
    if((m>0)&&(n>0))
    {
        vector<val_vec> A(m,val_vec(n));
        for(auto &a:A)
            for(auto &b:a)
                cin>>b;
        cout<<getMax_matFixedPath(A)<<endl;
    }
    else
        cout<<"ERROR"<<endl;
    return 0;
}
