//2-SAT算法，复杂度n+m
//luogu P4782
#include <iostream>
#include <vector>
#include <stack>

const int MAXN = 2e6+5;

int dfn[MAXN], low[MAXN], instk[MAXN], scci[MAXN], cnt=0, cscc=0;
std::vector<int> edges[MAXN];
std::stack<int> stk;
std::vector<int> scc[MAXN];
//含义见强连通分量tarjan算法
bool ans[MAXN];

void tarjan(int u){
    low[u] = dfn[u] = ++cnt;
    instk[u] = 1;
    stk.push(u);
    for(int i=0;i<edges[u].size();i++){
        int v = edges[u][i];
        if(!dfn[v]){
            tarjan(v);
            low[u] = std::min(low[u],low[v]);
        }
        else if(instk[v]){
            low[u] = std::min(low[u], dfn[v]);
        }
    }
    if(low[u]==dfn[u]){
        int top;
        cscc++;
        do{
            top = stk.top();
            stk.pop();
            instk[top] = 0;
            scci[top] = cscc;
            scc[cscc].push_back(top);
        }while(top!=u);
    }
}

int main(){
    int n,m;
    std::cin>>n>>m;
    //n个点，m个条件
    
    while(m--){
        int i,j;
        bool a,b;
        std::cin>>i>>a>>j>>b;
        //本题的条件为，i为a或（不是异或）j为b，其他题按情况处理
        //每个点x拆为两个点y和y+n,y代表x为0，y+n代表x为1
        
        //每条边x->y代表着，如果x，那么一定有y
        //本题如“i为假或j为真”可以拆为两个条件，这个条件满足（为真）时
        //i为真则j一定为真
        //j为假则i一定为假
        edges[i+(!a)*n].push_back(j+b*n);
        edges[j+(!b)*n].push_back(i+a*n);//逆否命题
    }
    
    for(int i=1;i<=2*n;i++){
        if(!dfn[i]) tarjan(i);//注意遍历所有dfn为零的点
    }
    
    for(int i=1;i<=n;i++){
        if(scci[i]==scci[i+n]){//如果i和i+n在一个强连通分量，则不可满足
            std::cout<<"IMPOSSIBLE\n";
            return 0;
        }
        else if(scci[i]>scci[i+n])
            ans[i] = 1;
        else
            ans[i] = 0;
    }
    std::cout<<"POSSIBLE\n";
    for(int i=1;i<=n;i++){
        std::cout<<ans[i]<<" ";
    }

    return 0;
}
