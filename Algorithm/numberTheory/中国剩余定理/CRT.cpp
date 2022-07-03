#include <iostream>

using namespace std;

typedef long long ll;

const int MAXN = 10005;

long long a[MAXN],r[MAXN];

long long exgcd(ll a, ll b, ll &x, ll &y){
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

int main(){
    int k;
    cin>>k;
    for(int i=1;i<=k;i++){
        cin>>a[i]>>r[i];
    }
    ll n=1,ans=0;
    for(int i=1;i<=k;i++){
        n = n * r[i];
    }
    for(int i=1;i<=k;i++){
        ll m = n/r[i];
        ll x,y;
        exgcd(m,r[i],x,y);
        ans = (ans+a[i]*m*x%n)%n;
    }
    cout<<ans<<endl;
    return 0;
}
