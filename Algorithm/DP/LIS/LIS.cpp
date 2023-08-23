//最长上升子序列 复杂度nlogn
//luogu B3637
#include <iostream>
#include <algorithm>
#include <cstring>

const int MAXN = 100005;

int arr[MAXN];
int dp[MAXN];
//dp[i]表示长度为i的上升子序列的最后一个元素的最小值
//例如1 2 5 3 4 1。
//最开始dp[1]=1，arr[2]=2>dp[1]，所以插入dp[2]=2;arr[3]同理，得到dp={1,2,5};到arr[4]=3时，我们找到第一个大于等于3的元素，即dp[3]，替换他，得到dp={1,2,3};接下来到arr[5]=4，现在4>3，可以插入末尾得到dp={1,2,3,4}，显然我们刚刚的操作把5换成3，让后面的数更有可能直接加入到数组末尾了。最后arr[6]=1，由于我们求的是最长上升子序列，而不是最长不下降，所以替换不影响。
//注意dp里面的数字并不是最长的序列，例如我们加一个0进去，dp={0,2,3,4}，但是0是在最后的，不存在0,2,3,4这个序列。我们只能计算长度。

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    
    int n;
    std::cin>>n;
    for(int i=1;i<=n;i++){
        std::cin>>arr[i];
    }
    
    std::memset(dp,0x3f,sizeof(dp));
    
    int maxv = dp[0];
    for(int i=1;i<=n;i++){
        *std::lower_bound(dp,dp+n,arr[i]) = arr[i];
        //换成最长不下降子序列时，用upper_bound
    }
    int ans = 0;
    while(dp[ans]!=maxv) ans++;
    std::cout<<ans<<"\n";

    return 0;
}
