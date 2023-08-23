//复杂度 nm
//bellman-ford, 单源最短路
//luogu p4779，有一个点TLE
#include <iostream>
#include <vector>
#include <cstring>

int const MAXN = 100005;
int const INF = 0x6fffffff;

struct Edge{
    int v,w;//下一点,权
    Edge(int v_, int w_):v(v_),w(w_){}
};

int dis[MAXN];
std::vector<Edge> graph[MAXN];

void init(int n){
    for(int i=1;i<=n;i++){
        dis[i]=INF;
        graph[i].clear();
    }
}

bool BF(int n, int s){
    //如果不存在最短路就返回0，否则返回1
    dis[s] = 0;
    bool flag = 1;
    for (int i=1;i<=n;i++){//松弛n-1轮，若第n轮还能松弛，就说明有负环
        flag = 1;
        for(int u=1;u<=n;u++){//这里看似是两层循环，实际上总数是边数，整个算法的复杂度是mn
            for (auto e : graph[u]){
                int w=e.w,v=e.v;
                if(dis[v]>dis[u]+w){
                    dis[v]=dis[u]+w;
                    flag = 0;
                }
            }
        }
        if(flag){
            break;
        }
    }
    
    return flag;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n,m,s;//点数，边数，起点
    std::cin>>n>>m>>s;
    init(n);

    for(int i=1;i<=m;i++){
        int u,v,w;
        std::cin>>u>>v>>w;
        //起点，终点，边权
        graph[u].push_back(Edge(v,w));
    }
    
    BF(n,s);

    for(int i=1;i<=n;i++){
        std::cout<<dis[i]<<" ";
    }
    
    return 0;
}
