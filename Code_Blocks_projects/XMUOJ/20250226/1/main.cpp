/*
数字之环

描述

你是一位专门研究古代文明的数字考古学家。在整理数据时，你偶然发现了一个被遗忘的数据环 - "数字之环"。

这个环形数据结构由N个相连的数据节点组成。每个节点都存储着珍贵的远古文明密码，这些密码可能揭示人类历史上未解之谜。但这些节点都被一种称为"量子纠缠锁"的安全机制保护着。

根据你的研究，每个数据节点都包含独特且极其重要的信息。然而，由于量子纠缠效应，如果在同一时间单位（比如同一天）内访问任意两个相邻的节点，就会触发系统的防御机制。这种机制会立即锁死被访问的节点，使存储的数据变得无法读取。

为了最大程度地获取这些珍贵的历史数据，同时避免触发量子纠缠锁的防御机制，你需要精心设计数据提取的时间表。

输入

一个数字，代表"数字之环"上的数据节点总数
一个数组，代表每个数据节点中存储的历史数据的价值评估分数

输出

一天之内你能够获取的最大价值数据。

输入样例 1

3
2 3 2
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef int idxT;
typedef long long valT;

vector<bool> getMax_Nadj(const vector<valT>::iterator it_s,const vector<valT>::iterator it_e,valT &res)
{
    vector<bool> Chose;
    res=0;
    if(it_s<it_e)
    {
        if(it_s==(it_e-1))
        {
            Chose.push_back(true);
            res=*it_s;
        }
        else if(it_s<(it_e-1))
        {
            valT Val_tmp[2]= {*it_s,0};
            vector<bool> Chose_tmp[2]= {{true},{}};
            res=Val_tmp[1]=(*it_s<*(it_s+1))?(Chose_tmp[1]= {false,true},*(it_s+1)):(Chose_tmp[1]= {true,false},*it_s);
            for(auto it=it_s+2; it<it_e; ++it)
            {
                idxT i=(idxT)((it-it_s)%2),j=(idxT)((it-it_s-1)%2);
                if(Chose_tmp[j].back())
                    if(Val_tmp[j]<(Val_tmp[i]+*it))
                        Val_tmp[i]+=*it,Chose_tmp[i].push_back(false),Chose_tmp[i].push_back(true);
                    else
                        Val_tmp[i]=Val_tmp[j],Chose_tmp[i]=Chose_tmp[j],Chose_tmp[i].push_back(false);
                else
                    Val_tmp[i]=Val_tmp[j]+*it,Chose_tmp[i]=Chose_tmp[j],Chose_tmp[i].push_back(true);
            }
            res=Val_tmp[(it_e-it_s-1)%2],Chose=Chose_tmp[(it_e-it_s-1)%2];
        }
    }
    return Chose;
}

int main()
{
    idxT n=0;
    cin>>n;
    if(n>0)
    {
        vector<valT> A(n);
        for(auto &a:A)
            cin>>a;
        valT res=0;
        if(n>3)
        {
            vector<bool> Chose=getMax_Nadj(A.begin(),A.end()-1,res);
            if(Chose.front()||Chose.back())
            {
                valT tmp=0;
                getMax_Nadj(A.begin()+1,A.end()-2,tmp);
                res=((tmp+A.back())>res)?(tmp+A.back()):res;
            }
            else
                res+=A.back();
        }
        else
            res=*max_element(A.begin(),A.end());
        cout<<res<<endl;
    }
    else
        cout<<"ERROR"<<endl;
    return 0;
}
