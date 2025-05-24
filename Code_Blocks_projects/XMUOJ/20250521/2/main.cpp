/*
五军对决

描述

五军对决模式中，需要将 k 名玩家分配到 k 个固定位置，每个玩家对每个位置有不同的熟练度分数。总分最高的分配方式能让五军更具战斗力。请用分支界限的剪枝策略求出最佳分配总分。

输入

    第一行：一个正整数k（玩家数及位置数，1 ≤ k ≤ 15）。

    接下来 k 行：第 i 行包含 k 个非负整数ai1 ai2 … aik，其中aij表示第 i 名玩家放置在第 j 个位置时获得的熟练度分数（0 ≤ aij ≤ 10^3），数字间以空格分隔。

输出

唯一一行：将 k 名玩家一一分配到 k 个位置后能得到的最大总熟练度分数（整数）。

输入样例 1

5
16 10 4 18 8
2 14 8 12 6
6 15 3 1 16
16 15 13 18 9
10 15 3 9 12

输出样例 1

73

来源

xmu

温馨提示

实在搞不定的话，你可以 点此下载测试数据 (./problem_5367_test_cases.zip)
*/

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

#define K_MAX 15
#define a_MAX 1000

using namespace std;

typedef short idxT;
typedef short valT;

typedef vector<valT> valVec;

struct queNode
{
    vector<bool> Chose;
    idxT cnt;
    valT val;
};

inline bool isPosible_node(const queNode &node,unordered_map<vector<bool>,valT> &curState_max)
{
    bool flag=false;
    auto mapIt=curState_max.find(node.Chose);
    if(mapIt==curState_max.end())
        curState_max[node.Chose]=node.val,flag=true;
    else if(node.val>=(mapIt->second))
        mapIt->second=node.val,flag=true;
    return flag;
}

inline valT getMax_nItmKPos(const vector<valVec> &A,const idxT k)
{
    valT res=0;
    if(A.size()>=(size_t)k)
    {
        bool flag=true;
        for(auto &vec:A)
            if(vec.size()!=(size_t)k)
            {
                flag=false;
                break;
            }
        if(flag)
        {
            unordered_map<vector<bool>,valT> curState_max;
            queue<queNode> Que;
            Que.push({vector<bool>(A.size()),0,0});
            while(!Que.empty())
            {
                auto &node=Que.front();
                if((node.cnt)++<k)
                {
                    if(isPosible_node(node,curState_max))
                    {
                        auto &Chose=node.Chose;
                        for(auto it=Chose.begin(); it<Chose.end(); ++it)
                            if(!(*it))
                            {
                                *it=true,node.val+=A[it-Chose.begin()][node.cnt-1];
                                if(isPosible_node(node,curState_max))
                                    Que.push(node);
                                *it=false,node.val-=A[it-Chose.begin()][node.cnt-1];
                            }
                    }
                }
                else
                    res=(node.val>res)?(node.val):res;
                Que.pop();
            }
        }
    }
    return res;
}

int main()
{
    idxT k=0;
    cin>>k;
    bool flag=true;
    if((k>0)&&(k<=K_MAX))
    {
        vector<valVec> A(k,valVec(k));
        for(auto &vec:A)
            for(auto &val:vec)
            {
                cin>>val;
                if((val<0)||(val>a_MAX))
                {
                    flag=false;
                    break;
                }
            }
        if(flag)
            cout<<getMax_nItmKPos(A,k)<<endl;
    }
    else
        flag=false;
    if(!flag)
        cout<<"ERROR!"<<endl;
    return 0;
}
