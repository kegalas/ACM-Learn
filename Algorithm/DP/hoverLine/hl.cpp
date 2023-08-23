//luogu p1387
//悬线法求最大矩形/正方形，复杂度 nm
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
#include <deque>
#include <regex>
#include <unordered_map>
#include <unordered_set>

#define debug(a) std::cout<<#a<<"="<<a<<std::endl
#define lth(i,x,y) for(int i=x;i<=y;i++)
#define htl(i,x,y) for(int i=x;i>=y;i--)
#define mms(x) memset(x, 0, sizeof(x))
#define pb push_back
#define mkp std::make_pair
#define fi first
#define se second

using LL = long long;
using ULL = unsigned long long;
using LD = long double;
using uint = unsigned;
using i128 = __int128;
using pii = std::pair<int,int>;
using pll = std::pair<LL,LL>;

int const MAXN = 105;
int const INF = 0x7fffffff;
double const EPS = 1e-8;
int const MOD = 998244353;
double const PI = acos(-1);

int grid[MAXN][MAXN];
int l[MAXN][MAXN], r[MAXN][MAXN], u[MAXN][MAXN];
//l,r分别表示从当前格向上的悬线最多能向左向右扩展多少格（含自己）
//u表示当前格向上能扩展多少格（含自己），即悬线
int ans = 0;

void dp(int n, int m){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(grid[i][j]) l[i][j] = l[i][j-1]+1;//这里的条件看情况选择，下面同理
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=m;j>=1;j--){
            if(grid[i][j]) r[i][j] = r[i][j+1]+1;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(grid[i][j]){
                u[i][j] = u[i-1][j]+1;
                if(grid[i-1][j]){
                    l[i][j] = std::min(l[i][j], l[i-1][j]);
                    r[i][j] = std::min(r[i][j], r[i-1][j]);
                }
                //然后在这里对ans进行该有的操作，因题而异
                ans = std::max(ans,std::min(u[i][j], l[i][j]+r[i][j]-1));
            }
        }
    }
}

void solve(){
    int n,m;
    std::cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            std::cin>>grid[i][j];
        }
    }
    dp(n,m);
    std::cout<<ans<<"\n";
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

	int T;
	T=1;
	while(T--){
	    solve();
	}

    return 0;
}
