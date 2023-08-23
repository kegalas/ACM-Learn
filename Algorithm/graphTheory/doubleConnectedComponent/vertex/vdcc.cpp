//复杂度 n+m
//tarjan求点双联通分量
//luogu p8435

//如果一张无向连通图不存在割点，则称之为点双联通图
//双连通分量是图的极大双联通子图
//极大指的是，不存在包含这个子图的更大的子图也是边双联通图
//若u-v点双联通，v-w点双联通，则u-w[并不一定]点双联通
//一张图是点双联通，当且仅当以下两个条件之一成立
//1. 图的顶点数不超过2
//2. 图中任意两点都同时包含在至少一个简单环中

//无向连通图中，对于任意两个点，如果无论删去哪个点（只能一个，且不能删除这两个点自己），都不能使它们不连通，则为点双联通
//但是，虽然边双联通中的割边不属于任何连通分量，但割点却可以属于多个点双联通分量

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

const int MAXN = 500005;
const int MAXM = 2000005;

int dfn[MAXN], low[MAXN], cnt=0;
//含义见割边模板
struct Edge{
    int v,next;//指向的点，边权，下一条边
};

Edge edges[MAXM*2];//存无向图记得开两倍
int head[MAXN],ecnt;//这个ecnt和割边那里不一样，但也可以等于1
bool cut[MAXN];//判断割点

inline void add(int u, int v){
    edges[++ecnt].v = v;
    edges[ecnt].next = head[u];
    head[u] = ecnt;
}

std::stack<int> stk;
int cdcc;
std::vector<std::vector<int> > dcc(MAXN);

void tarjan(int u, int root){
    low[u] = dfn[u] = ++cnt;
    stk.push(u);
    if(u==root && head[u]==0){
        dcc[++cdcc].push_back(u);
        return;
    }
    int tot=0;
    for(int i=head[u];i;i=edges[i].next){
        int v = edges[i].v;
        if(!dfn[v]){
            tarjan(v,root);
            low[u] = std::min(low[u],low[v]);
            if(low[v]>=dfn[u]){
                tot++;
                if(u!=root || tot>1) cut[u] = true;
                cdcc++;
                int z;
                do{
                    z = stk.top();
                    stk.pop();
                    dcc[cdcc].push_back(z);
                }while(z!=v);
                dcc[cdcc].push_back(u);
            }
        }
        else{
            low[u] = std::min(low[u], dfn[v]);
        }
    }
}

int main(){
    int n,m;
    std::cin>>n>>m;
    //点数，边数
    for(int i=1;i<=m;i++){
        int a,b;
        std::cin>>a>>b;
        //起点，终点
        if(a==b) continue;//点双联通需要注意排除自环才能处理孤立点
        add(a,b);
        add(b,a);
        //无向图
    }

    for(int i=1;i<=n;i++){
        if(!dfn[i])
            tarjan(i,i);
    }
    
    std::cout<<cdcc<<"\n";
    for(int i=1;i<=cdcc;i++){
        std::cout<<dcc[i].size()<<" ";
        for(auto x:dcc[i]) std::cout<<x<<" ";
        std::cout<<"\n";
    }
    
    return 0;
}
