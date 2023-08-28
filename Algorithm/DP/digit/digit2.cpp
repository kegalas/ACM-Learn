//数位dp另一例
//atcoder abc317_f
//本题给定n,a1,a2,a3。要求求三元组<x1,x2,x3>的个数，满足
//1. 1<=xi<=n，对所有i
//2. xi是ai的任意倍数，对所有i
//3. x1^x2^x3=0
//其中n取值[1,1e18]
//ai取值[1,10]

#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>

#define pb push_back
using LL = long long;
LL const MOD = 998244353;

std::vector<int> digit;
int dp[80][12][12][12][2][2][2][2][2][2];
int a1,a2,a3;

int dfs(int pos, int r1, int r2, int r3,
        bool l1, bool l2, bool l3,
        bool z1, bool z2, bool z3){
    //分布代表着，pos位数字，上一位搜索到的x1除以a1的余数,...,x1的limit,...,x1是否前面全是前导0
    int ret = 0;
    if(pos==-1){
        return !z1 && !z2 && !z3 && !r1 && !r2 && !r3;
        //每个数都没有前导零（即填入了至少一个数字），以及余数都是0（即xi已经是ai的倍数了）
    }
    if(dp[pos][r1][r2][r3][l1][l2][l3][z1][z2][z3] != -1) return dp[pos][r1][r2][r3][l1][l2][l3][z1][z2][z3];
    
    int m1 = l1 ? digit[pos] : 1;
    int m2 = l2 ? digit[pos] : 1;
    int m3 = l3 ? digit[pos] : 1;
    
    for(LL i=0;i<=m1;i++){
        for(LL j=0;j<=m2;j++){
            for(LL k=0;k<=m3;k++){
                if((i^j^k)!=0) continue;
                
                int newr1 = ((LL)r1+(i<<pos))%a1;//计算新的余数
                int newr2 = ((LL)r2+(j<<pos))%a2;
                int newr3 = ((LL)r3+(k<<pos))%a3;
                
                ret = (ret + dfs(pos-1,newr1,newr2,newr3,
                l1&&i==digit[pos], l2&&j==digit[pos],l3&&k==digit[pos],
                z1&&i==0,z2&&j==0,z3&&k==0))%MOD;
            }
        }
    }
    
    dp[pos][r1][r2][r3][l1][l2][l3][z1][z2][z3] = ret;
    return ret;
}

int getSum(LL x){
    digit.clear();
    std::memset(dp,-1,sizeof(dp));
    while(x){
        digit.pb(x%2);
        x/=2;
    }//本题低位到高位存更方便，方便移位运算
    return dfs(digit.size()-1,0,0,0,1,1,1,1,1,1);
}

void solve(){
    LL n;
    std::cin>>n>>a1>>a2>>a3;
    std::cout<<getSum(n)<<"\n";
}

signed main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

	solve();

    return 0;
}
