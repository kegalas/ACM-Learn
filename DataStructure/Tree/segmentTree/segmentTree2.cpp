//luogu 3372
#include <iostream>
#include <cstdio>

using namespace std;

typedef long long ll;

const int MAXN = 100005;

ll st[MAXN*4+2];//对于一颗线段树，n个数所组成的树最多有4n-5个节点，开大了一点
ll tag[MAXN*4+2];
ll arr[MAXN];

void build(int s, int t, int p){//区间左端点、右端点、区间编号
    if(s==t){
        st[p] = arr[s];
        return;
    }
    int m = s+((t-s)>>1);//写成(s+t)>>1可能会爆
    build(s,m,p*2);
    build(m+1,t,p*2+1);
    st[p] = st[p*2]+st[p*2+1];
}

void update(int l, int r, int s, int t, int p, ll c){//c表示加减的数值
    if(l<=s&&t<=r){
        st[p]+=(t-s+1)*c;
        tag[p]+=c;
        return;
    }
    ll m = s + ((t-s)>>1);
    if(tag[p]&&s!=t){
        st[p*2]   += (m-s+1)*tag[p];
        st[p*2+1] += (t-m)*tag[p];
        tag[p*2]  += tag[p];
        tag[p*2+1]+= tag[p];
        tag[p]=0;
    }
    if(l<=m) update(l, r, s, m, p*2, c);
    if(r>m)  update(l, r, m+1, t, p*2+1, c);
    st[p] = st[p*2] + st[p*2+1];

}

ll query(int l, int r, int s, int t, int p){
    if(l<=s&&t<=r){
        return st[p];
    }
    ll sum=0;
    ll m = s+((t-s)>>1);
    if(tag[p]){
        st[p*2]   += (m-s+1)*tag[p];
        st[p*2+1] += (t-m)*tag[p];
        tag[p*2]  += tag[p];
        tag[p*2+1]+= tag[p];
        tag[p]=0;
    }
    if(l<=m) sum+=query(l,r,s,m,p*2);
    if(r>m)  sum+=query(l,r,m+1,t,p*2+1);
    return sum;
}

int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%lld",&arr[i]);   
    }
    build(1,n,1);

    for(int i=1;i<=m;i++){
        int ope;
        cin>>ope;
        if(ope==1){
            int x,y,z;
            scanf("%d%d%d",&x,&y,&z);
            update(x, y, 1, n, 1, z);
        }
        else{
            int x,y;
            scanf("%d%d",&x,&y);
            cout<<query(x, y, 1, n, 1)<<endl;
        }
    }

    return 0;
}
