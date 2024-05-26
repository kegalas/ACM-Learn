//复杂度nlogn
//Luogu P1257
#include <iostream>
#include <algorithm>
#include <cmath>

typedef double db;
typedef long double LD;
db const EPS = 1e-9;
int const MAXN = 100005;
struct Point{db x,y;int id;}; // id为了记录最近点对是哪两个点
typedef Point Vec;

bool eq(db a, db b)  {return std::abs(a - b)< EPS;}//等于
bool ge(db a, db b)  {return a - b          > EPS;}//大于
bool le(db a, db b)  {return a - b          < -EPS;}//小于
bool geq(db a, db b) {return a - b          > -EPS;}//大于等于
bool leq(db a, db b) {return a - b          < EPS;}//小于等于
int sgn(db x) {
    if (std::abs(x) < EPS) return 0;
    if (x < 0) return -1;
    return 1;
} // 符号，等于零返回0，大于零返回1，小于零返回-1

Vec operator+(Vec a, Vec b){return {a.x+b.x, a.y+b.y};}
Vec operator-(Vec a, Vec b){return {a.x-b.x, a.y-b.y};}
Vec operator*(db k, Vec v){return {k*v.x, k*v.y};}
Vec operator*(Vec v, db k){return {v.x*k, v.y*k};}
db operator*(Vec a, Vec b){return a.x*b.x+a.y*b.y;}
db operator^(Vec a, Vec b){return a.x*b.y-a.y*b.x;}//叉积
db len2(Vec v){return v.x*v.x+v.y*v.y;}//长度平方
db len(Vec v){return std::sqrt(len2(v));}//向量长度

bool operator<(Point a, Point b){return le(a.x,b.x)||(eq(a.x,b.x)&&le(a.y,b.y));}//横坐标第一关键字，纵坐标第二关键字

bool cmp(Point const & a, Point const & b){
    return le(a.y, b.y);
}

db minDist;
int ansA, ansB;

Point po[MAXN];

inline void updAns(Point const & a, Point const & b){
    db dist = len(b-a);
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
                updAns(po[i],po[j]);
            }
        }
        std::sort(po+l, po+r+1, cmp); // 只排序y
        return;
    }

    int m = (l+r)>>1;
    db midx = po[m].x;
    calcMin(l,m);
    calcMin(m+1,r);
    
    //归并排序的合并，两个有序数组合并，合并之后仍然有序
    std::inplace_merge(po+l, po+m+1, po+r+1, cmp); // 只排序y

    static Point t[MAXN];
    int tsz = 0;

    for (int i = l; i <= r; ++i){
        if (le(std::abs(po[i].x - midx),minDist)) {
            for (int j = tsz - 1; j >= 0 && le(po[i].y - t[j].y,minDist); --j)
                updAns(po[i], t[j]);
            t[tsz++] = po[i];
        }
    }

}

int main(){
    int n;
    std::cin>>n;
    for(int i=1;i<=n;i++){
        std::cin>>po[i].x>>po[i].y;
        po[i].id = i;
    }

    std::sort(po+1,po+1+n); // 按照x第一，y第二排序
    minDist = 1e20;
    calcMin(1,n);

    std::cout<<std::fixed;
    std::cout.precision(4);
    std::cout<<minDist<<"\n";

    return 0;
}
