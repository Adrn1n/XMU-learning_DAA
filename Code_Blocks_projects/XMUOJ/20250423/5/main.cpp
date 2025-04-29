/*
最长路径

描述

在《明日方舟》的世界中，罗德岛的干员们需要在一张地图上寻找一条路径，以完成任务。​

这张地图可以表示为一个 m x n 的整数矩阵，每个单元格代表一个区域，数值表示该区域的危险等级。​

干员们只能从当前区域移动到上下左右相邻的区域，且只能移动到危险等级更高的区域。​

请你找出干员们可以行进的最长路径的长度。

输入

每个输入文件包含：​

    第一行一个整数 m，表示地图的行数。

    接下来的 m 行，每行包含 n 个整数，表示地图的每一行。

输出

每个输出文件包含一个整数，表示干员们可以行进的最长路径的长度

QQ截图20250419221101.png (./ba1e599c59.png)

输入样例 1

3
9 9 4
6 6 8
2 1 1

输出样例 1

4

来源

xmu

温馨提示

实在搞不定的话，你可以 点此下载测试数据 (./problem_5310_test_cases.zip)
*/

#include <iostream>
#include <sstream>
#include <vector>
#include <queue>

#define moveN 4

using namespace std;

typedef long long idxT;
typedef long long valT;

typedef vector<idxT> idxVec;

struct queNode
{
    idxT i,j,dist;
};

const idxT Move[moveN][2]= {{0,-1},{0,1},{-1,0},{1,0}};

inline idxT getMax_incrsPathLen(const vector<idxVec> &A)
{
    idxT res=0;
    if(!A.empty())
    {
        vector<vector<bool>> nVisit;
        bool flag=true;
        for(auto &a:A)
            if(!a.empty())
                nVisit.emplace_back(a.size(),true);
            else
            {
                flag=false;
                break;
            }
        if(flag)
            for(idxT i=0; (size_t)i<A.size(); ++i)
                for(idxT j=0; (size_t)j<(A[i].size()); ++j)
                    if(nVisit[i][j])
                    {
                        queue<queNode> que;
                        que.push({i,j,0}),nVisit[i][j]=false;
                        auto maxVal=A[i][j];
                        for(auto p=i; (size_t)p<A.size(); ++p)
                            for(auto q=j; (size_t)q<(A[p].size()); ++q)
                                if((nVisit[p][q])&&(A[p][q]>=maxVal))
                                {
                                    if(A[p][q]>maxVal)
                                        queue<queNode>().swap(que),maxVal=A[p][q];
                                    que.push({p,q,0});
                                }
                        while(!que.empty())
                        {
                            auto node=que.front(),tmp=node;
                            que.pop();
                            for(size_t k=0; k<moveN; tmp=node,++k)
                                if(((tmp.i+=Move[k][0])>=0)&&((size_t)(tmp.i)<A.size())&&((tmp.j+=Move[k][1])>=0)&&((size_t)(tmp.j)<(A[tmp.i].size()))&&(A[tmp.i][tmp.j]<A[node.i][node.j]))
                                    ++(tmp.dist),que.push(tmp),nVisit[tmp.i][tmp.j]=false,res=(res<(tmp.dist))?(tmp.dist):res;
                        }
                    }
    }
    return res;
}

int main()
{
    idxT m=0,n=0;
    cin>>m>>ws;
    if(m>0)
    {
        vector<idxVec> A(m);
        for(auto &vec:A)
        {
            valT val=0;
            string line_in;
            if(getline(cin,line_in))
            {
                stringstream ss(line_in);
                while(ss>>val)
                    vec.push_back(val);
            }
        }
        cout<<getMax_incrsPathLen(A)+1<<endl;
    }
    return 0;
}
