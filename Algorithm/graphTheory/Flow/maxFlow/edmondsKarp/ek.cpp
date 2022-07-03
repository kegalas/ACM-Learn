#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#define MAXN 50005
#define INF 0x3f3f3f3f

using namespace std;

struct Edge{
    int from, to, cap, flow;
    Edge(int u, int v, int c, int f):from(u),to(v),cap(c),flow(f){}
};

struct EdmondKarp{
    int n,m;
    vector<Edge> edges;  
    vector<int> G[MAXN]; //邻接表
    int a[MAXN];
    int p[MAXN];

    void init(int n){
        for(int i=0;i<n;i++){
            G[i].clear();
        }
        edges.clear();
    }

    void AddEdge(int from, int to, int cap){
        edges.push_back(Edge(from, to, cap, 0));
        edges.push_back(Edge(to, from, 0, 0));
        m = edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }

    int Maxflow(int s, int t){
        int flow = 0;
        for(;;){
            memset(a, 0 ,sizeof(a));
            queue<int> Q;
            Q.push(s);
            a[s] = INF;
            while(!Q.empty()){
                int x=Q.front();
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
    int s,t;
    int m;
    cin>>m>>s>>t;
    for(int i=1;i<=m;i++){
        int tmp1,tmp2,tmp3;
        cin>>tmp1>>tmp2>>tmp3;
        EK.AddEdge(tmp1,tmp2,tmp3);
    }

    cout<<EK.Maxflow(s,t)<<endl;

    return 0;
}

