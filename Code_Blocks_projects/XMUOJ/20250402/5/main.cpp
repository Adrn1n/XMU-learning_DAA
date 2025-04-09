/*
比特位战力值
描述

在《金铲铲之战》中，每位弈士的战斗力取决于他们所拥有的英雄数量。​给定一个整数n，表示你拥有的英雄数量上限。​对于每个从0到n的整数i，计算其二进制表示中1的个数，这代表该数量英雄的战斗力值。​请返回一个长度为n + 1的数组ans，其中ans[i]表示拥有i个英雄时的战斗力值。


输入

一个整数n


输出

​请返回一个长度为n + 1的数组ans

示例 1：

输入：n = 2
输出：[0,1,1]
解释：
0 --> 0
1 --> 1
2 --> 10
示例 2：

输入：n = 5
输出：[0,1,1,2,1,2]
解释：
0 --> 0
1 --> 1
2 --> 10
3 --> 11
4 --> 100
5 --> 101



输入样例 1

2
输出样例 1

0 1 1
*/

#include <iostream>
#include <vector>

using namespace std;

typedef long long idxT;
typedef long long cntT;

inline vector<cntT> getCnt_bin1s_0tn(const idxT n)
{
    vector<cntT> A;
    if(n>=0)
    {
        A.push_back(0);
        idxT pow2=1,pow=0;
        for(idxT i=1; i<=n; ++i)
            if(i==pow2)
                A.push_back(1),pow2<<=1,++pow;
            else
                A.push_back(pow-A[pow2-1-i]);
    }
    return A;
}

int main()
{
    idxT n=0;
    cin>>n;
    if(n>=0)
    {
        auto A=getCnt_bin1s_0tn(n);
        for(auto a:A)
            cout<<a<<' ';
        cout<<endl;
    }
    else
        cout<<"ERROR!"<<endl;
    return 0;
}
