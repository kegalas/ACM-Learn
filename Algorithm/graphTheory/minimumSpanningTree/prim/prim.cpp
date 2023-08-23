//复杂度 (m+n)logn
//最小生成树prim，luogu p3366
#include <iostream>
#include <vector>
#include <queue>

const int MAXN = 5005;
const int MAXM = 200005;
const int INF = 0x5fffffff;

struct edge{
    int v,w;

    edge(){};
    edge(int v,int w):v(v),w(w){}

    bool operator>(const edge& x) const {return w>x.w;}
};

std::vector<edge> graph[MAXN];
bool vis[MAXN];

std::priority_queue<edge, std::vector<edge>, std::greater<edge> > pq;

int main(){
    int n,m;//点数，边数
    std::cin>>n>>m;
    int ans = 0;
    int cnt = 1;

    for(int i=1;i<=m;i++){
        int u,v,w;//起点，终点，边权
        std::cin>>u>>v>>w;
        graph[u].push_back(edge(v,w));
        graph[v].push_back(edge(u,w));
        //无向图
    }

    for(int i=0;i<graph[1].size();i++){
        pq.push(graph[1][i]);
    }
    vis[1]=true;

    while(cnt!=n&&!pq.empty()){
        edge minx=pq.top();
        pq.pop();
        while(vis[minx.v]){
            if(pq.empty()){
                std::cout<<"orz\n";//不连通
                return 0;
            }
            minx=pq.top();
            pq.pop();
        }
        
        vis[minx.v] = true;
        ans+=minx.w;
        cnt++;
        
        for(int i=0;i<graph[minx.v].size();i++){
            if(!vis[graph[minx.v][i].v])
                pq.push(graph[minx.v][i]);
        }
    }

    if(cnt<n){
        std::cout<<"orz\n";
    }
    else{
        std::cout<<ans<<"\n";
    }

    return 0;
}
