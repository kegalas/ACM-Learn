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

//endpos(p)为模式串p在s中所有出现的结束位置的集合，例如aababc中，ab出现了两次，结束位置是{3,5}。endpos等价类即，endpos相同的子串构成的集合。例如b和ab都是结束在{3,5}，则它们是等价类。这说明它们总是一起出现，可以归到一个节点，并且长度小的一定是长度大的的后缀。
//next[ch]表示接受ch后的状态；fa表示该状态在parent tree上的父节点；len表示该状态对应的endpos等价类中最长串的长度。
//假设b是a的fa，a等价类的最长字符串为s，则b的最长字符串为，s的所有后缀中，不在等价类a里的，最长的字符串。

//SAM可以接受字符串的所有后缀，但是它包含了所有子串的信息。也就是从任意一个状态开始的路径，都是字符串的子串。
//可行状态是last状态，以及fa[last]、fa[fa[last]]直到根节点（空字符串）。

//除了等价类的最长字符串长度len，我们也可以计算minlen。等价类里所有字符串的长度恰好覆盖[minlen,len]之间的每一个整数。除了根节点，st[i].minlen = st[fa[i]].len+1;
//每个状态i对应的子串数量是st[i].len-st[st[i].fa].len

//算法并没有维护endpos等效类中，字符串出现的位置个数，需要自己去树形dp。
//注意，aababb中，ab的等价类为{3,5}，根据ab前面一个字符不同可以划分不同的等价类，例如aab和bab划分为{3},{5}。但是a的等价类为{1,2,4}，因为第一个的前面一个字符是空字符，只能划分出两个，即aa{2},ba{4}，树形DP需要在parent tree上注意缺少的这一部分。在建SAM时预处理dp[cur] = 1

class SAM{
public:
    State st[MAXN<<1];
    int cnt = 1, last = 1;
    //起始节点编号为1；last表示加入新字符前整个字符串所在的等价类
    int sonCnt[MAXN<<1],size[MAXN<<1];
    
    void insert(int ch){
        ch = ch-'a';
        int cur = ++cnt;
        int p = 0;
        st[cur].len = st[last].len + 1;
        for(p=last;p&&!st[p].next[ch];p=st[p].fa)
            st[p].next[ch] = cur;
        //对于每一个father状态，如果不存在ch的转移边，则连到cur
        int q = st[p].next[ch];
        if(q==0){
            //加入了从未加入的字符
            st[cur].fa = 1;
            sonCnt[1]++;
        }
        else if(st[p].len + 1 == st[q].len){
            //p到q是连续的转移
            st[cur].fa = q;
            sonCnt[q]++;
        }
        else{
            //不连续的转移
            //会新增一个节点r,拥有q的所有出边，father与q相同
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
