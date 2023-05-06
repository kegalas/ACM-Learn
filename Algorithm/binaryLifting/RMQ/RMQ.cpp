//复杂度 单次查询 logn 预处理 nlogn
//luogu P3865
#include <cstdio>
#include <iostream>

const int MAXN = 100005;
const int LOGN = 21;

int fmax[MAXN][LOGN+1];
//fmax[a][b]表示[a,a+2^b-1]中的最大值
int logn[MAXN];
//预先计算logn

int main(){
    int n,m;
    //数组大小以及查询次数
    scanf("%d%d",&n,&m);

    for(int i=1;i<=n;i++){
        scanf("%d",&fmax[i][0]);
    }

    logn[1] = 0;
    logn[2] = 1;

    for(int i=3;i<MAXN;i++){
        logn[i] = logn[i/2]+1;
        //预先计算logn
    }

    for(int j=1;j<=LOGN;j++){
        for(int i=1;i+(1<<j)-1<=n;i++){
            fmax[i][j] = std::max(fmax[i][j-1],fmax[i+(1<<(j-1))][j-1]);
        }
    }

    for(int i=1;i<=m;i++){
        int a,b;
        scanf("%d%d",&a,&b);
        //查询[a,b]分为两部分，即[a,a+2^s-1]与[b-2^s+1,b]
        int s = logn[b-a+1];
        printf("%d\n",std::max(fmax[a][s],fmax[b-(1<<s)+1][s]));
    }

    return 0;
}
