#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

typedef long long ll;

const int MAXN = 205;
const ll INF = 1LL<<35;

struct Edge{
    int from, to;
    ll cap,flow;
    Edge(int u, int v, ll c, ll f):from(u),to(v),cap(c),flow(f){}
};

struct EdmondKarp{
    int n,m;
    vector<Edge> edges;  
    vector<int> G[MAXN]; //邻接表
    ll a[MAXN];
    ll p[MAXN];

    void init(int n){
        for(int i=0;i<n;i++){
            G[i].clear();
        }
        edges.clear();
    }

    void AddEdge(int from, int to, ll cap){
        edges.push_back(Edge(from, to, cap, 0));
        edges.push_back(Edge(to, from, 0, 0));
        m = edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }

    int Maxflow(int s, int t){
        ll flow = 0;
        for(;;){
            memset(a, 0 ,sizeof(a));
            queue<ll> Q;
            Q.push(s);
            a[s] = INF;
            while(!Q.empty()){
                ll x=Q.front();
                Q.pop();
                for(int i=0;i<G[x].size();i++){
                    Edge& e = edges[G[x][i]];
                    if(!a[e.to]&&e.cap>e.flow){
                        p[e.to] = G[x][i];
                        a[e.to] = min(a[x], e.cap-e.flow);
                        Q.push(e.to);
                    }
                }
                if(a[t]) break;
            }
            if(!a[t]) break;
            for(int u=t;u!=s;u=edges[p[u]].from){
                edges[p[u]].flow+=a[t];
                edges[p[u]^1].flow -= a[t];
            }
            flow += a[t];
        }
        return flow;
    }
};


int main(){
    EdmondKarp EK;
    cin>>EK.n;
    //点数
    int s,t;
    int m;
    cin>>m>>s>>t;
    //边数，源点，汇点
    for(int i=1;i<=m;i++){
        int tmp1,tmp2,tmp3;
        cin>>tmp1>>tmp2>>tmp3;
        //起点，终点，边容量
        EK.AddEdge(tmp1,tmp2,tmp3);
    }

    cout<<EK.Maxflow(s,t)<<endl;

    return 0;
}

