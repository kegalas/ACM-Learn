//复杂度nlogn
//Luogu P1257
#include <iostream>
#include <algorithm>
#include <cmath>

const int MAXN = 200005;

struct Node{
    int x,y;
    int id;

    bool operator<(const Node& a) const {
        if(x!=a.x) return x<a.x;
        return y<a.y;
    }
}nodes[MAXN];

bool cmp(const Node& a, const Node& b){
    return a.y<b.y;
}

double minDist;
int ansA, ansB;

inline void updAns(const Node& a, const Node& b){
    double dist = sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+0.0);
    if(dist<minDist){
        minDist = dist;
        //如果要记录节点
        ansA = a.id;
        ansB = b.id;
    }
}

void calcMin(int l, int r){
    if(r-l<=3){
        for(int i=l;i<=r;i++){
            for(int j=i+1;j<=r;j++){
                updAns(nodes[i],nodes[j]);
            }
        }
        std::sort(nodes+l, nodes+r+1, cmp);
        return;
    }

    int m = (l+r)>>1;
    int midx = nodes[m].x;
    calcMin(l,m);
    calcMin(m+1,r);
    
    //归并排序的合并，两个有序数组合并，合并之后仍然有序
    std::inplace_merge(nodes+l, nodes+m+1, nodes+r+1, cmp);

    static Node t[MAXN];
    int tsz = 0;

    for (int i = l; i <= r; ++i){
        if (abs(nodes[i].x - midx) < minDist) {
            for (int j = tsz - 1; j >= 0 && nodes[i].y - t[j].y < minDist; --j)
                updAns(nodes[i], t[j]);
            t[tsz++] = nodes[i];
        }
    }

}

int main(){
    int n;
    std::cin>>n;
    for(int i=1;i<=n;i++){
        std::cin>>nodes[i].x>>nodes[i].y;
        nodes[i].id = i;
    }

    std::sort(nodes+1,nodes+1+n);
    minDist = 1e20;
    calcMin(1,n);

    printf("%.4f\n",minDist);

    return 0;
}
