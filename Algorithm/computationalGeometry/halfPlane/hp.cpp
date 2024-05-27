// 半平面交 luogu P4196
// 半平面即直线Ax+By+C=0分割平面坐标系的其中一半，这是一个点集
// 这里的板子是直线a->b的左半边
// 半平面交即为众多半平面划分出的点集的交集
// 本题是计算半平面划分出的多边形的面积

#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <regex>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/////////////////////////////////////////////////
// 数据类型定义

typedef double db;
typedef long double LD;
struct Point {
    db x, y;
};
typedef Point Vec;
struct Line {
    Point p;
    Vec v;
};  // 点向式直线，不保证方向向量为单位向量
struct Seg {
    Point a, b;
};  // 线段
struct Circle {
    Point o;
    db r;
};  // 圆心和半径

/////////////////////////////////////////////////
// 常数定义

Point const o{0.0, 0.0};                          // 原点
Line const ox{o, {1.0, 0.0}}, oy{o, {0.0, 1.0}};  // 横轴纵轴
db const PI = acos(-1);
db const EPS = 1e-9;

/////////////////////////////////////////////////
// 可调整精度的比较

bool eq(db a, db b) { return std::abs(a - b) < EPS; }  // 等于
bool ge(db a, db b) { return a - b > EPS; }            // 大于
bool le(db a, db b) { return a - b < -EPS; }           // 小于
bool geq(db a, db b) { return a - b > -EPS; }          // 大于等于
bool leq(db a, db b) { return a - b < EPS; }           // 小于等于
int sgn(db x) {
    if (std::abs(x) < EPS) return 0;
    if (x < 0) return -1;
    return 1;
}  // 符号，等于零返回0，大于零返回1，小于零返回-1

/////////////////////////////////////////////////
// 基础运算

Vec r90a(Vec v) { return {-v.y, v.x}; }  // 向量逆时针90度
Vec r90c(Vec v) { return {v.y, -v.x}; }  // 向量顺时针90度
Vec operator+(Vec a, Vec b) { return {a.x + b.x, a.y + b.y}; }
Vec operator-(Vec a, Vec b) { return {a.x - b.x, a.y - b.y}; }
Vec operator*(db k, Vec v) { return {k * v.x, k * v.y}; }
Vec operator*(Vec v, db k) { return {v.x * k, v.y * k}; }
db operator*(Vec a, Vec b) { return a.x * b.x + a.y * b.y; }
db operator^(Vec a, Vec b) { return a.x * b.y - a.y * b.x; }  // 叉积
db len2(Vec v) { return v.x * v.x + v.y * v.y; }              // 长度平方
db len(Vec v) { return std::sqrt(len2(v)); }                  // 向量长度
db slope(Vec v) {
    return v.y / v.x;
}  // 斜率，不存在时，用后面的paral_y函数，不要判断是否是无穷
db radp(Point x, Point a, Point b) {
    // 返回xa, xb的夹角弧度
    return fabs(atan2(fabs((a - x) ^ (b - x)), (a - x) * (b - x)));
}

/////////////////////////////////////////////////
// 向量操作

db sin_v(Vec a, Vec b) {
    return (a ^ b) / len(a) / len(b);
}  // 向量内积，右手定则
db cos_v(Vec a, Vec b) { return a * b / len(a) / len(b); }  // 向量夹角余弦
Vec norm(Vec v) { return {v.x / len(v), v.y / len(v)}; }  // 求其单位向量
Vec pnorm(Vec v) {
    return (v.x < 0 ? -1 : 1) / len(v) * v;
}  // 与原向量平行且横坐标大于零的单位向量
Vec dvec(Seg l) { return l.b - l.a; }  // 线段转化为向量（没有归一化）
Vec trunc(Vec v, db r) {               // v转化为长度为l的向量
    db l = len(v);
    if (!sgn(l)) return v;
    r /= l;
    return v * r;
}

/////////////////////////////////////////////////
// 直线操作

Line line(Point a, Point b) { return {a, b - a}; }  // 两点式直线
Line line(db k, db b) { return {{0, b}, {1, k}}; }  // 斜截式直线y=kx+b
Line line(Point p, db k) { return {p, {1, k}}; }    // 点斜式直线
Line line(Seg l) { return {l.a, l.b - l.a}; }       // 线段所在直线
db at_x(Line l, db x) {
    return l.p.y + (x - l.p.x) * l.v.y / l.v.x;
}  // 给定直线上的横坐标求纵坐标，要确保直线不与y轴平行
db at_y(Line l, db y) {
    return l.p.x + (y + l.p.y) * l.v.x / l.v.y;
}  // 与上相反
Point pedal(Point p, Line l) {
    return l.p - (l.p - p) * l.v / (l.v * l.v) * l.v;
}  // 求点到直线的垂足
Line perp(Line l, Point p) { return {p, r90c(l.v)}; }  // 过某点作直线的垂线
Line bisec(Point p, Vec a, Vec b) {
    return {p, norm(a) + norm(b)};
}  // 角平分线

/////////////////////////////////////////////////
// 线段操作

Point midp(Seg l) {
    return {(l.a.x + l.b.x) / 2.0, (l.a.y + l.b.y) / 2.0};
}  // 线段中点
Line perp(Seg l) { return {midp(l), r90c(l.b - l.a)}; }  // 线段中垂线

/////////////////////////////////////////////////
// 几何关系

bool verti(Vec a, Vec b) { return eq(a * b, 0.0); }  // 向量是否垂直
bool paral(Vec a, Vec b) { return eq(a ^ b, 0.0); }  // 向量是否平行
bool paral_x(Vec v) { return eq(v.y, 0.0); }         // 是否平行x轴
bool paral_y(Vec v) { return eq(v.x, 0.0); }         // 是否平行y轴
bool on(Point p, Line l) {
    return eq((p.x - l.p.x) * l.v.y, (p.y - l.p.y) * l.v.x);
}  // 点是否在直线上
bool on(Point p, Seg l) {
    return eq(len(p - l.a) + len(p - l.b), len(l.a - l.b));
}  // 点是否在线段上
// bool on(Point p, Seg l){return sgn((p-l.a)^(l.b-l.a))==0 &&
// sgn((p-l.a)*(p-l.b))<=0 ;}//点是否在线段上，无须len的判断法
int on(Point p, Circle c) {  // 0圆外，1圆上，2圆内
    db dst = len(p - c.o);
    if (sgn(dst - c.r) < 0) return 2;
    if (sgn(dst - c.r) == 0) return 1;
    return 0;
}
int on(Circle c1, Circle c2) {
    // 两圆关系，5相离、4外切、3相交、2内切、1内含
    db d = len(c1.o - c2.o);
    if (sgn(d - c1.r - c2.r) > 0) return 5;
    if (sgn(d - c1.r - c2.r) == 0) return 4;
    db l = fabs(c1.r - c2.r);
    if (sgn(d - l) > 0) return 3;
    if (sgn(d - l) == 0) return 2;
    return 1;
}
bool operator==(Point a, Point b) {
    return eq(a.x, b.x) && eq(a.y, b.y);
}  // 点重合
bool operator==(Line a, Line b) {
    return on(a.p, b) && on(a.p + a.v, b);
}  // 直线重合
bool operator==(Seg a, Seg b) {
    return ((a.a == b.a && a.b == b.b) || (a.a == b.b && a.b == b.a));
}  // 线段（完全）重合
bool operator<(Point a, Point b) {
    return le(a.x, b.x) || (eq(a.x, b.x) && le(a.y, b.y));
}  // 横坐标第一关键字，纵坐标第二关键字
bool tangency(Line l, Circle c) {
    return eq(std::abs((c.o ^ l.v) - (l.p ^ l.v)), c.r * len(l.v));
}  // 直线和圆是否相切
bool tangency(Circle c1, Circle c2) {
    return eq(len(c1.o - c2.o), c1.r + c2.r);
}  // 两个圆是否相切

/////////////////////////////////////////////////
// 距离

db dis(Point a, Point b) { return len(a - b); }  // 两点距离
db dis(Point p, Line l) {
    return std::abs((p ^ l.v) - (l.p ^ l.v)) / len(l.v);
}  // 点到直线的距离
db dis(Line a, Line b) {
    return std::abs((a.p ^ pnorm(a.v)) - (b.p ^ pnorm(b.v)));
}  // 两直线距离，需要确保平行
db dis(Point p, Seg s) {  // 点到线段的距离
    if (sgn(cos_v(p - s.a, s.b - s.a)) < 0 ||
        sgn(cos_v(p - s.b, s.a - s.b)) < 0)
        return std::min(dis(p, s.a), dis(p, s.b));
    return dis(p, line(s));
}
db dis(Seg s1,
       Seg s2) {  // 线段之间的距离，前提是不相交。相交时为0，需要自己判断
    return std::min(std::min(dis(s1.a, s2), dis(s1.b, s2)),
                    std::min(dis(s2.a, s1), dis(s2.b, s1)));
}

/////////////////////////////////////////////////
// 平移

Line operator+(Line l, Vec v) { return {l.p + v, l.v}; }    // 直线平移
Seg operator+(Seg l, Vec v) { return {l.a + v, l.b + v}; }  // 线段平移

/////////////////////////////////////////////////
// 旋转

Point rotate(Point p, db rad) {
    return {cos(rad) * p.x - sin(rad) * p.y, sin(rad) * p.x + cos(rad) * p.y};
}  // 绕原点旋转rad弧度
Point rotate(Point p, db rad, Point c) {
    return c + rotate(p - c, rad);
}  // 绕c旋转rad弧度
Line rotate(Line l, db rad, Point c = o) {
    return {rotate(l.p, rad, c), rotate(l.v, rad)};
}  // 直线绕c点旋转rad弧度
Seg rotate(Seg l, db rad, Point c = o) {
    return {rotate(l.a, rad, c), rotate(l.b, rad, c)};
};

/////////////////////////////////////////////////
// 对称

Point reflect(Point a, Point p) {
    return {p.x * 2.0 - a.x, p.y * 2.0 - a.y};
}  // a关于p的对称点
Line reflect(Line l, Point p) {
    return {reflect(l.p, p), l.v};
}  // 直线l关于p的对称直线
Seg reflect(Seg l, Point p) {
    return {reflect(l.a, p), reflect(l.b, p)};
}  // 线段l关于p的对称线段

Point reflect(Point a, Line ax) {
    return reflect(a, pedal(a, ax));
}  // 点a关于直线ax的对称点
Point reflect_v(Vec v, Line ax) {
    return reflect(v, ax) - reflect(o, ax);
}  // 向量v关于直线ax的对称向量
Line reflect(Line l, Line ax) {
    return {reflect(l.p, ax), reflect_v(l.v, ax)};
}  // 直线l关于直线ax的对称直线
Seg reflect(Seg l, Line ax) { return {reflect(l.a, ax), reflect(l.b, ax)}; }

/////////////////////////////////////////////////
// 交点

std::vector<Point> inter(Line a, Line b) {
    // 两直线的交点，没有交点返回空vector，否则返回一个大小为1的vector
    //  不能重叠
    db c = a.v ^ b.v;
    std::vector<Point> ret;
    if (eq(c, 0.0)) return ret;
    Vec v = 1 / c * Vec{a.p ^ (a.p + a.v), b.p ^ (b.p + b.v)};
    ret.push_back({v * Vec{-b.v.x, a.v.x}, v * Vec{-b.v.y, a.v.y}});
    return ret;
}

std::vector<Point> inter(Seg s1, Seg s2) {
    // 两线段的交点，没有交点返回空vector，否则返回一个大小为1的vector
    // 这里特别规定，如果两条线段有重叠线段，会返回第一条线段的两个端点
    std::vector<Point> ret;
    using std::max;
    using std::min;
    bool check = true;
    check = check && geq(max(s1.a.x, s1.b.x), min(s2.a.x, s2.b.x));
    check = check && geq(max(s2.a.x, s2.b.x), min(s1.a.x, s1.b.x));
    check = check && geq(max(s1.a.y, s1.b.y), min(s2.a.y, s2.b.y));
    check = check && geq(max(s2.a.y, s2.b.y), min(s1.a.y, s1.b.y));
    if (!check) return ret;

    db pd1 = (s2.a - s1.a) ^ (s1.b - s1.a);
    db pd2 = (s2.b - s1.a) ^ (s1.b - s1.a);
    if (sgn(pd1 * pd2) == 1) return ret;
    std::swap(s1, s2);  // 双方都要跨立实验
    pd1 = (s2.a - s1.a) ^ (s1.b - s1.a);
    pd2 = (s2.b - s1.a) ^ (s1.b - s1.a);
    if (sgn(pd1 * pd2) == 1) return ret;

    if (sgn(pd1) == 0 && sgn(pd2) == 0) {
        ret.push_back(s2.a);
        ret.push_back(s2.a);
        return ret;
    }
    return inter(line(s2), line(s1));
}

std::vector<Point> inter(Line l, Circle c) {
    // 直线与圆的交点
    Point p = pedal(c.o, l);
    db h = len(p - c.o);
    std::vector<Point> ret;
    if (ge(h, c.r)) return ret;
    if (eq(h, c.r)) {
        ret.push_back(p);
        return ret;
    };
    db d = std::sqrt(c.r * c.r - h * h);
    Vec v = d / len(l.v) * l.v;
    ret.push_back(p - v);
    ret.push_back(p + v);
    return ret;
}

std::vector<Point> inter(Circle c1, Circle c2) {
    // 两个圆的交点
    Vec v1 = c2.o - c1.o, v2 = r90c(v1);
    db d = len(v1);
    std::vector<Point> ret;
    if (ge(d, c1.r + c2.r) || ge(std::abs(c1.r - c2.r), d)) return ret;
    if (eq(d, c1.r + c2.r) || eq(std::abs(c1.r - c2.r), d)) {
        ret.push_back(c1.o + c1.r / d * v1);
        return ret;
    }
    db a = ((c1.r * c1.r - c2.r * c2.r) / d + d) / 2.0;
    db h = std::sqrt(c1.r * c1.r - a * a);
    Vec av = a / len(v1) * v1, hv = h / len(v2) * v2;
    ret.push_back(c1.o + av + hv);
    ret.push_back(c1.o + av - hv);
    return ret;
}

/////////////////////////////////////////////////
// 多边形相关

db area(std::vector<Point> const& ps) {
    // 逆时针排序的多边形的顶点，计算面积
    db ret = 0.0;
    for (int i = 0, sz = ps.size(); i < sz; i++) {
        ret += (ps[i] ^ ps[(i + 1) % sz]) / 2.0;
    }
    return ret;
}

bool isconvex(std::vector<Point> const& poly) {
    // 多边形是否为凸
    std::vector<bool> s(3, false);
    for (int i = 0, n = poly.size(); i < n; i++) {
        int j = (i + 1) % n;
        int k = (j + 1) % n;
        s[sgn((poly[j] - poly[i]) ^ (poly[k] - poly[i])) + 1] = true;
        if (s[0] && s[2]) return false;
    }
    return true;
}

int inpoly(std::vector<Point> const& poly, Point p) {
    // 一个点是否在多边形内？
    // 0外部，1内部，2边上，3顶点上
    int n = poly.size();
    for (int i = 0; i < n; i++) {
        if (poly[i] == p) return 3;
    }
    for (int i = 0; i < n; i++) {
        if (on(p, Seg{poly[(i + 1) % n], poly[i]})) return 2;
    }
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        int k = sgn((p - poly[j]) ^ (poly[i] - poly[j]));
        int u = sgn(poly[i].y - p.y);
        int v = sgn(poly[j].y - p.y);
        if (k > 0 && u < 0 && v >= 0) cnt++;
        if (k < 0 && v < 0 && u >= 0) cnt--;
    }
    return cnt != 0;
}

std::vector<Point> convexCut(std::vector<Point> const& ps, Point p1, Point p2) {
    // p1p2连成的直线，切开凸多边形，获得左半边的凸多边形
    // 多边形逆时针，左半边指(p2-p1)向量的左半边
    std::vector<Point> ret;
    int n = ps.size();
    for (int i = 0; i < n; i++) {
        Point q1 = ps[i], q2 = ps[(i + 1) % n];
        int d1 = sgn((p2 - p1) ^ (q1 - p1)), d2 = sgn((p2 - p1) ^ (q2 - p1));
        if (d1 >= 0) ret.push_back(q1);
        if (d1 * d2 < 0) ret.push_back(inter(line(q1, q2), line(p1, p2))[0]);
    }

    return ret;
}

/////////////////////////////////////////////////
// 三角形四心
// 可能都需要判断三点共线的情况

Point barycenter(Point a, Point b, Point c) {
    // 重心
    return {(a.x + b.x + c.x) / 3.0, (a.y + b.y + c.y) / 3.0};
}

Point circumcenter(Point a, Point b, Point c) {
    // 外心
    db a2 = a * a, b2 = b * b, c2 = c * c;
    db d = 2.0 * (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
    return 1 / d * r90c(a2 * (b - c) + b2 * (c - a) + c2 * (a - b));
}

Point incenter(Point a, Point b, Point c) {
    // 内心
    db a1 = len(b - c), b1 = len(a - c), c1 = len(a - b);
    db d = a1 + b1 + c1;
    return 1 / d * (a1 * a + b1 * b + c1 * c);
}

Point orthocenter(Point a, Point b, Point c) {
    // 垂心
    db n = b * (a - c), m = a * (b - c);
    db d = (b - c) ^ (a - c);
    return 1 / d * r90c(n * (c - b) - m * (c - a));
}

/////////////////////////////////////////////////
// 圆切线

std::vector<Line> tangentLine(Point p, Circle c) {
    // 过一点做圆的切线
    std::vector<Line> ret;
    int x = on(p, c);
    if (x == 2) return ret;
    if (x == 1) {
        ret.push_back(line(p, p + r90a(p - c.o)));
    }
    db d = dis(p, c.o);
    db l = c.r * c.r / d;
    db h = std::sqrt(c.r * c.r - l * l);
    ret.push_back(line(p, c.o + (trunc(p - c.o, l) + trunc(r90a(p - c.o), h))));
    ret.push_back(line(p, c.o + (trunc(p - c.o, l) + trunc(r90c(p - c.o), h))));
    return ret;
}

std::vector<Seg> getTangent(Circle a, Circle b) {
    // 求两圆的公共切线，这里用切点的线段表示了
    // 其中线段的a点代表圆a的切点
    std::vector<Seg> ret;
    db dist = len(a.o - b.o);

    auto mul = [](Point a_, Point b_) -> Point {
        return {a_.x * b_.x - a_.y * b_.y, a_.x * b_.y + a_.y * b_.x};
    };

    auto getInTangent = [&mul](Circle a_, Circle b_, db flg = 1.0) -> Seg {
        Point base = b_.o - a_.o;
        db w = a_.r + b_.r;
        db h = std::sqrt(len2(base) - w * w);
        Point k = mul(base, Point{w, h * flg}) * (1.0 / len2(base));
        return Seg{a_.o + k * a_.r, b_.o - k * b_.r};
    };

    auto getOutTangent = [&mul](Circle a_, Circle b_, db flg = 1.0) -> Seg {
        Point base = b_.o - a_.o;
        db h = b_.r - a_.r;
        db w = std::sqrt(len2(base) - h * h);
        Point k = mul(mul(base, Point{w, h * flg}) * (1.0 / len2(base)),
                      Point{0, flg});
        return Seg{a_.o + k * a_.r, b_.o - k * b_.r};
    };

    if (dist > a.r + b.r + EPS) ret.push_back(getInTangent(a, b, 1));

    if (dist > a.r + b.r - EPS) ret.push_back(getInTangent(a, b, -1));

    if (dist > std::abs(a.r - b.r) + EPS) ret.push_back(getOutTangent(a, b, 1));

    if (dist > std::abs(a.r - b.r) - EPS)
        ret.push_back(getOutTangent(a, b, -1));

    return ret;
}

/////////////////////////////////////////////////
// 相交面积

db interArea(Circle c, Point a, Point b) {
    // 圆c和三角形c.o a b的相交面积
    if (sgn((c.o - a) ^ (c.o - b)) == 0) return 0.0;
    Point q[5];
    int len = 0;
    q[len++] = a;
    Line l = line(a, b);
    auto vec = inter(l, c);
    if (vec.size() == 2) {
        if (sgn((a - vec[0]) * (b - vec[0])) < 0) q[len++] = vec[0];
        if (sgn((a - vec[1]) * (b - vec[1])) < 0) q[len++] = vec[1];
    }
    q[len++] = b;
    if (len == 4 && sgn((q[0] - q[1]) * (q[2] - q[1])) > 0)
        std::swap(q[1], q[2]);
    db res = 0.0;
    for (int i = 0; i < len - 1; i++) {
        if (on(q[i], c) == 0 || on(q[i + 1], c) == 0) {
            db arg = radp(c.o, q[i], q[i + 1]);
            res += c.r * c.r * arg / 2.0;
        } else {
            res += fabs((q[i] - c.o) ^ (q[i + 1] - c.o)) / 2.0;
        }
    }
    return res;
}

db interArea(Circle c, std::vector<Point> const& poly) {
    // 多边形和圆相交面积
    db ans = 0.0;
    for (int i = 0, sz = poly.size(); i < sz; i++) {
        int j = (i + 1) % sz;
        db ar = interArea(c, poly[i], poly[j]);
        if (sgn((poly[j] - c.o) ^ (poly[i] - c.o)) >= 0)
            ans += ar;
        else
            ans -= ar;
    }
    return fabs(ans);
}

db interArea(Circle c1, Circle c2) {
    // 两圆相交面积
    int rel = on(c1, c2);
    if (rel >= 4) return 0.0;
    if (rel <= 2) return std::min(PI * c1.r * c1.r, PI * c2.r * c2.r);

    db d = len(c1.o - c2.o);
    db alpha = acos((c1.r * c1.r + d * d - c2.r * c2.r) / (2 * c1.r * d));
    db beta = acos((c2.r * c2.r + d * d - c1.r * c1.r) / (2 * c2.r * d));
    db h = c1.r * sin(alpha);
    db s1 = c1.r * c1.r * alpha, s2 = c2.r * c2.r * beta;
    db s3 = d * h;
    return s1 + s2 - s3;
}

struct halfplane {
    Point s, e;
    db angle;
    // 表示向量s->e的左半平面
    halfplane() {}
    halfplane(Point s_, Point e_) : s(s_), e(e_) {}
    halfplane(Line l) : s(l.p), e(l.p + l.v) {}
    void calcAngle() { angle = atan2(e.y - s.y, e.x - s.x); }
    bool operator<(halfplane const& b) const { return angle < b.angle; }
};

struct halfplanes {
    int n;
    static int const MAXP = 1010;
    halfplane hp[MAXP];
    Point p[MAXP];
    int que[MAXP];
    int st, ed;

    void push(halfplane tmp) { hp[n++] = tmp; }

    void unique() {  // 去重
        int m = 1;
        for (int i = 1; i < n; i++) {
            if (sgn(hp[i].angle - hp[i - 1].angle) != 0)
                hp[m++] = hp[i];
            else if (sgn((hp[m - 1].e - hp[m - 1].s) ^
                         (hp[i].s - hp[m - 1].s)) > 0)
                hp[m - 1] = hp[i];
        }
        n = m;
    }

    bool halfplaneInsert() {
        // 这里指的是处理hp数组中的元素
        // 放入hp中需要使用push
        for (int i = 0; i < n; i++) hp[i].calcAngle();
        std::sort(hp, hp + n);
        unique();
        que[st = 0] = 0;
        que[ed = 1] = 1;
        p[1] = inter(line(hp[0].s, hp[0].e), line(hp[1].s, hp[1].e))[0];
        for (int i = 2; i < n; i++) {
            while (st < ed && sgn((hp[i].e - hp[i].s) ^ (p[ed] - hp[i].s)) < 0)
                ed--;
            while (st < ed &&
                   sgn((hp[i].e - hp[i].s) ^ (p[st + 1] - hp[i].s)) < 0)
                st++;
            que[++ed] = i;
            if (line(hp[i].s, hp[i].e) ==
                line(hp[que[ed - 1]].s, hp[que[ed - 1]].e))
                return false;
            p[ed] = inter(line(hp[i].s, hp[i].e),
                          line(hp[que[ed - 1]].s, hp[que[ed - 1]].e))[0];
        }
        while (st < ed && sgn((hp[que[st]].e - hp[que[st]].s) ^
                              (p[ed] - hp[que[st]].s)) < 0)
            ed--;
        while (st < ed && sgn((hp[que[ed]].e - hp[que[ed]].s) ^
                              (p[st + 1] - hp[que[ed]].s)) < 0)
            st++;
        if (st + 1 >= ed) return false;
        return true;
    }

    std::vector<Point> getConvex() {
        // 返回半平面交出来的凸多边形
        // 需要先调用halfplaneinsert()且返回true
        p[st] = inter(line(hp[que[st]].s, hp[que[st]].e),
                      line(hp[que[ed]].s, hp[que[ed]].e))[0];
        std::vector<Point> ret(ed - st + 1);
        for (int j = st, i = 0; j <= ed; i++, j++) ret[i] = p[j];

        return ret;
    }
} hps;

void solve() {
    int n;
    std::cin >> n;  // 多边形个数
    while (n--) {
        int m;  // 多边形点数，逆时针输入
        std::cin >> m;
        std::vector<Point> ps(m);
        for (int i = 0; i < m; i++) std::cin >> ps[i].x >> ps[i].y;
        for (int i = 0; i < m; i++) hps.push(halfplane(ps[i], ps[(i + 1) % m]));
    }

    if (!hps.halfplaneInsert()) {
        std::cout << "0.000\n";
        return;
    }
    auto vec = hps.getConvex();
    std::cout << std::fixed;
    std::cout.precision(3);
    std::cout << area(vec) << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int T;
    // std::cin >> T;
    T = 1;
    while (T--) {
        solve();
    }

    return 0;
}
