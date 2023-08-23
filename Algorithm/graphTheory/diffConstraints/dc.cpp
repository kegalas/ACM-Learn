//差分约束，复杂度同SPFA
//luogu p5960
//使用介绍见markdown
#include <iostream>
#include <vector>
#include <queue>

int const MAXN = 5005;
int const INF = 0x5fffffff;

struct Edge{
    int v,w;
    Edge(int v_, int w_):v(v_),w(w_){}
};

int dis[MAXN];//距离
int cnt[MAXN];//算到达本节点所要经过的边数，若cnt>=n，则说明有负权环
bool tag[MAXN];//用于判断是否为上次松弛过的节点的边所连的点

std::queue<int> qu;
std::vector<Edge> graph[MAXN];

void init(int n){
    while(!qu.empty()) qu.pop();
    for(int i=1;i<=n;i++){
        dis[i] = INF;
        cnt[i] = 0;
        tag[i] = 0;
        graph[i].clear();
    }
}

bool SPFA(int n, int s){
    //如果不存在最短路就返回0，否则返回1
    dis[s] = 0;
    tag[s] = 1;
    qu.push(s);
    bool flag = 1;

    while(!qu.empty()){
        if(!flag) break;
        int u = qu.front();
        qu.pop();
        tag[u]=0;
        for(auto e : graph[u]){
            int v = e.v, w = e.w;
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                cnt[v]=cnt[u]+1;
                if(cnt[v]>=n) {
                    flag = 0;
                    break;
                }
                if(!tag[v]){
                    qu.push(v);
                    tag[v]=1;
                }
            }
        }
    }
    return flag;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n,m;
    std::cin>>n>>m;
    init(n+1);
    
    for(int i=1;i<=m;i++){
        int v,u,w;
        std::cin>>v>>u>>w;
        graph[u].push_back(Edge(v,w));
    }
    for(int i=1;i<=n;i++){
        graph[n+1].push_back(Edge(i,0));
    }
    n++;
    
    if(!SPFA(n,n)){
        std::cout<<"NO\n";
        return 0;
    }
    for(int i=1;i<=n-1;i++){
        std::cout<<dis[i]<<" ";
    }
    

    return 0;
}