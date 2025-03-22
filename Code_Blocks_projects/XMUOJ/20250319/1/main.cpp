/*
最大数值和

描述

1.png (./cee578ccf5.png)

在《明日方舟》中，干员们组成了一个数字三角形。每个干员都有一个特定的数值（例如攻击力）。你需要从三角形的顶部出发，选择一条路径到底部。每一步只能从一个干员移动到正下方或右下方的干员。你的目标是找到一条路径，使得路径上干员的数值之和最大。

输入

输入的是一行是一个整数N，给出三角形的行数。下面的N行给出数字三角形。数字三角形上的数的范围都在0和100之间。

输出

输出最大的和。

输入样例 1

5
7
3 8
8 1 0
2 7 4 4
4 5 2 6 5

输出样例 1

30


*/

#include <iostream>
#include <vector>
#include <algorithm>

#define val_MAX 100

using namespace std;

typedef long long idxT;
typedef long long valT;
typedef vector<valT> vecValT;

valT getMax_pathVal(vector<vecValT> A)
{
    valT maxVal=0;
    if(!A.empty())
    {
        for(auto it=A.begin(); it<A.end(); ++it)
            if((*it).size()!=(size_t)(it-A.begin()+1))
                return maxVal;
        if(A.size()>1)
            for(auto it1=A.rbegin()+1; it1<A.rend(); ++it1)
                for(auto it2=(*it1).rbegin(),it=it2; (it2<(*it1).rend())&&(it=(*(it1-1)).rbegin()+(it2-(*it1).rbegin()),true); ++it2)
                    *it2+=max(*it,*(it+1));
        maxVal=(A.front()).front();
    }
    return maxVal;
}

int main()
{
    idxT N=0;
    cin>>N;
    bool flag=true;
    if((N>0)&&(!(flag=false)))
    {
        vector<vecValT> A(N);
        for(auto it=A.begin(); it<A.end(); ++it)
        {
            for(idxT i=0; i<=(it-A.begin()); ++i)
            {
                valT a=0;
                cin>>a;
                if((a<0)||(a>val_MAX))
                {
                    flag=true;
                    break;
                }
                else
                    (*it).push_back(a);
            }
            if(flag)
                break;
        }
        cout<<getMax_pathVal(A)<<endl;
    }
    if(flag)
        cout<<"ERROR!"<<endl;
    return 0;
}
