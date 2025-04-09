/*
装备资源
描述

在《金铲铲之战》中，​你和两位对手（Alice 和 Bob）在战场上争夺装备资源。​战场上共有3n堆装备，每堆装备的数量各不相同。​你们按照以下规则轮流挑选装备：​

每轮选择任意 3 堆装备。

Alice先挑选，取走装备数量最多的一堆。​

你接着挑选，取走装备数量第二多的一堆。​

Bob最后挑选，取走剩下的一堆。

重复上述过程，直到所有装备被分完。​你的目标是通过合理的策略，最大化你获得的装备数量。


输入

输入共两行，第一行为n，第二行输入3n个整数。


输出

输出一个数，为你可获得的最大硬币数


输入样例 1

2
4 5 2 6 4 2
输出样例 1

9
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long idxT;
typedef long long valT;

inline valT getMax_2PerSum(vector<valT> A)
{
    valT maxS=0;
    if((!A.empty())&&(!(A.size()%3)))
    {
        sort(A.begin(),A.end(),greater<valT>());
        auto endLen=A.size()/3;
        for(auto it=A.begin()+1; (size_t)(A.end()-it)>endLen; it+=2)
            maxS+=*it;
    }
    return maxS;
}

int main()
{
    idxT n=0;
    cin>>n;
    if(n>0)
    {
        vector<valT> A(3*n);
        for(auto &a:A)
            cin>>a;
        cout<<getMax_2PerSum(A)<<endl;
    }
    else
        cout<<"ERROR!"<<endl;
    return 0;
}
