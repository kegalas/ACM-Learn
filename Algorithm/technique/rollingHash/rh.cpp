//atcoder abc331_f
//滚动哈希+线段树
#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <array>

using LL = long long;

int const MAXN = 1000005;

constexpr int B = 5;
LL mod[B] = {998244353, 1000000007, 1000000009, 1000000021, 1000000033};
LL base[B];

struct Hash{
    LL h1, h2, pw;  
    Hash():h1(0),h2(0),pw(1){} // 字符串拼接哈希时，拼接操作的幺元
};
using T = std::array<Hash, B>; // 存多个哈希，以减小碰撞概率

T operator+(T lhs, T rhs){
    // 区间拼接
    T res;
    for(int i=0;i<B;i++){
        res[i].h1 = (lhs[i].h1*rhs[i].pw + rhs[i].h1)%mod[i];
        res[i].h2 = (lhs[i].h2 + lhs[i].pw*rhs[i].h2)%mod[i];
        res[i].pw = (lhs[i].pw*rhs[i].pw)%mod[i];
        // 见字符串拼接的哈希
    }
    return res;
}

T gen(char c){
    // 单个字符的哈希
    T res;
    for(int i=0;i<B;i++){
        res[i].h1 = c;
        res[i].h2 = c;
        res[i].pw = base[i];
    }
    return res;
}

struct Node
{
    int s,t;//该端点的起点和终点下标
    T v;
};

Node st[MAXN*4+2];
std::string arr;

void build(int s, int t, int p=1){
    st[p].s = s;
    st[p].t = t;
    if(s==t) {
        st[p].v = gen(arr[s]);
        return;
    }
    int m = s+((t-s)>>1);
    build(s,m,p*2);
    build(m+1,t,p*2+1);
    st[p].v = st[p*2].v + st[p*2+1].v;
}

void update(int i, char ch, int p=1){
    int s = st[p].s, t = st[p].t;
    if(s==t){
        st[p].v = gen(ch);
        return;
    }
    
    int m = s+((t-s)>>1);
    if(i<=m) update(i, ch, p*2);
    if(i>m)  update(i, ch, p*2+1);
    st[p].v = st[p*2].v + st[p*2+1].v;
}

T query(int l, int r, int p=1){
    int s = st[p].s, t = st[p].t;
    if(l<=s && t<=r) return st[p].v;

    int m = s+((t-s)>>1);
    T ret;
    if(l<=m) ret = ret+query(l,r,p*2);
    if(r>m)  ret = ret+query(l,r,p*2+1);
    
    return ret;
}


void solve(){
    std::mt19937_64 rng(time(0));
    for(int i=0;i<B;i++){
        base[i] = rng() % mod[i]; // 即随机生成的x
    }
    
    int n,q;
    std::cin>>n>>q;
    std::cin>>arr;
    arr = '#'+arr;
    build(1, n);
    
    while(q--){
        int op;
        std::cin>>op;
        if(op==1){
            int x;
            char c;
            std::cin>>x>>c;
            update(x,c);
        }
        else{
            // 判断[l,r]是否为回文串
            int l, r;
            std::cin>>l>>r;
            auto h = query(l, r);
            bool ans = 1;
            for(int i=0;i<B;i++){
                ans &= (h[i].h1==h[i].h2);
            }
            std::cout<<(ans?"Yes":"No")<<"\n";
        }
    }
}