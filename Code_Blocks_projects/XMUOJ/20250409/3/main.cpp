/*
找零

描述

在《江南百景图》中，你是茶铺的掌柜，售卖每杯花柠茶，每杯价格为 5 铜钱。
百姓络绎不绝地来购买，每人只买一杯，但付的铜钱可能是 5、10 或 20。

你一开始没有任何零钱，只能用顾客之前支付的零钱来找零。

若你能为所有人成功找零，返回true，否则返回false。

输入

第一行为N，表示有N名顾客向你购买柠檬水。

第二行为N个数字，表示每个顾客像你支付的金额

输出

如果你能给每位顾客正确找零，返回 true ，否则返回 false。

输入样例 1

5
5 5 5 10 20

输出样例 1

true

输入样例 2

2
10 10

输出样例 2

false

来源

xmu

温馨提示

实在搞不定的话，你可以 点此下载测试数据 (./problem_5271_test_cases.zip)
*/

#include <iostream>
#include <vector>
#include <map>

#define PRICE 5

using namespace std;

typedef long long idxT;
typedef short valT;
typedef map<valT,idxT> walletT;

const valT AllPays[3]= {5,10,20};

inline bool makeBestChange(walletT &wallet,valT val)
{
    for(auto it=wallet.rbegin(); (it!=wallet.rend())&&(val>0); ++it)
        if(((it->first)<=val)&&((it->second>0)))
            val-=(it->first),--(it->second);
    return !val;
}

inline bool can_makeChangeAll(const vector<valT> &Pays,const valT price)
{
    if(Pays.empty())
        return true;
    else
    {
        walletT Wallet;
        bool flag=true;
        for(auto &pay:Pays)
        {
            ++Wallet[pay];
            auto rest=(valT)(pay-price);
            if(rest>0)
            {
                if(!(flag=makeBestChange(Wallet,rest)))
                    break;
            }
            else if(rest<0)
            {
                flag=false;
                break;
            }
        }
        return flag;
    }
}

int main()
{
    idxT N=0;
    cin>>N;
    bool flag=true;
    if(N>0)
    {
        vector<valT> Pays(N);
        for(auto &a:Pays)
        {
            cin>>a;
            if((a!=*AllPays)&&(a!=AllPays[1])&&(a!=AllPays[2]))
            {
                flag=false;
                break;
            }
        }
        if(flag)
        {
            flag=false;
            if(can_makeChangeAll(Pays,PRICE))
                cout<<"true"<<endl;
            else
                cout<<"false"<<endl;
        }
        else
            flag=true;
    }
    if(flag)
        cout<<"ERROR!"<<endl;
    return 0;
}
