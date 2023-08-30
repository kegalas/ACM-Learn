//可持久化线段树，区间修改、区间查询，操作复杂度logn
//hdu 4348

#include <iostream>

using LL = long long;
int const MAXV = 3e6+5;
int const MAXN = 1e5+5;

struct Node{
    LL val, tag;
    int ls,  rs;
}st[MAXV];

inline int& ls(int x){return st[x].ls;}
inline int& rs(int x){return st[x].rs;}
inline LL& val(int x){return st[x].val;}
inline LL& tag(int x){return st[x].tag;}
inline int getMid(int s, int t){
    if(s+t==0) return 0;
    if(s+t>0) return (s+t)/2;
    return -((-s-t+1)/2);
}

int stcnt = 1;
int L = 1, R = 1e6+5;//这里根据题目信息选择区间范围
LL arr[MAXN], roots[MAXN];

void build(int s=L, int t=R, int p=1){
    if(s==t) val(p) = arr[s], tag(p) = 0;
    else{
        ls(p) = ++stcnt, rs(p) = ++stcnt;
        int mid = getMid(s,t);
        build(s,mid,ls(p));
        build(mid+1,t,rs(p));
        val(p) = val(ls(p)) + val(rs(p));
    }
}

void add(int l, int r, LL k, int p, int q, int s=L, int t=R){
    //l,r是修改范围，其他同单点修改
    ls(q) = ls(p), rs(q) = rs(p), tag(q) = tag(p);
    if(l<=s && t<=r){
        if(t>s) tag(q) += k;
    }
    else{
        int mid = getMid(s,t);
        if(s<=r && mid>=l) ls(q) = ++stcnt, add(l,r,k,ls(p),ls(q),s,mid);
        if(mid+1<=r && t>=l) rs(q) = ++stcnt, add(l,r,k,rs(p),rs(q),mid+1,t);
    }
    val(q) = val(p) + (std::min(r,t)-std::max(l,s)+1)*k;
}

LL query(int l, int r, int p, LL tg=0, int s=L, int t=R){
    //l,r是修改范围，tg是一种标记永久化的技术，其他同单点修改
    if(s>r || t<l) return 0;
    else if(s>=l && t<=r) return val(p) + tg*(t-s+1);
    else{
        int mid = getMid(s,t);
        return query(l,r,ls(p),tg+tag(p),s,mid) + query(l,r,rs(p),tg+tag(p),mid+1,t);
    }
}

void solve(){
    int m;
    std::cin>>m;
    for(int i=L;i<=R;i++){
        std::cin>>arr[i];
    }
    stcnt = 1;
    build();
    roots[0] = 1;
    int time = 0;//本题只有加数才算进行一次版本修改
    while(m--){
        char o;int l,r;LL d;
        std::cin>>o;
        if(o=='C'){
            std::cin>>l>>r>>d;//[l,r]上每个数+d
            time++;
            roots[time] = ++stcnt;
            add(l,r,d,roots[time-1],roots[time]);
        }
        else if(o=='Q'){
            std::cin>>l>>r;//查询当前版本[l,r]和
            std::cout<<query(l,r,roots[time])<<"\n";
        }
        else if(o=='H'){
            std::cin>>l>>r>>d;//查询版本d的[l,r]和
            std::cout<<query(l,r,roots[d])<<"\n";
        }
        else if(o=='B'){
            std::cin>>d;//把版本倒回d，中间的版本失效
            time = d;
        }
    }
    std::cout<<"\n";
}

signed main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

	while(std::cin>>R){//本题多组数据
	    solve();
	}

    return 0;
}
