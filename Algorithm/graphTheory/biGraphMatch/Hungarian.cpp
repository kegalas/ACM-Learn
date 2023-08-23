//复杂度 nm
//luogu p3386
//求二分图最大匹配，根据定理，最大匹配=最小点覆盖，以及最小边覆盖=点数-最大匹配

//二分图是"可以将点集分为两个不相交的部分，所有边连接的两个顶点在不同的部分中"的图

//二分图的匹配：边集的任意子集的任意两条边都没有公共顶点，则这个子集是一个匹配
//二分图的最大匹配：所有匹配中边数最多的
//最小点覆盖：选最少的点，满足每条边至少有一个端点被选
//最大独立集：选最多的点，满足两两之间没有边相连
//这里的二分图是无向图
//如果最大匹配中所有点都被匹配，那么叫做完美匹配

#include <iostream>
#include <cstring>

const int MAXN = 505;
bool graph[MAXN][MAXN];
bool vis[MAXN];
int toLeft[MAXN];//标记右边节点i连到了哪个左边界点，即toLeft[i]

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
    //返回最大的边数
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