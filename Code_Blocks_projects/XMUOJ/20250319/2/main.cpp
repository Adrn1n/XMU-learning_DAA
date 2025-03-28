/*
战斗力总和

描述

在《明日方舟》中，博士需要携带一些干员进入战场。每个干员占据一定的背包空间（体积），并为团队提供一定的战斗力（价值）。背包的总容量为V，博士需要选择一些干员放入背包，使得背包中干员的总体积不超过V，同时战斗力总和最大。
数据范围

0<N,V≤1000
0<vi,wi≤100

输入

    第一行包含两个整数N和V，分别表示干员的数量和背包的容量。
    接下来N行，每行包含两个整数vi​和wi​，分别表示第i个干员占据的空间和提供的战斗力。

输出

输出一个整数，表示最大战斗力总和。

输入样例 1

4 5
1 2
2 4
3 4
4 5

输出样例 1

8


*/

// 可用 B+ 树存储数据提升时空效率, 但是需要手动实现, 有些麻烦, 此处没有采用

#include <iostream>
#include <vector>
#include <algorithm>

#define N_MAX 1000
#define V_MAX 1000
#define v_MAX 100
#define w_MAX 100

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
        {
            vector<valT> Tmp;
            for(auto it2=maxW_V.begin(); (it2+(it1->v))<maxW_V.end(); ++it2)
                Tmp.push_back((it1->w)+(*it2));
            for(idxT i=0; (size_t)i<Tmp.size(); ++i)
                maxW_V[i+(it1->v)]=max(maxW_V[i+(it1->v)],Tmp[i]);
        }
        return maxW_V.back();
    }
    return -1;
}

int main()
{
    idxT N=0;
    valT V=0;
    cin>>N>>V;
    bool flag=true;
    if((N>0)&&(N<=N_MAX)&&(V>=0)&&(V<=V_MAX))
    {
        vector<ArkN_OperatorNode> A(N);
        for(auto &a:A)
        {
            valT v=0,w=0;
            cin>>v>>w;
            if((v>=0)&&(v<=v_MAX)&&(w>=0)&&(w<=w_MAX))
                a.v=v,a.w=w;
            else
            {
                flag=false;
                break;
            }
        }
        if(flag)
            flag=false,cout<<getMax_pakW_V(A,V)<<endl;
        else
            flag=true;
    }
    if(flag)
        cout<<"ERROR!"<<endl;
    return 0;
}
