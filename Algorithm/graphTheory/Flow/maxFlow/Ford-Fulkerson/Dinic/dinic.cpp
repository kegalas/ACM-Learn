//luogu P3376
//Dinic算法的时间复杂度为O(n^2m)，这题不会超时
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

typedef long long LL;

const int MAXN = 205;
const LL INF = 0xffffffff;

struct Edge{
    int v;LL w;//指向的点，容量
    Edge(int v_, LL w_):v(v_),w(w_){}
};

std::vector<Edge> edges;
std::vector<std::vector<int> > graph(MAXN);//vector版的链式前向星
std::vector<int> cur(MAXN);
int level[MAXN];
LL flow[MAXN];

bool BFS(int const & s, int const & t){//BFS分层
    std::memset(level, -1, sizeof(level));
    level[s] = 0;
    std::queue<int> qu;
    qu.push(s);

    while(!qu.empty()){
        int p = qu.front();
        qu.pop();
        int size = graph[p].size();
        for(int i=0;i<size;i++){
            int eg = graph[p][i];
            int to = edges[eg].v;
            LL vol = edges[eg].w;
            if(vol>0 && level[to] == -1){
                level[to] = level[p] + 1;
                qu.push(to);
            }
        }
    }

    return level[t] != -1;
}

LL DFS(int const & p, LL const & flow, int const & s, int const & t){
    if(p==t) return flow;

    LL surplus = flow;//剩余流量

    int size = graph[p].size();
    for(int & i=cur[p];i<size && surplus;i++){//这里i是引用，是当前弧优化
        int eg = graph[p][i];
        int to = edges[eg].v;
        LL vol = edges[eg].w;
        if(vol>0 && level[to]==level[p]+1){
            LL c = DFS(to, std::min(vol, surplus), s, t);
            surplus -= c;
            edges[eg].w -= c;
            edges[eg^1].w += c;
        }
    }

    return flow - surplus;
}

LL Dinic(int const & p, LL const & flow, int const & s, int const & t){
    LL ans = 0;
    while(BFS(s,t)){
        cur.assign(MAXN,0);
        ans += DFS(p,flow,s,t);
    }
    return ans;
}

int main(){
    int n,m,s,t;//点数，边数，源点，汇点
    std::cin>>n>>m>>s>>t;

    for(int i=1;i<=m;i++){
        int u,v;LL w;
        std::cin>>u>>v>>w;
        graph[u].push_back(edges.size());
        edges.push_back(Edge(v,w));
        graph[v].push_back(edges.size());
        edges.push_back(Edge(u,0));
    }

    std::cout<<Dinic(s,INF,s,t)<<"\n";

    return 0;
}
