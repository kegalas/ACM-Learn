//luogu P3381
//EK+SPFA的实现，复杂度为O(nmf)，即点数、边数、最大流
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

typedef long long LL;
typedef std::pair<LL,LL> pll;

const int MAXN = 5005;
const LL INF = 0xffffffff;

struct Edge{
    int v;LL w;LL c;//指向的点，容量，费用
    Edge(int v_, LL w_, LL c_):v(v_),w(w_),c(c_){}
};

std::vector<Edge> edges;
std::vector<std::vector<int> > graph(MAXN);//vector版的链式前向星
int last[MAXN];
LL flow[MAXN];
LL dis[MAXN];
bool inq[MAXN];

bool SPFA(int s, int t){
    std::queue<int> qu;
    qu.push(s);
    
    std::memset(last,-1,sizeof(last));
    std::memset(dis,127,sizeof(dis));
    std::memset(inq,0,sizeof(inq));

    flow[s] = INF;
    dis[s] = 0;
    inq[s] = 1;
    
    while(!qu.empty()){
        int p = qu.front();
        qu.pop();
        inq[p] = 0;

        int size = graph[p].size();
        for(int i=0;i<size;i++){
            int eg = graph[p][i];
            int to = edges[eg].v;
            LL vol = edges[eg].w;
            if(vol>0 && dis[to]>dis[p]+edges[eg].c){
                last[to] = eg;
                flow[to] = std::min(flow[p], vol);
                dis[to] = dis[p]+edges[eg].c;
                if(!inq[to]){
                    qu.push(to);
                    inq[to] = 1;
                }
            }
        }
    }
    return last[t] != -1;
}

pll MCMF(int s, int t){
    LL maxflow = 0, mincost = 0;

    while(SPFA(s,t)){
        maxflow += flow[t];
        mincost += dis[t] * flow[t];
        for(int i=t;i!=s;i=edges[last[i]^1].v){
            edges[last[i]].w -= flow[t];
            edges[last[i]^1].w += flow[t];
        }
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

    pll ans = MCMF(s,t);
    std::cout<<ans.first<<" "<<ans.second<<"\n";

    return 0;
}