//单调队列，luogu1886
//本题是滑动窗口，即在长度为n的数组中，给出一个长度为k的连续区间，从左向右滑动，求每个区间中的最大值和最小值
//求最小值时，我们可以维护一个单增的双端队列。x加入队尾时，如果队尾元素b>=x，则把队尾弹出，直到b<x或者栈空时把x入队。
//因为我们的区间长度有限，每次我们的区间左端点向右枚举+1时，判断队首元素的下标，如果小于区间左端点，就出队。
//之后留在队首的元素就是区间最小值
//具体可见代码。最大值维护同理。

//复杂度n

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
        std::cout<<arr[dq.front()]<<" ";//输出最小值
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
        std::cout<<arr[dq.front()]<<" ";//输出最大值
    }

    return 0;
}
