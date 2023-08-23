//复杂度 n^3
//floyd全源最短路
//luogu p5905，由于不能判断负环和速度慢，会wa和tle一些
//floyd虽然不能处理负环但是可以接受负边
#include <iostream>
#include <cstring>

using LL = long long;

int const MAXN = 3005;
LL const INF = 1e17; //不能设置为int的最大值，否则后面加法可能导致溢出
LL graph[MAXN][MAXN];

int main(){
    int n,m;//点数，边数
    std::cin>>n>>m;
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=n;j++){
            graph[i][j] = INF;
        }
    }
    for(int i=1;i<=m;i++){
        int u,v;LL w;
        std::cin>>u>>v>>w;//起点，终点，边权
        graph[u][v] = std::min(graph[u][v], w);//处理重边
    }
    for(int i = 1;i<=n;i++){
        graph[i][i] = 0;
    }

    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                graph[i][j] = std::min(graph[i][j],graph[i][k]+graph[k][j]);
            }
        }
    }
    
    for(int i=1;i<=n;i++){
        LL res=0;
        for(LL j=1;j<=n;j++){
            if(graph[i][j]>1e9) graph[i][j] = 1e9;
            res += j*graph[i][j];
        }
        std::cout<<res<<"\n";
    }

    return 0;
}
