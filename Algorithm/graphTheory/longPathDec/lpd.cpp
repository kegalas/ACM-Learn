//长链剖分定义子树最深深度最深的节点为重子节点
//任意节点p的k级祖先q所在的链长度一定大于k
//任意节点p到根节点最多经过sqrt n级别的轻边

//luogu p5903
//求任意节点的第k级祖先，预处理nlogn，查询常数

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

int const MAXN = 500005;
int const INF = 0x7fffffff;
double const EPS = 1e-8;
int const MOD = 998244353;
double const PI = acos(-1);

struct Node{
    int fa, dep, hson;//父节点、深度、重子节点
    int top;//链头，即所在的长链中深度最小的那个节点 
    int len,dfn,mdfn;//部分链长，dfs序，子树最大dfs序
}node[MAXN];

int dfnmap[MAXN];//dfs序对应节点

std::vector<int> edges[MAXN];

void dfs1(int u, int d=1){
    node[u].len = 1, node[u].dep = d;
    for(auto v:edges[u]){
        if(!node[v].dep){
            dfs1(v,d+1);
            node[v].fa = u;
            if(node[v].len+1>node[u].len)
                node[u].hson = v, node[u].len = node[v].len+1;
        }
    }
}

int cnt = 0;
void dfs2(int u, int tp){
    node[u].dfn = ++cnt;
    node[u].top = tp;
    dfnmap[cnt] = u;
    if(node[u].hson) dfs2(node[u].hson, tp);
    for(auto v:edges[u]){
        if(!node[v].top) dfs2(v,v);
    }
    node[u].mdfn = cnt;
}

void cut(int r=1){
    dfs1(r);
    dfs2(r,r);
}

std::vector<int> anc[MAXN], des[MAXN];
//分别存储（链头）节点p的1,2,...,node[p].len-1级祖先节点和子孙节点
int const LOGN = 21;
int fa[MAXN][LOGN];
int logn[MAXN];

void init(int r, int n){
    cut(r);
    
    logn[1] = 0;
    logn[2] = 1;
    for(int i=3;i<MAXN;i++){
        logn[i] = logn[i/2]+1;
        //预先计算logn
    }
    
    for(int i=1;i<=n;i++) fa[i][0] = node[i].fa;
    for(int j=1;j<LOGN;j++){
        for(int i=1;i<=n;i++){
            fa[i][j] = fa[fa[i][j-1]][j-1];
        }
    }
    
    for(int i=1;i<=n;i++){
        if(node[i].top==i){
            for(int j=0,p=i;j<node[i].len;j++,p=fa[p][0])
                anc[i].pb(p);
            for(int j=0;j<node[i].len;j++)
                des[i].pb(dfnmap[node[i].dfn+j]);
        }
    }
}

int query(int u, int k){
    //查询节点u的k级祖先
    if(k==0) return u;
    int i = logn[k];
    int v = fa[u][i];
    int tp = node[v].top;
    int d = k - (1<<i) + node[tp].dep - node[v].dep;
    if(d>0)
        return anc[tp][d];
    else
        return des[tp][-d];
}

//本题数据输入是随机的，下面是生成数据的函数
#define ui unsigned int
ui s;

inline ui get(ui x) {
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return s = x; 
}

void solve(){
    int n,q;
    std::cin>>n>>q>>s;
    int r;
    for(int i=1;i<=n;i++){
        int u;
        std::cin>>u;
        if(u==0){
            r = i;
            continue;
        }
        edges[u].pb(i);
        edges[i].pb(u);
    }
    init(r,n);
    
    LL ans = 0;
    LL res = 0;
    for(LL i=1;i<=q;i++){
        LL x = ((get(s)^ans)%n)+1;
        LL k = (get(s)^ans)%node[x].dep;
        
        ans = query(x,k);
        res = res ^ (i*ans);
    }
    std::cout<<res<<"\n";
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
