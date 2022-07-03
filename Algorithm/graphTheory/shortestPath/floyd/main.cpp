//floyd
#include <iostream>
#include <cstring>

#define MAXN 5005
#define MAXINT 0x3fffffff //不能设置为int的最大值，否则后面加法可能导致溢出


using namespace std;

int graph[MAXN][MAXN];

int main(){
    int n,m;
    cin>>n>>m;
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=n;j++){
            graph[i][j] = MAXINT;
        }
    }
    for(int i = 1;i<=n;i++){
        graph[i][i] = 0;
    }
    for(int i=1;i<=m;i++){
        int a,b,v;
        cin>>a>>b>>v;
        graph[a][b] = v;
    }

    for(int k = 1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                graph[i][j] = min(graph[i][j],graph[i][k]+graph[k][j]);
            }
        }
    }


    for(int i = 1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cout<<graph[i][j]<<" ";
        }
        cout<<endl;
    }

    return 0;
}
