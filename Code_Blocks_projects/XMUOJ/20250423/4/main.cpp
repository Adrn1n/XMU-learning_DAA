/*
最大网络秩

描述

在提瓦特大陆的七国中，城市之间通过传送锚点相连，形成了一个庞大的传送网络。​

每个传送锚点连接两座不同的城市，形成一条双向的传送路径。​

两座不同城市构成的城市对的网络秩定义为：与这两座城市直接相连的传送路径总数。如果存在一条传送路径直接连接这两座城市，则这条路径只计算一次。​

整个传送网络的最大网络秩是所有不同城市对中的最大网络秩。​

给你整数 n 和数组 roads，返回整个传送网络的最大网络秩。

输入

每个输入文件包含：​

    第一行一个整数 n，表示城市的数量。

    接下来的若干行，每行两个整数 ai 和 bi，表示城市 ai 与城市 bi 之间存在一条传送路径。

输出

每个输出文件包含一个整数，表示整个传送网络的最大网络秩。​

QQ截图20250419220653.png (./3bd31c2975.png)

输入样例 1

4
0 1
0 3
1 2
1 3

输出样例 1

4

来源

xmu

温馨提示

实在搞不定的话，你可以 点此下载测试数据 (./problem_5309_test_cases.zip)
*/

#include <iostream>
#include <vector>
#include <forward_list>
#include <algorithm>
#include <utility>

using namespace std;

typedef long long idxT;
typedef long long cntT;

typedef forward_list<idxT> idxLList;
typedef pair<idxT,cntT> PIC;

inline PIC getVert_maxDegre(const vector<idxLList> &adjList)
{
    PIC res= {-1,0};
    if(!adjList.empty())
    {
        cntT tmp=0;
        for(auto it1=adjList.begin(); it1<adjList.end(); ++it1,tmp=0)
        {
            for(auto it2=it1->begin(); it2!=it1->end(); ++it2,++tmp);
            if(tmp>res.second)
                res= {it1-adjList.begin(),tmp};
        }
    }
    return res;
}

inline bool rmVert(vector<idxLList> &adjList,const idxT vert)
{
    if((vert>=0)&&(adjList.size()>(size_t)vert))
    {
        adjList.erase(adjList.begin()+vert);
        for(auto it1=adjList.begin(); it1<adjList.end(); ++it1)
            for(auto it2=it1->before_begin(),it3=it1->begin(); it3!=it1->end(); ++it2,++it3)
                if(*it3==vert)
                {
                    it1->erase_after(it2);
                    break;
                }
        return true;
    }
    else
        return false;
}

int main()
{
    idxT n=0;
    cin>>n;
    if(n>0)
    {
        vector<idxLList> adjList(n);
        idxT a=0,b=0;
        while(cin>>a>>b)
            if((a>=0)&&(a<n)&&(b>=0)&&(b<n)&&(find(adjList[a].begin(),adjList[a].end(),b)==adjList[a].end())&&(find(adjList[b].begin(),adjList[b].end(),a)==adjList[b].end()))
                adjList[a].push_front(b),adjList[b].push_front(a);
            else
                cout<<"ERROR!"<<endl;
        auto tmp=getVert_maxDegre(adjList);
        if((tmp.first)>=0)
        {
            auto res=tmp.second;
            rmVert(adjList,tmp.first),tmp=getVert_maxDegre(adjList);
            if((tmp.first)>=0)
                res+=(tmp.second);
            cout<<res<<endl;
        }
        else
            cout<<"ERROR!"<<endl;
    }
    return 0;
}
