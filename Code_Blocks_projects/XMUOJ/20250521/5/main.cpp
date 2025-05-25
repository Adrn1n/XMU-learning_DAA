/*
符文之链

描述

召唤师在装备符文时，将 k 块符文按顺序合并成一条符文链。每次合并相邻两块会产生一次“合并增益”，等于它们的分值之和。合并后产生的新符文的分值等于两者之和，并接入原链位置。要将所有符文合并成一块，整个过程中合并顺序会影响总增益。请用分支界限算法搜索最优合并顺序，使总增益最大。

输入

    k（符文块数，1 ≤ k ≤ 12）。

    第二行 k 个正整数 ri（每块符文初始分值，1 ≤ ri ≤ 10^4），以空格分隔。

输出

最大合并总增益

输入样例 1

5
6 5 16 5 22

输出样例 1

172

来源

xmu

温馨提示

实在搞不定的话，你可以 点此下载测试数据 (./problem_5370_test_cases.zip)
*/

#include <iostream>
#include <forward_list>
#include <queue>
#include <map>

#define K_MIN 1
#define K_MAX 12
#define R_MIN 1
#define R_MAX 10000

using namespace std;

typedef short idxT;
typedef int valT;

struct queNode
{
    forward_list<valT> Items;
    valT val;
};

inline bool isPosible_node(const queNode &node,map<forward_list<valT>,valT> &curState_max)
{
    bool flag=false;
    auto mapIt=curState_max.find(node.Items);
    if(mapIt==curState_max.end())
        curState_max[node.Items]=node.val,flag=true;
    else if(node.val>=(mapIt->second))
        mapIt->second=node.val,flag=true;
    return flag;
}

inline valT getMaxVal_combin2(const forward_list<valT> &A)
{
    valT res=0;
    map<forward_list<valT>,valT> curState_max;
    queue<queNode> Que;
    Que.push({A,0});
    while(!Que.empty())
    {
        auto &node=Que.front();
        if(distance((node.Items).begin(),(node.Items).end())>1)
        {
            if(isPosible_node(node,curState_max))
            {
                auto &items=node.Items;
                for(auto it=items.begin(); it!=items.end(); ++it)
                {
                    auto next_it=next(it);
                    if(next_it!=items.end())
                    {
                        auto tmp=*next_it;
                        (*it)+=tmp,items.erase_after(it),node.val+=(*it);
                        if(isPosible_node(node,curState_max))
                            Que.push(node);
                        node.val-=(*it),(*it)-=tmp,items.insert_after(it,tmp);
                    }
                }
            }
        }
        else
            res=(node.val>res)?(node.val):res;
        Que.pop();
    }
    return res;
}

int main()
{
    idxT k=0;
    cin>>k;
    bool flag=true;
    if((k>=K_MIN)&&(k<=K_MAX))
    {
        forward_list<valT> A(k);
        for(auto &r:A)
        {
            cin>>r;
            if((r<R_MIN)||(r>R_MAX))
            {
                flag=false;
                break;
            }
        }
        if(flag)
            cout<<getMaxVal_combin2(A)<<endl,flag=false;
        else
            flag=true;
    }
    if(flag)
        cout<<"ERROR!"<<endl;
    return 0;
}
