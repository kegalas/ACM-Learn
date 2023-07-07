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

struct Node{
    int l,r;
    mutable LL v;  
    Node(int l, int r, LL v):l(l),r(r),v(v){}
    bool operator<(Node const & x) const {return l<x.l;}
};

class ODT{
public:
    std::set<Node> tree;
    
    auto split(int pos){
        auto it = tree.lower_bound(Node(pos,0,0));
        
        if(it!=tree.end() && it->l==pos)
            return it;
        it--;
        int l = it->l, r = it->r;
        LL v = it->v;
        tree.erase(it);
        tree.insert(Node(l,pos-1,v));
        return tree.insert(Node(pos,r,v)).first;
    }
    
    void assign(int l, int r, int v){
        //给区间赋值
        auto end = split(r+1), begin = split(l);//必须要注意顺序
        tree.erase(begin,end);
        tree.insert(Node(l,r,v));
    }
    
    void perf(int l, int r){//其他操作的模板函数
        auto end = split(r+1), begin = split(l);
        for(auto it=begin;it!=end;it++){
            //这里是操作
        }
    }
};

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

	

    return 0;
}
