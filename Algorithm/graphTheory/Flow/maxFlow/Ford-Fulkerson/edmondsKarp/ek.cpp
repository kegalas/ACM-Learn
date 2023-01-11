//luogu P3376
//EK算法的时间复杂度为O(nm^2)，这题不会超时
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
int last[MAXN];
LL flow[MAXN];

bool BFS(int const & s, int const & t){
    std::memset(last,-1,sizeof(last));
    std::queue<int> qu;
    qu.push(s);
    flow[s] = INF;
    while(!qu.empty()){
        int p = qu.front();
        qu.pop();
        if(p == t) break;

        int size = graph[p].size();
        for(int i=0;i<size;i++){
            int eg = graph[p][i];
            int to = edges[eg].v;
            LL vol = edges[eg].w;
            if(vol>0 && last[to] == -1){
                last[to] = eg;
                flow[to] = std::min(flow[p], vol);
                qu.push(to);
            }
        }
    }
    return last[t] != -1;
}

LL EK(int const & s, int const & t){
    LL ans = 0;

    while(BFS(s,t)){
        ans += flow[t];
        for(int i=t;i!=s;i=edges[last[i]^1].v){
            edges[last[i]].w -= flow[t];
            edges[last[i]^1].w += flow[t];
        }
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

    std::cout<<EK(s,t)<<"\n";

    return 0;
}
