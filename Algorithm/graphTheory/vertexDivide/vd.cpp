//点分治 复杂度nlog^2n
//poj 1741
//查询树上长度小于等于k的路径的数量
#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <vector>
#include <cstdio>

int const MAXN = 10007;

struct Edge{
    int v,w,next;//指向的点，边权，下一条边
};

Edge edges[MAXN*2];
int head[MAXN],cnt;

inline void add(int u, int v, int w){
    edges[++cnt].w = w;
    edges[cnt].v = v;
    edges[cnt].next = head[u];
    head[u] = cnt;
}

int sz[MAXN], mss[MAXN];//树的大小（含自己），最大子树大小（不含自己）
int ctr=-1;//重心
bool del[MAXN];//这个点是否在分治的时候被删除

void dfsCtr(int u, int fa, int const n){//需要传入树的点的个数
    //执行完后ctr为本子树的重心
    sz[u] = 1, mss[u] = 0;
    for(int e=head[u];e;e=edges[e].next){
        int v = edges[e].v;
        if(v==fa || del[v]) continue;
        dfsCtr(v,u,n);
        if(ctr!=-1) return;
        mss[u] = std::max(mss[u],sz[v]);
        sz[u] += sz[v];
    }
    mss[u] = std::max(mss[u],n-sz[u]);
    if(mss[u]<=n/2) ctr = u, sz[fa] = n-sz[u];//注意要改编sz以保证复杂度正确
}

int dis[MAXN];//dis[x]存储点x到根root的距离
int indexx[MAXN];//要对节点编号按照dis进行排序，indexx[0]代表元素个数
int belong[MAXN];//判断子树节点属于哪一个子子树
int cntsame[MAXN];//查询[l,r]时，维护[l+1,r]中belong与l的belong相同的个数，见calc函数

bool cmp(int x,int y){return dis[x]<dis[y];}

void dfsDis(int u, int fa, int from){
    //获得子树到根节点的距离，from用于计算belong
    indexx[++indexx[0]] = u;
    belong[u] = from;
    for(int e=head[u];e;e=edges[e].next){
        int v = edges[e].v, w = edges[e].w;
        if(v==fa || del[v]) continue;
        dis[v] = dis[u] + w;
        cntsame[from]++;
        dfsDis(v,u,from);
    }
}

int calc(int u,int k){
    indexx[0] = 0;
    indexx[++indexx[0]] = u;
    belong[u] = u;
    dis[u] = 0;
    cntsame[u] = 1;
    for(int e=head[u];e;e=edges[e].next){
        int v = edges[e].v, w =edges[e].w;
        if(del[v]) continue;
        dis[v] = dis[u] + w;
        cntsame[v] = 1;
        dfsDis(v,u,v);
    }
    std::sort(indexx+1,indexx+1+indexx[0],cmp);
    
    int l=1, r=indexx[0],ans=0;
    while(l<r){
        int x = indexx[l], y = indexx[r];
        if(dis[x]+dis[y]>k){
            cntsame[belong[y]]--;//把cntsame由[l,r]转移,r-1]
            r--;
        }
        else{
            //显然，如果不考虑两个点在同一个子子树内，则l和l+1~r的每个点都满足dis[x]+dis[y]<=k
            //减去同子子树的情况，即减去[l+1,r]中和l拥有相同belong的点
            cntsame[belong[x]]--;//把cntsame由[l,r]转移到[l+1,r]，一定要注意顺序
            ans += r-l-cntsame[belong[x]];
            l++;
        } 
    }
    return ans;
}

int res = 0;

void divide(int u, int k){
    del[u] = 1;
    res += calc(u,k);
    for(int e=head[u];e;e=edges[e].next){
        int v = edges[e].v, w = edges[e].w;
        if(del[v]) continue;
        ctr = -1;
        dfsCtr(v,0,sz[v]);
        divide(ctr,k);
    }
}

void solve(int n, int k){
    for(int i=1;i<n;i++){
        int u,v,w;
        std::cin>>u>>v>>w;
        add(u,v,w);
        add(v,u,w);
    }
    dfsCtr(1,0,n);
    divide(ctr,k);
    std::cout<<res<<"\n";
    
    ctr = -1;
    cnt = 0;
    res = 0;
    for(int i=1;i<=n;i++) head[i] = 0,del[i] = 0;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

	int n,k;
	
	while(std::cin>>n>>k){
	    if(n==0&&k==0) break;
	    solve(n,k);
	}

    return 0;
}
