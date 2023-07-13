//SPOJ DQUERY
//复杂度 n sqrt(n)
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

int const MAXN = 30005;
int const MAXQ = 200005;
int const MAXA = 1e6+5;
int const INF = 0x7fffffff;
double const EPS = 1e-8;
int const MOD = 998244353;
double const PI = acos(-1);

int arr[MAXN];
int sq;//分块数

struct Query{
    int l,r,id;
    bool operator<(Query const & x)const{
        if(l/sq != x.l/sq)//根据归属于哪个块排序
            return l<x.l;
        if(l/sq & 1)      //玄学奇偶排序
            return r<x.r;
        return r>x.r;
    }  
}Q[MAXQ];

int ans[MAXQ], cnt[MAXA], cur, l=1,r=0;

inline void add(int p){
    if(cnt[arr[p]]==0)
        cur++;
    cnt[arr[p]]++;
}

inline void del(int p){
    cnt[arr[p]]--;
    if(cnt[arr[p]]==0)
        cur--;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

	int n;
	std::cin>>n;
	sq = std::sqrt(n);
	for(int i=1;i<=n;i++) std::cin>>arr[i];
	int q;
	std::cin>>q;
	for(int i=0;i<q;i++){
	    std::cin>>Q[i].l>>Q[i].r;
	    Q[i].id = i;
	}
	std::sort(Q,Q+q);
	
	for(int i=0;i<q;i++){
	    while(l>Q[i].l)
	        add(--l);
	    while(r<Q[i].r)
	        add(++r);
	    while(l<Q[i].l)
	        del(l++);
	    while(r>Q[i].r)
	        del(r--);
	    ans[Q[i].id] = cur;
	}
	
	for(int i=0;i<q;i++){
	    std::cout<<ans[i]<<"\n";
	}

    return 0;
}
