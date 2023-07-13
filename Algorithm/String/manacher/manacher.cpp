//manacher 算法
//luogu P3805
//复杂度O(n)
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

std::vector<int> getD1(std::string const & str){
    //返回字符串以某一位为中心的，最长的（奇数长度）回文子串的长度半径
    //例如abcba中，d1[2] = 3
    int n = str.size();
    std::vector<int> d(n);
    for(int i=0,l=0,r=-1;i<n;i++){
        int j = l+r-i;
        int dj = j>=0?d[j]:0;
        d[i] = std::max(std::min(dj,j-l+1),0);
        
        if(j-dj<l){
            while(i-d[i]>=0 && i+d[i]<n && str[i-d[i]]==str[i+d[i]])
                d[i]++;
            l = i-d[i]+1, r = i+d[i]-1;
        }
    }
    
    return d;
}

std::vector<int> getD2(std::string const & str){
    //返回字符串以某一位的左边间隙为中心的，最长的（偶数长度）回文子串的长度半径
    //例如abba中，d2[2] = 2
    int n = str.size();
    std::vector<int> d(n);
    for(int i=0,l=0,r=-1;i<n;i++){
        int j = l+r-i;
        int dj = j>=0?d[j]:0;
        d[i] = std::max(std::min(dj,j-l),0);
        
        if(j-dj-1<l){
            while(i-d[i]-1>=0 && i+d[i]<n && str[i-d[i]-1]==str[i+d[i]])
                d[i]++;
            l = i-d[i], r = i+d[i]-1;
        }
    }
    
    return d;
}

signed main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    std::string str;
	std::cin>>str;

    int ans = 0;

    for(auto x:getD1(str)){
        ans = std::max(ans,x*2-1);
    }

    for(auto x:getD2(str)){
        ans = std::max(ans,x*2);
    }
    
    std::cout<<ans<<"\n";

    return 0;
}
