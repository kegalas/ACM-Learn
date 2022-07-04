//luogu P3376
//超时
#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const ll INF = 0xffffffff;
const int MAXM = 100005;

struct Edge{
    int to;
    int rev;
    ll cap;
    Edge()=default;
    Edge(int to, ll cap, int rev):to(to),cap(cap),rev(rev){}

};

vector<Edge> G[MAXM];
bool used[MAXM]; 

ll dfs(int v, int t, ll f){
    if(v==t) return f;
    used[v] = true;
    for(int i=0;i<G[v].size();i++){
        Edge& e=G[v][i];
        if(!used[e.to]&&e.cap>0){
            ll d = dfs(e.to, t, min(f,e.cap));
            if(d>0){
                e.cap-=d;
                G[e.to][e.rev].cap+=d;
                return d;
            }
        }
    }
    return 0;
}

ll max_flow(int s, int t){
    ll flow = 0;
    for(;;){
        memset(used,0,sizeof(used));
        ll f = dfs(s,t,INF);
        if(f==0) return flow;
        flow+=f;
    }
}

int main(){
    int n,m;
    cin>>n>>m;
    //点数，边数
    int s,t;
    cin>>s>>t;
    //源点，汇点
    for(int i=1;i<=m;i++){
        int a,b;
        ll c;
        scanf("%d%d%ld",&a,&b,&c);
        //起点，终点，边容量
        //cin>>a>>b>>c;
        G[a].push_back(Edge(b,c,G[b].size()));//这里第三个参数实际上是反向边的编号
        G[b].push_back(Edge(a,0,G[a].size()-1));
    }
    
    ll ans = max_flow(s,t);
    //得到最大流
    printf("%ld",ans);
    //cout<<ans<<endl;
    return 0;
}

/*
4 5 4 3
4 2 30
4 3 20
2 3 20
2 1 30
1 3 40
*/

