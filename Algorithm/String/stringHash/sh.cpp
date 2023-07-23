//自然溢出法，字符串哈希
//luogu P3370
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

using LL = long long;
using ULL = unsigned long long;
using i128 = __int128;
using pii = std::pair<int,int>;
using pll = std::pair<LL,LL>;

int const MAXN = 200005;
int const INF = 0x7fffffff;
double const EPS = 1e-8;
int const MOD = 998244353;
double const PI = acos(-1);

ULL arr[MAXN];

ULL H(std::string const & str){
    ULL ret = 0;
    ULL const base = 131;
    
    for(auto c:str){
        ret = ret*base+(ULL)c;
    }
    return ret;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int n;
    std::cin>>n;
	std::string str;
	for(int i=1;i<=n;i++){
	    std::cin>>str;
	    arr[i] = H(str);
	}
	std::sort(arr+1,arr+1+n);
	
	int ans = 1;
	for(int i=2;i<=n;i++){
	    if(arr[i]!=arr[i-1]) ans++;
	}
	std::cout<<ans<<"\n";
	
	
    return 0;
}
