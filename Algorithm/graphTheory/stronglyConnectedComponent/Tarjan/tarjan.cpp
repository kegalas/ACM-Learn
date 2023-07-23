//强连通分量，复杂度 n+m
//luogu P2863
#include <iostream>
#include <vector>
#include <stack>

const int MAXN = 10005;
const int MAXM = 50005;

int dfn[MAXN], low[MAXN], instk[MAXN], scci[MAXN], cnt=0, cscc=0;
std::vector<int> edges[MAXN];
std::stack<int> stk;
std::vector<int> scc[MAXN];
//dfn是dfs时的顺序的序号
//stk中存入两类点，访问到节点x时
//1.搜索树上x的祖先节点
//2.已经访问过，并且存在一条路径到达x祖先的节点
//low[x]定义为满足以下两个条件的节点的最小dfn
//1.该点在stk中
//2.存在一条从subtree(x)出发的有向边，以该点为终点
//scci[x]代表，x这个结点在第几个分量中
//cscc代表有几个分量
//scc[j]中表示，第j个分量的所有节点

void tarjan(int u){
    low[u] = dfn[u] = ++cnt;
    instk[u] = 1;
    stk.push(u);
    for(int i=0;i<edges[u].size();i++){
        int v = edges[u][i];
        if(!dfn[v]){
            tarjan(v);
            low[u] = std::min(low[u],low[v]);
        }
        else if(instk[v]){
            low[u] = std::min(low[u], dfn[v]);
        }
    }
    if(low[u]==dfn[u]){
        int top;
        cscc++;
        do{
            top = stk.top();
            stk.pop();
            instk[top] = 0;
            scci[top] = cscc;
            scc[cscc].push_back(top);
        }while(top!=u);
    }
}

int main(){
    int n,m;
    std::cin>>n>>m;
    
    for(int i=1;i<=m;i++){
        int a,b;
        std::cin>>a>>b;
        edges[a].push_back(b);//有向边
    }
    
    for(int i=1;i<=n;i++){
        if(!dfn[i]) tarjan(i);//注意遍历所有dfn为零的点
    }
    
    int ans = 0;
    for(int i=1;i<=cscc;i++){
        if(scc[i].size()>1) ans++;
    }
    std::cout<<ans<<"\n";
    return 0;
}
