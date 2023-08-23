//树剖求LCA，每次查询复杂度 logn，常数很小
//luogu p3379

//树根节点的子节点中子树最大的为它的重子节点，其他的为轻子节点（整棵树的根节点是轻点，其他子树的根节点可轻可重）
//节点连向其轻子节点的边叫轻边，否则叫重边
//节点数为n，则从任意节点向上到根节点，经过的轻边数不超过logn
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
    int fa, sz, dep, hson;//父节点、子树大小（包含自己）、深度、重子节点
    int top;//链头，即所在的重链中深度最小的那个节点
}node[MAXN];

std::vector<int> edges[MAXN];

void dfs1(int u, int d=1){
    //在dfs2之前先用dfs1
    int size = 1, ma = 0;
    node[u].dep = d;
    for(auto v:edges[u]){
        if(!node[v].dep){
            dfs1(v,d+1);
            node[v].fa = u;
            size += node[v].sz;
            if(node[v].sz > ma){
                node[u].hson = v, ma = node[v].sz;
            }
        }
    }
    node[u].sz = size;
}

void dfs2(int u){
    //需要先把根节点的top设置为自己
    for(auto v:edges[u]){
        if(!node[v].top){
            if(v==node[u].hson) node[v].top = node[u].top;
            else node[v].top = v;
            dfs2(v);
        }
    }
}

int lca(int a, int b){
    while(node[a].top!=node[b].top){
        if(node[node[a].top].dep>node[node[b].top].dep)
            a = node[node[a].top].fa;
        else
            b = node[node[b].top].fa;
    }
    if(node[a].dep > node[b].dep) return b;
    return a;
}

void cut(int r=1){
    //进行树剖预处理
    dfs1(r);
    node[r].top = r;
    dfs2(r);
}

void solve(){
    int n,m,s;
    std::cin>>n>>m>>s;
    for(int i=1;i<=n-1;i++){
        int u,v;
        std::cin>>u>>v;
        edges[u].pb(v);
        edges[v].pb(u);
    }
    
    cut(s);
    
    while(m--){
        int x,y;
        std::cin>>x>>y;
        std::cout<<lca(x,y)<<"\n";
    }
    
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
