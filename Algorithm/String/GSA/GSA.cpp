//广义后缀自动机，其实就是插入多个字符串的后缀自动机，但只能离线build
//luogu p6139
//后缀自动机的性质都可以用过来
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

struct State{
    int fa,len,next[26];//似乎有些编译器next是保留字，需要注意
};

class GSA{
public:
    State st[MAXN<<1];
    int cnt = 1;//起始节点编号为1
    
    int insert(int last, int ch){
        //传入的是即将插入的字符的父节点编号，以及该字符
        //只用在build里，不要直接把字符串插入，应该先insertTrie再build
        int cur = st[last].next[ch];
        int p = 0;
        st[cur].len = st[last].len + 1;
        
        for(p=st[last].fa;p && !st[p].next[ch];p=st[p].fa)
            st[p].next[ch] = cur;
        
        int q = st[p].next[ch];
        if(q==0){
            st[cur].fa = 1;
        }
        else if(st[p].len+1==st[q].len){
            st[cur].fa = q;
        }
        else{
            int r = ++cnt;
            st[r].fa = st[q].fa;
            for(int i=0;i<26;i++)
                if(st[st[q].next[i]].len)
                    st[r].next[i] = st[q].next[i];
            st[r].len = st[p].len+1;
            for(;p && st[p].next[ch]==q;p=st[p].fa)
                st[p].next[ch] = r;
            st[cur].fa = st[q].fa = r;
        }
        return cur;
        //返回插入节点编号
    }
    
    void build(){
        std::queue<pii> qu;
        for(int i=0;i<26;i++){
            if(st[1].next[i]) qu.push({1,i});
        }
        while(!qu.empty()){
            int fa = qu.front().first;
            int ch = qu.front().second;
            qu.pop();
            int p = insert(fa,ch);
            for(int i=0;i<26;i++){
                if(st[p].next[i]) qu.push({p,i});
            }
        }
    }
    
    void insertTrie(std::string const & str){
        int cur = 1;
        for(auto c:str){
            if(!st[cur].next[c-'a']){
                st[cur].next[c-'a']=++cnt;
            }
            cur = st[cur].next[c-'a'];
        }
    }
};

GSA gsa;

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int n;
    std::cin>>n;
    
    for(int i=1;i<=n;i++){
        std::string str;
        std::cin>>str;
        gsa.insertTrie(str);
    }
    gsa.build();
    
    LL ans1 = 0;
    for(int i=2;i<=gsa.cnt;i++){
        ans1 += 1ll*gsa.st[i].len - gsa.st[gsa.st[i].fa].len;
    }
    std::cout<<ans1<<"\n";
    std::cout<<gsa.cnt<<"\n";

    return 0;
}
