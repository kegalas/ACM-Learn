//复杂度 单次查询 logn 预处理 nlogn
//luogu P3379
#include <iostream>
#include <vector>
#include <cstdio>

int const MAXN = 500005;
int const LOGN = 31;

std::vector<int> edge[MAXN];//邻接表
int logn[MAXN];
int fa[MAXN][LOGN],deep[MAXN];
//fa[a][b]代表a的第2^b个祖先，deep是深度，根节点深度为1

void build(int u,int father){
    fa[u][0] = father;
    deep[u] = deep[father]+1;

    for(int i=1;i<=logn[deep[u]];i++){
        fa[u][i] = fa[fa[u][i-1]][i-1];
    }

    for(auto v:edge[u]){
        if(v==father) continue;
        build(v,u);
    }
}

int lca(int x,int y){
    if(deep[x]>deep[y]) std::swap(x,y);
    //保证y比x深

    while(deep[x]!=deep[y]){
        y = fa[y][logn[deep[y]-deep[x]]];
    }
    
    if(x==y) return x;
    
    for(int k=logn[deep[x]];k>=0;k--){
        if(fa[x][k]!=fa[y][k]){
            x = fa[x][k], y = fa[y][k];
        }
    }
    return fa[x][0];
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    
    int n,m,s;
    std::cin>>n>>m>>s;
    //点数，询问数，根节点序号
    
    for(int i=2;i<=n;i++){
        logn[i] = logn[i/2] + 1;
        //必须的初始化
    }

    for(int i=1;i<=n-1;i++){
        int a,b;
        std::cin>>a>>b;
        //读入树
        edge[a].push_back(b);
        edge[b].push_back(a);
    }

    build(s,0);//必须build才能用

    for(int i=1;i<=m;i++){
        int x,y;
        std::cin>>x>>y;
        //查询x,y的最近公共祖先
        std::cout<<lca(x,y)<<"\n";
    }

    return 0;
}
