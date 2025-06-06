/*
梦幻料理学院

描述

在梦幻料理学院，大厨们为迎接一场盛大的美食节，精心准备了三道特色佳肴：香煎鲈鱼、辣炒牛柳、蜜汁叉烧。为了展示这些美味，他们面前摆放了一排精致的餐盘，每个餐盘仅能容纳一道菜品。为了视觉与味觉的双重盛宴，大厨们制定了严格的摆放规则：相邻两个餐盘的菜品不能相同，且首尾两个餐盘的菜品也需迥异。现在，大厨们需要计算出所有满足这些规则的菜品摆放方式的总数。

输入

输入包含多个测试案例，每个测试案例占一行，由一个整数N构成，(0 < N <= 50)。N代表了餐盘的数量。

输出

对于每一个测试案例，请输出所有满足规则的菜品摆放方式的总数，每个案例的输出占一行。

输入样例 1

1
2

输出样例 1

3
6


*/

#include <iostream>

#define N_MAX 50

using namespace std;

typedef short idxT;
typedef unsigned long long cntT;

inline cntT getDiff_N(idxT &n)
{
    if(n>1)
    {
        cntT cnt=3<<1,nConsidHT=3<<1;
        n-=2;
        while((n--)>0)
            nConsidHT<<=1,cnt=nConsidHT-cnt;
        return cnt;
    }
    else if(n==1)
        return 3;
    else
        return 0;
}

int main()
{
    idxT N=0;
    while(cin>>N)
        if((N>0)&&(N<=N_MAX))
            cout<<getDiff_N(N)<<endl;
        else
            cout<<"ERROR!"<<endl;
    return 0;
}
