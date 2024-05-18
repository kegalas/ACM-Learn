//复杂度 nlogn，其中求凸包nlogn，旋转卡壳本身为n
//Luogu P1452
//旋转卡壳和凸包
//注意题给条件，如果是整数坐标，务必切换到long long来避免误差

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

typedef long long db;
struct Point{db x,y;};
typedef Point Vec;

Vec operator+(Vec a, Vec b){return {a.x+b.x, a.y+b.y};}
Vec operator-(Vec a, Vec b){return {a.x-b.x, a.y-b.y};}
Vec operator*(db k, Vec v){return {k*v.x, k*v.y};}
Vec operator*(Vec v, db k){return {v.x*k, v.y*k};}
db operator*(Vec a, Vec b){return a.x*b.x+a.y*b.y;}
db operator^(Vec a, Vec b){return a.x*b.y-a.y*b.x;}//叉积
bool operator<(Point a, Point b){return (a.x<b.x)||((a.x==b.x)&&(a.y<b.y));}//横坐标第一关键字，纵坐标第二关键字
db len2(Vec v){return v.x*v.x+v.y*v.y;}//长度平方

int sgn(db x) {
    if (x==0) return 0;
    if (x<0) return -1;
    return 1;
} // 符号，等于零返回0，大于零返回1，小于零返回-1

std::vector<Point> convexHull(std::vector<Point> const & poly){
	// 返回凸包上的点
	// 如果要判断一个多边形是不是凸包，可以用其生成一个凸包，判断点数是否相同
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

db rc(std::vector<Point> const & ch){
    // 返回凸包直径的平方
    int tn = ch.size();
    int cnt=0;
    if(tn==2){
        return len2(ch[0]-ch[1]);
    }
    int i=0,j=0;
    for(int k=0;k<tn;k++){
        if(!(ch[i]<ch[k])) i=k;
        if(ch[j]<ch[k]) j=k;
    }
    db res = 0;
    int si=i,sj=j;
    while(i!=sj||j!=si){
        res = std::max(res, len2(ch[i]-ch[j]));
        if(sgn((ch[(i+1)%tn]-ch[i])^(ch[(j+1)%tn]-ch[j]))<0){
            i = (i+1)%tn;
        }else{
            j = (j+1)%tn;
        }
        
        cnt++;
    }

    return res;
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
    std::cout<<rc(ch)<<"\n";
    return 0;
}
