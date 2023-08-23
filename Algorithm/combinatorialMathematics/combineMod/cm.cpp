//复杂度 初始化为nlogn 后续查询为O(1)
//luogu P3414，只能过50%
#include <iostream>

using LL = long long;

const int MAXN = 200005;
const LL MOD = 6662333;

LL fac[MAXN];
LL invFac[MAXN];

LL qPowMod(LL x, LL p, LL m){
    //x^p % m
    LL ans = 1;
    while(p){
        if(p&1){
            ans = (ans*x)%m;
        }
        x = (x*x)%m;
        p>>=1;
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
    //n里面选m个
    if(n<0||m<0||m>n) return 0;
    return (((fac[n]*invFac[m])%MOD)*invFac[n-m])%MOD;
}

int main(){
    int n;
    std::cin>>n;
    init(n);
    LL ans = 0;
    for(int i=0;i<=n;i+=2){
        ans += comb(n,i);
        ans %= MOD;
    }
    std::cout<<ans<<"\n";

    return 0;
}
