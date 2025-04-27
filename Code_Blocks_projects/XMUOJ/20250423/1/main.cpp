/*
秘密镇法官

描述

在鸣潮的世界中，鸣潮镇有 n 位居民，编号从 1 到 n。传言称，其中一位居民是秘密的镇法官。​

如果镇法官确实存在，那么他必须满足以下两个条件：​

    镇法官不会信任任何人。

    除了镇法官本人，每位居民都信任镇法官。​

只有一个人同时满足这两个条件。​

给定一个数组 trust，其中 trust[i] = [ai, bi] 表示编号为 ai 的居民信任编号为 bi 的居民。​

如果镇法官存在并且可以确定其身份，请返回该法官的编号；否则，返回 -1。

输入

    第一行包含一个整数 n，表示居民的总数。

    接下来的若干行，每行包含两个整数 ai 和 bi，表示编号为 ai 的居民信任编号为 bi 的居民。

输出

输出一个整数，表示镇法官的编号；如果无法确定镇法官的身份，输出 -1。

示例 1：

输入：n = 2, trust = [[1,2]]
输出：2

示例 2：

输入：n = 3, trust = [[1,3],[2,3]]
输出：3

示例 3：

输入：n = 3, trust = [[1,3],[2,3],[3,1]]
输出：-1

输入样例 1

3
1 3
2 3

输出样例 1

3

来源

xmu

温馨提示

实在搞不定的话，你可以 点此下载测试数据 (./problem_5306_test_cases.zip)
*/

#include <iostream>
#include <vector>
#include <forward_list>

using namespace std;

typedef long long idxT;

inline idxT get_allInNOut(const vector<forward_list<idxT>> &adjList)
{
    idxT res=-1;
    if(!adjList.empty())
    {
        bool flag=false;
        for(auto it1=adjList.begin(); it1<adjList.end(); ++it1)
            if((*it1).empty())
            {
                if(flag)
                {
                    res=-1,flag=false;
                    break;
                }
                else
                    res=it1-adjList.begin(),flag=true;
            }
        if(flag)
        {
            for(auto it1=adjList.begin(); it1<adjList.end(); ++it1,flag=true)
                if(it1-adjList.begin()==res)
                    continue;
                else
                {
                    for(auto &vert:*it1)
                        if(vert==res)
                        {
                            flag=false;
                            break;
                        }
                    if(flag)
                    {
                        res=-1;
                        break;
                    }
                }
        }
    }
    return res;
}

int main()
{
    idxT n=0;
    cin>>n;
    if(n>0)
    {
        vector<forward_list<idxT>> adjList(n);
        idxT a=0,b=0;
        while(cin>>a>>b)
            if((a>0)&&(a<=n)&&(b>0)&&(b<=n))
                adjList[a-1].push_front(b-1);
            else
                cout<<"ERROR!"<<endl;
        auto res=get_allInNOut(adjList);
        if(res>=0)
            ++res;
        cout<<res<<endl;
    }
    return 0;
}
