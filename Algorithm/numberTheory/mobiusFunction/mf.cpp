//线性筛求莫比乌斯函数，复杂度n，求单个函数值直接分解质因数即可（复杂度sqrt n）
//验证正确性可见杜教筛模板 luogu p4213
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
#define pb push_back
#define mkp make_pair
#define fi first
#define se second

using LL = long long;
using ULL = unsigned long long;
using LD = long double;
using uint = unsigned;
using i128 = __int128;
using pii = std::pair<int,int>;
using pll = std::pair<LL,LL>;

int const MAXN = 200005;
int const INF = 0x7fffffff;
double const EPS = 1e-8;
int const MOD = 998244353;
double const PI = acos(-1);

int mu[MAXN];
std::vector<int> prime;
bool isnp[MAXN];

void mobius(int n){
    mu[1] = 1;
    for(int i=2;i<=n;i++){
        if(!isnp[i]){
            prime.push_back(i);
            mu[i] = -1;
        }
        
        for(auto p:prime){
            if(i*p>n) break;
            isnp[i*p] = 1;
            if(i%p==0){
                mu[i*p] = 0;
                break;
            }
            else{
                mu[i*p] = mu[i] * mu[p];
            }
        }
    }
}

void solve(){
    int n;
    std::cin>>n;
    mobius(n);
    for(int i=1;i<=n;i++){
        std::cout<<mu[i]<<" ";
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

	int T;
	T=1;
	while(T--){
	    solve();
	}

    return 0;
}
