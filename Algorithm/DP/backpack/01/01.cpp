//复杂度 nW
//luogu P1048
#include <iostream>
#include <cmath>

int const MAXN = 1005;

using namespace std;

int dp[MAXN];
int w[MAXN];
int v[MAXN];

int main(){
    int n,W;//物品数，背包大小
    cin>>W>>n;
    for(int i=1;i<=n;i++){
        cin>>w[i]>>v[i];//物品体积，物品价值
    }
    for(int i=1;i<=n;i++){
        for(int j=W;j>=w[i];j--){
			dp[j] = std::max(dp[j],dp[j-w[i]]+v[i]);
        }
    }
    cout<<dp[W]<<endl;
    return 0;

}

