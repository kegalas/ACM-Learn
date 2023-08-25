//单调栈 luogu p5788
//本题定义f[i]为数列中第i个元素之后第一个大于a[i]的元素的下标（不存在则为0）
//很显然我们可以维护一个单调不增的栈
//当push的元素x大于栈顶t时，第一个大于t的元素就是x。反复出栈直到栈顶t小于等于x或栈空，入栈。
//复杂度 n

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

#define LL long long
#define ULL unsigned long long
#define i128 __int128
#define debug(a) std::cout<<#a<<"="<<a<<std::endl
#define lth(i,x,y) for(int i=x;i<=y;i++)
#define htl(i,x,y) for(int i=x;i>=y;i--)
#define mms(x) memset(x, 0, sizeof(x))

const int MAXN = 3000005;
const int INF = 0x7fffffff;
const double EPS = 1e-8;
const int MOD = 998244353;
const double PI = acos(-1);

int arr[MAXN];
int ans[MAXN];
int stk[MAXN];

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int n;
    std::cin>>n;

    for(int i=1;i<=n;i++){
        std::cin>>arr[i];
    }

    int top = 0;

    for(int i=1;i<=n;i++){
        while(top&&arr[stk[top]]<arr[i]){
            ans[stk[top]] = i;//这一行是具体的操作，因题而异；而其他行在这个for循环里都是固定的
            top--;
        }

        stk[++top] = i;
    }

    for(int i=1;i<=n;i++){
        std::cout<<ans[i]<<" ";
    }

    return 0;
}