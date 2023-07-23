//luogu P3381
//Dinic+SPFA的实现，复杂度为O(nmf)，即点数、边数、最大流
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

typedef long long LL;
typedef std::pair<LL,LL> pll;

const int MAXN = 5005;
const LL INF = 0xffffffff;

struct Edge{
    int v;LL w,c;//指向的点，容量，费用
    Edge(int v_, LL w_, LL c_):v(v_),w(w_),c(c_){}
};

std::vector<Edge> edges;
std::vector<std::vector<int> > graph(MAXN);//vector版的链式前向星
std::vector<int> cur(MAXN);
LL dis[MAXN];
bool inq[MAXN];

bool SPFA(int s, int t){//BFS分层
    std::fill(dis,dis+MAXN,INF);
    std::memset(inq, 0, sizeof(inq));

    dis[s] = 0;
    inq[s] = 1;

    cur.assign(MAXN,0);//初始化当前弧
    std::queue<int> qu;
    qu.push(s);

    while(!qu.empty()){
        int p = qu.front();
        qu.pop();
        inq[p] = 0;
        
        int size = graph[p].size();
        for(int i=0;i<size;i++){
            int eg = graph[p][i];
            int to = edges[eg].v;
            LL vol = edges[eg].w;
            if(vol>0 && dis[to] > dis[p]+edges[eg].c){
                dis[to] = dis[p]+edges[eg].c;
                if(!inq[to]){
                    qu.push(to);
                    inq[to] = 1;
                }
            }
        }
    }

    return dis[t] != INF;
}

LL DFS(int const & p, LL const & flow, int const & s, int const & t){
    if(p==t) return flow;

    LL surplus = flow;//剩余流量
    inq[p] = 1;//由于在SPFA中都会清零，可以复用

    int size = graph[p].size();
    for(int i=cur[p];i<size && surplus;i++){
        int eg = graph[p][i];
        cur[p] = i;//更新当前弧
        int to = edges[eg].v;
        LL vol = edges[eg].w;
        if(!inq[to] && vol>0 && dis[to]==dis[p]+edges[eg].c){
            LL cx = DFS(to, std::min(vol, surplus), s, t);
            surplus -= cx;
            edges[eg].w -= cx;
            edges[eg^1].w += cx;
        }
    }
    inq[p] = 0;

    return flow - surplus;
}

pll MCMF(int const & p, LL const & flow, int const & s, int const & t){
    LL maxflow = 0, mincost = 0;
    while(SPFA(s,t)){
        LL ret = DFS(p,flow,s,t);
        maxflow += ret;
        mincost += ret * dis[t];
    }
    return {maxflow,mincost};
}

int main(){
    int n,m,s,t;//点数，边数，源点，汇点
    std::cin>>n>>m>>s>>t;

    for(int i=1;i<=m;i++){
        int u,v;LL w,c;
        std::cin>>u>>v>>w>>c;
        graph[u].push_back(edges.size());
        edges.push_back(Edge(v,w,c));
        graph[v].push_back(edges.size());
        edges.push_back(Edge(u,0,-c));
    }
    pll ans = MCMF(s,INF,s,t);
    std::cout<<ans.first<<" "<<ans.second<<"\n";

    return 0;
}