//回文字动机，复杂度：线性
//luogu p5496
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

int const MAXN = 500005;
int const INF = 0x7fffffff;
double const EPS = 1e-8;
int const MOD = 998244353;
double const PI = acos(-1);

struct State{
    int len, fail, next[26], sum;  
};

std::string str;

//PAM的每一个状态代表原字符串的一个回文子串，每一个转移代表从当前状态字符串的前后同时加一个相同字符后的状态。可以接受其所有回文子串。除了奇根都是可行状态（当然不能为空时偶根不可行）
//fail指针指向该状态的最长回文真后缀。例如ayawaya就指向aba。总体和AC自动机的fail转移很像，都是没有ch的转移，则看fail有没有ch的转移，若fail没有则看fail[fail]的，以此类推。
//回文串分为奇长度和偶长度的，所以PAM有奇根和偶根，偶根的fail指向奇根，奇根不可能失配。
//PAM和SAM一样是动态构建的。

class PAM{
public:
    int last,cnt,pos;
    State st[MAXN];//最多有n+2个状态和n个转移
    
    void init(){
        last = 1,pos = -1;
        cnt = 2;//起始两个根为1奇根，2偶根，len分别为-1和0
        st[1].len = -1, st[2].len = 0, st[2].fail = 1;
    }
    
    int up(int p){
        while(str[pos-1-st[p].len]!=str[pos])
            p = st[p].fail;
        return p;
    }
    
    void insert(int ch){
        pos++;
        ch = ch-'a';
        int p = up(last);
        int & q = st[p].next[ch];
        if(!q){
            q=++cnt;
            st[q].len = st[p].len+2;
            st[q].fail = p==1 ? 2 : st[up(st[p].fail)].next[ch];
            st[q].sum = st[st[q].fail].sum + 1;
        }
        last = q;
    }
};

PAM pam;

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

	std::cin>>str;
	
	pam.init();
	int k = 0;
	
	for(auto & c:str){
	    c = (c-97+k)%26+97;
	    pam.insert(c);
	    k = pam.st[pam.last].sum;
	    std::cout<<k<<" ";
	}

    return 0;
}
