//复杂度 n
//poj 1655
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

int const MAXN = 20005;

std::vector<int> edges[MAXN];
int sz[MAXN], mss[MAXN];//树的大小（含自己），最大子树大小（不含自己）
std::vector<int> ctr;//重心

void dfs(int u, int fa, int const n){//需要传入点的个数
    sz[u] = 1, mss[u] = 0;
    int size = edges[u].size();
    for(int e=0;e<size;e++){
        int v = edges[u][e];
        if(v==fa) continue;
        dfs(v,u,n);
        mss[u] = std::max(mss[u],sz[v]);
        sz[u] += sz[v];
    }
    mss[u] = std::max(mss[u],n-sz[u]);
    if(mss[u]<=n/2) ctr.push_back(u);
}

void solve(){
    int n;
    std::cin>>n;
    ctr.clear();
    
    for(int i=1;i<=n;i++) edges[i].clear();
    
    for(int i=1;i<=n-1;i++){
        int u,v;
        std::cin>>u>>v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    
    dfs(1,0,n);
    if(ctr.size()==1){
        std::cout<<ctr[0]<<" "<<mss[ctr[0]]<<"\n";
    }
    else{
        if(ctr[0]<ctr[1]){
            std::cout<<ctr[0]<<" "<<mss[ctr[0]]<<"\n";
        }
        else{
            std::cout<<ctr[1]<<" "<<mss[ctr[1]]<<"\n";
        }
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

	int T;
	std::cin>>T;
	//T=1;
	while(T--){
	    solve();
	}

    return 0;
}
