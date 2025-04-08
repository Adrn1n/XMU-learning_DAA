/*
搭配词汇
描述

在《无限暖暖》的奇幻世界里，暖暖需要通过搭配词汇来解锁特定的时尚风格。你得到了一个单词s，代表一套完整的穿搭描述，同时拥有一个时尚词典wordDict，其中包含了一些时尚单词。

你的任务是判断是否可以利用时尚词典中的一个或多个单词拼接出s，从而确定这套搭配是否可行！

注意：

不要求必须使用wordDict里的所有单词。
允许重复使用wordDict里的单词。

输入

单词s，表示一整套穿搭描述。

字符串列表wordDict，包含多个时尚单词，长度不超过s的长度。


输出

如果s可以由wordDict里的单词拼接得到，则返回true，否则返回false。

示例：

输入: s = "fashionqueen", wordDict = ["fashion", "ion", "queen"]

输出: true

解释: 返回 true 因为 "fashionqueen" 可以由 "fashion", "ion", "queen"拼接成。

注意，你可以重复使用字典中的单词。


输入样例 1

fashionqueen
fashion
ion
queen
输出样例 1

true
*/

#include <iostream>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

typedef string::const_iterator strCIt;

inline bool ifDictCatS(const string &S,const set<string> &Dict)
{
    if((!S.empty())&&(!Dict.empty()))
    {
        set<strCIt> A;
        do
        {
            auto it=S.begin();
            if(!A.empty())
                it=*A.begin(),A.erase(A.begin());
            for(auto &s:Dict)
                if((size_t)(distance(it,S.end()))>=s.size())
                    if(equal(it,it+(long long)(s.size()),s.begin()))
                    {
                        if((it+=(long long)(s.size()))==S.end())
                            return true;
                        else
                            A.insert(it);
                    }
        }
        while(!A.empty());
    }
    return false;
}

int main()
{
    string s,tmp;
    cin>>s;
    if(!s.empty())
    {
        set<string> wordDict;
        while(cin>>tmp)
            wordDict.insert(tmp);
        if(ifDictCatS(s,wordDict))
            cout<<"true"<<endl;
        else
            cout<<"false"<<endl;
    }
    return 0;
}
