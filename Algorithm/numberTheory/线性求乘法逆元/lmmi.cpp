//线性求逆元，对于1~n这些数，复杂度总共n
//luogu p3381, loj 110
#include <iostream>

using LL = long long;

int const MAXN = 3000005;
LL inv[MAXN];

void getinv(LL n, LL m){
    //求1~n中，每个数在模m意义下的乘法逆元
    inv[1] = 1;
    for(LL i=2;i<=n;i++){
        //inv[i] = -(b/i)*inv[b%i]; //这样写会出现负数
        inv[i] = (LL)(m-m/i)*inv[m%i]%m;
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    LL n, p;
    std::cin>>n>>p;
    getinv(n,p);
    for(int i=1;i<=n;i++){
        std::cout<<inv[i]<<"\n";
    }

    return 0;
}
