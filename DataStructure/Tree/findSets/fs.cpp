//复杂度 很小
//并查集 Luogu3367

#include <iostream>

const int MAXN = 10005;

class DSU{
public:
    int fa[MAXN], rk[MAXN];
    
    void init(int n){
        for(int i=1;i<=n;i++) fa[i] = i, rk[i] = 1;
    }
    
    int find(int x){
        //没有路径压缩的find，在需要删除操作时，不能使用路径压缩，只能按秩合并保证复杂度
        return fa[x]==x ? x : find(fa[x]);
    }
    
    int findc(int x){
        //带路径压缩的find
        return fa[x]==x ? x : (fa[x] = findc(fa[x]));
    }
    
    void merge(int x, int y){
        //按秩合并，如果不需要则直接 fa[find(x)] = find(y);
        x = find(x), y = find(y);
        if(x==y) return;
        if(rk[x]>rk[y]) std::swap(x,y);
        fa[x] = y;
        if(rk[x]==rk[y]) rk[y]++;
    }
    
    void mergec(int x, int y){
        //按秩合并+路径压缩，如果不需要则直接 fa[findc(x)] = findc(y);
        x = findc(x), y = findc(y);
        if(x==y) return;
        if(rk[x]>rk[y]) std::swap(x,y);
        fa[y] = x;
        if(rk[x]==rk[y]) rk[y]++;
    }
    
    void erase(int x){
        --rk[find(x)];
        fa[x] = x;
    }
};

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    
    int n,m;
    std::cin>>n>>m;
    
    DSU dsu;
    dsu.init(n);
    
    while(m--){
        int ope,x,y;
        std::cin>>ope>>x>>y;
        
        if(ope==1){
            dsu.mergec(x,y);
        }
        else{
            if(dsu.findc(x)==dsu.findc(y)) std::cout<<"Y\n";
            else std::cout<<"N\n";
        }
    }
    
    return 0;
}
