//复杂度 n+m
//tarjan求割边，可以正确处理重边
//如果无向图中删掉某条边会使无向图的连通分量数增多，那么这条边叫割边
//luogu p1656
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

const int MAXN = 20005;
const int MAXM = 100005;

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
            tarjan(i,0);
    }
    
    std::vector<std::pair<int,int> > ans;
    for(int i=2;i<ecnt;i+=2){
        if(bridges[i]){
            int u = edges[i].v;
            int v = edges[i^1].v;
            if(u>v) std::swap(u,v);
            ans.push_back({u,v});
        }
    }
    std::sort(ans.begin(),ans.end());
    for(auto x:ans) std::cout<<x.first<<" "<<x.second<<"\n";
    
    return 0;
}
