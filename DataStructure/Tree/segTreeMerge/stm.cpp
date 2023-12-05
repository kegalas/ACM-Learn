//线段树合并，合并复杂度大概是O(klogN)，N是值域，k是若干线段树一共进行过k次插入
//luogu p3224
#include <iostream>

using LL = long long;
int const MAXN = 100005;

class DSU{
public:
    int fa[MAXN], rk[MAXN];
    
    void init(int n){
        for(int i=1;i<=n;i++) fa[i] = i, rk[i] = 1;
    }

    int findc(int x){
        //带路径压缩的find
        return fa[x]==x ? x : (fa[x] = findc(fa[x]));
    }

    void mergec(int x, int y){
        //按秩合并+路径压缩，如果不需要则直接 fa[findc(x)] = findc(y);
        x = findc(x), y = findc(y);
        if(x==y) return;
        if(rk[x]>rk[y]) std::swap(x,y);
        fa[y] = x;
        if(rk[x]==rk[y]) rk[y]++;
    }
};

DSU dsu;

int const MAXV = 8e6+5;//能开多大开多大，128M可以开到800万

struct Node{
    LL val, tag;
    int ls,  rs;
}st[MAXV];

inline int& ls(int x){return st[x].ls;}
inline int& rs(int x){return st[x].rs;}
inline LL& val(int x){return st[x].val;}
inline LL& tag(int x){return st[x].tag;}

inline int getMid(int s, int t){
    //处理负数边界时，需要强行向下取整，而不是向零取整
    if(s+t==0) return 0;
    if(s+t>0) return (s+t)/2;
    return -((-s-t+1)/2);
}

int stcnt = 1;
int L = 1, R = MAXN;//这里根据题目信息选择区间范围

void upd(int &p, LL k, int len){
    if(!p) p = ++stcnt;
    val(p) += k * len;
    tag(p) += k;
}

void spreadTag(int p, int len){
    if(len<=1) return;
    upd(ls(p), tag(p), len-len/2);
    upd(rs(p), tag(p), len/2);
    tag(p) = 0;
}

LL query(int l, int r, int p = 1, int s = L, int t = R){
    if(s>=l && t<=r) return val(p);
    spreadTag(p, t-s+1);
    int mid = getMid(s,t);
    LL ret = 0;
    if(mid >= l) ret += query(l, r, ls(p), s, mid);
    if(mid < r)  ret += query(l, r, rs(p), mid+1, t);
    return ret;
}

void add(int l, int r, LL k, int p = 1, int s = L, int t = R){
    if(s>=l && t<=r){
        val(p) += k * (t-s+1);
        tag(p) += k;
        return;
    }
    spreadTag(p, t-s+1);
    int mid = getMid(s,t);
    if(mid >= l) add(l, r, k, ls(p), s, mid);
    if(mid < r)  add(l, r, k, rs(p), mid+1, t);
    val(p) = val(ls(p)) + val(rs(p));
}

int kth(int k, int p=1, int s=L, int t=R){//查询排名第k的数
    if(s==t) return val(p)>=k?s:0;
    int mid = getMid(s,t);
    if(val(ls(p)) >= k)
        return kth(k, ls(p), s, mid);
    else
        return kth(k-val(ls(p)), rs(p), mid+1, t);
}

//动态开点线段树，之前的各种操作中都有p=1这一参数默认值，这其实是根节点的意思。也就是如果我们设置不同的p，可以开多颗线段树。
//线段树合并就是把重合位置的节点的值加起来，对于没有重合位置的节点则原地保留，常常用于权值线段树

int merge(int p, int q, int s=L, int t=R){
    //不新开空间的合并方式
    //把q为根的树合并到p为根的树上，返回p，即新根节点
    //由于各题不一样，所以要在合并后手动把roots[j]指定为p
    if(!p||!q) return p+q;
    if(s==t) return val(p)+=val(q), p;
    int mid = getMid(s,t);
    ls(p) = merge(ls(p), ls(q), s, mid);
    rs(p) = merge(rs(p), rs(q), mid+1, t);
    val(p) = val(ls(p)) + val(rs(p));
    return p;
}

// int merge(int p, int q, int s=L, int t=R){
    // //新开空间的合并方式
    // //把p,q为根的两棵树合并到r为根的树上，返回r，即新根节点
    // //由于各题不一样，所以要在合并后手动把roots[i]和[j]指定为r
    // if(!p||!q) return p+q;
    // int r = ++stcnt;
    // if(s==t) return val(r) = val(p)+val(q), r;
    // int mid = getMid(s,t);
    // ls(r) = merge(ls(p), ls(q), s, mid);
    // rs(r) = merge(rs(p), rs(q), mid+1, t);
    // val(r) = val(ls(r)) + val(rs(r));
    // return r;
// }

int roots[MAXN];
int mp[MAXN];

void solve(){
    int m;
    std::cin>>R>>m;
    dsu.init(R);
    mp[0] = -1;
    for(int i=1;i<=R;i++){
        int x;
        std::cin>>x;
        mp[x] = i;
        roots[i] = ++stcnt;
        add(x,x,1,roots[i]);
    }
    for(int i=1;i<=m;i++){
        int u,v;
        std::cin>>u>>v;
        int fu = dsu.findc(u), fv = dsu.findc(v);
        dsu.mergec(u,v);
        roots[fv] = merge(roots[fu],roots[fv]);
    }
    int q;
    std::cin>>q;
    while(q--){
        char o;int x,y;
        std::cin>>o>>x>>y;
        if(o=='Q'){
            int fx = dsu.findc(x);
            int ans = kth(y,roots[fx]);
            std::cout<<mp[ans]<<"\n";
        }
        else{
            int fx = dsu.findc(x), fy = dsu.findc(y);
            dsu.mergec(x,y);
            roots[fy] = merge(roots[fx],roots[fy]);
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
