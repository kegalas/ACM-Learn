//复杂度 优先队列实现为mlogm
//dijkstra，单源最短路
//luogu p4779
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
int const MAXN = 500005;
int const MAXINT = 0x7fffffff;

struct Edge{
    int v,w;//下一点，权
    Edge(int v_, int w_):v(v_),w(w_){}
};

struct Node {
    int dis, u;//存储起点到u点的距离
    Node(int dis_, int u_):dis(dis_),u(u_){};
    bool operator>(Node const & a) const { return dis > a.dis; }
};

std::vector<Edge> graph[MAXN];
int dis[MAXN];
bool tag[MAXN];

std::priority_queue<Node, std::vector<Node>, std::greater<Node> > pq;

void init(int n){
    for(int i=1;i<=n;i++){
        dis[i] = MAXINT;
        //初始化为无限远
        tag[i] = 0;
        graph[i].clear();
    }
    while(!pq.empty()) pq.pop();
}

void dijk(int s){
    dis[s]=0;
    pq.push(Node(0,s));

    while (!pq.empty())
    {
        int u = pq.top().u;
        pq.pop();
        if(tag[u]) continue;
        tag[u]=1;
        for(auto g : graph[u]){
            int v = g.v, w = g.w;
            if(dis[v]>dis[u]+w){
                dis[v] = dis[u]+w;
                pq.push(Node(dis[v],v));
            }
        }
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n,m,s;
    std::cin>>n>>m>>s;
    //点数，边数，起点
    init(n);

    for(int i=1;i<=m;i++){
        int u,v,w;
        std::cin>>u>>v>>w;//起点，终点，边权
        graph[u].push_back(Edge(v,w));
    }
    dijk(s);

    for(int i=1;i<=n;i++){
        std::cout<<dis[i]<<" ";
    }
    return 0;
}
