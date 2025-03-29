/*
编辑阵容

描述

在《金铲铲之战》中，玩家需要组建一个强大的阵容。每个阵容可以用一个字符串表示，字符串的每个字符代表一个英雄或装备。玩家可以进行以下操作来调整阵容：

    ​插入：添加一个英雄或装备。
    ​删除：移除一个英雄或装备。
    ​替换：将一个英雄或装备替换为另一个。

现在有n个初始阵容和m次询问。对于每次询问，给出一个目标阵容和操作次数上限，求在操作次数上限内，有多少个初始阵容可以调整为目标阵容。

输入

    第一行包含两个整数n和m，分别表示初始阵容的数量和询问的次数。
    接下来n行，每行包含一个字符串，表示一个初始阵容。
    接下来m行，每行包含一个字符串和一个整数，表示目标阵容和操作次数上限。

输出

对于每次询问，输出一个整数，表示在操作次数上限内可以调整为目标阵容的初始阵容数量。

输入样例 1

3 2
abc
acd
bcd
ab 1
acbd 2

输出样例 1

1
3


*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long idxT;
typedef string::const_iterator strIt_c;
typedef vector<idxT> idxVec;

typedef struct QueryNode_
{
    string s;
    idxT max_ops{};
} QueryNode;

inline bool isFormSats(const string &form,const QueryNode &QueryNode)
{
    idxT maxSame=0,len1=(idxT)(form.size()),len2=(idxT)((QueryNode.s).size());
    strIt_c it1=form.begin(),it2=(QueryNode.s).begin();
    if(len1<len2)
        swap(len1,len2),swap(it1,it2);
    if(len2)
    {
        vector<idxVec> Tmp(2,idxVec(len1));
        for(idxT i=0; i<len2; ++i)
            for(idxT j=i; j<(len1-(len2-i)+1); ++j)
            {
                if(it1[j]==it2[i])
                    maxSame=1;
                else
                    maxSame=0;
                if(j)
                    if(i==j)
                        Tmp[i%2][j]=Tmp[(i+1)%2][j-1]+maxSame;
                    else
                        Tmp[i%2][j]=max(Tmp[(i+1)%2][j-1]+maxSame,Tmp[i%2][j-1]);
                else
                    Tmp[0][0]=maxSame;
            }
        maxSame=Tmp[(len2-1)%2].back();
    }
    return (len1-maxSame)<=QueryNode.max_ops;
}

int main()
{
    idxT n=0,m=0;
    cin>>n>>m;
    if((n>0)&&(m>=0))
    {
        vector<string> Org(n);
        for(auto &s:Org)
            cin>>s;
        while(m-->0)
        {
            QueryNode query;
            cin>>query.s>>query.max_ops;
            idxT cnt=0;
            for(auto &form:Org)
                if(isFormSats(form,query))
                    ++cnt;
            cout<<cnt<<endl;
        }
    }
    else
        cout<<"ERROR!"<<endl;
    return 0;
}
