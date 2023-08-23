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
#define pb push_back
#define mkp make_pair
#define fi first
#define se second

using LL = long long;
using ULL = unsigned long long;
using uint = unsigned;
using i128 = __int128;
using pii = std::pair<int,int>;
using pll = std::pair<LL,LL>;

int const MAXN = 200005;
int const INF = 0x7fffffff;
int const MOD = 998244353;

/////////////////////////////////////////////////
//数据类型定义

typedef double db;
typedef long double LD;
struct Point{db x,y;};
typedef Point Vec;
struct Line{Point p; Vec v;};//点向式直线，不保证方向向量为单位向量
struct Seg{Point a,b;};//线段
struct Circle{Point o;db r;};//圆心和半径

/////////////////////////////////////////////////
//常数定义

Point const o{0.0,0.0};//原点
Line const ox{o,{1.0,0.0}}, oy{o,{0.0,1.0}};//横轴纵轴
db const PI = acos(-1);
db const EPS = 1e-9;

/////////////////////////////////////////////////
//可调整精度的比较

bool eq(db a, db b)  {return std::abs(a - b)< EPS;}//等于
bool ge(db a, db b)  {return a - b          > EPS;}//大于
bool le(db a, db b)  {return a - b          < -EPS;}//小于
bool geq(db a, db b) {return a - b          > -EPS;}//大于等于
bool leq(db a, db b) {return a - b          < EPS;}//小于等于

/////////////////////////////////////////////////
//基础运算

Vec r90a(Vec v){return {-v.y, v.x};}//向量逆时针90度
Vec r90c(Vec v){return {v.y, -v.x};}//向量顺时针90度
Vec operator+(Vec a, Vec b){return {a.x+b.x, a.y+b.y};}
Vec operator-(Vec a, Vec b){return {a.x-b.x, a.y-b.y};}
Vec operator*(db k, Vec v){return {k*v.x, k*v.y};}
Vec operator*(Vec v, db k){return {v.x*k, v.y*k};}
db operator*(Vec a, Vec b){return a.x*b.x+a.y*b.y;}
db operator^(Vec a, Vec b){return a.x*b.y-a.y*b.x;}//叉积
db len2(Vec v){return v.x*v.x+v.y*v.y;}//长度平方
db len(Vec v){return std::sqrt(len2(v));}//向量长度
db slope(Vec v){return v.y/v.x;}//斜率，不存在时，用后面的paral_y函数，不要判断是否是无穷

/////////////////////////////////////////////////
//向量操作

db cos_v(Vec a, Vec b){return a*b/len(a)/len(b);}//向量夹角余弦
Vec norm(Vec v){return {v.x/len(v), v.y/len(v)};}//求其单位向量
Vec pnorm(Vec v){return (v.x<0?-1:1)/len(v)*v;}//与原向量平行且横坐标大于零的单位向量
Vec dvec(Seg l){return l.b-l.a;}//线段转化为向量（没有归一化）

/////////////////////////////////////////////////
//直线操作

Line line(Point a, Point b){return {a,b-a};}//两点式直线
Line line(db k, db b){return {{0,b},{1,k}};}//斜截式直线y=kx+b
Line line(Point p, db k){return {p,{1,k}};}//点斜式直线
Line line(Seg l){return {l.a, l.b-l.a};}//线段所在直线
db at_x(Line l, db x){return l.p.y+(x-l.p.x)*l.v.y/l.v.x;}//给定直线上的横坐标求纵坐标，要确保直线不与y轴平行
db at_y(Line l, db y){return l.p.x+(y+l.p.y)*l.v.x/l.v.y;}//与上相反
Point pedal(Point p, Line l){return l.p-(l.p-p)*l.v/(l.v*l.v)*l.v;}//求点到直线的垂足
Line perp(Line l, Point p){return {p,r90c(l.v)};}//过某点作直线的垂线
Line bisec(Point p, Vec a, Vec b){return {p,norm(a)+norm(b)};}//角平分线

/////////////////////////////////////////////////
//线段操作

Point midp(Seg l){return {(l.a.x+l.b.x)/2.0,(l.a.y+l.b.y)/2.0};}//线段中点
Line perp(Seg l){return {midp(l), r90c(l.b-l.a)};}//线段中垂线

/////////////////////////////////////////////////
//几何关系

bool verti(Vec a, Vec b){return eq(a*b,0.0);}//向量是否垂直
bool paral(Vec a, Vec b){return eq(a^b,0.0);}//向量是否平行
bool paral_x(Vec v){return eq(v.y,0.0);}//是否平行x轴
bool paral_y(Vec v){return eq(v.x,0.0);}//是否平行y轴
bool on(Point p, Line l){return eq((p.x-l.p.x)*l.v.y, (p.y-l.p.y)*l.v.x);}//点是否在直线上
bool on(Point p, Seg l){return eq(len(p-l.a)+len(p-l.b),len(l.a-l.b));}//点是否在线段上
bool operator==(Point a, Point b){return eq(a.x,b.x)&&eq(a.y,b.y);}//点重合
bool operator==(Line a, Line b){return on(a.p,b)&&on(a.p+a.v,b);}//直线重合
bool operator==(Seg a, Seg b){return ((a.a==b.a&&a.b==b.b)||(a.a==b.b&&a.b==b.a));}//线段（完全）重合
bool operator<(Point a, Point b){return le(a.x,b.x)||(eq(a.x,b.x)&&le(a.y,b.y));}//横坐标第一关键字，纵坐标第二关键字
bool tangency(Line l, Circle c){return eq(std::abs((c.o^l.v)-(l.p^l.v)),c.r*len(l.v));}//直线和圆是否相切
bool tangency(Circle c1, Circle c2){return eq(len(c1.o-c2.o),c1.r+c2.r);}//两个圆是否相切

/////////////////////////////////////////////////
//距离

db dis(Point a, Point b){return len(a-b);}//两点距离
db dis(Point p, Line l){return std::abs((p^l.v)-(l.p^l.v))/len(l.v);}//点到直线的距离
db dis(Line a, Line b){return std::abs((a.p^pnorm(a.v))-(b.p^pnorm(b.v)));}//两直线距离，需要确保平行

/////////////////////////////////////////////////
//平移

Line operator+(Line l, Vec v){return {l.p+v, l.v};}//直线平移
Seg operator+(Seg l, Vec v){return {l.a+v,l.b+v};}//线段平移

/////////////////////////////////////////////////
//旋转

Point rotate(Point p, db rad){return {cos(rad)*p.x-sin(rad)*p.y,sin(rad)*p.x+cos(rad)*p.y};}//绕原点旋转rad弧度
Point rotate(Point p, db rad, Point c){return c+rotate(p-c,rad);}//绕c旋转rad弧度
Line rotate(Line l, db rad, Point c=o){return {rotate(l.p,rad,c),rotate(l.v,rad)};}//直线绕c点旋转rad弧度
Seg rotate(Seg l, db rad, Point c=o){return {rotate(l.a,rad,c), rotate(l.b,rad,c)};};

/////////////////////////////////////////////////
//对称

Point reflect(Point a, Point p){return {p.x*2.0-a.x, p.y*2.0-a.y};}//a关于p的对称点
Line reflect(Line l, Point p){return {reflect(l.p,p),l.v};}//直线l关于p的对称直线
Seg reflect(Seg l, Point p){return {reflect(l.a,p),reflect(l.b,p)};}//线段l关于p的对称线段

Point reflect(Point a, Line ax){return reflect(a, pedal(a,ax));}//点a关于直线ax的对称点
Point reflect_v(Vec v, Line ax){return reflect(v,ax)-reflect(o,ax);}//向量v关于直线ax的对称向量
Line reflect(Line l, Line ax){return {reflect(l.p, ax),reflect_v(l.v, ax)};}//直线l关于直线ax的对称直线
Seg reflect(Seg l, Line ax){return {reflect(l.a, ax), reflect(l.b, ax)};}

/////////////////////////////////////////////////
//交点

std::vector<Point> inter(Line a, Line b){
    //两直线的交点，没有交点返回空vector，否则返回一个大小为1的vector
    db c = a.v^b.v;
    std::vector<Point> ret;
    if(eq(c,0.0)) return ret;
    Vec v = 1/c*Vec{a.p^(a.p+a.v), b.p^(b.p+b.v)};
    ret.push_back({v*Vec{-b.v.x, a.v.x},v*Vec{-b.v.y, a.v.y}});
    return ret;
}

std::vector<Point> inter(Line l, Circle c){
    //直线与圆的交点
    Point p = pedal(c.o, l);
    db h = len(p-c.o);
    std::vector<Point> ret;
    if(ge(h,c.r)) return ret;
    if(eq(h,c.r)) {ret.push_back(p);return ret;};
    db d = std::sqrt(c.r*c.r - h*h);
    Vec v = d/len(l.v)*l.v;
    ret.push_back(p+v);ret.push_back(p+v);
    return ret;
}

std::vector<Point> inter(Circle c1, Circle c2){
    //两个圆的交点
    Vec v1 = c2.o - c1.o, v2 = r90c(v1);
    db d = len(v1);
    std::vector<Point> ret;
    if(ge(d, c1.r+c2.r)||ge(std::abs(c1.r-c2.r),d)) return ret;
    if(eq(d, c1.r+c2.r)||eq(std::abs(c1.r-c2.r),d)){ret.push_back(c1.o+c1.r/d*v1);return ret;}
    db a = ((c1.r*c1.r-c2.r*c2.r)/d+d)/2.0;
    db h = std::sqrt(c1.r*c1.r-a*a);
    Vec av = a/len(v1)*v1, hv = h/len(v2)*v2;
    ret.push_back(c1.o+av+hv);ret.push_back(c1.o+av-hv);
    return ret;
}

/////////////////////////////////////////////////
//三角形四心

Point barycenter(Point a, Point b, Point c){
    //重心
    return {(a.x+b.x+c.x)/3.0, (a.y+b.y+c.y)/3.0};
}

Point circumcenter(Point a, Point b, Point c){
    //外心
    db a2 = a*a, b2 = b*b, c2 = c*c;
    db d = 2.0*(a.x*(b.y-c.y))+b.x*(c.y-a.y)+c.x*(a.y-b.y);
    return 1/d * r90c(a2*(b-c)+b2*(c-a)+c2*(a-b));
}

Point incenter(Point a, Point b, Point c){
    //内心
    db a1 = len(b-c), b1 = len(a-c), c1 = len(a-b);
    db d = a1+b1+c1;
    return 1/d * (a1*a+b1*b+c1*c);
}

Point orthocenter(Point a, Point b, Point c){
    //垂心
    db n = b*(a-c), m = a*(b-c);
    db d = (b-c)^(a-c);
    return 1/d * r90c(n*(c-b)-m*(c-a));
}

int arr[MAXN];

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

	int a,b;
	std::cin>>a>>b;
	std::cout<<a+b<<"\n";

    return 0;
}
