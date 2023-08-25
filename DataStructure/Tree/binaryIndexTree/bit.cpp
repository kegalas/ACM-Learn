//复杂度 单次查询 logn 单次修改 logn
//树状数组，维护的是数组的前缀和，有大量的应用
//luogu P3374

//普通的树状数组要维护的信息，其运算要满足结合律和可差分
//结合律不难理解，可差分指的是若已知x op y和x，则可以求出y
//这样的运算例如加，乘，异或。乘如果在模意义下可差分，需要保证每个数都有逆元，如果模数为质数则肯定有
//gcd,max这种是不可差分的

#include <iostream>

int const MAXN = 1000005;
using LL = long long;

class Fenwick{
public:
    LL data[MAXN];
    int size = 0;
    
    void init(int size_){size=size_;}
    
    inline int lowbit(int x){
        return x&(-x);
    }
    
    void update(int p, LL k){//位置p的元素加k
        for(;p<=size;p+=lowbit(p)){
            data[p]+=k;
        }
    }
    
    LL query(int p){//查询[1,p]的和
        LL ret=0;
        for(;p;p-=lowbit(p)){
            ret += data[p];
        }
        return ret;
    }
};

Fenwick fenwick;

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    
	int n,m;
    std::cin>>n>>m;
    //数组长度，查询数
    fenwick.init(n);
    for(int i=1;i<=n;i++){
        LL tmp;
        std::cin>>tmp;
        fenwick.update(i,tmp);
    }

    for(int i=1;i<=m;i++){
        int op;
        int x,y;
        LL k;
        std::cin>>op>>x;
        if(op==1){
            std::cin>>k;
            //将单点增加k，如果想要改成修改，则可以update(x,k-查询x位置上的数)
            fenwick.update(x,k);
        }
        else{
            std::cin>>y;
            //输出[x,y]的数组和
            std::cout<<fenwick.query(y)-fenwick.query(x-1)<<"\n";
        }
    }
    
    return 0;
}