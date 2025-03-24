/*
跳一跳

描述

在《无畏契约》的训练场中，特工需要通过一系列的跳跃训练来提升机动性。​训练场地上有一段长度为n的跑道，特工每次可以向前跳跃 1 米、2 米或 3 米。​请编写一个程序，计算特工从起点跳到终点共有多少种不同的跳跃方案。

输入

共一行，包含一个整数n。1≤n≤15

输出

共一行，包含一个整数，表示方案数。

输入样例 1

5

输出样例 1

13


*/

#include <iostream>
#include <vector>
#include <algorithm>

#define n_MAX 15
#define baseMeth_N 3

using namespace std;

typedef short idxT;
typedef int cntT;

cntT getMeth_cnt(const idxT n,const idxT k)
{
    cntT cnt=0;
    if((n>0)&&(k>0))
    {
        vector<cntT> A;
        for(idxT i=0; i<n; ++i)
        {
            if(i<k)
                cnt=1;
            else
                cnt=0;
            auto maxStep=min(i,k);
            for(idxT j=0; j<maxStep; ++j)
                cnt+=A[i-1-j];
            A.push_back(cnt);
        }
    }
    return cnt;
}

int main()
{
    idxT n=0;
    cin>>n;
    if(n<=n_MAX)
        cout<<getMeth_cnt(n,baseMeth_N)<<endl;
    else
        cout<<"ERROR!"<<endl;
    return 0;
}
