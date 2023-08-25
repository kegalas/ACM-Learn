//对于序列上的区域离线询问问题，如果[l,r]的答案能够O(1)拓展得到
//[l-1,r],[l+1,r],[l,r-1],[l,r+1]的答案，那么就可以在O(n sqrt(n))中解决所有询问
//SPOJ DQUERY
//本题是给定若干个区间[l,r]，查询这个范围内有多少个不同的数
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
int sq;//分块数sq = sqrt(n)

struct Query{
    int l,r,id;//询问区间和询问下标
    bool operator<(Query const & x)const{
        if(l/sq != x.l/sq)//根据归属于哪个块排序
            return l<x.l;
        if(l/sq & 1)      //玄学奇偶排序
            return r<x.r;
        return r>x.r;
    }  
}Q[MAXQ];

int ans[MAXQ], cnt[MAXA], cur;
int l=1,r=0;//初始化询问区间

inline void add(int p){
    if(cnt[arr[p]]==0)//新增一种数
        cur++;
    cnt[arr[p]]++;
}

inline void del(int p){
    cnt[arr[p]]--;
    if(cnt[arr[p]]==0)//把一种数全部删完
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
	    Q[i].id = i;//把询问离线
	}
	std::sort(Q,Q+q);
	
	for(int i=0;i<q;i++){
	    while(l>Q[i].l)
	        add(--l);//当前区间l大于查询的l，要把左边的数加进来
	    while(r<Q[i].r)
	        add(++r);//当前区间r小于查询的r，要把右边的数加进来
	    while(l<Q[i].l)
	        del(l++);//当前区间l小于查询的l，要把左边的数删掉
	    while(r>Q[i].r)
	        del(r--);//当前区间r大于查询的r，要把右边的数删掉
	    //注意上述顺序，扩张区间是先移动再更新，缩减区间是先更新再移动
	    //四个操作的具体实现可能会有不一样，具体题目具体讨论
	    ans[Q[i].id] = cur;
	}
	
	for(int i=0;i<q;i++){
	    std::cout<<ans[i]<<"\n";
	}

    return 0;
}
