/*
最大数值和

描述

在《王者荣耀》的战场上，英雄们的表现直接影响团队的胜负。​每位英雄在一场比赛中的表现可以用一个整数表示，正数代表积极的贡献，负数代表失误或负面影响。​现给定一个连续的英雄表现数组，请你找出一个连续的子数组（至少包含一个元素），使得该子数组的表现总和最大，并返回其最大值。

输入

输入一个数组

输出

输出最大和

输入样例 1

5 -1 2

输出样例 1

6


*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long valT;

valT getMax_SubArr(const vector<valT> &A)
{
    valT res=0;
    if(!A.empty())
    {
        valT max2=0;
        res=A.front();
        for(auto &a:A)
            max2=max(max2+a,a),res=max(res,max2);
    }
    return res;
}

int main()
{
    vector<valT> A;
    valT a;
    while(cin>>a)
        A.push_back(a);
    cout<<getMax_SubArr(A)<<endl;
    return 0;
}
