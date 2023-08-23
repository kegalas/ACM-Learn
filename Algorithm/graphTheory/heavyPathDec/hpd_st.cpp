//树剖维护树上路径的点权和，维护和查询一次复杂度 logn
//luogu p3384

//树根节点的子节点中子树最大的为它的重子节点，其他的为轻子节点（整棵树的根节点是轻点，其他子树的根节点可轻可重）
//节点连向其轻子节点的边叫轻边，否则叫重边
//节点数为n，则从任意节点向上到根节点，经过的轻边数不超过logn
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>

#define pb push_back
#define mkp std::make_pair
#define fi first
#define se second

using LL = long long;

int const MAXN = 100005;
int const INF = 0x7fffffff;
LL MOD = 998244353;

struct Node{
    int fa, sz, dep, hson;//父节点、子树大小（包含自己）、深度、重子节点
    int top;//链头，即所在的重链中深度最小的那个节点 
    int dfn, mdfn;//该节点的dfs序，该节点子树的最大dfs序
    LL v;//点上的权
}node[MAXN];
int dfnmap[MAXN];//映射dfn对应的点编号

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

int cnt=0;

void dfs2(int u){
    //需要先把根节点的top设置为自己
    node[u].dfn = ++cnt;
    dfnmap[cnt] = u;
    if(node[u].hson!=0){
        node[node[u].hson].top = node[u].top;
        dfs2(node[u].hson);
    }
    //采取这个改变的原因是，每棵子树的dfs序是连续的，根节点dfs序最小
    //而如果我们强制先遍历重子节点，那么重链上的dfs序是连续的，并且链头dfs序最小。这样就能用线段树维护链上的信息了
    
    for(auto v:edges[u]){
        if(!node[v].top){
            node[v].top = v;
            dfs2(v);
        }
    }
    
    node[u].mdfn = cnt;
}

void cut(int r){
    dfs1(r);
    node[r].top = r;
    dfs2(r);
}

struct Nodest
{
    int s,t;//该端点的起点和终点下标
    LL tag, v;
};

Nodest st[MAXN*4+2];

void build(int s, int t, int p){
    st[p].s = s;
    st[p].t = t;
    if(s==t) {
        st[p].v = node[dfnmap[s]].v%MOD;
        st[p].tag = 0;
        return;
    }
    int m = s+((t-s)>>1);
    build(s,m,p*2);
    build(m+1,t,p*2+1);
    st[p].v = (st[p*2].v + st[p*2+1].v)%MOD;
    st[p].tag = 0;
}

void spreadTag(int p){
    if(st[p].tag){
        int s = st[p].s, t = st[p].t;
        int m = s+((t-s)>>1);
        st[p*2].v     = (st[p*2].v + (m-s+1)*st[p].tag)%MOD;
        st[p*2+1].v   = (st[p*2+1].v + (t-m)*st[p].tag)%MOD;
        st[p*2].tag   = (st[p].tag + st[p*2].tag)%MOD;
        st[p*2+1].tag = (st[p].tag + st[p*2+1].tag)%MOD;
        st[p].tag=0;
    }
}

void update(int l, int r, int p, LL k){
    int s = st[p].s, t = st[p].t;
    if(l<=s && t<=r){
        st[p].v   = (st[p].v + (t-s+1) * k)%MOD;
        st[p].tag = (st[p].tag + k)%MOD;
        return;
    }
    spreadTag(p);
    
    int m = s+((t-s)>>1);
    if(l<=m) update(l, r, p*2, k);
    if(r>m)  update(l, r, p*2+1, k);
    st[p].v = (st[p*2].v + st[p*2+1].v)%MOD;
}

LL query(int l, int r, int p){
    int s = st[p].s, t = st[p].t;
    if(l<=s && t<=r) return st[p].v%MOD;
    
    spreadTag(p);
    int m = s+((t-s)>>1);
    LL ret = 0;
    if(l<=m) ret = (ret + query(l,r,p*2))%MOD;
    if(r>m)  ret = (ret + query(l,r,p*2+1))%MOD;
    
    return ret;
}

void update_path(int x, int y, LL k){
    while(node[x].top != node[y].top){
        if(node[node[x].top].dep > node[node[y].top].dep){
            update(node[node[x].top].dfn, node[x].dfn, 1, k);
            x = node[node[x].top].fa;
        }
        else{
            update(node[node[y].top].dfn, node[y].dfn, 1, k);
            y = node[node[y].top].fa;
        }
    }
    if(node[x].dep>node[y].dep){
        update(node[y].dfn, node[x].dfn, 1, k);
    }
    else{
        update(node[x].dfn, node[y].dfn, 1, k);
    }
}

LL query_path(int x, int y){
    LL ans = 0;
    while(node[x].top != node[y].top){
        if(node[node[x].top].dep > node[node[y].top].dep){
            ans += query(node[node[x].top].dfn, node[x].dfn, 1);
            x = node[node[x].top].fa;
        }
        else{
            ans += query(node[node[y].top].dfn, node[y].dfn, 1);
            y = node[node[y].top].fa;
        }
    }
    if(node[x].dep>node[y].dep){
        ans += query(node[y].dfn, node[x].dfn, 1);
    }
    else{
        ans += query(node[x].dfn, node[y].dfn, 1);
    }
    
    return ans%MOD;
}

void update_subtree(int x, LL k){
    update(node[x].dfn, node[x].mdfn, 1, k);
}

LL query_subtree(int x){
    return query(node[x].dfn, node[x].mdfn, 1)%MOD;
}

void solve(){
    int n,m,r;
    std::cin>>n>>m>>r>>MOD;//节点个数，操作个数，根节点序号，取模数
    for(int i=1;i<=n;i++){
        std::cin>>node[i].v;
    }
    for(int i=1;i<n;i++){
        int x,y;
        std::cin>>x>>y;
        edges[x].pb(y);
        edges[y].pb(x);
    }
    
    cut(r);
    build(1,n,1);
    
    while(m--){
        int ope,x,y;
        LL z;
        std::cin>>ope;
        
        if(ope==1){
            std::cin>>x>>y>>z;
            update_path(x,y,z);
        }
        else if(ope==2){
            std::cin>>x>>y;
            std::cout<<query_path(x,y)<<"\n";
        }
        else if(ope==3){
            std::cin>>x>>z;
            update_subtree(x,z);
        }
        else if(ope==4){
            std::cin>>x;
            std::cout<<query_subtree(x)<<"\n";
        }
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
