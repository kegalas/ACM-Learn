//乘法逆元
//分为扩展欧几里得法、快速幂法、线性求逆元
//ax≡1(mod b)，x为a在乘法意义上的逆元，记作a^(-1)，或者inv(a)
//用扩展欧几里得法的角度看，就是求ax+by=1的整数解
//快速幂法利用费马小定理，需要b为素数

#include <iostream>
#include <cstdio>

using namespace std;

const int MAXN = 3000005;

int exgcd(int a, int b, int &x, int &y){
    if(!b){
        x=1;
        y=0;
        return a;
    }
    int d = exgcd(b,a%b,x,y);
    int tmp = x;
    x = y;
    y = tmp - a/b*y;
    return d;   
}

void exgcd_inv(int a, int b){
    int x,y;
    int d = exgcd(a,b,x,y);
    if(d!=1){//显然a，b要互质才会有逆元
        cout<<"None"<<endl;
    }
    else{
        cout<<(x+b)%b<<endl;//实际上是为了防止出现x为负数的情况
    }
}

int qPowMod(int a, int n, int b){
    int ans = 1;
    while(n){
        if(n&1){
            ans = ans%b*a%b;
        }
        a = a%b*a%b;
        n>>=1;
    }
    return ans;
}

void fermat_inv(int a, int b){
    cout<<qPowMod(a,b-2,b)<<endl;
}

long long inv[MAXN];

int main(){
    long long a,b,n;
    cin>>a>>b;
    exgcd_inv(a,b);
    //fermat_inv(a,b);

    /*
    //线性求逆元
    inv[1] = 1;
    for(long long i = 2;i<=n;i++){
        //inv[i] = -(b/i)*inv[b%i]; //这样写会出现负数
        inv[i] = (long long)(b-b/i)*inv[b%i]%b;
    }
    for(long long i=1;i<=n;i++){
        printf("%lld\n",inv[i]);
    }
    */



    return 0;
}
