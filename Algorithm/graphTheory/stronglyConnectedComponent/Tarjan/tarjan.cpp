#include <iostream>
#include <vector>
#include <stack>

using namespace std;

const int MAXN = 5005;
const int MAXM = 10005;

int dfn[MAXN], low[MAXN], instk[MAXN], scc[MAXN], cnt=0, cscc=0;
//scc代表每个店所属的强连通分量的编号
vector<int> edges[MAXN];
stack<int> stk;

void tarjan(int u){
    low[u] = dfn[u] = ++cnt;
    instk[u] = 1;
    stk.push(u);
    for(int i=0;i<edges[u].size();i++){
        int v = edges[u][i];
        if(!dfn[v]){
            tarjan(v);
            low[u] = min(low[u],low[v]);
        }
        else if(instk[v]){
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(low[u]==dfn[u]){
        int top;
        cscc++;
        do{
            top = stk.top();
            stk.pop();
            instk[top] = 0;
            scc[top] = cscc;
        }while(top!=u);
    }
}

int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int a,b;
        cin>>a>>b;
        edges[a].push_back(b);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i])
            tarjan(i);
    }
    for(int i=1;i<=n;i++){
        cout<<scc[i]<<endl;
    }
    return 0;
}
