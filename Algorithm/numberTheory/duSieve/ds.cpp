//杜教筛 复杂度n^(2/3)
//luogu p4213
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

int const MAXN = 2000005;
int const INF = 0x7fffffff;
double const EPS = 1e-8;
int const MOD = 998244353;
double const PI = acos(-1);

int mu[MAXN];
LL phi[MAXN];
std::vector<int> prime;
bool isnp[MAXN];
LL sum_mu[MAXN],sum_phi[MAXN];
std::unordered_map<LL,LL> mp_mu,mp_phi;

void sieve(int n=MAXN-1){
    mu[1] = 1;
    phi[1] = 1;
    for(int i=2;i<=n;i++){
        if(!isnp[i]){
            prime.push_back(i);
            mu[i] = -1;
            phi[i] = i-1;
        }
        
        for(auto p:prime){
            if(i*p>n) break;
            isnp[i*p] = 1;
            if(i%p==0){
                mu[i*p] = 0;
                phi[i*p] = phi[i] * p;
                break;
            }
            else{
                mu[i*p] = mu[i] * mu[p];
                phi[i*p] = phi[i] * phi[p];
            }
        }
    }
    for(int i=1;i<=n;i++){
        sum_mu[i] = sum_mu[i-1]+mu[i];
        sum_phi[i] = sum_phi[i-1]+phi[i];
    }
}

LL sum1(LL n){
    if(n<MAXN){
        return sum_phi[n];
    }
    if(mp_phi.count(n)){
        return mp_phi[n];
    }
    LL l=2, r=0;
    LL ret = n*(1+n)/2;
    while(l<=n){
        r = n/(n/l);
        ret -= (r-l+1)*sum1(n/l);
        l = r+1;
    }
    mp_phi[n] = ret;
    return ret;
}

LL sum2(LL n){
    if(n<MAXN){
        return sum_mu[n];
    }
    if(mp_mu.count(n)){
        return mp_mu[n];
    }
    LL l=2, r=0;
    LL ret = 1;
    while(l<=n){
        r = n/(n/l);
        ret -= (r-l+1)*sum2(n/l);
        l = r+1;
    }
    mp_mu[n] = ret;
    return ret;
}

void solve(){
    LL n;
    std::cin>>n;
    std::cout<<sum1(n)<<" "<<sum2(n)<<"\n";
    
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    sieve();

	int T;
	std::cin>>T;
	//T=1;
	while(T--){
	    solve();
	}

    return 0;
}
