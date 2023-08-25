//二维树状数组 支持单点修改和区间查询
//loj 133
#include <iostream>

int const MAXN = 5005;
using LL = long long;

class BIT2D{
public:
    int N,M;
    LL data[MAXN][MAXN];
    
    void init(int n,int m){
        N = n, M = m;
    }
    
    inline int lowbit(int x){
        return x&(-x);
    }
    
    void add(int x, int y, LL v){//把(x,y)这个点加上v
        for(int i=x;i<=N;i+=lowbit(i)){
            for(int j=y;j<=M;j+=lowbit(j)){
                data[i][j] += v;
            }
        }
    }
    
    LL sum(int x, int y){
        LL ret = 0;
        for(int i=x;i>0;i-=lowbit(i)){
            for(int j=y;j>0;j-=lowbit(j)){
                ret += data[i][j];
            }
        }
        return ret;
    }
    
    LL query(int x1, int y1, int x2, int y2){//查询(x1,y1)-(x2,y2)这个矩形的区间和
        return sum(x2,y2) - sum(x2,y1-1) - sum(x1-1, y2) + sum(x1-1, y1-1);
    }
};

BIT2D bit2d;

void solve(){
    int n,m;
    std::cin>>n>>m;
    bit2d.init(n,m);
    int ope;
    while(std::cin>>ope){
        if(ope==1){
            int x,y;LL k;
            std::cin>>x>>y>>k;
            bit2d.add(x,y,k);
        }
        else{
            int a,b,c,d;
            std::cin>>a>>b>>c>>d;
            std::cout<<bit2d.query(a,b,c,d)<<"\n";
        }
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    
	int T;
	T=1;
	while(T--){
	    solve();
	}

    return 0;
}
