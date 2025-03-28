/*
完全战斗力总和

描述

在《明日方舟》中，博士需要携带一些干员进入战场。每种干员有无限件可用，每件干员占据一定的背包空间（体积），并为团队提供一定的战斗力（价值）。背包的总容量为V，博士需要选择一些干员放入背包，使得背包中干员的总体积不超过V，同时战斗力总和最大。

输入

    第一行包含两个整数N和V，分别表示干员的种类数量和背包的容量。
    接下来N行，每行包含两个整数vi​和wi​，分别表示第i种干员占据的空间和提供的战斗力。

输出

输出一个整数，表示最大战斗力总和。

输入样例 1

4 5
1 2
2 4
3 4
4 5

输出样例 1

10


*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef short idxT;
typedef long long valT;

typedef struct ArkN_OperatorNode_
{
    valT v,w;
} ArkN_OperatorNode;

inline valT getMax_pakW_V(const vector<ArkN_OperatorNode> &A,const valT V)
{
    if((!A.empty())&&(V>=0))
    {
        vector<valT> maxW_V(V+1);
        for(auto it1=A.begin(); it1<A.end(); ++it1)
            for(auto it2=maxW_V.begin(); (it2+(it1->v))<maxW_V.end(); ++it2)
                maxW_V[(it1->v)+(it2-maxW_V.begin())]=max(maxW_V[(it1->v)+(it2-maxW_V.begin())],it1->w+(*it2));
        return maxW_V.back();
    }
    return -1;
}

int main()
{
    idxT N=0;
    valT V=0;
    cin>>N>>V;
    if((N>0)&&(V>=0))
    {
        vector<ArkN_OperatorNode> A(N);
        for(auto &a:A)
            cin>>a.v>>a.w;
        cout<<getMax_pakW_V(A,V)<<endl;
    }
    else
        cout<<"ERROR!"<<endl;
    return 0;
}
