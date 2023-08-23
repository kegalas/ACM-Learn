//复杂度 mlogm
//最小生成树Kruskal，luogu p3366
#include <iostream>
#include <algorithm>

int const MAXM = 200005;
int const MAXN = 5005;

struct Edge{
    int u,v,w;//最小生成树是在无向图上跑的，由于要排序，所以记录uvw
    bool operator<(Edge const & x) const {
        return w<x.w;
    }  
};

Edge edges[MAXM];
int find_sets[MAXN];//并查集

int find(int x){return find_sets[x]==x ? x : find_sets[x] = find(find_sets[x]);}

int main(){
    int n,m;//点数和边数

    std::cin>>n>>m;
    for(int i=1;i<=m;i++){
        std::cin>>edges[i].u>>edges[i].v>>edges[i].w;
    }
    std::sort(edges+1,edges+1+m);

    for(int i=1;i<=n;i++){
        find_sets[i]=i;
    }

    int ans = 0;
    int cnt=0;

    for(int i=1;i<=m;i++){
        int u = edges[i].u, v = edges[i].v;
        int x = find(u);
        int y = find(v);

        if(x!=y){
            ans += edges[i].w;
            find_sets[x] = y;
            cnt++;
        }
    }
    //计数，如果小于n-1则不连通
    
    if(cnt<n-1){
        std::cout<<"orz\n";
    }
    else{
        std::cout<<ans<<"\n";
    }

    return 0;
}
