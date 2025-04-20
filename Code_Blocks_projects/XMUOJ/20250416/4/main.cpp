/*
完美战令

描述

在激烈的召唤师峡谷对战中，有位技术高超的英雄在关键时刻必须做出抉择。传闻中，只有释放心中真正的信念，才能扭转战局，化险为夷。

给定一个字符串s，英雄可以在其中舍弃至多一个字符，试图让这段“战令”变得完美（成为回文序列）。

请你判断英雄是否能够在舍弃最多一个字符后，让这段话语成为回文。若可以则返回true，否则返回false。

输入

输入为一行字符串，由英文字母组成，表示英雄的战令语句。

输出

输出为一个字符串，若能通过舍弃至多一个字符使得战令变为回文，则输出true；否则输出false。

示例 1：

输入：s = "aba"
输出：true

示例 2：

输入：s = "abca"
输出：true
解释：你可以删除字符 'c' 。

示例 3：

输入：s = "abc"
输出：false

输入样例 1

aba

输出样例 1

true

来源

xmu

温馨提示

实在搞不定的话，你可以 点此下载测试数据 (./problem_5300_test_cases.zip)
*/

#include <iostream>
#include <string>

using namespace std;

inline bool isPalindrome_rmMax1(const string &S)
{
    if(S.empty())
        return true;
    else
    {
        bool flag=false;
        for(auto Start1=S.begin(),Start2=Start1,End1=S.end()-1,End2=End1; Start1<End1;)
            if(*Start1==*End1)
                ++Start1,--End1;
            else
            {
                if(flag)
                    if((Start1-S.begin())>(S.end()-1-End1))
                        Start1=Start2,End1=End2;
                    else
                        return false;
                else
                    Start2=Start1++,End2=End1-1,flag=true;
            }
        return true;
    }
}

int main()
{
    string s;
    cin>>s;
    if(isPalindrome_rmMax1(s))
        cout<<"true"<<endl;
    else
        cout<<"false"<<endl;
    return 0;
}
