//luogu p3372 和线段树区间加，维护区间和一样
//复杂度n sqrt(n)
//在块内时对块操作，跨块时中间对块操作，两边多余部分暴力处理
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

LL arr[MAXN];

class BA{
public:
    int st[MAXN],ed[MAXN],size[MAXN],bel[MAXN];//每一段的开始下标、结束下标、段大小；每个元素属于哪个段
    int sq;
    LL sum[MAXN];//保存第i个块的和
    LL tag[MAXN];
    
    void init(int n){
        sq = std::sqrt(n);
        for(int i=1;i<=sq;i++){
            st[i] = n / sq * (i-1) + 1;
            ed[i] = n / sq * i;
            size[i] = ed[i] - st[i] + 1;
        }
        ed[sq] = n;//最后一段可能长度不够n/sq
        size[sq] = ed[sq] - st[sq] + 1;
        
        for(int i=1;i<=sq;i++)
            for(int j=st[i];j<=ed[i];j++)
                bel[j] = i, sum[i] += arr[j];
    }
    
    void update(int l, int r, LL k){
        if(bel[l]==bel[r]){
            for(int i=l;i<=r;i++){
                arr[i]+=k;
                sum[bel[i]] += k;
            }
            return;
        }
        
        for(int i=l;i<=ed[bel[l]];i++){
            arr[i]+=k;
            sum[bel[i]]+=k;
        }
        for(int i=st[bel[r]];i<=r;i++){
            arr[i]+=k;
            sum[bel[i]]+=k;
        }
        for(int i=bel[l]+1;i<bel[r];i++){
            tag[i] += k;
        }
    }
    
    LL query(int l, int r){
        LL ret = 0;
        if(bel[l]==bel[r]){
            for(int i=l;i<=r;i++)
                ret += arr[i] + tag[bel[i]];
            return ret;
        }
        
        for(int i=l;i<=ed[bel[l]];i++)
            ret += arr[i] + tag[bel[i]];
        for(int i=st[bel[r]];i<=r;i++)
            ret += arr[i] + tag[bel[i]]; 
        for(int i=bel[l]+1;i<bel[r];i++)
            ret += sum[i] + tag[i] * size[i];
        return ret;
    }
};

BA ba;//注意，开了大数组，要声明在main函数外面，或者可以去用动态分配内存

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

	int n,m;
	std::cin>>n>>m;
	
	for(int i=1;i<=n;i++){
	    std::cin>>arr[i];
	}
	ba.init(n);

    while(m--){
        int ope,x,y;
        
        LL k;
        std::cin>>ope>>x>>y;
        
        if(ope==1){
            std::cin>>k;
            ba.update(x,y,k);
        }
        else{
            std::cout<<ba.query(x,y)<<"\n";
        }
    }

    return 0;
}
