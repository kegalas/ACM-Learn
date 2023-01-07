//luogu 6577
//二分图的最大权匹配，必须是完备匹配才能正确运行，即左右各n个点，最大匹配有n条边
//随机数据O(n^3)，最坏O(n^4)，所以luogu上会超时一些数据
#include <iostream>
#include <cstring>

typedef long long LL;

const int MAXN = 505;
const LL INF = 1e17;
LL graph[MAXN][MAXN];
LL labelL[MAXN], labelR[MAXN];
bool visL[MAXN],visR[MAXN];
int toLeft[MAXN];
LL upd[MAXN];

bool match(int const & i, int const & pointNum){
    visL[i] = true;
    for(int j=1;j<=pointNum;j++){
        if(!visR[j]){
            if(labelL[i]+labelR[j]-graph[i][j]==0){
                visR[j] = true;
                if(!toLeft[j]||match(toLeft[j],pointNum)){
                    toLeft[j] = i;
                    return true;
                }
            }
            else{
                upd[j] = std::min(upd[j],labelL[i]+labelR[j]-graph[i][j]);
            }
        }
    }
    return false;
}

LL KM(int const & pointNum){
    std::memset(toLeft,0,sizeof(toLeft));
    for(int i=1;i<=pointNum;i++){
        labelL[i] = -INF;
        labelR[i] = 0;
        for(int j=1;j<=pointNum;j++) labelL[i] = std::max(labelL[i], graph[i][j]);
    }

    for(int i=1;i<=pointNum;i++){
        for(int j=1;j<=pointNum;j++) upd[j] = INF;
        while(true){
            std::memset(visL,0,sizeof(visL));
            std::memset(visR,0,sizeof(visR));
            if(match(i,pointNum)) break;
            LL delta = INF;
            for(int j=1;j<=pointNum;j++)
                if(!visR[j]) delta = std::min(delta,upd[j]);
            for(int j=1;j<=pointNum;j++){
                if(visL[j]) labelL[j] -= delta;
                if(visR[j]) labelR[j] += delta;
            }
        }
    }

    LL ans = 0;
    for(int i=1;i<=pointNum;i++) ans += graph[toLeft[i]][i];
    return ans;//输出最大权匹配的权值和
}

int main(){
    int n,e;//一边的点数；边数
    std::cin>>n>>e;
    
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            graph[i][j] = -INF;
        }
    }
    
    for(int i=1;i<=e;i++){
        int x,y;
        std::cin>>x>>y;
        std::cin>>graph[x][y];
    }

    std::cout<<KM(n)<<"\n";
    for(int i=1;i<=n;i++){
        std::cout<<toLeft[i]<<" ";
    }
    std::cout<<"\n";

    return 0;
}
