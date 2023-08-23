//树的直径，复杂度n
//poj1985，输出树上最长路径的长度，即树的直径
//两遍dfs版可以求出路径上的点，但树形dp的可以处理负边权问题
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

typedef std::pair<int,int> pii;

int const MAXN = 200005;

std::vector<pii> edges[MAXN];//first是v，second是w
int dis[MAXN];
int far;

void dfs(int u, int fa){
    int size = edges[u].size();
    for(int i=0;i<size;i++){
        pii e = edges[u][i];
        int v = e.first, w = e.second;
        if(v==fa) continue;
        dis[v] = dis[u]+w;
        if(dis[v]>dis[far]) far=v;
        dfs(v,u);
    }
}

void solve(){
    int n,m;
    std::cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v,w;
        char trash;//poj 1985的输入数据问题
        std::cin>>u>>v>>w>>trash;
        edges[u].push_back(std::make_pair(v,w));
        edges[v].push_back(std::make_pair(u,w));
    }
    dfs(1,0);
    dis[far] = 0;
    dfs(far,0);
    std::cout<<dis[far]<<"\n";
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

	int T;
	T=1;
	while(T--){
	    solve();
	}

    return 0;
}
