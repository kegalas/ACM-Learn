//序列自动机，复杂度 O(n|S|)
//luogu p5826，如果要完成subtask3需要用可持久化线段树维护next
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

int const MAXN = 200005;
int const INF = 0x7fffffff;
double const EPS = 1e-8;
int const MOD = 998244353;
double const PI = acos(-1);
int const MAXS = 105;

struct State{
    int next[MAXS];  
};

//SQA接受字符串的所有子序列（不需要连续，可以为空）

class SQA{
public:
    State st[MAXN];
    
    void build(std::vector<int> const & str){
        int nxt[MAXS];
        std::fill(nxt,nxt+MAXS,0);
        int n = str.size();
        
        for(int i=n-1;i>=0;i--){
            nxt[str[i]] = i+2;//1号节点是起始空节点
            for(int ch=0;ch<MAXS;ch++){
                st[i+1].next[ch] = nxt[ch];
            }
        }
    }
    
    bool query(std::vector<int> const & str){
		//查询str是否是子序列（可以不连续）
        int p = 1, n=str.size();
        for(int i=0;i<n;i++){
            p = st[p].next[str[i]];
            if(p==0) return false;
        }
        
        return true;
    }
};

SQA sqa;

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

	int type,n,q,m;
	std::cin>>type>>n>>q>>m;
	std::vector<int> vec(n);
	
	for(int i=0;i<n;i++){
	    std::cin>>vec[i];
	}
	
	sqa.build(vec);
	
	for(int i=1;i<=q;i++){
	    int L;
	    std::cin>>L;
	    std::vector<int> tmp(L);
	    for(int j=0;j<L;j++){
	        std::cin>>tmp[j];
	    }
	    if(sqa.query(tmp)){
	        std::cout<<"Yes\n";
	    }
	    else{
	        std::cout<<"No\n";
	    }
	}

    return 0;
}
