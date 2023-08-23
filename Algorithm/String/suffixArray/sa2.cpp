//求后缀树组，复杂度O(nlogn)
//luogu p3809
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

int const MAXN = 1000005;
int const INF = 0x7fffffff;
double const EPS = 1e-8;
int const MOD = 998244353;
double const PI = acos(-1);

int arr[MAXN];

int rk[MAXN<<1],sa[MAXN],tarr[MAXN<<1],cnt[MAXN],rkt[MAXN];
//rk[i]表示后缀i（从1开始，后缀i代表字符串从i开始到结束的子串）的排名，sa[i]表示所有后缀第i小的起点序号，排名和编号都从1开始

void getSA(std::string const & s){
    int n = s.size();
    if(n==1){
        rk[1] = sa[1] = 1;
        return;
    }
    
    int m = 128;
    for(int i=1;i<=n;i++)
        ++cnt[rk[i]=s[i-1]];
    for(int i=1;i<=m;i++)
        cnt[i] += cnt[i-1];
    for(int i=n;i>=1;i--)
        sa[cnt[rk[i]]--] = i;
    
    for(int w=1;;w<<=1){
        for(int i=n;i>n-w;i--)
            tarr[n-i+1] = i;
        for(int i=1,p=w;i<=n;i++)
            if(sa[i]>w) tarr[++p]=sa[i]-w;
        std::fill(cnt+1,cnt+m+1,0);
        for(int i=1;i<=n;i++)
            cnt[rkt[i] = rk[tarr[i]]]++;
        for(int i=1;i<=m;i++)
            cnt[i]+=cnt[i-1];
        for(int i=n;i>=1;i--)
            sa[cnt[rkt[i]]--] = tarr[i];
        m = 0;
        auto rp = [&](int x){return std::make_pair(rk[x],rk[x+w]);};
        for(int i=1;i<=n;i++)
            tarr[sa[i]] = rp(sa[i-1])==rp(sa[i]) ? m:++m;
        std::copy(tarr+1,tarr+n+1,rk+1);
        if(n==m) break;
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

	std::string str;
	std::cin>>str;
	
	getSA(str);
	int n = str.size();
	for(int i=1;i<=n;i++){
	    std::cout<<sa[i]<<" ";
	}

    return 0;
}
