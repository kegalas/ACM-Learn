//luogu 3386
#include <iostream>
#include <cstring>

const int MAXN = 505;
bool graph[MAXN][MAXN];
bool vis[MAXN];
int toLeft[MAXN];

bool match(int const & i, int const & rightNum){
    for(int j=1;j<=rightNum;j++){
        if(graph[i][j]&&!vis[j]){
            vis[j] = true;
            if(toLeft[j]==0 || match(toLeft[j], rightNum)){
                toLeft[j] = i;
                return true;
            }
        }
    }
    return false;
}

int hungarian(int const & leftNum, int const & rightNum){
    int cnt = 0;

    for(int i=1;i<=leftNum;i++){
        std::memset(vis,0,sizeof(vis));
        if(match(i,rightNum)) cnt++;
    }

    return cnt;
}

int main(){
    int n,m,e;//左边点数，右边点数，边数
    std::cin>>n>>m>>e;
    
    for(int i=1;i<=e;i++){
        int x,y;
        std::cin>>x>>y;
        graph[x][y] = true;
    }

    std::cout<<hungarian(n,m)<<"\n";

    return 0;
}
