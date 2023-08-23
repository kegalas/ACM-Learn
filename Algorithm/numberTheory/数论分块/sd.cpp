//UVA 11526
//数论分块模板 复杂度sqrt n
//要求计算i=1~n, ans = ans+n/i
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
#define mkp make_pair
#define fi first
#define se second

using LL = long long;
using ULL = unsigned long long;
using LD = long double;
using uint = unsigned;
using i128 = __int128;
using pii = std::pair<int,int>;
using pll = std::pair<LL,LL>;

int const MAXN = 200005;
int const INF = 0x7fffffff;
double const EPS = 1e-8;
int const MOD = 998244353;
double const PI = acos(-1);

int arr[MAXN];

void solve(){
    LL n;
    std::cin>>n;
    LL ans = 0;
    
    LL l = 1, r = 0;
    
    while(l<=n){
        r = n/(n/l);
        ans += (r-l+1) * (n/l);
        l = r+1;  
    }
    std::cout<<ans<<"\n";
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

	int T;
	std::cin>>T;
	//T=1;
	while(T--){
	    solve();
	}

    return 0;
}
