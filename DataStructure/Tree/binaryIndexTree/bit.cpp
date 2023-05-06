//复杂度 单次查询 logn 单次修改 logn
//树状数组

#include <iostream>
#include <cstdio>
#define MAXN 500005

using namespace std;

int arr[MAXN];
int bit[MAXN];

inline int lowbit(int n){
    return n&(-n);
}

void update(int p, int k, int n){
    for(;p<=n;p+=lowbit(p)){
        bit[p]+=k;
    }
}

int query(int p){
    int ans=0;
    for(;p;p-=lowbit(p)){
        ans+=bit[p];
    }
    return ans;
}

int main(){
	int n,m;
    scanf("%d%d",&n,&m);
    //数组长度，查询数
    for(int i=1;i<=n;i++){
        scanf("%d",&arr[i]);
        update(i,arr[i],n);
    }

    for(int i=1;i<=m;i++){
        int op;
        int x,y,k;
        scanf("%d",&op);
        scanf("%d",&x);
        if(op==1){
            scanf("%d",&k);
            //将单点增加k，如果想要改成修改，则可以update(x,-arr[x]+k)
            update(x,k,n);
        }
        else{
            scanf("%d",&y);
            //输出[x,y]的数组和
            cout<<query(y)-query(x-1)<<endl;
        }
    }
    return 0;
}

