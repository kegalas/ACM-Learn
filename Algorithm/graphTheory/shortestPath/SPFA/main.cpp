/*
    bellman-ford的优化
    只有上一次被松弛的结点，所连接的边，
    才有可能引起下一次的松弛操作
*/
#include <iostream>
#include <vector>
#include <queue>

#define MAXN 500005
#define INF  0x5fffffff

using namespace std;

struct edge{
    int v;
    int w;
};

int dis[MAXN];//距离
int cnt[MAXN];//算到达本节点所要经过的边数，若cnt>=n，则说明有负权环
bool tag[MAXN];//用于判断是否为上次松弛过的节点的边所连的点

int n,m,s;
queue<int> qu;
vector<edge> graph[MAXN];

int main(){
    cin>>n>>m>>s;

    for(int i=1;i<=n;i++){
        dis[i] = INF;
    }

    dis[s] = 0;
    tag[s] = 1;

    for(int i=1;i<=m;i++){
        int a,b,c;
        cin>>a>>b>>c;
        //起点，终点，边权
        edge tmp;
        tmp.v=b;
        tmp.w=c;
        graph[a].push_back(tmp);
    }

    qu.push(s);

    bool is_negative_circle = 0;

    while(!qu.empty()){
        if(is_negative_circle) break;
        int u = qu.front();
        qu.pop();
        tag[u]=0;
        for(auto e : graph[u]){
            int v = e.v, w = e.w;
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                cnt[v]=cnt[u]+1;
                if(cnt[v]>=n) {
                    is_negative_circle = 1;
                    break;
                }
                if(!tag[v]){
                    qu.push(v);
                    tag[v]=1;
                }
            }
        }
    }

    cout<<is_negative_circle<<endl;//可以输出是否有负权环

    for(int i=1;i<=n;i++){
        //if(dis[i]!=INF){
            cout<<dis[i]<<" ";
        //}
        //else{
        //    cout<<"2147483647 ";//根据luogu P3371要输出这个数
        //}
    }

    return 0;
}
