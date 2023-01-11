//luogu 3376
//复杂度O(ef)，边数乘以最大流，所以在luogu上这题超时
#include <iostream>
#include <cstring>
#include <vector>

typedef long long LL;

const int MAXN = 205;
const LL INF = 0xffffffff;

struct Edge{
    int v;LL w;//指向的点，容量
    Edge(int v_, LL w_):v(v_),w(w_){}
};

std::vector<Edge> edges;
std::vector<std::vector<int> > graph(MAXN);//vector版的链式前向星
bool vis[MAXN];

LL DFS(int const & p, LL const & flow, int const & s, int const & t){
    if(p==t) return flow;
    vis[p] = true;

    int size = graph[p].size();
    for(int i=0 ; i<size ; i++){
        int eg = graph[p][i];
        int to = edges[eg].v;
        LL vol = edges[eg].w, c;

        if(vol>0 && !vis[to] && (c=DFS(to,std::min(flow,vol),s,t))!=-1){
            edges[eg].w -= c;
            edges[eg^1].w += c;
            return c;
        }
    }

    return -1;
}

LL FF(int const & p, LL const & flow, int const & s, int const & t){
    LL ans = 0, c;
    while((c=DFS(p,flow,s,t))!=-1){
        std::memset(vis,0,sizeof(vis));
        ans += c;
    }
    return ans;
}

int main(){
    int n,m,s,t;//点数，边数，源点，汇点
    std::cin>>n>>m>>s>>t;

    for(int i=1;i<=m;i++){
        int u,v;LL w;
        std::cin>>u>>v>>w;//起点，终点，边容量
        graph[u].push_back(edges.size());
        edges.push_back(Edge(v,w));
        graph[v].push_back(edges.size());
        edges.push_back(Edge(u,0));
    }

    std::cout<<FF(s,INF,s,t)<<"\n";//输出最大流

    return 0;
}
