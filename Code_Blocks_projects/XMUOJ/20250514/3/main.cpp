/*
编码统计

描述

在王者峡谷中，每位英雄都拥有一个独特的身份编码。一个合法的编码是一个不超过 10n10n 的非负整数，且所有位上的数字互不相同（如 102、504 是合法的，而 101、122 是非法的）。

你的任务是：给定一个整数n，统计区间[0, 10^n)内所有“数字各位互不相同”的编码数量。

输入

一个整数n（范围：0 <= n <= 8），表示编码最大位数范围。

输出

输出满足条件的编码数量。

示例 1：

输入：n = 2
输出：91
解释：答案应为除去 11、22、33、44、55、66、77、88、99 外，在 0 ≤ x < 100 范围内的所有数字。

示例 2：

输入：n = 0
输出：1

输入样例 1

2

输出样例 1

91

来源

xmu

温馨提示

实在搞不定的话，你可以 点此下载测试数据 (./problem_5363_test_cases.zip)
*/

#include <iostream>

#define N_MAX 8

using namespace std;

typedef short idxT;
typedef int cntT;

inline cntT getCnt_nDigDiff(const idxT n)
{
    cntT cnt=0;
    if((n>=0)&&(n<=N_MAX))
    {
        cnt=1;
        if(n>0)
        {
            cnt*=9;
            for(idxT i=0; i<(n-1); ++i)
                cnt*=(9-i);
        }
    }
    return cnt;
}

int main()
{
    idxT n=0;
    cin>>n;
    if((n>=0)&&(n<=N_MAX))
    {
        cntT res=0;
        for(idxT i=0; i<=n; ++i)
            res+=getCnt_nDigDiff(i);
        cout<<res<<endl;
    }
    return 0;
}
