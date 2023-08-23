//复杂度 n+m
//tarjan求割点,luogu P3388
//如果无向图中删掉某个点和其所有相连的边边会使无向图的连通分量数增多，那么这个点叫割点
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

const int MAXN = 20005;
const int MAXM = 100005;

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

void tarjan(int u, int root){
    int tot = 0;
    low[u] = dfn[u] = ++cnt;
    for(int i=head[u];i;i=edges[i].next){
        int v = edges[i].v;
        if(!dfn[v]){
            tarjan(v,root);
            low[u] = std::min(low[u],low[v]);
            //一个点x是割点的充要条件是，它至少一个子节点y满足dfn[x]<=low[y]，特别的，对于根节点，需要至少两个这样的子节点
            if(low[v]>=dfn[u]){
                tot++;
                if(u!=root || tot>1) cut[u] = true;
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
        add(a,b);
        add(b,a);
        //无向图
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i])
            tarjan(i,i);
    }
    
    std::vector<int> ans;
    for(int i=1;i<=n;i++) if(cut[i]) ans.push_back(i);
    std::sort(ans.begin(),ans.end());
    std::cout<<ans.size()<<"\n";
    for(auto x:ans) std::cout<<x<<" ";
    
    return 0;
}