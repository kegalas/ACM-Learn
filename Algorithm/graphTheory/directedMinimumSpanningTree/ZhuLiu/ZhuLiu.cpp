//复杂度 nm
//最小树形图，朱刘算法
//从根节点能到达其他所有点
//luogu4716
#include <iostream>

using namespace std;

const int MAXN = 105;
const int MAXM = 10005;
const int INF = 0x7fffffff;

struct Edge{
    int u,v,w;
};

Edge edge[MAXM]; 
int vis[MAXN],id[MAXN];
int in[MAXN],pre[MAXN];
int n,m,root;

int zhuliu(){
    int ans = 0;
    for(;;){
        for(int i=1;i<=n;i++) in[i]=INF;
        
        for(int i=1;i<=m;i++){
            int u = edge[i].u;
            int v = edge[i].v;
            if(u!=v&&edge[i].w<in[v]){//遍历所有边，找到对每个点的最短入边
                in[v] = edge[i].w;
                pre[v] = u;
            }
        }
        
        for(int i=1;i<=n;i++){
            if(i!=root&&in[i]==INF){
                return -1;//无解
            }
        }
        
        int cnt = 0;//记录环数以及下一次循环的点数
        
        for(int i=1;i<=n;i++){
            vis[i] = -1;
            id[i] = -1;
        }
        
        in[root] = 0;
        
        for(int i=1;i<=n;i++){
            if(i==root) continue;
            ans += in[i];
            int v=i;
            while(vis[v]!=i&&id[v]==-1&&v!=root){
                vis[v] = i;
                v = pre[v];
            }
            if(v!=root&&id[v]==-1){
                id[v] = ++cnt;
                for(int u=pre[v];u!=v;u=pre[u]) id[u] = cnt;
            }
        }
        
        if(cnt==0){//无环，得到解
            break;
        }
        
        for(int i=1;i<=n;i++){
            if(id[i]==-1) id[i]=++cnt;
        }
        
        for(int i=1;i<=m;i++){
            int u = edge[i].u;
            int v = edge[i].v;
            edge[i].u = id[u];
            edge[i].v = id[v];
            if(edge[i].u!=edge[i].v) edge[i].w -= in[v];
        }
        
        n = cnt;
        root = id[root];
    }
    return ans;
}

int main(){
    //freopen("in.in","r",stdin);
    cin>>n>>m>>root;
    //点数，边数，根节点序号
    for(int i=1;i<=m;i++){
        cin>>edge[i].u>>edge[i].v>>edge[i].w;
        //起点，终点，边权
    }
    cout<<zhuliu()<<endl;
    return 0;
}

