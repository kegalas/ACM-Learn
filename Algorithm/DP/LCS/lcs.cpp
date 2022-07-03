#include <iostream>
#include <cmath>
#include <string>
#define MAXN 5005


using namespace std;

int dp[MAXN][MAXN];
string s,t;

int main(){
    int n,m;
    cin>>n>>m;
    cin>>s;
    cin>>t;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(s[i]==t[j]){
                dp[i+1][j+1] = dp[i][j]+1;
            }
            else{
                dp[i+1][j+1] = max(dp[i+1][j],dp[i][j+1]);
            }
        }
    }
    cout<<dp[n][m]<<endl;
    return 0;
}


