//单调队列，luogu1886
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

#define LL long long
#define ULL unsigned long long
#define i128 __int128
#define debug(a) std::cout<<#a<<"="<<a<<std::endl
#define lth(i,x,y) for(int i=x;i<=y;i++)
#define htl(i,x,y) for(int i=x;i>=y;i--)
#define mms(x) memset(x, 0, sizeof(x))

const int MAXN = 1000005;
const int INF = 0x7fffffff;
const double EPS = 1e-8;
const int MOD = 998244353;
const double PI = acos(-1);

int arr[MAXN];

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int n,k;
    std::cin>>n>>k;

    for(int i=1;i<=n;i++){
        std::cin>>arr[i];
    }

    std::deque<int> dq;

    for(int i=1;i<k;i++){
        while(!dq.empty()&&arr[dq.back()]>=arr[i]) dq.pop_back();
        dq.push_back(i);
    }

    for(int i=k;i<=n;i++){
        while(!dq.empty()&&arr[dq.back()]>=arr[i]) dq.pop_back();
        dq.push_back(i);
        while(dq.front()<=i-k) dq.pop_front();
        std::cout<<arr[dq.front()]<<" ";
    }

    std::cout<<"\n";

    dq.clear();

    for(int i=1;i<k;i++){
        while(!dq.empty()&&arr[dq.back()]<=arr[i]) dq.pop_back();
        dq.push_back(i);
    }

    for(int i=k;i<=n;i++){
        while(!dq.empty()&&arr[dq.back()]<=arr[i]) dq.pop_back();
        dq.push_back(i);
        while(dq.front()<=i-k) dq.pop_front();
        std::cout<<arr[dq.front()]<<" ";
    }

    return 0;
}
