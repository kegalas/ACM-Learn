//复杂度logn
//快速幂
//luogu P1226
#include <iostream>

using LL = long long;

LL qPow(LL x, LL p){
    //x^p
    LL res = 1;
    while(p){
        if(p&1){
            res = res * x;
        }
        x *= x;
        p>>=1;
    }
    return res;
}

LL qPowMod(LL x, LL p, LL m){
    //x^p % m
    LL res = 1;
    while(p){
        if(p&1){
            res = (res * x)%m;
        }
        x = (x*x)%m;
        p>>=1;
    }
    return res;
}


int main(){
    LL a,b,p;
    std::cin>>a>>b>>p;
    std::cout<<a<<"^"<<b<<" mod "<<p<<"="<<qPowMod(a,b,p);

    return 0;
}

