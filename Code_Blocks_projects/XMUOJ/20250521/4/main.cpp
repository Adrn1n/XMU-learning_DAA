/*
峡谷魔塔

描述

在王者峡谷中，魔塔关卡会依次释放 n 波小兵。每波小兵都有血量和给定的分值奖励。你手上的技能“屠戮”每次可以针对一整波小兵造成固定伤害 D，并清除这波小兵获得对应分值；也可以跳过不清，保留技能次数。技能次数上限为 K 次。请用分支界限策略决定对哪几波释放技能，使得在最多 K 次释放内，获得的总分值最大。

输入

    n（波数，1 ≤ n ≤ 20），

    K（最大释放次数，1 ≤ K ≤ n），

    D（技能伤害，1 ≤ D ≤ 10^5）。

    接下来 n 行，第 i 行两个正整数 hi（第 i 波小兵血量，1 ≤ hi ≤ 10^5）和 vi（对应获得分值，1 ≤ vi ≤ 10^4），以空格分隔。

输出

最大可获总分值

输入样例 1

9 5 43
4 14
21 74
10 35
12 98
31 85
35 25
15 52
34 43
13 86

输出样例 1

395

来源

xmu

温馨提示

实在搞不定的话，你可以 点此下载测试数据 (./problem_5369_test_cases.zip)
*/

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

#define N_MIN 1
#define N_MAX 20
#define K_MIN 1
#define HT_MIN 1
#define HT_MAX 100000
#define VT_MIN 1
#define VT_MAX 10000

using namespace std;

typedef short idxT;
typedef int HT;
typedef int VT;

struct nodeT
{
    HT h;
    VT v;
};

struct queNode
{
    idxT cnt;
    VT val;
    vector<bool> Chose;
};

inline bool isPosible_node(const queNode &node,unordered_map<vector<bool>,VT> &curState_max)
{
    bool flag=false;
    auto mapIt=curState_max.find(node.Chose);
    if(mapIt==curState_max.end())
        curState_max[node.Chose]=node.val,flag=true;
    else if(node.val>=(mapIt->second))
        mapIt->second=node.val,flag=true;
    return flag;
}

inline VT getMaxVal_nodeNHLEM(const vector<nodeT> &A,const idxT n,const HT m)
{
    VT res=0;
    unordered_map<vector<bool>,VT> curState_max;
    queue<queNode> Que;
    Que.push({0,0,vector<bool>(A.size())});
    while(!Que.empty())
    {
        auto &node=Que.front();
        bool flag=true;
        if((node.cnt)++<n)
        {
            if(isPosible_node(node,curState_max))
            {
                auto &Chose=node.Chose;
                for(idxT i=0; (size_t)i<(A.size()); ++i)
                    if((!Chose[i])&&(A[i].h<=m))
                    {
                        Chose[i]=true,node.val+=A[i].v,flag=false;
                        if(isPosible_node(node,curState_max))
                            Que.push(node);
                        Chose[i]=false,node.val-=A[i].v;
                    }
            }
        }
        if(flag)
            res=(node.val>res)?(node.val):res;
        Que.pop();
    }
    return res;
}

int main()
{
    idxT n=0,K=0;
    HT D=0;
    cin>>n>>K>>D;
    bool flag=true;
    if((n>=N_MIN)&&(n<=N_MAX)&&(K>=K_MIN)&&(K<=n)&&(D>=HT_MIN)&&(D<=HT_MAX))
    {
        vector<nodeT> A(n);
        for(auto &node:A)
        {
            cin>>node.h>>node.v;
            if((node.h<HT_MIN)||(node.h>HT_MAX)||(node.v<VT_MIN)||(node.v>VT_MAX))
            {
                flag=false;
                break;
            }
        }
        if(flag)
            cout<<getMaxVal_nodeNHLEM(A,K,D)<<endl,flag=false;
        else
            flag=true;
    }
    if(flag)
        cout<<"ERROR!"<<endl;
    return 0;
}
