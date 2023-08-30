//主席树，查询静态区间第k小，复杂度logn
//luogu p3834

#include <iostream>
#include <algorithm>

using LL = long long;
int const MAXV = 8e6+5;
int const MAXN = 2e5+5;

struct Node{
    LL val;
    int ls,  rs;
}st[MAXV];

inline int& ls(int x){return st[x].ls;}
inline int& rs(int x){return st[x].rs;}
inline LL& val(int x){return st[x].val;}
inline int getMid(int s, int t){
    //处理负数边界时，需要强行向下取整，而不是向零取整
    if(s+t==0) return 0;
    if(s+t>0) return (s+t)/2;
    return -((-s-t+1)/2);
}

int stcnt = 1;
int L = 1, R = 2e5+5;

void build(int s=L, int t=R, int p=1){
    //初始化建成全0的，因为主席树是权值线段树的可持久化版
    val(p) = 0;
    if(s!=t){
        ls(p) = ++stcnt, rs(p) = ++stcnt;
        int mid = getMid(s,t);
        build(s,mid,ls(p));
        build(mid+1,t,rs(p));
    }
}

void add(int i, LL k, int p, int q, int s=L, int t=R){
    //参数同单点修改
    if(s==t) val(q) = val(p) + k;
    else{
        ls(q) = ls(p), rs(q) = rs(p);
        int mid = getMid(s,t);
        if(i<=mid) ls(q) = ++stcnt, add(i,k,ls(p),ls(q),s,mid);
        else rs(q) = ++stcnt, add(i,k,rs(p),rs(q),mid+1,t);
        val(q) = val(ls(q)) + val(rs(q));
    }
}

int arr[MAXN], disc[MAXN], assi[MAXN],ori[MAXN];
//arr是输入的原数组，disc是离散化后的，assi是临时的辅助数组
//ori[i]代表着在arr里排名为i的数
int roots[MAXN];

int kth(int k, int p, int q, int s=L, int t=R){
    if(s==t) return ori[s];
    int mid = getMid(s,t);
    if(val(ls(q)) - val(ls(p))>=k){
        return kth(k, ls(p), ls(q), s, mid);
    }
    else{
        return kth(k-(val(ls(q))-val(ls(p))), rs(p), rs(q), mid+1, t);
    }
}

int lrkth(int l, int r, int k){
    //查询数组arr的[l,r]区间中第k小的数
    return kth(k,roots[l-1],roots[r]);
}

void solve(){
    int m;
    std::cin>>R>>m;
    for(int i=L;i<=R;i++){
        std::cin>>arr[i];
        disc[i] = assi[i] = arr[i]; 
    }
    std::sort(assi+L,assi+R+1);
    int last = std::unique(assi+L,assi+R+1) - (assi+L);
    for(int i=L;i<=R;i++){
        disc[i] = std::lower_bound(assi+L,assi+last,disc[i]) - (assi+L)+1;
        ori[disc[i]] = arr[i];
    }
    //这上面都是离散化和数据输入
    
    build();
    roots[0] = 1;
    for(int i=L;i<=R;i++){
        roots[i] = ++stcnt;
        add(disc[i],1,roots[i-1],roots[i]);
        //和权值线段树的思路一致
    }
    
    while(m--){
        int l,r,k;
        std::cin>>l>>r>>k;
        std::cout<<lrkth(l,r,k)<<"\n";
    }
}

signed main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

	int T;
	T=1;
	while(T--){
	    solve();
	}

    return 0;
}
