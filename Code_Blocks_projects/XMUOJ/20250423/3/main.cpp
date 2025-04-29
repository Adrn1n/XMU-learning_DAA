/*
移除通道

描述

在《王者荣耀》的世界中，召唤师们的战斗场地由若干个据点组成，编号从 1 到 n。​

这些据点通过双向通道连接，形成了一棵树结构，确保任意两个据点之间有且仅有一条路径相连。​

某一天，为了增强战术灵活性，系统在这棵树中添加了一条新的通道，连接了两个不同的据点，导致图中出现了一个环。​

现在，系统希望移除一条边，以恢复树的结构。​

请找出一条可以移除的边，使得移除后图仍然是一棵包含 n 个节点的树。如果有多个答案，返回输入列表中最后出现的那条边。

输入

每个输入文件包含：​

    若干行，每行两个整数 ai 和 bi，表示据点 ai 与据点 bi 之间存在一条双向通道。

输出

每个输出文件包含一行，两个整数，表示应移除的边的两个端点。

QQ截图20250419220142.png (./887ccd1cfa.png)

输入样例 1

1 2
1 3
2 3

输出样例 1

2 3

来源

xmu

温馨提示

实在搞不定的话，你可以 点此下载测试数据 (./problem_5308_test_cases.zip)
*/

#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long idxT;

typedef pair<idxT,idxT> PII;
typedef vector<idxT> idxVec;

inline PII getLast_unDirTre_more1edge(const vector<PII> &Edges)
{
    PII res= {0,0};
    if(!Edges.empty())
    {
        vector<idxVec> conetComps;
        bool flag=true;
        for(auto it=Edges.begin(); (it<Edges.end())&&flag; ++it)
            if((it->first)==(it->second))
                res=*it,flag=false;
            else
            {
                auto it1=conetComps.begin(),it2=it1;
                for(bool flag1=true,flag2=flag1; ((it1<conetComps.end())&&(it2<conetComps.end()))&&(flag1||flag2);)
                {
                    if(flag1)
                    {
                        if(find(it1->begin(),it1->end(),it->first)!=it1->end())
                            flag1=false;
                        else
                            ++it1;
                    }
                    if(flag2)
                    {
                        if(find(it2->begin(),it2->end(),it->second)!=it2->end())
                            flag2=false;
                        else
                            ++it2;
                    }
                }
                if((it1==conetComps.end())&&(it2==conetComps.end()))
                    conetComps.push_back({it->first,it->second});
                else if(it1==conetComps.end())
                    it2->push_back(it->first);
                else if(it2==conetComps.end())
                    it1->push_back(it->second);
                else
                {
                    if(it1==it2)
                        res=*it,flag=false;
                    else
                    {
                        for(auto it3=it2->begin(); it3<it2->end(); ++it3)
                            it1->push_back(*it3);
                        conetComps.erase(it2);
                    }
                }
            }
    }
    return res;
}

int main()
{
    vector<PII> Edges;
    PII edge;
    while(cin>>edge.first>>edge.second)
        Edges.push_back(edge);
    edge=getLast_unDirTre_more1edge(Edges);
    cout<<edge.first<<' '<<edge.second<<endl;
    return 0;
}
