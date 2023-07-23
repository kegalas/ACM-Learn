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

typedef double db;
typedef long double LD;

struct Point{db x,y;};
typedef Point Vec;
struct Line{Point p; Vec v;};//点向式直线，不保证方向向量为单位向量
struct Seg{Point a,b;};//线段
struct Circle{Point o;db r;};//圆心和半径

Point const o{0.0,0.0};//原点
Line const ox{o,{1.0,0.0}}, oy{o,{0.0,1.0}};//横轴纵轴
db const PI = acos(-1);
db const EPS = 1e-9;

bool eq(db a, db b)  {return std::abs(a - b)< EPS;}//等于
bool ge(db a, db b)  {return a - b          > EPS;}//大于
bool le(db a, db b)  {return a - b          < -EPS;}//小于
bool geq(db a, db b) {return a - b          > -EPS;}//大于等于
bool leq(db a, db b) {return a - b          < EPS;}//小于等于

Vec r90a(Vec v){return {-v.y, v.x};}//向量逆时针90度
Vec r90c(Vec v){return {v.y, -v.x};}//向量顺时针90度
Vec operator+(Vec a, Vec b){return {a.x+b.x, a.y+b.y};}
Vec operator-(Vec a, Vec b){return {a.x-b.x, a.y-b.y};}
Vec operator*(db k, Vec v){return {k*v.x, k*v.y};}
Vec operator*(Vec v, db k){return {v.x*k, v.y*k};}
db operator*(Vec a, Vec b){return a.x*b.x+a.y*b.y;}
db operator^(Vec a, Vec b){return a.x*b.y-a.y*b.x;}//叉积
db len2(Vec v){return v.x*v.x+v.y*v.y;}
db len(Vec v){return std::sqrt(len2(v));}//向量长度
db slope(Vec v){return v.y/v.x;}//斜率，不存在时，用后面的paral_y函数，不要判断是否是无穷

db cos_v(Vec a, Vec b){return a*b/len(a)/len(b);}//向量夹角余弦
Vec norm(Vec v){return {v.x/len(v), v.y/len(v)};}//求其单位向量
Vec pnorm(Vec v){return (v.x<0?-1:1)/len(v)*v;}//与原向量平行且横坐标大于零的单位向量
Vec dvec(Seg l){return l.b-l.a;}//线段转化为向量（没有归一化）

Line line(Point a, Point b){return {a,b-a};}//两点式直线
Line line(db k, db b){return {{0,b},{1,k}};}//斜截式直线y=kx+b
Line line(Point p, db k){return {p,{1,k}};}//点斜式直线
Line line(Seg l){return {l.a, l.b-l.a};}//线段所在直线
db at_x(Line l, db x){return l.p.y+(x-l.p.x)*l.v.y/l.v.x;}//给定直线上的横坐标求纵坐标，要确保直线不与y轴平行
db at_y(Line l, db y){return l.p.x+(y+l.p.y)*l.v.x/l.v.y;}//与上相反
Point pedal(Point p, Line l){return l.p-(l.p-p)*l.v/(l.v*l.v)*l.v;}//求点到直线的垂足
Line perp(Line l, Point p){return {p,r90c(l.v)};}//过某点作直线的垂线
Line bisec(Point p, Vec a, Vec b){return {p,norm(a)+norm(b)};}//角平分线

Point midp(Seg l){return {(l.a.x+l.b.x)/2,(l.a.y+l.b.y)/2};}//线段中点
Line perp(Seg l){return {midp(l), r90c(l.b-l.a)};}//线段中垂线

bool verti(Vec a, Vec b){return eq(a*b,0.0);}//向量是否垂直
bool paral(Vec a, Vec b){return eq(a^b,0.0);}//向量是否平行
bool paral_x(Vec v){return eq(v.y,0.0);}//是否平行x轴
bool paral_y(Vec v){return eq(v.x,0.0);}//是否平行y轴

int arr[MAXN];

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

	

    return 0;
}
