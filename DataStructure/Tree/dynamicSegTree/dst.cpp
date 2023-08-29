//动态开点线段树
//luogu p3372，由于并没有找到合适的习题，我把题中的查询范围全部加了一个偏移值-5e4

//动态开点线段树并不是动态分配内存，只是在范围很大，但查询不多的时候，可以用
//普通线段树的空间复杂度是O(n)，单次操作的时间复杂度是O(logn)
//动态开点，设查询为m次，时间复杂度仍然为O(logn)，但是空间复杂度变成O(mlogn)
//动态开点还可以处理查询范围为负数的情况，比如查询[-5,6]这一段上的和
//动态开点假设初始数组全部为0，输入一个数组时直接add修改线段树即可

#include <iostream>

using LL = long long;
int const MAXN = 8e6+5;//能开多大开多大，128M可以开到800万

struct Node{
    LL val, tag;
    int ls,  rs;
}st[MAXN];

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
int L = -(1e6+5), R = 1e6+5;//这里根据题目信息选择区间范围

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

void solve(){
    int n,m;
    std::cin>>n>>m;
    int const offset = -5e4;
    for(int i=1;i<=n;i++){
        int a;
        std::cin>>a;
        add(i+offset,i+offset,a);
    }
    while(m--){
        int ope, l, r, x;
        std::cin>>ope>>l>>r;
        l += offset;
        r += offset;
        if(ope==1){
            std::cin>>x;
            add(l,r,x);
        }
        else{
            std::cout<<query(l,r)<<"\n";
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
