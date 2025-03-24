/*
平分战力

描述

在《王者荣耀》的战场上，英雄的合理分组对于取得胜利至关重要。​现有一支由 N 名英雄组成的队伍，每位英雄都有一个正整数的战斗力值。请你编写一个程序，判断是否可以将这支队伍分成两个子队伍，使得两个子队伍的战斗力总和相等。

输入

输入一个数组，例如：1 5 11 5

输出

输出字符串“true”或“false”

例如：输入1 5 11 5，输出true

解释：数组可以分割成 [1, 5, 5] 和 [11]

输入样例 1

1 5 11 5

输出样例 1

true


*/

#include <iostream>
#include <vector>
#include <numeric>
//#include <set>
#include <stack>

using namespace std;

typedef long long valT;

typedef struct recurNode_
{
    vector<valT>::const_iterator it;
    bool chose,done;
} recurNode;

//bool canDividSameS2(const vector<valT> &A)
//{
//    if(!A.empty())
//    {
//        valT S=accumulate(A.begin(),A.end(),(valT)0);
//        if(S%2)
//            return false;
//        else
//        {
//            S>>=1;
//            set<valT> allPosiSum= {0};
//            for(auto &a:A)
//            {
//                set<valT> Tmp;
//                for(auto &s:allPosiSum)
//                    if(a>S)
//                        break;
//                    else
//                    {
//                        valT val=a+s;
//                        if(val==S)
//                            return true;
//                        else if(val<S)
//                            Tmp.insert(val);
//                    }
//                allPosiSum.insert(Tmp.begin(),Tmp.end());
//            }
//        }
//    }
//    return false;
//}

bool canDividSameS2(const vector<valT> &A)
{
    if(!A.empty())
    {
        valT S=accumulate(A.begin(),A.end(),(valT)0);
        if(S%2)
            return false;
        else
        {
            valT val=0;
            stack<recurNode> recurStack;
            S>>=1,recurStack.push({A.begin(),true,false}),val+=A.front();
            while(!recurStack.empty())
                if(val>S)
                {
                    val-=*((recurStack.top()).it),recurStack.pop();
                    if(!recurStack.empty())
                        (recurStack.top()).done=true;
                }
                else if(val<S)
                {
                    recurNode &node=recurStack.top();
                    if(node.done)
                        if(node.chose)
                            node.chose=false,node.done=false,val-=*(node.it);
                        else
                        {
                            recurStack.pop();
                            if(!recurStack.empty())
                                (recurStack.top()).done=true;
                        }
                    else
                    {
                        if(node.it<(A.end()-1))
                            recurStack.push({node.it+1,true,false}),val+=*(node.it+1);
                        else
                        {
                            recurStack.pop();
                            if(!recurStack.empty())
                                (recurStack.top()).done=true;
                        }
                    }
                }
                else
                    return true;
        }
    }
    return false;
}

int main()
{
    vector<valT> A;
    valT a=0;
    while(cin>>a)
        A.push_back(a);
    cout<<(canDividSameS2(A)?"true":"false")<<endl;
    return 0;
}
