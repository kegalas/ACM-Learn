#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <set>
#include <unordered_set>

using LL = long long;
#define int LL
#define pb push_back

const int MAXN = 6e5+5;
const int MAXM = MAXN;
const int LOGN = 30;

struct Edge{
    int v,w,next;//指向的点，边权，下一条边
};

Edge edges[MAXM];
int head[MAXN],cnt1;

Edge vte[MAXM];
int vth[MAXN],vtc;

inline void add(int u, int v, int w){
    edges[++cnt1].w = w;
    edges[cnt1].v = v;
    edges[cnt1].next = head[u];//把下一条边设置为当前起点的第一条边
    head[u] = cnt1;//该边称为当前起点的第一条边
}

inline void add2(int u, int v, int w){
    vte[++vtc].w = w;
    vte[vtc].v = v;
    vte[vtc].next = vth[u];//把下一条边设置为当前起点的第一条边
    vth[u] = vtc;//该边称为当前起点的第一条边
}

int fa[MAXN][LOGN],deep[MAXN];
//fa[a][b]代表a的第2^b个祖先，deep是深度，根节点深度为1

int dfn[MAXN];
int cnt = 0;
int mindis[MAXN];

void buildLCA(int u,int father){
    fa[u][0] = father;
    deep[u] = deep[father]+1;
    dfn[u] = ++cnt;

    for(int i=1;i<LOGN;i++){
        fa[u][i] = fa[fa[u][i-1]][i-1];
    }

    for(int e=head[u];e;e=edges[e].next){
        int v = edges[e].v, w = edges[e].w;
        if(v==father) continue;
        mindis[v] = std::min(mindis[u], w);
        buildLCA(v,u);
    }
}

int LCA(int x,int y){
    if(deep[x]>deep[y]) std::swap(x,y);
    //保证y比x深
    int tmp = deep[y]-deep[x];
    for(int i=0;tmp;i++,tmp>>=1){
        if(tmp&1) {
            y=fa[y][i];
        }
    }

    if(x==y) return y;

    for(int i=LOGN-1;i>=0&&y!=x;i--){
        if(fa[x][i]!=fa[y][i]){
            x = fa[x][i];
            y = fa[y][i];
        }
    }

    return fa[y][0];
}

int crux[MAXN];//关键节点
int a[MAXN];

inline bool cmp(int x, int y){
    return dfn[x]<dfn[y];
}

void buildVT(int k){
    std::sort(crux+1,crux+1+k,cmp);
    int acnt=0;
    for(int i=1;i<k;i++){
        a[++acnt] = crux[i];
        a[++acnt] = LCA(crux[i],crux[i+1]);
    }
    a[++acnt] = crux[k];
    std::sort(a+1,a+1+acnt,cmp);
    int len = std::unique(a+1,a+1+acnt)-a-1;
    for(int i=1,lca;i<len;i++){
        lca = LCA(a[i],a[i+1]);
        add2(lca,a[i+1],std::min(mindis[lca],mindis[a[i+1]]));
    }
    
}

std::unordered_set<int> s;
int dp[MAXN];
void dfs(int u){
    dp[u] = 0;
    for(int e=vth[u];e;e=vte[e].next){
        int v = vte[e].v, w = vte[e].w;
        dfs(v);
        if(s.count(v)) dp[u]+=w;
        else dp[u] = std::min(dp[v],w);
    }
    vth[u] = 0;
}

void solve(){
    int n;
    std::cin>>n;
    for(int i=1;i<=n-1;i++){
        int u,v,w;
        std::cin>>u>>v>>w;
        add(u,v,w);
        add(v,u,w);
    }
    
    mindis[1] = 1<<30;
    buildLCA(1,0);
    int Q;
    std::cin>>Q;
    
    while(Q--){
        int k;
        std::cin>>k;
        k++;
        s.clear();
        std::memset(dp,0,sizeof(dp));
        vtc = 0;
        
        crux[1] = 1;
        s.insert(1);
        for(int i=2;i<=k;i++){
            std::cin>>crux[i];
            s.insert(crux[i]);
        }
        buildVT(k);
        
        // for(int i=1;i<=n;i++){
            // std::cout<<i<<" ";
            // for(auto e:vt[i]){
                // std::cout<<e.fi<<" ";
            // }
            // std::cout<<"\n";
        // }
        
        dfs(1);
        std::cout<<dp[1]<<"\n";
    }
}

signed main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

	int T;
	T=1;
	while(T--){
	    solve();
	}

    return 0;
}
