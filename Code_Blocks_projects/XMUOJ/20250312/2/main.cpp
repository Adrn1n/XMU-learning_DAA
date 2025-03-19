/*
连招顺序

描述

在《王者荣耀》的战场中，每位英雄都有特定的技能连招顺序。​为了探索不同的技能组合效果，现给定一个只包含技能伤害数值和连招符号（+、-、*）的字符串，表示英雄的一套技能连招顺序。​请你为该连招顺序添加括号，以改变其运算优先级，计算出所有可能的组合结果。​有效的连招符号包含加法（+）、减法（-）以及乘法（*）。

输入

输入为一行字符串

输出

输出为所有可能的结果，每个一行，从小到大排列

输入样例 1

2-1-1

输出样例 1

0
2


*/

#include <iostream>
#include <string>
#include <stack>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long valT;
typedef string::const_iterator cStrIt;

typedef struct recurStrNode_
{
    const string s;
    cStrIt it;
} recurStrNode;

typedef enum IDs_op_ {ERROR,add,subtract,times} IDs_op;

inline IDs_op getOpRes(cStrIt &Start,cStrIt &End,string &res)
{
    IDs_op op=ERROR;
    if((Start<End)&&(((*Start>='0')&&(*Start<='9'))||((Start<(End-1))&&((*Start=='+')||(*Start=='-'))&&(*(Start+1)>='0')&&(*(Start+1)<='9'))))
    {
        valT a=stoll(string(Start,End)),b=0;
        auto opPos=Start;
        for(++Start; Start<End; ++Start)
            if((*Start<'0')||(*Start>'9'))
            {
                if(op==ERROR)
                {
                    opPos=Start++;
                    if((Start<End)&&(((*Start>='0')&&(*Start<='9'))||((Start<(End-1))&&((*Start=='+')||(*Start=='-'))&&(*(Start+1)>='0')&&(*(Start+1)<='9'))))
                    {
                        b=stoll(string(Start,End));
                        switch(*(Start-1))
                        {
                        case '+':
                        {
                            op=add;
                            a+=b;
                            break;
                        }
                        case '-':
                        {
                            op=subtract;
                            a-=b;
                            break;
                        }
                        case '*':
                        {
                            op=times;
                            a*=b;
                            break;
                        }
                        default:
                            return op;
                        }
                    }
                    else
                        return op;
                }
                else
                    break;
            }
        if(op==ERROR)
            op=add;
        res=to_string(a),End=Start,Start=opPos;
    }
    return op;
}

inline set<valT> getCalResAll_set(const string &S)
{
    set<valT> resSet= {};
    if(!S.empty())
    {
        stack<string> expriStack;
        stack<cStrIt> itStack;
        do
        {
            string s,res;
            cStrIt Start,Start1,End,End1,Front;
            if(expriStack.empty())
                s=S,Front=S.begin(),End=End1=S.end();
            else
                s=expriStack.top(),Front=(expriStack.top()).begin(),End=End1=(expriStack.top()).end();
            bool flag=true;
            if(expriStack.size()==itStack.size())
                if(expriStack.empty())
                    Start=Start1=S.begin();
                else
                    Start=Start1=(expriStack.top()).begin();
            else
                Start=Start1=itStack.top(),itStack.pop(),flag=false;
            if(getOpRes(Start,End,res)!=ERROR)
                if((Start==Start1)&&(End==End1))
                {
                    if(flag)
                        resSet.insert(stoll(res));
                    if(!expriStack.empty())
                        expriStack.pop();
                }
                else
                    itStack.push(Start+1),s.replace(s.begin()+(Start1-Front),s.begin()+(End-Front),res),expriStack.push(s);
            else
                return {};
        }
        while(!itStack.empty());
    }
    return resSet;
}

inline IDs_op getOp(cStrIt &Start,const cStrIt &End)
{
    IDs_op op=ERROR;
    if((Start<End)&&(((*Start>='0')&&(*Start<='9'))||((Start<(End-1))&&((*Start=='+')||(*Start=='-'))&&((*(Start+1)>='0')&&(*(Start+1)<='9')))))
    {
        for(++Start; Start<End; ++Start)
            if((*Start<'0')||(*Start>'9'))
            {
                if((++Start<End)&&(((*Start>='0')&&(*Start<='9'))||((Start<(End-1))&&((*Start=='+')||(*Start=='-'))&&((*(Start+1)>='0')&&(*(Start+1)<='9')))))
                {
                    switch(*(Start-1))
                    {
                    case '+':
                    {
                        op=add;
                        break;
                    }
                    case '-':
                    {
                        op=subtract;
                        break;
                    }
                    case '*':
                    {
                        op=times;
                        break;
                    }
                    default:
                        return op;
                    }
                }
                else
                    return op;
                break;
            }
        if(op==ERROR)
            op=add;
    }
    return op;
}

inline bool recurPushStrStack(const cStrIt Start,const cStrIt End,stack<recurStrNode> &Stack)
{
    if(Start<End)
    {
        Stack.push({string(Start,End),}),(Stack.top()).it=((Stack.top()).s).begin();
        return true;
    }
    else
        return false;
}

inline bool mergeRes(const vector<valT> &lRes,const vector<valT> &rRes,const IDs_op op,vector<valT> &Res)
{
    if((!lRes.empty())&&(!rRes.empty()))
    {
        for(auto &l:lRes)
            for(auto &r:rRes)
                switch(op)
                {
                case add:
                {
                    Res.push_back(l+r);
                    break;
                }
                case subtract:
                {
                    Res.push_back(l-r);
                    break;
                }
                case times:
                {
                    Res.push_back(l*r);
                    break;
                }
                default:
                    return false;
                }
        return true;
    }
    else
        return false;
}

inline vector<valT> getCalResAll_vec(const string &S)
{
    vector<valT> Res;
    if(!S.empty())
    {
        IDs_op op=ERROR;
        bool flag=true;
        for(auto it=S.begin(),End=S.end(); it<End; flag=false)
            if((op=getOp(it,End))!=ERROR)
                if(it==End)
                {
                    if(flag)
                        Res.push_back(stoll(S));
                    break;
                }
                else
                {
                    stack<recurStrNode> lExpriStack,rExpriStack;
                    stack<vector<valT>> lValsStack,rValsStack;
                    stack<IDs_op> opStack;
                    if(recurPushStrStack(S.begin(),it-1,lExpriStack)&&recurPushStrStack(it,S.end(),rExpriStack))
                    {
                        opStack.push(op),lValsStack.emplace(),rValsStack.emplace();
                        while(!rExpriStack.empty())
                        {
                            auto &l_expri=(lExpriStack.top()).s,&r_expri=(rExpriStack.top()).s;
                            auto l_it=(lExpriStack.top()).it,r_it=(rExpriStack.top()).it;
                            if(l_it==(l_expri.end()))
                                if(r_it==(r_expri.end()))
                                {
                                    vector<valT> l_vals=lValsStack.top(),r_vals=rValsStack.top();
                                    op=opStack.top(),lExpriStack.pop(),rExpriStack.pop(),opStack.pop(),lValsStack.pop(),rValsStack.pop();
                                    if(rExpriStack.empty())
                                    {
                                        if(!mergeRes(l_vals,r_vals,op,Res))
                                            return {};
                                    }
                                    else
                                    {
                                        if((rExpriStack.top()).it==((rExpriStack.top()).s).begin())
                                        {
                                            if(!mergeRes(l_vals,r_vals,op,lValsStack.top()))
                                                return {};
                                        }
                                        else
                                        {
                                            if(!mergeRes(l_vals,r_vals,op,rValsStack.top()))
                                                return {};
                                        }
                                    }
                                }
                                else
                                {
                                    if((op=getOp((rExpriStack.top()).it,r_expri.end()))!=ERROR)
                                        if((rExpriStack.top()).it==r_expri.end())
                                        {
                                            if(r_it==(r_expri.begin()))
                                                (rValsStack.top()).push_back(stoll(r_expri));
                                        }
                                        else
                                        {
                                            r_it=(rExpriStack.top()).it;
                                            if(recurPushStrStack(r_expri.begin(),r_it-1,lExpriStack)&&recurPushStrStack(r_it,r_expri.end(),rExpriStack))
                                                opStack.push(op),lValsStack.emplace(),rValsStack.emplace();
                                            else
                                                return {};
                                        }
                                    else
                                        return {};
                                }
                            else
                            {
                                if((op=getOp((lExpriStack.top()).it,((lExpriStack.top()).s).end()))!=ERROR)
                                    if((lExpriStack.top()).it==l_expri.end())
                                    {
                                        if(l_it==(l_expri.begin()))
                                            (lValsStack.top()).push_back(stoll(l_expri));
                                    }
                                    else
                                    {
                                        l_it=(lExpriStack.top()).it;
                                        if(recurPushStrStack(l_expri.begin(),l_it-1,lExpriStack)&&recurPushStrStack(l_it,l_expri.end(),rExpriStack))
                                            opStack.push(op),lValsStack.emplace(),rValsStack.emplace();
                                        else
                                            return {};
                                    }
                                else
                                    return {};
                            }
                        }
                    }
                    else
                        return {};
                }
            else
                return {};
        sort(Res.begin(),Res.end());
    }
    return Res;
}

int main()
{
    string S;
    cin>>S;
    auto Res_set=getCalResAll_set(S); // 测试答案要求带有按操作符考虑的重数, 故不可用; 在此做不计重数的比对, 以验证此算法的正确性
    auto Res_vec=getCalResAll_vec(S);
    set<valT> Res_vec2set(Res_vec.begin(),Res_vec.end());
    if(Res_set==Res_vec2set)
        for(auto &val:Res_vec)
            cout<<val<<endl;
    else
        cout<<ERROR<<endl;
    return 0;
}
