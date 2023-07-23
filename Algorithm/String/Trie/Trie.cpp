//复杂度 插入或查找一次 模板串长度
//luogu p8306
#include <iostream>
#include <cstdio>
#include <cstring>

int const MAXN = 100005;
int const MAXM = 3000005;

class Trie{
public:
    int nxt[MAXM][128];
    int cnt;
    int sum[MAXM];
    
    void init(){
        for(int i=0;i<=cnt;i++) for(int j=0;j<128;j++) nxt[i][j] = 0;
        for(int i=0;i<=cnt;i++) sum[i] = 0;
        cnt = 0;
    }
    
    void insert(std::string const & s){
        int cur = 0;
        for(auto c:s){
            int i=c;
            if(!nxt[cur][i]){
                nxt[cur][i]=++cnt;
            }
            cur = nxt[cur][i];
            sum[cur]++;
        }
    }
    
    int find_prefix(std::string const & s){
        int cur=0;
        int ret=0;
        for(auto c:s){
            int i=c;
            if (!nxt[cur][i])
            {
               return 0;
            }            
            cur = nxt[cur][i];
            ret = sum[cur];
        }
        return ret;
    }
};

Trie trie;

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    
    int T;
    std::cin>>T;
    
    while(T--){
        int n,q;
        std::cin>>n>>q;
        trie.init();
        for(int i=1;i<=n;i++){
            std::string str;
            std::cin>>str;
            trie.insert(str);
        }
        
        for(int i=1;i<=q;i++){
            std::string str;
            std::cin>>str;
            std::cout<<trie.find_prefix(str)<<"\n";
        }
    }
    
    return 0;
}

