//复杂度 n+m
//tarjan求割边，不考虑重边，如果有重边那么一定不是割边
//luogu p1656
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

const int MAXN = 20005;
const int MAXM = 100005;

int dfn[MAXN], low[MAXN], cnt=0, fa[MAXN];//fa记录父节点
//dfn为对一个图进行dfs时，dfs的顺序序号
//low[x]为所有符合以下要求之一的节点的dfn中的最小值
//1.以x为根的子树的所有节点
//2.通过非dfs生成树上的边能够到达该子树的所有节点
vector<int> edges[MAXN];
vector<pair<int, int>> bridges;//存储割边

void tarjan(int u){
    low[u] = dfn[u] = ++cnt;
    for(int i=0;i<edges[u].size();i++){
        int v = edges[u][i];
        if(!dfn[v]){
            fa[v] = u;
            tarjan(v);
            low[u] = min(low[u],low[v]);            
            if(low[v]>dfn[u])//边u-v是割边的充要条件
                bridges.emplace_back(u,v);
        }
        else if(fa[u]!=v){
            low[u] = min(low[u], dfn[v]);
        }
    }
}

int main(){
    int n,m;
    cin>>n>>m;
    //点数，边数
    for(int i=1;i<=m;i++){
        int a,b;
        cin>>a>>b;
        //起点，终点
        edges[a].push_back(b);
        edges[b].push_back(a);
		//无向图
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i])
            tarjan(i);
    }
    
    for(auto& x:bridges){
        if(x.first>x.second) std::swap(x.first,x.second);
    }
    std::sort(bridges.begin(),bridges.end());
    for(int i=0;i<bridges.size();i++){
        cout<<bridges[i].first<<" "<<bridges[i].second<<endl;
        //输出割边
    }    
    return 0;
}
