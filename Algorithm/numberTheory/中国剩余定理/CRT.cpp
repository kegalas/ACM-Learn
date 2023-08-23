//中国剩余定理 复杂度 klogk
//luogu p1495
#include <iostream>

using namespace std;

typedef long long ll;

const int MAXN = 10005;

ll exgcd(ll a, ll b, ll &x, ll &y){
    if(!b){
        x=1;
        y=0;
        return a;
    }
    ll d = exgcd(b,a%b,x,y);
    ll tmp = x;
    x = y;
    y = tmp - (a/b)*y;
    return d;
}

ll exgcd_inv(ll a, ll b){
    ll x,y;
    ll d = exgcd(a,b,x,y);
    return (x+b)%b;
}

class CRT{
public:
    ll ax[MAXN],rx[MAXN];//每个方程的形式为x≡ai(mod ri)，要求ri互质
    int k=0;//k个方程
    
    void add(ll a, ll r){
        ax[++k] = a;
        rx[k] = r;
    }
    
    ll solve(){
        ll n=1, ans=0;
        for(int i=1;i<=k;i++){
            n = n * rx[i];
        }
        for(int i=1;i<=k;i++){
            ll m = n/rx[i];
            ans = (ans+ax[i]*m*exgcd_inv(m,rx[i]))%n;
        }
        
        return ans;
    }
};

CRT crt;

int main(){
    int k;
    cin>>k;
    for(int i=1;i<=k;i++){
        ll a,r;
        std::cin>>r>>a;
        crt.add(a,r);
    }
    cout<<crt.solve()<<endl;
    return 0;
}
