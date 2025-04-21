/*
潮汐之力

描述

在鸣潮的传说中，每一枚数字符文都蕴含着潮汐的力量。传说只有把这些符文按照巧妙的顺序连接起来，才能召唤出那最强大的潮汐之力，而这股力量必须是 3 的倍数，才能激起涌动的梦幻浪潮。
给你一个整数数组digits，你可以按任意顺序选取其中某些符文，将它们连接起来形成一个数字。请你返回能够形成的最大的 3 的倍数的数字（以字符串形式返回）。
注意：

    如果无法形成 3 的倍数，请返回空字符串。

    返回的结果不应包含不必要的前导零。

输入

输入为一行由空格分隔的整数，表示每个数字符文的取值。

输出

输出为一个字符串，表示能形成的最大的 3 的倍数。如果无法形成，则输出空字符串。注意不要输出多余的前导零。

示例 1：

输入：digits = [8,1,9]
输出："981"

示例 2：

输入：digits = [8,6,7,1,0]
输出："8760"

示例 3：

输入：digits = [1]
输出：""

示例 4：

输入：digits = [0,0,0,0,0,0]
输出："0"

输入样例 1

8 1 9

输出样例 1

981

来源

xmu

温馨提示

实在搞不定的话，你可以 点此下载测试数据 (./problem_5301_test_cases.zip)
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

typedef long long valT;
typedef short restT;

typedef struct nodeT_
{
    string val;
    restT rest;
    bool flag;
} nodeT;

inline string buildRes_nodeArr(const vector<nodeT> &A)
{
    string res;
    for(auto it=A.begin(); it<A.end(); ++it)
        if(it->flag)
        {
            if((res.empty())&&(!stoll(it->val)))
            {
                res="0";
                break;
            }
            else
                res+=it->val;
        }
    return res;
}

inline string getMax_numDiv3InVec_nOrd(const vector<valT> &A)
{
    string res;
    if(!A.empty())
    {
        vector<nodeT> Arr;
        restT Rest=0;
        for(auto it=A.begin(); it<A.end(); ++it)
            if(*it>=0)
            {
                string val;
                restT rest=0;
                for(valT a=*it,tmp=0; a>0; a/=10)
                    val+=(char)('0'+(tmp=a%10)),rest=(restT)((rest+tmp)%3);
                if(val.empty())
                    val="0";
                reverse(val.begin(),val.end()),Rest=(restT)((Rest+rest)%3);
                Arr.push_back({val,rest,true});
            }
        if(!Arr.empty())
        {
            sort(Arr.begin(),Arr.end(),[](const nodeT &a,const nodeT &b)
            {
                return a.val>b.val;
            });
            if(!Rest)
                res=buildRes_nodeArr(Arr);
            else
            {
                bool flag=false;
                auto it=Arr.rbegin();
                for(; it<Arr.rend(); ++it)
                    if(it->rest==Rest)
                    {
                        it->flag=false,flag=true;
                        break;
                    }
                if(flag)
                    res=buildRes_nodeArr(Arr),it->flag=true,it=Arr.rbegin(),flag=false;
                for(restT cnt=0; it<Arr.rend(); ++it)
                    if(it->rest==(3-Rest))
                    {
                        if(cnt)
                        {
                            it->flag=false,flag=true;
                            break;
                        }
                        else
                            it->flag=false,cnt=1;
                    }
                if(flag)
                    res=max(res,buildRes_nodeArr(Arr));
            }
        }
    }
    return res;
}

int main()
{
    valT val=0;
    vector<valT> digits;
    while(cin>>val)
        digits.push_back(val);
    cout<<getMax_numDiv3InVec_nOrd(digits)<<endl;
    return 0;
}
