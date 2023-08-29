//权值线段树
//loj 104

//权值线段树大部分时候是用来代替平衡树使用的
//和树状数组求逆序对很像，他把每一个[x,x]范围上的节点视作一个桶，插入数据时，add(x,x,1)，删除一个时add(x,x,-1)。
//查询复杂度为O(logv)，v为值域

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
int L = -(1e7+5), R = 1e7+5;

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

void insert(int v){//插入一个数
    add(v,v,1);
}

void remove(int v){//删除一个数，相同的只删一个
    add(v,v,-1);
}

int countL(int v){//计算小于v的数的个数
    return query(L, v-1);
}

int countG(int v){//计算大于v的数的个数
    return query(v+1, R);
}

int rank(int v){//求v的排名，即小于v的数的个数+1
    return countL(v)+1;
}

int kth(int k, int p=1, int s=L, int t=R){//查询排名第k的数
    if(s==t) return s;
    int mid = getMid(s,t);
    if(val(ls(p)) >= k)
        return kth(k, ls(p), s, mid);
    else
        return kth(k-val(ls(p)), rs(p), mid+1, t);
}

int pre(int v){//查询v的前驱，即第一个比v小的数，可能需要保证一定存在
    int r = countL(v);
    return kth(r);
}

int suc(int v){//查询v的后继
    int r = val(1) - countG(v) + 1;
    return kth(r);
}

void solve(){
    int n;
    std::cin>>n;
    while(n--){
        int ope,x;
        std::cin>>ope>>x;
        if(ope==1) insert(x);
        else if(ope==2) remove(x);
        else if(ope==3) std::cout<<rank(x)<<"\n";
        else if(ope==4) std::cout<<kth(x)<<"\n";
        else if(ope==5) std::cout<<pre(x)<<"\n";
        else std::cout<<suc(x)<<"\n";
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
