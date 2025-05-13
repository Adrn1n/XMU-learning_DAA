/*
符文解码

描述

在王者峡谷中，法师女英雄“上官婉儿”偶然发现了一串神秘的通信符文。这些符文由数字 2~9 组成，疑似是远古荣耀神殿之间用于传递密令的方式。每个数字对应一些特定的字母（与现实中老式电话按键上的字母相同），而真正的密令隐藏在所有可能的字母组合中。

你作为辅助婉儿的召唤师，需要帮她破解这些通信符文，列出它可能代表的所有字母组合。

200px-telephone-keypad2svg.png (./9210a38a78.png)

输入

一个仅包含数字2到9的字符串，长度不超过 4。

输出

按任意顺序输出所有可能的字母组合，组合之间用空格分隔。

输入样例 1

23

输出样例 1

ad ae af bd be bf cd ce cf

来源

xmu

温馨提示

实在搞不定的话，你可以 点此下载测试数据 (./problem_5335_test_cases.zip)
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define MAX_LEN 4

using namespace std;

typedef short idxT;
typedef char valT;
typedef short cntT;

typedef vector<valT> valVec;

const vector<valVec> Dict= {{},{'a','b','c'},{'d','e','f'},{'g','h','i'},{'j','k','l'},{'m','n','o'},{'p','q','r','s'},{'t','u','v'},{'w','x','y','z'}};

inline vector<idxT> str2idxVec(const string &S)
{
    vector<idxT> A;
    for(auto &c:S)
        A.push_back((valT)(c-'0'));
    return A;
}

inline cntT repeatValVec(vector<valVec> &A,const cntT k)
{
    cntT cnt=0;
    auto len=A.size();
    while(++cnt<k)
//        A.insert(A.end(),A.begin(),A.begin()+(_Bit_const_iterator::difference_type)len); // macOS 和 Linux 都可按照意思正确执行, 但是 Windows 就不行; OJ 提交错误也应该与此有关
        for(size_t i=0; i<len; ++i)
            A.push_back(A[i]);
    return cnt;
}

inline vector<valVec> getAll_posiCombine(const vector<idxT> &A)
{
    vector<valVec> Res;
    for(auto it=A.rbegin(); it<A.rend(); ++it)
        if(((*it)>0)&&((*it<=9)))
        {
            auto len=Res.size();
            if(len>0)
            {
                repeatValVec(Res,(cntT)(Dict[(*it)-1].size()));
                for(cntT i=0; (size_t)i<Dict[(*it)-1].size(); ++i)
                    for(auto j=0; (size_t)j<len; ++j)
                        Res[i*len+j].push_back(Dict[(*it)-1][i]);
            }
            else
                for(cntT i=0; (size_t)i<Dict[(*it)-1].size(); ++i)
                    Res.push_back({Dict[*(it)-1][i]});
        }
    for(auto &res:Res)
        reverse(res.begin(),res.end());
    return Res;
}

int main()
{
    string S;
    while(cin>>S)
        if(S.size()<=MAX_LEN)
            break;
        else
            cout<<"ERROR!"<<endl;
    auto A=str2idxVec(S);
    auto Res=getAll_posiCombine(A);
    for(auto &res:Res)
    {
        for(auto &c:res)
            cout<<c;
        cout<<' ';
    }
    cout<<endl;
    return 0;
}
