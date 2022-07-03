#include <iostream>
#include <cstdio>
#include <algorithm>

const int MAXN = 100005;

int arr[MAXN];
int dp[MAXN];
int len;

int main(){
    freopen("in.in","r",stdin);
    int cnt = 0;
    while(scanf("%d",&arr[++cnt])!=EOF){

    }
    cnt--;

    len = 1;
    dp[1] = arr[1];

    for(int i=2;i<=cnt;i++){//最长不上升
        if(arr[i]<=dp[len]) dp[++len] = arr[i];
        else{
            int j = std::upper_bound(dp+1,dp+len+1,arr[i],std::greater<int>())-dp;
            dp[j] = arr[i];
        }
    }

    std::cout<<len<<std::endl;

    len = 1;
    dp[1] = arr[1];

    for(int i=2;i<=cnt;i++){//最长上升
        if(arr[i]>dp[len]) dp[++len] = arr[i];
        else{
            int j = std::lower_bound(dp+1,dp+len+1,arr[i])-dp;
            dp[j] = arr[i];
        }
    }

    std::cout<<len<<std::endl;

    return 0;
}
