#include <iostream>
#include <cmath>

#define MAXN 5005



using namespace std;

int dp[MAXN][MAXN];
int w[MAXN],v[MAXN];


int main(){
	int n,W;
	cin>>n>>W;
	
	for(int i=1;i<=n;i++){
		cin>>w[i]>>v[i];
	}
	
	for(int i=0;i<n;i++){
		for(int j=0;j<=W;j++){
			if(j<w[i+1]) dp[i+1][j] = dp[i][j];
			else{
				dp[i+1][j] = max(dp[i][j], dp[i+1][j-w[i+1]]+v[i+1]);
			}
		}
	}
	cout<<dp[n][W]<<endl;
	
	
	
	
    return 0;
}


