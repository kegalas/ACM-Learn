//单调栈 luogu5788
#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <vector>
#include <cstdint>
#include <cstdio>
#include <bitset>

#define LL long long
#define ULL unsigned long long
#define i128 __int128
#define debug(a) std::cout<<#a<<"="<<a<<std::endl
#define lth(i,x,y) for(int i=x;i<=y;i++)
#define htl(i,x,y) for(int i=x;i>=y;i--)
#define mms(x) memset(x, 0, sizeof(x))

const int MAXN = 3000005;
const int INF = 0x7fffffff;
const double EPS = 1e-8;
const int MOD = 998244353;
const double PI = acos(-1);

int arr[MAXN];
int ans[MAXN];
int stk[MAXN];

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int n;
    std::cin>>n;

    for(int i=1;i<=n;i++){
        std::cin>>arr[i];
    }

    int top = 0;

    for(int i=1;i<=n;i++){
        while(top&&arr[stk[top]]<arr[i]){
            ans[stk[top]] = i;
            top--;
        }

        stk[++top] = i;
    }

    for(int i=1;i<=n;i++){
        std::cout<<ans[i]<<" ";
    }

    return 0;
}