//二维树状数组 支持单点修改和区间查询
//poj 1195
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <cstdio>

int const MAXN = 1055;

class BIT2D{
public:
    int N,M;
    int data[MAXN][MAXN];
    
    void init(int n,int m){
        N = n, M = m;
    }
    
    inline int lowbit(int n){
        return n&(-n);
    }
    
    void add(int x, int y, int v){//把(x,y)加上v
        for(int i=x;i<=N;i+=lowbit(i)){
            for(int j=y;j<=M;j+=lowbit(j)){
                data[i][j] += v;
            }
        }
    }
    
    int sum(int x, int y){
        int ret = 0;
        for(int i=x;i>0;i-=lowbit(i)){
            for(int j=y;j>0;j-=lowbit(j)){
                ret += data[i][j];
            }
        }
        return ret;
    }
    
    int query(int x1, int y1, int x2, int y2){//查询(x1,y1)-(x2,y2)这个矩形的区间和
        return sum(x2,y2) - sum(x2,y1-1) - sum(x1-1, y2) + sum(x1-1, y1-1);
    }
};

BIT2D bit2d;

void solve(){
    int ope;
    while(scanf("%d",&ope)){
        if(ope==0){
            int s;
            scanf("%d",&s);
            bit2d.init(s,s);
        }
        else if(ope==1){
            int x,y,a;
            scanf("%d%d%d",&x, &y, &a);
            x++,y++;
            bit2d.add(x,y,a);
        }
        else if(ope==2){
            int x1,y1,x2,y2;
            scanf("%d%d%d%d",&x1, &y1, &x2, &y2);
            x1++,y1++,x2++,y2++;
            printf("%d\n",bit2d.query(x1,y1,x2,y2));
        }
        else{
            break;
        }
    }
}

int main(){

	int T;
	T=1;
	while(T--){
	    solve();
	}

    return 0;
}
