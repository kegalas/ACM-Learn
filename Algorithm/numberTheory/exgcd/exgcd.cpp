//求解ax+by=gcd(a,b)的一组解
//扩展欧几里得
#include <iostream>

using namespace std;

int exgcd(int a, int b, int &x, int &y){
    if(!b){
        x = 1;
        y = 0;//此时ax+by=gcd(a,b)中b=0，任何数与0的最大公约数是他本身，所以ax+0y=a，x=1 y=0
        return a;
    }
    int d = exgcd(b, a%b, x, y);
    int t = x;
    x = y;
    y = t-(a/b)*y;
    return d;
}

int main(){
    int a,b,x,y,z;
    cin>>a>>b;
    z = exgcd(a,b,x,y);
    cout<<x<<" "<<y<<" "<<z<<endl;
    return 0;
}
