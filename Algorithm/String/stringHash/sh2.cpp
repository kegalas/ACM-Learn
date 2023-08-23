//双哈希法，两个字符串的两个哈希必须分别相同，才会被考虑为相同的字符串
//比起单哈希，更不容易被卡
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

double const PI = acos(-1);

ULL const MOD1 = 998244353;
ULL const MOD2 = 1e9+7;
ULL const base = 131;

struct Data{//把字符串的两个哈希捆起来，便于排序比较等操作
    ULL x,y;
};

ULL H1(std::string const & str){
    ULL ret = 0;
    for(auto c:str){
        ret = (ret*base+(ULL)c)%MOD1;
    }
    return ret;
}

ULL H2(std::string const & str){
    ULL ret = 0;
    for(auto c:str){
        ret = (ret*base+(ULL)c)%MOD2;
    }
    return ret;
}

bool cmp(Data a, Data b){
    return a.x<b.x;
}

Data data[MAXN];

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

	int n;
	std::cin>>n;
	std::string str;
	for(int i=1;i<=n;i++){
	    std::cin>>str;
	    data[i] = {H1(str),H2(str)};
	}
	std::sort(data+1,data+1+n,cmp);
	
	int ans = 1;
	for(int i=2;i<=n;i++){
	    if(data[i].x!=data[i-1].x || data[i].y!=data[i-1].y){
	        ans ++;
	    }
	}
	std::cout<<ans<<"\n";

    return 0;
}
