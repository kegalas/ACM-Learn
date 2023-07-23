//后缀自动机，构建SAM的复杂度为O(n)，空间复杂度为O(|S|n)，|S|为字符集的大小
//luogu p3804
//SAM是动态构建的，每次插入一个字符即可
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

int const MAXN = 1000005;
int const INF = 0x7fffffff;
double const EPS = 1e-8;
int const MOD = 998244353;
double const PI = acos(-1);

int arr[MAXN];

struct State{
    int fa,len,next[26];//似乎有些编译器next是保留字，需要注意
};

class SAM{
public:
    State st[MAXN<<1];
    int cnt = 1, last = 1;
    int sonCnt[MAXN<<1],size[MAXN<<1];
    
    void insert(int ch){
        ch = ch-'a';
        int cur = ++cnt;
        int p = 0;
        st[cur].len = st[last].len + 1;
        for(p=last;p&&!st[p].next[ch];p=st[p].fa)
            st[p].next[ch] = cur;
        int q = st[p].next[ch];
        if(q==0){
            st[cur].fa = 1;
            sonCnt[1]++;
        }
        else if(st[p].len + 1 == st[q].len){
            st[cur].fa = q;
            sonCnt[q]++;
        }
        else{
            int r = ++cnt;
            st[r] = st[q];
            st[r].len = st[p].len + 1;
            for(;p&&st[p].next[ch]==q;p=st[p].fa){
                st[p].next[ch]=r;
            }
            st[cur].fa = st[q].fa = r;
            sonCnt[r]+=2;
        }
        last = cur;
        size[cur] = 1;
    }
    
    LL calc(){
        LL ans = 0;
        std::queue<int> qu;
        for(int i=1;i<=cnt;i++){
            if(sonCnt[i]==0) qu.push(i);
        }
        
        while(!qu.empty()){
            int fr = qu.front();
            qu.pop();
            if(size[fr]>1) ans = std::max(ans,1ll*size[fr]*st[fr].len);
            int fa = st[fr].fa;
            size[fa] += size[fr];
            sonCnt[fa]--;
            if(sonCnt[fa]==0) qu.push(fa);
        }
        return ans;
    }
};

SAM sam;

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

	std::string str;
	std::cin>>str;

    for(auto c:str){
        sam.insert(c);
    }
    
    std::cout<<sam.calc()<<"\n";

    return 0;
}
