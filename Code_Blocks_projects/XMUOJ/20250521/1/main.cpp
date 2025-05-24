/*
英雄选拔

描述

王者峡谷即将开战，你需要从备选的 n 名英雄中挑选若干组成出战阵容。每个英雄都有对应的金币花费和团队协同得分，阵容总花费不得超过 W（金钱预算）。请用分支界限算法计算可以获得的最大协同得分。

输入

    第一行：两个正整数n（备选英雄数量，1 ≤ n ≤ 100）和W（总金币预算，1 ≤ W ≤ 10^5），以空格分隔。

    接下来 n 行：第 i 行包含两个正整数ci（第 i 个英雄的花费，1 ≤ ci ≤ W）和si（第 i 个英雄的协同得分，1 ≤ si ≤ 10^4），以空格分隔。

输出

唯一一行：选出若干英雄，且总花费不超过W时所能获得的最大团队协同得分（整数）。

输入样例 1

5 19
7 17
3 7
3 14
3 14
5 15

输出样例 1

60

来源

xmu

温馨提示

实在搞不定的话，你可以 点此下载测试数据 (./problem_5366_test_cases.zip)
*/

#include <iostream>
#include <vector>
#include <queue>

#define N_MAX 100
#define W_MAX 100000
#define S_MAX 10000

using namespace std;

typedef short idxT;
typedef int WT;
typedef short ST;

struct Hero
{
    WT c;
    ST s;
};

struct queNode
{
    vector<Hero>::const_iterator it;
    WT C;
    ST S;
};

inline ST getMaxS_sumHerosCstLeW(const vector<Hero> &Heros,const WT W)
{
    ST res=0;
    queue<queNode> Que;
    queNode node= {Heros.begin(),0,0};
    do
        if(Que.empty())
            Que.push(node);
        else
        {
            node=Que.front(),Que.pop();
            if(node.it==Heros.end())
                res=(node.S>res)?(node.S):res;
            else
            {
                ++(node.it),Que.push(node);
                if((node.C+=((node.it-1)->c))<=W)
                    node.S+=((node.it-1)->s),Que.push(node);
            }
        }
    while(!Que.empty());
    return res;
}

int main()
{
    idxT n=0;
    WT W=0;
    cin>>n>>W;
    bool flag=true;
    if((n>0)&&(n<=N_MAX)&&(W>0)&&(W<=W_MAX))
    {
        vector<Hero> Heros(n);
        for(auto &hero:Heros)
        {
            cin>>hero.c>>hero.s;
            if((hero.c<=0)||(hero.c>W)||(hero.s<=0)||(hero.s>S_MAX))
            {
                flag=false;
                break;
            }
        }
        if(flag)
            cout<<getMaxS_sumHerosCstLeW(Heros,W)<<endl;
    }
    else
        flag=false;
    if(!flag)
        cout<<"ERROR"<<endl;
    return 0;
}
