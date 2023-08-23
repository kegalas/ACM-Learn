//复杂度 n+m
//tarjan求边双联通分量
//luogu p8436

//如果一张无向连通图不存在割边，则称之为边双联通图
//双连通分量是图的极大双联通子图
//极大指的是，不存在包含这个子图的更大的子图也是边双联通图
//若u-v边双联通，v-w边双联通，则u-w边双联通
//一张图是边双联通，当且仅当每条边都在至少一个简单环中

//无向连通图中，对于任意两个点，如果无论删去哪条边（只能一条），都不能使它们不连通，则为边双联通
//同时这也意味着，把割边删去后的图，就是若干个双联通分量

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

const int MAXN = 500005;
const int MAXM = 2000005;

int dfn[MAXN], low[MAXN], cnt=0;
//dfn为对一个图进行dfs时，dfs的顺序序号
//low[x]为以下所有符合要求的节点的dfn中的最小值
//1.以x为根的子树的所有节点
//2.通过非dfs生成树上的边能够到达该子树的所有节点
struct Edge{
    int v,next;//指向的点，边权，下一条边
};

Edge edges[MAXM*2];//存无向图记得开两倍
int head[MAXN],ecnt=1;//注意这个ecnt=1，这是用来方便in_edge判断的
bool bridges[MAXM*2];//判断一条边是不是割边

inline void add(int u, int v){
    edges[++ecnt].v = v;
    edges[ecnt].next = head[u];
    head[u] = ecnt;
}

void tarjan(int u, int in_edge){
    low[u] = dfn[u] = ++cnt;
    for(int i=head[u];i;i=edges[i].next){
        int v = edges[i].v;
        if(!dfn[v]){
            tarjan(v,i);
            low[u] = std::min(low[u],low[v]);
            if(low[v]>dfn[u])//边u-v是割边的充要条件
                bridges[i] = bridges[i^1] = true;          
            
        }
        else if(i != (in_edge ^ 1)){
            low[u] = std::min(low[u], dfn[v]);
        }
    }
}

//这之上同求割边

int dcci[MAXN], cdcc;//记录点i属于双联通分量dcci[i]，以及总的dcc个数
std::vector<std::vector<int> > dcc(MAXN);//存储双联通分量dcc[i]中有哪些点

void getDCC(int u){
    dcci[u] = cdcc;
    dcc[cdcc].push_back(u);
    for(int i=head[u];i;i=edges[i].next){
        int v = edges[i].v;
        if(dcci[v] || bridges[i]) continue;
        getDCC(v);
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    
    int n,m;
    std::cin>>n>>m;
    //点数，边数
    for(int i=1;i<=m;i++){
        int a,b;
        std::cin>>a>>b;
        //起点，终点
        add(a,b);
        add(b,a);
		//无向图
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i])
            tarjan(i,0);
    }
    
    //以上求完了割边
    
    for(int i=1;i<=n;i++){
        if(!dcci[i]){
            cdcc++;
            getDCC(i);
        }
    }
    
    std::cout<<cdcc<<"\n";
    for(int i=1;i<=cdcc;i++){
        std::cout<<dcc[i].size()<<" ";
        for(auto x:dcc[i]){
            std::cout<<x<<" ";
        }
        std::cout<<"\n";
    }
     
    return 0;
}
