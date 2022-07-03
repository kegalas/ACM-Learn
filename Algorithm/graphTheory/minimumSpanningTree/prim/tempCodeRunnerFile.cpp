#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

const int MAXN = 5005;
const int MAXM = 200005;
const int INF = 0x5fffffff;

struct edge{
    int v,w;

    edge()=default;
    edge(int v,int w):v(v),w(w){}

    bool operator>(const edge& x) const {return w>x.w;}
};

int graph[MAXN][MAXN];
bool vis[MAXN];

priority_queue<edge, vector<edge>, greater<edge> > pq;

int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    int ans = 0;
    int cnt = 1;
    
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            graph[i][j]=INF;
        }
    }

    for(int i=1;i<=n;i++){
        graph[i][i]=0;
    }

    for(int i=1;i<=m;i++){
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        graph[a][b] = c;
        graph[b][a] = c;
    }

    for(int i=2;i<=n;i++){
        if(graph[1][i]!=INF){
            pq.push(edge(i,graph[1][i]));
        }
    }
    vis[1]=true;

    while(cnt!=n&&!pq.empty()){
        edge minx=pq.top();
        while(vis[minx.v]){
            pq.pop();
            minx=pq.top();
        }
        pq.pop();
        vis[minx.v] = true;
        ans+=minx.w;
        cnt++;
        
        for(int i=1;i<=n;i++){
            if(i==minx.v) continue;
            if(!vis[i]&&graph[minx.v][i]!=INF)
                pq.push(edge(i,graph[minx.v][i]));
        }
    }

    if(cnt<n){
        cout<<"orz"<<endl;
    }
    else{
        cout<<ans<<endl;
    }

    return 0;
}
