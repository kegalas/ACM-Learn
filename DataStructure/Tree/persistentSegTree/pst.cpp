//可持久化线段树，单点修改、区间查询，操作复杂度logn
//luogu p3919
//可持久化线段树是完全可持久化的，意味着可以查询历史修改，以及对每一个历史状态都可以再修改
#include <iostream>

using LL = long long;
int const MAXV = 3e7+5;
int const MAXN = 1e6+5;

struct Node{
    LL val;
    int ls,  rs;
}st[MAXV];

inline int& ls(int x){return st[x].ls;}
inline int& rs(int x){return st[x].rs;}
inline LL& val(int x){return st[x].val;}
inline int getMid(int s, int t){
    if(s+t==0) return 0;
    if(s+t>0) return (s+t)/2;
    return -((-s-t+1)/2);
}

int stcnt = 1;
int L = 1, R = 1e6+5;//这里根据题目信息选择区间范围
LL arr[MAXN], roots[MAXN];//arr存初始数组，roots[i]表示第i次操作的根节点

void build(int s=L, int t=R, int p=1){
    //一般不会完全动态开点，会把初始状态建树
    if(s==t) val(p) = arr[s];
    else{
        ls(p) = ++stcnt, rs(p) = ++stcnt;
        int mid = getMid(s,t);
        build(s,mid,ls(p));
        build(mid+1,t,rs(p));
        val(p) = val(ls(p)) + val(rs(p));
    }
}

void assign(int i, LL k, int p, int q, int s=L, int t=R){
    //这里是单点修改操作，如果改成区间加，则下一行改成val(q)=val(p)+k
    //修改第i位为k，对版本x的根节点p进行修改，修改完为版本y的根节点q
    if(s==t) val(q) = k;
    else{
        ls(q) = ls(p), rs(q) = rs(p);
        int mid = getMid(s,t);
        if(i<=mid) ls(q) = ++stcnt, assign(i,k,ls(p),ls(q),s,mid);
        else rs(q) = ++stcnt, assign(i,k,rs(p),rs(q),mid+1,t);
        val(q) = val(ls(q)) + val(rs(q));
    }
}

LL query(int l, int r, int p, int s=L, int t=R){
    //查询区间和
    //对版本p查询
    if(s>r || t<l) return 0;
    else if(s>=l && t<=r) return val(p);
    else{
        int mid = getMid(s,t);
        return query(l,r,ls(p),s,mid) + query(l,r,rs(p),mid+1,t);
    }
}

void solve(){
    int m;
    std::cin>>R>>m;
    for(int i=L;i<=R;i++){
        std::cin>>arr[i];
    }
    build();
    roots[0] = 1;//别忘了初始化初始区间的根
    for(int t=1;t<=m;t++){
        int v, o;
        std::cin>>v>>o;//v是对第v个版本操作
        if(o==1){
            int i;LL k;
            std::cin>>i>>k;
            roots[t] = ++stcnt;//本题的修改和查询都算一个版本
            assign(i,k,roots[v],roots[t]);
            //注意你把第1个版本修改为第5个，不会对2、3、4版本产生影响
        }
        else{
            int i;
            std::cin>>i;
            roots[t] = roots[v];//虽然修改也算一个版本，但是可以和之前的合并
            std::cout<<query(i,i,roots[v])<<"\n";
        }
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
