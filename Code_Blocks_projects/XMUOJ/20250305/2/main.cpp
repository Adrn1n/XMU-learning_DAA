/*
英雄排名

描述

在一个虚拟的游戏世界中，有n位英雄的战斗力被记录在一个排行榜上。然而，由于系统错误，这个排行榜变得混乱无序。你的任务是计算其中正确的战斗力排名的总数。

正确排名的定义如下：如果一位英雄排在另一位英雄的前面，并且他的战斗力确实高于后者，那么这就算作一次正确排名。

数据范围：1≤n≤100000

输入

第一行包含整数n，表示英雄的个数。

第二行包含 n 个整数，每个数表示英雄的战斗力。

输出

输出一个整数，表示正确排名的总数。

输入样例 1

6
2 3 4 5 6 1

输出样例 1

5


*/

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>

#define n_MAX 100000

using namespace std;

typedef int idxT;
typedef long long valT;
typedef long long cntT;

typedef struct mSortNode_
{
    vector<valT>::iterator Start,End;
} mSortNode;

cntT mergeSort(vector<valT> A)
{
    cntT invsN=0;
    if(!A.empty())
    {
        queue<idxT> divQue;
        divQue.push((idxT)(A.size()));
        for(idxT tmp=0; (tmp=divQue.front())>1; divQue.pop(),divQue.push(tmp>>1),divQue.push(tmp-(tmp>>1)));
        queue<mSortNode> srtdQue;
        for(auto it=A.begin(); !divQue.empty(); divQue.pop())
        {
            idxT tmp=divQue.front();
            if(tmp>1)
            {
                if(*it>*(it+1))
                    swap(*it,*(it+1)),++invsN;
                srtdQue.push({it,it+=2});
            }
            else
                srtdQue.push({it,++it});
        }
        for(mSortNode node1,node2; node1=srtdQue.front(),srtdQue.pop(),!srtdQue.empty(); srtdQue.pop())
        {
            node2=srtdQue.front();
            vector<valT> tmp(node2.End-node1.Start);
            auto it=tmp.begin(),it1=node1.Start,it2=node2.Start;
            while((it1<node1.End)&&(it2<node2.End))
                if(*it1>*it2)
                    *it++=*it2++,invsN+=(node1.End-it1);
                else
                    *it++=*it1++;
            while(it1<node1.End)
                *it++=*it1++;
            while(it2<node2.End)
                *it++=*it2++;
            copy(tmp.begin(),tmp.end(),node1.Start);
            srtdQue.push({node1.Start,node2.End});
        }
    }
    return invsN;
}

int main()
{
    idxT n=0;
    cin>>n;
    if((n>0)&&(n<=n_MAX))
    {
        vector<valT> A(n);
        for(auto &a:A)
            cin>>a;
        cout<<mergeSort(A)<<endl;
    }
    else
        cout<<"ERROR"<<endl;
    return 0;
}
