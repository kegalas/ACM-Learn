//复杂度 (m+n)logn
#include <iostream>
#include <vector>
#include <queue>

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

vector<edge> graph[MAXN];
bool vis[MAXN];

priority_queue<edge, vector<edge>, greater<edge> > pq;

//以下orz代表不连通

int main(){
    int n,m;//点数，边数
    scanf("%d%d",&n,&m);
    int ans = 0;
    int cnt = 1;

    for(int i=1;i<=m;i++){
        int a,b,c;//起点，终点，边权
        scanf("%d%d%d",&a,&b,&c);
        graph[a].push_back(edge(b,c));
        graph[b].push_back(edge(a,c));
        //无向图
    }

    for(int i=0;i<graph[1].size();i++){
        pq.push(graph[1][i]);
    }
    vis[1]=true;

    while(cnt!=n&&!pq.empty()){
        edge minx=pq.top();
        pq.pop();
        while(vis[minx.v]){
            if(pq.empty()){
                cout<<"orz"<<endl;
                return 0;
            }
            minx=pq.top();
            pq.pop();
        }
        
        vis[minx.v] = true;
        ans+=minx.w;
        cnt++;
        
        for(int i=0;i<graph[minx.v].size();i++){
            if(!vis[graph[minx.v][i].v])
                pq.push(graph[minx.v][i]);
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
