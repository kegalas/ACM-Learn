//复杂度 nm
/*
    bellman-ford的优化
    只有上一次被松弛的结点，所连接的边，
    才有可能引起下一次的松弛操作
*/
//spfa 单源最短路
//luogu P3371
#include <iostream>
#include <vector>
#include <queue>

int const MAXN = 100005;
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
    int n,m,s;
    std::cin>>n>>m>>s;
    init(n);

    for(int i=1;i<=m;i++){
        int u,v,w;
        std::cin>>u>>v>>w;
        //起点，终点，边权
        graph[u].push_back(Edge(v,w));
    }

    SPFA(n,s);
    for(int i=1;i<=n;i++){
        if(dis[i]!=INF){
            std::cout<<dis[i]<<" ";
        }
        else{
            std::cout<<"2147483647 ";//根据luogu P3371要输出这个数
        }
    }

    return 0;
}
