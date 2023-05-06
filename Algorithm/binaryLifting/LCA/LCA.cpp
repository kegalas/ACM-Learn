//复杂度 单次查询 logn 预处理 nlogn
//luogu P3379
#include <iostream>
#include <vector>
#include <cstdio>

const int MAXN = 500005;
const int LOGN = 31;

std::vector<int> edge[MAXN];//邻接表
int fa[MAXN][LOGN],deep[MAXN];
//fa[a][b]代表a的第2^b个祖先，deep是深度，根节点深度为1

void build(int v,int father){
    fa[v][0] = father;
    deep[v] = deep[father]+1;

    for(int i=1;i<LOGN;i++){
        fa[v][i] = fa[fa[v][i-1]][i-1];
    }

    for(auto v1:edge[v]){
        if(v1==father) continue;
        build(v1,v);
    }
}

int lca(int x,int y){
    if(deep[x]>deep[y]) std::swap(x,y);
    //保证y比x深

    int tmp = deep[y]-deep[x];
    for(int i=0;tmp;i++,tmp>>=1){
        if(tmp&1) y=fa[y][i];
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

int main(){
    int n,m,s;
    scanf("%d%d%d",&n,&m,&s);
    //点数，询问数，根节点序号

    for(int i=1;i<=n-1;i++){
        int a,b;
        scanf("%d%d",&a,&b);
        //读入树
        edge[a].push_back(b);
        edge[b].push_back(a);
    }

    build(s,0);

    for(int i=1;i<=m;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        //查询x,y的最近公共祖先
        printf("%d\n",lca(x,y));
    }

    return 0;
}
