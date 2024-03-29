//复杂度 单次查询 logn 单次修改 logn
//luogu p3372
//线段树维护的数据要求满足结合律，比如区间和，区间最大区间最小，区间gcd
//区间修改一般支持加、乘、赋值

#include <iostream>

int const MAXN = 100005;
using LL = long long;

struct Node
{
    int s,t;//该端点的起点和终点下标
    LL tag, v;
};

Node st[MAXN*4+2];
LL arr[MAXN];

void build(int s, int t, int p=1){
    st[p].s = s;
    st[p].t = t;
    if(s==t) {
        st[p].v = arr[s];
        st[p].tag = 0;
        return;
    }
    int m = s+((t-s)>>1);
    build(s,m,p*2);
    build(m+1,t,p*2+1);
    st[p].v = st[p*2].v + st[p*2+1].v;
    st[p].tag = 0;
}

void spreadTag(int p){
    if(st[p].tag){
        int s = st[p].s, t = st[p].t;
        int m = s+((t-s)>>1);
        st[p*2].v     += (m-s+1)*st[p].tag;
        st[p*2+1].v   += (t-m)*st[p].tag;
        st[p*2].tag   += st[p].tag;
        st[p*2+1].tag += st[p].tag;
        st[p].tag=0;
    }
}

void update(int l, int r, LL k, int p=1){
    int s = st[p].s, t = st[p].t;
    if(l<=s && t<=r){
        st[p].v   += (t-s+1) * k;
        st[p].tag += k;
        return;
    }
    spreadTag(p);
    
    int m = s+((t-s)>>1);
    if(l<=m) update(l, r, k, p*2);
    if(r>m)  update(l, r, k, p*2+1);
    st[p].v = st[p*2].v + st[p*2+1].v;
}

LL query(int l, int r, int p=1){
    int s = st[p].s, t = st[p].t;
    if(l<=s && t<=r) return st[p].v;
    
    spreadTag(p);
    int m = s+((t-s)>>1);
    LL ret = 0;
    if(l<=m) ret+=query(l,r,p*2);
    if(r>m)  ret+=query(l,r,p*2+1);
    
    return ret;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    
    int n,m;
    std::cin>>n>>m;
    
    for(int i=1;i<=n;i++){
        std::cin>>arr[i];
    }
    
    build(1,n);
    
    while(m--){
        int ope,x,y,z;
        std::cin>>ope;
        
        if(ope==1){
            std::cin>>x>>y>>z;
            update(x,y,z);
        }
        else{
            std::cin>>x>>y;
            std::cout<<query(x,y)<<"\n";
        }
    }

    return 0;
}

