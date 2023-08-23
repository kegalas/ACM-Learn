//Z函数，复杂度O(n)
//luogu P5410

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

std::vector<int> zFunc(std::string const & str){
    //求出一个字符串的z函数，即满足z[i]是s[0...x-1]==s[i...i+x-1]的最大的x
    //特别的z[0]=0，也有些题目是等于串长，需要自行调整
    //kmp里面添加字符集外字符的操作在这里也可以用
    int n = str.size();
    std::vector<int> z(n);
    
    for(int i=1,l=0,r=0;i<n;i++){
        if(z[i-l]<r-i+1)
            z[i] = z[i-l];
        else{
            z[i] = std::max(r-i+1,0);
            while(i+z[i]<n && str[z[i]]==str[i+z[i]])
                z[i]++;
            l = i, r = i + z[i] - 1;
        }
    }
    
    return z;
}

signed main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

	std::string a,b;
	std::cin>>a>>b;
	
	auto zf = zFunc(b);
	zf[0] = b.size();
	LL ans = zf[0]+1;
	int n = b.size(),nb=b.size();
	
	for(int i=1;i<n;i++){
	    ans = ans ^ ((i+1)*1ll*(zf[i]+1));
	}
	
	std::cout<<ans<<"\n";
	
	std::string tmp = b + "#" + a;
	zf = zFunc(tmp);
	n = tmp.size();
	ans = zf[nb+1]+1;
	
	for(int i=nb+2;i<n;i++){
	    ans = ans ^ ((i-nb)*1ll*(zf[i]+1));
	}
	
	std::cout<<ans<<"\n";
	

    return 0;
}
