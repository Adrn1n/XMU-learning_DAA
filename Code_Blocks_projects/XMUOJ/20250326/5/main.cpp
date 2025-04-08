/*
回忆碎片信
描述

在《恋与制作人》的世界里，你收到了一封神秘的回忆碎片信📜，其中包含了一串字符s，代表你与李泽言、白起、许墨、周棋洛之间的一段未知故事。

你的任务是找出这封信中最长的回文子串，因为它可能暗示着你与某位男主的最深刻羁绊💖。


回文：如果字符串向前和向后读都相同，则它满足回文性。


输入

一个字符串s，表示信中的内容（1 ≤s.length≤ 1000）。


输出

一个字符串，表示s中最长的回文子串（如果有多个长度相同的回文子串，返回最先出现的那个）。


输入样例 1

abaxyzzyxf
输出样例 1

xyzzyx
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef short idxT;
typedef string::const_iterator strCIt;
typedef vector<idxT> idxVec;

inline idxT getMax_PalindromeLen(strCIt &Start,const strCIt End)
{
    idxT len=0;
    if(Start<End)
    {
        auto resIt=Start;
        vector<idxVec> A(End-Start);
        A[0].push_back(len=1);
        for(auto it=Start+1; it<End; ++it)
        {
            auto idx=(idxT)(it-Start);
            for(auto &l:A[idx-1])
            {
                auto it1=it-1-l;
                if((it1>=Start)&&(*it1==*it))
                {
                    auto len1=(idxT)(l+2);
                    A[idx].push_back(len1);
                    if(len1>len)
                        len=len1,resIt=it-(len-1);
                }
            }
            if(*it==*(it-1))
            {
                A[idx].push_back(2);
                if(len<2)
                    len=2,resIt=it-(len-1);
            }
            A[idx].push_back(1);
        }
        Start=resIt;
    }
    return len;
}

int main()
{
    string s;
    cin>>s;
    strCIt Start=s.begin();
    for(auto len=getMax_PalindromeLen(Start,s.end()); len; --len)
        cout<<Start[len-1];
    cout<<endl;
    return 0;
}
