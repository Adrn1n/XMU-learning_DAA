/*
找重复

描述

在《王者荣耀》的战场上，英雄的合理选择对于取得胜利至关重要。​现有一个长度为n+1的英雄编号数组hero_ids，其中每个编号都在1到n的范围内，且n ≥ 1。

​这意味着至少有一个英雄被重复选择。​请你在不修改数组的前提下，找出任意一个被重复选择的英雄编号。

输入

输入一个数组

输出

输出重复数字

输入样例 1

2 3 5 4 3

输出样例 1

3


*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long idxT;
typedef long long valT;

valT getDup_val(vector<valT> A)
{
    if(!A.empty())
    {
        sort(A.begin(),A.end());
        for(auto it=A.begin(); it<(A.end()-1); ++it)
            if(*it==*(it+1))
                return *it;
    }
    return 0;
}

int main()
{
    valT a=0;
    vector<valT> A;
    while(cin>>a)
        A.push_back(a);
    cout<<getDup_val(A)<<endl;
    return 0;
}
