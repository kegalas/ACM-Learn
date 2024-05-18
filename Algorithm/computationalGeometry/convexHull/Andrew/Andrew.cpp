//复杂度 nlogn
//luogu P2742，求凸包周长
//注意题给条件，如果是整数坐标，务必切换到long long来避免误差

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

typedef double db;
struct Point{db x,y;};
typedef Point Vec;
db const EPS = 1e-9;

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
bool operator<(Point a, Point b){return le(a.x,b.x)||(eq(a.x,b.x)&&le(a.y,b.y));}//横坐标第一关键字，纵坐标第二关键字
db len2(Vec v){return v.x*v.x+v.y*v.y;}//长度平方
db len(Vec v){return std::sqrt(len2(v));}//向量长度

std::vector<Point> convexHull(std::vector<Point> const & poly){
	// 返回凸包上的点，逆时针顺序
	// 如果要判断一个多边形是不是凸包，也可以用其生成一个凸包，判断点数是否相同
	// 此时要将下面的sgn(...)<=0改成sgn(...)<0
    int k = 0;
    int n = poly.size();
    std::vector<Point> qs;
    for(int i=0;i<n;i++){
        while(k>1&&sgn((qs[k-1]-qs[k-2])^(poly[i]-qs[k-1]))<=0){
            qs.pop_back();
            k--;
        }
        qs.push_back(poly[i]);
        k++;
    }
    for(int i=n-2,t=k;i>=0;i--){
        while(k>t&&sgn((qs[k-1]-qs[k-2])^(poly[i]-qs[k-1]))<=0) {
            qs.pop_back();
            k--;
        }
        qs.push_back(poly[i]);
        k++;
    }
    qs.pop_back();
    return qs;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    
    int n;
    std::cin>>n;
    std::vector<Point> po(n);
    for(int i=0;i<n;i++){
        std::cin>>po[i].x>>po[i].y;
        //输入点的横纵坐标
    }

    std::sort(po.begin(), po.end());
    std::vector<Point> ch = convexHull(po);
    db ans = 0.0;
    for(int i=0,sz=ch.size();i<sz;i++){
        ans += len(ch[(i+1)%sz]-ch[i]);
    }
    std::cout<<std::fixed;
    std::cout.precision(2);
    std::cout<<ans<<"\n";

    return 0;
}
