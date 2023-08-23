//复杂度 扩展欧几里得法和费马小定理法都是logn
//乘法逆元
//ax≡1(mod b)，x为a在乘法意义上的逆元，记作a^(-1)，或者inv(a)
//用扩展欧几里得法的角度看，就是求ax+by=1的整数解
//快速幂法利用费马小定理，需要b为素数，并且疑似比exgcd常数大
//luogu P3811，会TLE，需要线性求逆元
//但loj 110不会TLE

#include <iostream>
using LL = long long;
#define int LL

int exgcd(int a,int b,int& x,int& y){
    if(b==0){
        x = 1;
        y = 0;
        return a;
    }
    int d = exgcd(b,a%b,y,x);
    y -= (a/b)*x;
    return d;
}

int exgcd_inv(int a, int b){
    //a在模b意义下的逆元
    int x,y;
    int d = exgcd(a,b,x,y);
    if(d!=1){//显然a，b要互质才会有逆元
        return -1;
    }
    else{
        return (x+b)%b;//实际上是为了防止出现x为负数的情况
    }
}

int qPowMod(int x, int p, int mod){
    //x^p % m
    int ans = 1;
    while(p){
        if(p&1){
            ans = (ans*x)%mod;
        }
        x = (x*x)%mod;
        p>>=1;
    }
    return ans;
}

int fermat_inv(int a, int b){//a在模b意义下的逆元
    return qPowMod(a,b-2,b);
}

signed main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    
    int n,p;
    std::cin>>n>>p;
    for(int i=1;i<=n;i++){
        std::cout<<fermat_inv(i,p)<<"\n";
    }

    return 0;
}
