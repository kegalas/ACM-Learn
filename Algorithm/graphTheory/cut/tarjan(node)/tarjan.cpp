//tarjan求割点,luogu P3388
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

const int MAXN = 20005;
const int MAXM = 100005;

int dfn[MAXN], low[MAXN], cnt=0;
vector<int> edges[MAXN];
vector<int> cut;//存储割点

void tarjan(int u, bool root = true){
    int tot = 0;
    low[u] = dfn[u] = ++cnt;
    for(int i=0;i<edges[u].size();i++){
        int v = edges[u][i];
        if(!dfn[v]){
            tarjan(v,false);
            low[u] = min(low[u],low[v]);
            tot += (low[v]>=dfn[u]);//统计满足的点的个数
        }
        else{
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(tot>root){//如果是根节点，则需要有至少两个子树，否则只需要有一个子树
        cut.push_back(u);
    }
}

int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int a,b;
        cin>>a>>b;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i])
            tarjan(i);
    }
    cout<<cut.size()<<endl;
    sort(cut.begin(),cut.end());
    for(int i=0;i<cut.size();i++){
        cout<<cut[i]<<" ";
    }
    return 0;
}
