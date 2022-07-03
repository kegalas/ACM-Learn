//线段树

#include <iostream>
#include <cstdio>

using namespace std;

#define MAXN 100010

struct segmentTree
{
    int l,r;
    long long val;
    long long tag;
};

segmentTree st[4*MAXN+2];
long long arr[MAXN+2];

void build(long long p, long long l, long long r){
    st[p].l = l;
    st[p].r = r;
    if(l==r) {
        st[p].val = arr[l];
        return;
    }
    int mid = (l+r)/2;
    build(p*2,l,mid);
    build(p*2+1,mid+1,r);
    st[p].val = st[p*2].val + st[p*2+1].val;
}

void spreadTag(int p){
    if(st[p].tag){
        st[p*2].val   += st[p].tag*(st[p*2].r-st[p*2].l+1);
        st[p*2+1].val += st[p].tag*(st[p*2+1].r-st[p*2+1].l+1);
        st[p*2].tag   += st[p].tag;
        st[p*2+1].tag += st[p].tag;
        st[p].tag = 0;
    }
}

void update_add(int p, int ul, int ur, int k){
    if(ul<=st[p].l&&ur>=st[p].r){
        st[p].val+=(long long)(k*(st[p].r-st[p].l+1));
        st[p].tag+=k;
        return;
    }
    spreadTag(p);
    int mid = (st[p].l+st[p].r)/2;
    if(ul<=mid) update_add(p*2,  ul, ur, k);
    if(ur>mid)  update_add(p*2+1,ul, ur, k);
    st[p].val = st[p*2].val + st[p*2+1].val;
}

long long query(int p, int ql, int qr){
    if(ql<=st[p].l&&qr>=st[p].r) return st[p].val;
    spreadTag(p);
    int mid = (st[p].l+st[p].r)/2;
    long long ans = 0;
    if(ql<=mid) ans+=query(p*2,ql,qr);
    if(qr>mid)  ans+=query(p*2+1,ql,qr);
    return ans;
}




int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%lld",&arr[i]);
    }

    build(1,1,n);


    for(int i=1;i<=m;i++){
        int ope;
        cin>>ope;
        if(ope==1){
            int x,y,z;
            scanf("%d%d%d",&x,&y,&z);
            update_add(1,x,y,z);
        }
        else{
            int x,y;
            scanf("%d%d",&x,&y);
            cout<<query(1,x,y)<<endl;
        }
    }

    return 0;
}

