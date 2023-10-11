//luogu P1115
//复杂度 n
//求一个数组里面最大连续子段的和，可以为空，此时和为0
//如果要保证非空，则可以在外部加一条
//ans = std::max(ans, arr[i]);
//并且如果每个数都是负数，则直接输出最大的负数。
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

LL calc(std::vector<LL> const & vec){
    LL ret=0;
    LL cur=0;
    for(int i=0;i<vec.size();i++){
        cur += vec[i];
        if(cur<0) cur = 0;
        ret = std::max(ret, cur);
    }
    return ret;
}

void solve(){
    int n;
    std::cin>>n;
    std::vector<LL> vec(n);
    LL ans = -1e15;
    for(int i=0;i<n;i++){
        std::cin>>vec[i];
        ans = std::max(ans,vec[i]);
    }
    if(ans<0){
        std::cout<<ans<<"\n";
        return;
    }
    ans = std::max(ans, calc(vec));
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
