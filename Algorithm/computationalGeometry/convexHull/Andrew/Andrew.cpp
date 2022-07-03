#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

#define MAXN 50005

using namespace std;

struct Point{
    double x,y;
    Point()=default;
    Point(double x, double y):x(x),y(y){}
    Point operator + (Point p){
        return Point(x+p.x, y+p.y);
    }
    Point operator - (Point p){
        return Point(x-p.x, y-p.y);
    }
    Point operator * (double d){
        return Point(x*d, y*d);
    }
    double dot(Point p){//点积
        return x*p.x+y*p.y;
    }
    double det(Point p){//叉积
        return x*(p.y)-(p.x)*y;
    }

};

int n;
Point po[MAXN*2];

bool cmp(Point& a, Point& b){
    if(a.x!=b.x) return a.x<b.x;
    return a.y<b.y;
}

vector<Point> convexHull(){
    int k = 0;
    vector<Point> qs;
    for(int i=0;i<n;i++){
        while(k>1&&(qs[k-1]-qs[k-2]).det(po[i]-qs[k-1])<=0){
            qs.erase(qs.end()-1);
            k--;
        }
        qs.push_back(po[i]);
        k++;
    }
    for(int i=n-2,t=k;i>=0;i--){
        while(k>t&&(qs[k-1]-qs[k-2]).det(po[i]-qs[k-1])<=0) {
            qs.erase(qs.end()-1);
            k--;
        }
        qs.push_back(po[i]);
        k++;
    }
    qs.erase(qs.end()-1);
    return qs;
}

int main(){

    cin>>n;
    for(int i=0;i<n;i++){
        cin>>po[i].x>>po[i].y;
    }

    sort(po,po+n,cmp);

    for(auto p:convexHull()){
        cout<<p.x<<" "<<p.y<<endl;
    }




    return 0;
}

