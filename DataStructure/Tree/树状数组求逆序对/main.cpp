//Luogu P1908
#include <iostream>
#include <algorithm>

#define LL long long

const int MAXN = 500005;

LL arr[MAXN];
LL n;

struct Par{
    LL value,id;
}par[MAXN];

bool cmp(const Par& a,const Par& b){
    if(a.value!=b.value) return a.value<b.value;
    return a.id<b.id;
}

LL bit[MAXN];

inline LL lowbit(LL n){
    return n&(-n);
}

void update(LL p, LL k){
    for(;p<=n;p+=lowbit(p)){
        bit[p]+=k;
    }
}

long long query(LL p){
    LL ans=0;
    for(;p;p-=lowbit(p)){
        ans+=bit[p];
    }
    return ans;
}

int main(){
    std::cin>>n;

    for(int i=1;i<=n;i++){
        std::cin>>par[i].value;
        par[i].id = i;
    }

    std::sort(par+1,par+1+n,cmp);

    for(int i=1;i<=n;i++){
        arr[par[i].id] = i;
    }//这一步其实是离散化

    LL ans = 0;

    for(int i=1;i<=n;i++){
        ans += query(arr[i]);
        update(arr[i],1);
    }

    ans = n*(n-1)/2-ans;//本来统计的是等于或顺序对，现在反过来计算逆序对

    std::cout<<ans<<"\n";

    return 0;
}
