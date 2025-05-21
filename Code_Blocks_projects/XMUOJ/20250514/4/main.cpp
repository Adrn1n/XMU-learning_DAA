/*
源石谜板解锁

描述

在罗德岛的作战演习中，博士需要操控一块 2×3 的“源石控制板”。板上包含编号为 1~5 的模块，以及一个编号为 0 的空位。一次操作是将空位与其相邻的模块（上下左右之一）交换位置。

你的目标是将初始状态的板调整成目标状态[[1,2,3],[4,5,0]]，即所有模块有序排列，空位在最后。

请你编写一个程序，返回最少需要多少步操作才能完成该目标。如果无法完成，则返回-1。

输入

一个 2×3 的二维列表board，表示初始谜板状态。

输出

一个整数，表示最少所需的移动次数；若无法解开谜板，返回-1。

QQ截图20250512180703.png (./57209e6e3a.png)

输入样例 1

[[1,2,3],[4,0,5]]

输出样例 1

1

来源

xmu

温馨提示

实在搞不定的话，你可以 点此下载测试数据 (./problem_5364_test_cases.zip)
*/

#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#include <set>

#define MOV_DIM 2
#define MOV_N 4

using namespace std;

typedef short idxT;
typedef short valT;
typedef short movIdxT;
typedef short cntT;

typedef pair<idxT,idxT> PII;
typedef vector<valT> valVec;

struct queNode
{
    vector<valVec> board;
    set<PII> MovLocs;
    cntT step;
};

const idxT Mov[MOV_DIM][MOV_N]= {{-1,1,0,0},{0,0,-1,1}};
const vector<valVec> GoalBoard= {{1,2,3},{4,5,0}};

const valT movEle=0;

inline vector<valVec> get_board()
{
    vector<valVec> board;
    char c;
    if((cin>>c)&&(c=='['))
        while((cin>>c)&&(c=='['))
        {
            board.emplace_back();
            valT a;
            bool flag;
            while((flag=true,cin>>a)&&((board.back()).push_back(a),cin>>c))
            {
                flag=false;
                if(c==']')
                    break;
                else if(c!=',')
                    return board;
            }
            if(flag)
                return board;
            else
            {
                if((c!=']')||(!(cin>>c))||(c!=','))
                    break;
            }
        }
    return board;
}

inline bool is2board_same(const vector<valVec> &board1,const vector<valVec> &board2)
{
    if(board1.size()==(board2.size()))
    {
        for(auto it1=board1.begin(),it2=board2.begin(); it1<(board1.end()); ++it1,++it2)
            if(it1->size()==it2->size())
            {
                for(auto it3=it1->begin(),it4=it2->begin(); it3<(it1->end()); ++it3,++it4)
                    if((*it3)!=(*it4))
                        return false;
            }
            else
                return false;
        return true;
    }
    else
        return false;
}

inline set<PII> getMovEles_loc(const vector<valVec> &board)
{
    set<PII> Res;
    for(idxT i=0; (size_t)i<(board.size()); ++i)
        for(idxT j=0; (size_t)j<(board[i].size()); ++j)
            if(board[i][j]==movEle)
                Res.insert({i,j});
    return Res;
}

inline cntT getMinStep_toGoalBoard(vector<valVec> &board,const vector<valVec> &goalBoard)
{
    if(is2board_same(board,goalBoard))
        return 0;
    else
    {
        if(board.size()==(goalBoard.size()))
        {
            bool flag=true;
            for(vector<valVec>::const_iterator it1=board.begin(),it2=goalBoard.begin(); it1<(board.end()); ++it1,++it2)
                if(it1->size()!=it2->size())
                {
                    flag=false;
                    break;
                }
            if(flag)
            {
                auto MovLocs=getMovEles_loc(goalBoard);
                if(!MovLocs.empty())
                {
                    queue<queNode> Que;
                    set<vector<valVec>> visBoards= {goalBoard};
                    Que.push({goalBoard,MovLocs,0});
                    while(!Que.empty())
                    {
                        auto node=Que.front();
                        if(is2board_same(node.board,board))
                            return node.step;
                        else
                        {
                            MovLocs=node.MovLocs;
                            for(auto it=((node.MovLocs).begin()); it!=((node.MovLocs).end()); ++it)
                                for(movIdxT i=0; i<MOV_N; ++i)
                                {
                                    PII loc= {it->first-(Mov[0][i]),it->second-(Mov[1][i])};
                                    if((loc.first>=0)&&((size_t)(loc.first)<((node.board).size()))&&(loc.second>=0)&&((size_t)(loc.second)<((node.board)[loc.first].size()))&&((node.board)[loc.first][loc.second]!=movEle))
                                    {
                                        swap(node.board[it->first][it->second],node.board[loc.first][loc.second]);
                                        if(visBoards.find(node.board)==visBoards.end())
                                        {
                                            auto eleIt=MovLocs.find(*it);
                                            if(eleIt==MovLocs.end())
                                                return -1;
                                            else
                                            {
                                                auto tmp=*eleIt;
                                                MovLocs.erase(eleIt),MovLocs.insert(loc),Que.push({node.board,MovLocs,(cntT)(node.step+1)}),visBoards.insert(node.board),MovLocs.erase(loc),MovLocs.insert(tmp);
                                            }
                                        }
                                        swap(node.board[it->first][it->second],node.board[loc.first][loc.second]);
                                    }
                                }
                            Que.pop();
                        }
                    }
                }
            }
        }
        return -1;
    }
}

int main()
{
    auto board=get_board();
    cout<<getMinStep_toGoalBoard(board,GoalBoard)<<endl;
    return 0;
}
