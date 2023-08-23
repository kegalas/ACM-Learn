//复杂度 n
//拓扑排序, luogu B3644
#include <iostream>
#include <vector>
#include <queue>

int const MAXN = 105;

std::vector<int> graph[MAXN];
int in[MAXN];

int main(){
    int n;
    std::cin>>n;

    for(int i=1;i<=n;i++){
        while(true){
            int v;
            std::cin>>v;
            if(v==0) break;
            graph[i].push_back(v);
            in[v]++;
        }
    }
    
    std::queue<int> qu;
    for(int i=1;i<=n;i++){
        if(in[i]==0) qu.push(i);
    }
    
    while(!qu.empty()){
        int u = qu.front();
        qu.pop();
        std::cout<<u<<" ";
        for(auto v:graph[u]){
            in[v]--;
            if(in[v]==0) qu.push(v);
        }
    }

    return 0;
}

