//luogu P1776
#include <iostream>
#include <cmath>

int const MAXN = 100007;
int const MAXW = 40007;
typedef long long LL;

using namespace std;

LL dp[MAXW];
int w[MAXN];
int v[MAXN];

int main(){
    int m,W;//物品种类数，背包大小
    cin>>m>>W;
    int n = 0;
    for(int i=1;i<=m;i++){
        int c = 1;
        int p,h,k;//物品价值，物品体积，物品数量
        cin>>p>>h>>k;
        while(k>c){
            k -= c;
            v[++n] = c*p;
            w[n] = c*h;
            c *= 2;
        }
        v[++n] = p*k;
        w[n] = h*k;
    }
    for(int i=1;i<=n;i++){
	    for(int j=W;j>=w[i];j--){
	        dp[j] = std::max(dp[j],dp[j-w[i]]+v[i]);
        }
    }
    cout<<dp[W]<<endl;
    return 0;

}
