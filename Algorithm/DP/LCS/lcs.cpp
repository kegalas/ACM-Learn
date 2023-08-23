//最长公共子序列，复杂度nm
//hdu 1159
//luogu p1439因为是排列，可以转化为LIS问题，复杂度是nlogn。但hdu1159没有这种性质，复杂度到不了nlogn
#include <iostream>
#include <cstring>
#include <string>
#define MAXN 505

int dp[MAXN][MAXN];

int lcs(std::string const & s1, std::string const & s2){
    int n1=s1.size(),n2=s2.size();
    std::memset(dp,0,sizeof(dp));
    
    for(int i=1;i<=n1;i++){
        for(int j=1;j<=n2;j++){
            if(s1[i-1]==s2[j-1])
                dp[i][j] = dp[i-1][j-1]+1;
            else
                dp[i][j] = std::max(dp[i][j-1],dp[i-1][j]);
        }
    }
    return dp[n1][n2];
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    
    std::string s1,s2;
    
    while(std::cin>>s1>>s2){
        std::cout<<lcs(s1,s2)<<"\n";
    }
    
    return 0;
}


