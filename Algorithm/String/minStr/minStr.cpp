//最小表示法
//luogu P1368
//复杂度 O(n)
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

int const MAXN = 300005;
int const INF = 0x7fffffff;
double const EPS = 1e-8;
int const MOD = 998244353;
double const PI = acos(-1);

int arr[MAXN];

int minStr(int n){//数组下标从0开始，共n个；返回最小表示的开始下标
    int i=0, j=1, k=0;
    while(i<n && j<n && k<n){
        if(arr[(i+k)%n]==arr[(j+k)%n]){
            k++;
        }
        else if(arr[(i+k)%n]>arr[(j+k)%n]){//最大表示法时就把这一段和下一段换一下
            i += k+1;
            k = 0;
        }
        else{
            j += k+1;
            k = 0;
        }
        
        if(i==j) j++;
    }
    
    return std::min(i,j);
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

	int n;
	std::cin>>n;
	
	for(int i=0;i<n;i++){
	    std::cin>>arr[i];
	}
	
	int ans = minStr(n);
	
	for(int i=0;i<n;i++){
	    std::cout<<arr[(i+ans)%n]<<" ";
	}
	std::cout<<"\n";

    return 0;
}
