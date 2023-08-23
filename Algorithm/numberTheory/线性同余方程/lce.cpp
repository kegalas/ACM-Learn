//复杂度 logn
//ax≡c (mod b)求解x
//和ax+by=c等价
//luogu p1082
#include <iostream>

using namespace std;

int exgcd(int a,int b,int& x,int& y){
    if(b==0){
        x = 1;
        y = 0;
        return a;
    }
    int d = exgcd(b,a%b,y,x);
    y -= (a/b)*x;
    return d;
}

int linearEquation(int a, int b, int c, int &x, int &y){
    int d = exgcd(a,b,x,y);
    if(c%d!=0) return -1;
    x = x*c/d;
    y = y*c/d;

    return d;
}

int main(){
    int a,b,c,x,y;

    cin>>a>>b;
    c=1;

    int d = linearEquation(a,b,c,x,y);
    //d是a,b的最大公约数，如果无解d==-1
    //下面输出的是最小整数解
    int t = b/d;
    x = (x%t+t)%t;
    cout<<x<<endl;

    return 0;
}
