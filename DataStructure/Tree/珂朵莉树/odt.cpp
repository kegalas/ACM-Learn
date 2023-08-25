//珂朵莉树，区间推平问题
//方便给某个区间赋值，区间加数，维护区间第k大值，区间和等等
//数据随机的情况下，复杂度为nloglogn
//珂朵莉树的每一个节点都是一个区间，这个区间内的值相同。
//cf896c
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
            //这些操作都很暴力，例如k大值，就把区间全部枚举排序一遍去找
            //例如区间和，就枚举区间加起来，注意是加it->v * (it->r-it->l+1)
            //例如区间加数，就枚举区间给所有的it->v都加一个数
        }
    }
};

ODT odt;

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    //珂朵莉树的初始化不能用assign，设范围为[1,w]，初值全部为0，则
    int w = 100;
	odt.tree.insert(Node(1,w,0));

    return 0;
}
