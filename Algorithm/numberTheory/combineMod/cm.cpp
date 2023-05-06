//复杂度 初始化为nlogn 后续查询为O(1)
#include <iostream>

#define LL long long

const int MAXN = 200005;
const int MOD = 998244353;

LL fac[MAXN];
LL invFac[MAXN];

LL qPowMod(LL a, LL n, LL b){
    LL ans = 1;
    while(n){
        if(n&1){
            ans = ans%b*a%b;
        }
        a = a%b*a%b;
        n>>=1;
    }
    return ans;
}

LL fermat_inv(LL a, LL b){
    return qPowMod(a,b-2,b);
}

void init(int n){
    fac[0] = 1;
    invFac[0] = 1;

    for(int i=1;i<=n;i++){
        fac[i] = (fac[i-1]*i)%MOD;
        invFac[i] = fermat_inv(fac[i],MOD);
    }
}

LL comb(LL n, LL m){
    if(n<0||m<0||m>n) return 0;
    return (((fac[n]*invFac[m])%MOD)*invFac[n-m])%MOD;
}

int main(){
    int n,m;
    std::cin>>n>>m;
    
    init(n);
    
    std::cout<<comb(n,m)<<"\n";

    return 0;
}
