//luogu P3369
//所有操作均为logn
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

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp> //仅限g++可以使用

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

int arr[MAXN];

namespace pbds = __gnu_pbds;

pbds::tree<LL, pbds::null_type, std::less<LL>, 
           pbds::rb_tree_tag, pbds::tree_order_statistics_node_update> tr;

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

	LL n;
	std::cin>>n;
	
	for(int i=1;i<=n;i++){
	    int ope;
	    LL x;
	    std::cin>>ope>>x;
	    
	    if(ope==1) tr.insert((x<<20)+i);
	    else if(ope==2) tr.erase(tr.lower_bound(x<<20));
	    else if(ope==3) std::cout<<tr.order_of_key(x<<20)+1<<"\n";
	    else if(ope==4) std::cout<<((*tr.find_by_order(x-1))>>20)<<"\n";
	    else if(ope==5){
	        auto it = tr.lower_bound(x<<20);
	        it--;
	        std::cout<<((*it)>>20)<<"\n";
	    }
	    else{
	        auto it = tr.upper_bound((x<<20)+n);
	        std::cout<<((*it)>>20)<<"\n";
	    }
	}

    return 0;
}
