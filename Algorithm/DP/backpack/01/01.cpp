#include <iostream>
#include <cmath>

#define MAXN 5005


using namespace std;

int dp[MAXN][MAXN];
int w[MAXN];
int v[MAXN];

int main(){
    int n,W;
    cin>>n>>W;
    for(int i=1;i<=n;i++){
        cin>>w[i]>>v[i];
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=W;j++){
            if(j<w[i]){
                dp[i][j]=dp[i-1][j];
            }
            else{
                dp[i][j]=max(dp[i-1][j],dp[i-1][j-w[i]]+v[i]);
            }
        }
    }
    cout<<dp[n][W]<<endl;
    return 0;

}

