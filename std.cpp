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

#define debug(a) std::cout<<#a<<"="<<(a)<<"\n"
#define rep(i,x,y) for(int i=(x);i<=(y);i++)
#define rrep(i,x,y) for(int i=(x);i>=(y);i--)
#define mms(x) memset((x), 0, sizeof(x))
#define pb push_back
#define mkp std::make_pair
#define fi first
#define se second

using LL = long long;
using ULL = unsigned long long;
using DB = double;
using LD = long double;
using ui = unsigned;
using i128 = __int128;
using pii = std::pair<int,int>;
using pll = std::pair<LL,LL>;

int const MAXN = 200005;
int const INF = 0x7fffffff;
DB const EPS = 1e-8;
int const MOD = 998244353;
DB const PI = acos(-1);

int arr[MAXN];

void solve(){
    int n;
    std::cin>>n;
    for(int i=1;i<=n;i++){
        std::cin>>arr[i];
    }
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
