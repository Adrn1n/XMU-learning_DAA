/*
峡谷夺宝

描述

峡谷中有 n 个宝箱，各宝箱之间路径可达，路径耗时 tij。你从起点 S 出发，需恰好访问所有宝箱并回到 S，且总耗时最短。使用分支界限算法求最短哈密顿回路的总耗时。

输入

    第一行：一个正整数n（宝箱数，也即图中顶点数，2 ≤ n ≤ 12）。

    接下来 n 行：第 u 行包含 n 个非负整数t[u][1] t[u][2] … t[u][n]，其中t[u][v]表示从顶点 u 到 v 的耗时（0 ≤ t[u][v] ≤ 10^4）；若 u==v，则 t[u][v]=0，其他均可能不对称。

    最后一行：一个整数S（起点编号，1 ≤ S ≤ n）。

输出

唯一一行：从 S 出发，恰好访问所有宝箱一次并返回 S 的最短总耗时（整数）。若不存在可行回路，则输出-1。

输入样例 1

6
0 16 10 8 20 18
18 0 14 8 11 11
7 10 0 8 18 12
18 2 12 0 2 18
20 5 2 11 0 19
10 9 18 6 9 0
5

输出样例 1

39

来源

xmu

温馨提示

实在搞不定的话，你可以 点此下载测试数据 (./problem_5368_test_cases.zip)
*/

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

#define N_MIN 2
#define N_MAX 12
#define T_MAX 10000

using namespace std;

typedef short idxT;
typedef int valT;

typedef vector<valT> valVec;
typedef unordered_map<vector<bool>,valT> bV2val_map;

struct queNode
{
    vector<bool> Visit;
    idxT idx,cnt;
    valT val;
};

inline bool isPosible_node(const queNode &node,vector<bV2val_map> &curState_min)
{
    bool flag=false;
    if((node.idx>=0)&&((size_t)(node.idx)<curState_min.size()))
    {
        auto mapIt=curState_min[node.idx].find(node.Visit);
        if(mapIt==curState_min[node.idx].end())
            (curState_min[node.idx])[node.Visit]=node.val,flag=true;
        else if(node.val<=(mapIt->second))
            mapIt->second=node.val,flag=true;
    }
    return flag;
}

inline valT getMin_hamiltonianCircuitDG(const vector<valVec> &adjTab,const idxT startIdx)
{
    valT res=-1;
    auto n=(idxT)(adjTab.size());
    if((startIdx>=0)&&(startIdx<n))
    {
        bool flag=true;
        for(auto &vec:adjTab)
            if(vec.size()!=(size_t)n)
            {
                flag=false;
                break;
            }
        if(flag)
        {
            vector<bV2val_map> CurStateMin(n);
            queue<queNode> Que;
            Que.push({vector<bool>(n),startIdx,0,0});
            while(!Que.empty())
            {
                auto &node=Que.front();
                if(++(node.cnt)<n)
                {
                    if(isPosible_node(node,CurStateMin))
                    {
                        auto &Vis=node.Visit;
                        for(idxT i=0; i<n; ++i)
                            if((!Vis[i])&&(i!=startIdx)&&(adjTab[node.idx][i]))
                            {
                                auto tmp=node.idx;
                                Vis[i]=true,node.idx=i,node.val+=adjTab[tmp][i];
                                if(isPosible_node(node,CurStateMin))
                                    Que.push(node);
                                Vis[i]=false,node.idx=tmp,node.val-=adjTab[tmp][i];
                            }
                    }
                }
                else
                    (node.val)+=adjTab[node.idx][startIdx],res=((node.val<res)||(res==-1))?(node.val):res;
                Que.pop();
            }
        }
    }
    return res;
}

int main()
{
    idxT n=0,s=0;
    cin>>n;
    bool flag=false;
    if((n>=N_MIN)&&(n<=N_MAX))
    {
        vector<valVec> t(n,valVec(n));
        for(auto &vec:t)
            for(auto &val:vec)
            {
                cin>>val;
                if((val<0)||(val>T_MAX))
                {
                    flag=true;
                    break;
                }
            }
        if(!flag)
        {
            cin>>s;
            if((s>0)&&(s<=n))
                cout<<getMin_hamiltonianCircuitDG(t,(idxT)(s-1))<<endl;
            else
                flag=true;
        }
    }
    if(flag)
        cout<<"ERROR!"<<endl;
    return 0;
}
