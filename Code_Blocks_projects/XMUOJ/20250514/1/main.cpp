/*
名字搜索

描述

在王者峡谷中，每个格子代表一个英雄名字首字母构成的战场地图（二维字符网格board）。现在有一支战队希望沿着地图上相邻的格子（上下左右）依次选取英雄组成一个特定战术组合（即目标字符串word）。

请你判断：该战术组合是否可以通过地图中相邻英雄首字母拼出？每个格子只能使用一次。

输入

    一个字符串word（如"ABCCED"）

    一个二维字符数组board（如[["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]]）

输出

如果可以拼出该组合，输出true；否则输出false。

QQ截图20250512171152.png (./9d9e303f92.png)

输入样例 1

"ABCCED"
[["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]]

输出样例 1

true

来源

xmu

温馨提示

实在搞不定的话，你可以 点此下载测试数据 (./problem_5361_test_cases.zip)
*/

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <stack>

#define MOV_DIM 2
#define MOV_N 4

using namespace std;

typedef string valT;
typedef char val_atomT;
typedef long long idxT;
typedef short movIdxT;

typedef vector<valT> valVec;
typedef pair<idxT,idxT> PII;

struct stakNode
{
    PII loc;
    movIdxT idx;
};

const idxT Mov[MOV_DIM][MOV_N]= {{0,0,1,-1},{1,-1,0,0}};

inline valT get_word()
{
    string word;
    val_atomT c=0;
    if((cin>>c)&&(c=='"'))
        while((cin>>c)&&(c!='"'))
            word.push_back(c);
    return word;
}

inline vector<valVec> get_board()
{
    vector<valVec> board;
    val_atomT c;
    if((cin>>c)&&(c=='['))
        while((cin>>c)&&(c=='['))
        {
            board.emplace_back();
            while((cin>>c)&&(c=='"'))
            {
                (board.back()).emplace_back("");
                while((cin>>c)&&(c!='"'))
                    ((board.back()).back()).push_back(c);
                if((c!=EOF)&&(cin>>c))
                {
                    if(c==']')
                        break;
                    else if(c!=',')
                        return board;
                }
                else
                    return board;
            }
            if((c!=']')||(!(cin>>c))||(c!=','))
                return board;
        }
    return board;
}

inline bool canBoardBuild_word(const vector<valVec> &board,const valT &word)
{
    if(word.empty())
        return true;
    else
    {
        if(!board.empty())
        {
            vector<vector<bool>> nUsed;
            nUsed.reserve(board.size());
            for(auto &vert:board)
                nUsed.emplace_back(vert.size(),true);
            string str=word;
            stack<stakNode> Stak;
            for(idxT i=0; (size_t)i<board.size(); ++i)
                for(idxT j=0; (size_t)j<board[i].size(); ++j)
                    if(word.rfind(board[i][j],0)==0)
                    {
                        str=str.substr(board[i][j].size()),nUsed[i][j]=false,Stak.push({{i,j},0});
                        while(!Stak.empty())
                            if(str.empty())
                                return true;
                            else
                            {
                                auto &node=Stak.top();
                                auto &loc=node.loc;
                                bool flag=true;
                                for(; flag&&(node.idx<MOV_N); ++node.idx)
                                {
                                    loc.first+=Mov[0][node.idx],loc.second+=Mov[1][node.idx];
                                    if((loc.first>=0)&&((size_t)(loc.first)<board.size())&&(loc.second>=0)&&((size_t)(loc.second)<(board[loc.first].size()))&&nUsed[loc.first][loc.second]&&(str.rfind(board[loc.first][loc.second],0)==0))
                                        str=str.substr(board[loc.first][loc.second].size()),nUsed[loc.first][loc.second]=false,Stak.push({{loc.first,loc.second},0}),flag=false;
                                    loc.first-=Mov[0][node.idx],loc.second-=Mov[1][node.idx];
                                }
                                if(flag)
                                    str.insert(0,board[loc.first][loc.second]),nUsed[loc.first][loc.second]=true,Stak.pop();
                            }
                    }
        }
        return false;
    }
}

int main()
{
    auto word=get_word();
    auto board=get_board();
    if(canBoardBuild_word(board,word))
        cout<<"true"<<endl;
    else
        cout<<"false"<<endl;
    return 0;
}
