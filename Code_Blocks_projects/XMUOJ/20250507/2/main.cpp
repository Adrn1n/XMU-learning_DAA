/*
镜之双生牌

描述

在王者荣耀的世界里，法师英雄“镜”最近获得了一套神秘的双生镜像卡牌。这些卡牌原本是荣耀大陆上的强力神器，却在镜的一次修炼中意外发生了魔力共鸣，每两张卡牌融为了一体，变成了双面牌——每张卡牌正反两面分别印着不同的英雄头像，分别用数字 1~78 来编号。

镜决定将这些卡牌作为对抗神器，用来与敌人进行一场智力博弈。她邀请你来与她进行这场卡牌游戏——规则很简单，但胜负却并不容易预判。
游戏规则

    初始时，桌上有N张双面卡牌。

    每张卡牌正反面分别为Ai、Bi（都是1∼78之间的整数）。

    两位玩家轮流操作，你是先手。

    每次操作，玩家从桌面上移除任意一对卡牌，满足：

        它们正面相同，或者

        它们反面相同。

    如果在你的回合中无法再找到合法配对移除，你将输掉比赛。

两位玩家都非常聪明，会采取最优策略。现在，请你判断，在双方都采取最优策略的前提下，你是否能获胜。

输入

第一行一个整数N（1 ≤ N ≤ 18）——表示双面卡牌的数量。

接下来N行，每行两个整数Ai和Bi（1 ≤Ai,Bi≤ 78）——分别表示第i张卡牌正反两面的英雄编号。

输出

如果你能在双方都采取最优策略的情况下获胜，输出：YES，否则输出：NO

输入样例 1

4
1 4
2 3
2 4
2 1

输出样例 1

YES

输入样例 2

1
1 1

输出样例 2

NO

来源

xmu

温馨提示

实在搞不定的话，你可以 点此下载测试数据 (./problem_5334_test_cases.zip)
*/

#include <iostream>
#include <utility>
#include <vector>
#include <stack>

#define MAX_N 18
#define MAX_VAL 78

using namespace std;

typedef short idxT;
typedef short valT;

typedef pair<valT,valT> PVV;

struct stakNode
{
    idxT a,b;
    bool isOver;
};

inline bool canRm_2elm(const PVV &a,const PVV &b)
{
    return (a.first==b.first)||(a.second==b.second);
}

inline bool allCan_1stRmLastRmAll(const vector<PVV> &A)
{
    stack<stakNode> Stak;
    stakNode node= {0,0,false};
    vector<bool> Used(A.size());
    do
    {
        if((!Stak.empty())&&((Stak.top()).isOver))
            node=Stak.top(),Used[node.a]=Used[node.b]=node.isOver=false,Stak.pop();
        bool flag=true;
        for(++(node.b); (size_t)(node.a)<(A.size()-1); ++(node.a),node.b=(idxT)(node.a+1))
            if(!(Used[node.a]))
                for(; (size_t)(node.b)<A.size(); ++node.b)
                    if((!Used[node.b])&&canRm_2elm(A[node.a],A[node.b]))
                    {
                        Used[node.a]=Used[node.b]=true,Stak.push(node),flag=false;
                        break;
                    }
        if(flag&&(!Stak.empty()))
        {
            if((Stak.size())%2)
                node=Stak.top(),Used[node.a]=Used[node.b]=false,Stak.pop();
            if(Stak.empty())
                return false;
            else
                (Stak.top()).isOver=true;
        }
    }
    while(!Stak.empty());
    return true;
}

int main()
{
    idxT N=0;
    cin>>N;
    if((N>0)&&(N<=MAX_N))
    {
        vector<PVV> A(N);
        for(auto &p:A)
            while(cin>>p.first>>p.second)
                if((p.first>0)&&(p.first<=MAX_VAL)&&(p.second>0)&&(p.second<=MAX_VAL))
                    break;
                else
                    cout<<"ERROR!"<<endl;
        if(allCan_1stRmLastRmAll(A))
            cout<<"NO"<<endl;
        else
            cout<<"YES"<<endl;
    }
    return 0;
}
