//树状数组

#include <iostream>
#include <cstdio>
#define MAXN 500005

using namespace std;

int arr[MAXN];
int bit[MAXN];

int n,m;

inline int lowbit(int n){
    return n&(-n);
}

void update(int p, int k){
    for(;p<=n;p+=lowbit(p)){
        bit[p]+=k;
    }
}

long long query(int p){
    int ans=0;
    for(;p;p-=lowbit(p)){
        ans+=bit[p];
    }
    return ans;
}

int main(){
    scanf("%d%d",&n,&m);
    //数组长度，查询数
    for(int i=1;i<=n;i++){
        scanf("%d",&arr[i]);
        update(i,arr[i]);
    }

    for(int i=1;i<=m;i++){
        int op;
        int x,y,k;
        scanf("%d",&op);
        scanf("%d",&x);
        if(op==1){
            scanf("%d",&k);
            //将单点修改为k
            update(x,k);
        }
        else{
            scanf("%d",&y);
            //输出[x,y]的数组和
            cout<<query(y)-query(x-1)<<endl;
        }
    }
    return 0;
}

