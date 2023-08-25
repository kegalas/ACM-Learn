//01字典树，复杂度线性
//HDU4825
#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <vector>
#include <cstdint>
#include <cstdio>
#include <bitset>
#include <deque>
#include <regex>
#include <unordered_map>
#include <unordered_set>

#define debug(a) std::cout<<#a<<"="<<a<<std::endl
#define lth(i,x,y) for(int i=x;i<=y;i++)
#define htl(i,x,y) for(int i=x;i>=y;i--)
#define mms(x) memset(x, 0, sizeof(x))

using LL = long long;
using ULL = unsigned long long;
using i128 = __int128;
using pii = std::pair<int,int>;
using pll = std::pair<LL,LL>;

int const MAXN = 3200005;
int const INF = 0x7fffffff;
double const EPS = 1e-8;
int const MOD = 998244353;
double const PI = acos(-1);
int const MAXBIT = 35;//注意题目给的数据范围，这里2^32以下可以处理

class Trie{
public:
    int nxt[MAXN][2];
    int cnt;
    LL num[MAXN];
    
    void init(){
        for(int i=0;i<=cnt;i++) for(int j=0;j<2;j++) nxt[i][j] = 0;
        for(int i=0;i<=cnt;i++) num[i] = 0;
        cnt = 0;
    }
    
    void insert(LL n){
		//插入一个自然数
        int cur = 0;
        for(LL i=MAXBIT;i>=0;i--){
            LL bit = (n>>i)&1;
            if(!nxt[cur][bit]){
                nxt[cur][bit] = ++cnt;
            }
            cur = nxt[cur][bit];
        }
        num[cur] = n;
    }
    
    LL find_max(LL x){
		//查询x与数组内的所有数的异或的最大值
        int cur=0;
        for(int i=MAXBIT;i>=0;i--){
            LL bit = (x>>i)&1;
            if(nxt[cur][bit^1])//尽量走与当前位不同的路径，最小值应改为走相同的
                cur = nxt[cur][bit^1];
            else
                cur = nxt[cur][bit];
        }
        return num[cur];
    }
};

Trie trie;

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

	int T;
	std::cin>>T;
	
	for(int TT = 1;TT<=T;TT++){
	    std::cout<<"Case #"<<TT<<":\n";
	    int n,q;
	    std::cin>>n>>q;
	    trie.init();
	    
	    for(int i=1;i<=n;i++){
	        LL tmp;
	        std::cin>>tmp;
	        trie.insert(tmp);
	    }
	    
	    for(int i=1;i<=q;i++){
	        LL tmp;
	        std::cin>>tmp;
	        std::cout<<trie.find_max(tmp)<<"\n";
	    }
	}

    return 0;
}
