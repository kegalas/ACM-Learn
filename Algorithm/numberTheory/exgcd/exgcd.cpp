//复杂度 logn
//求解ax+by=c的一组解，c不是gcd(a,b)的倍数则无解
//扩展欧几里得
//luogu P5656
#include <iostream>
#include <cmath>

using LL = long long;

LL exgcd(LL a,LL b,LL& x,LL& y){
    //求出的是ax+by=gcd(a,b)的一组解，等于c的需要转换一下
    if(b==0){
        x = 1;
        y = 0;//此时ax+by=gcd(a,b)中b=0，任何数与0的最大公约数是他本身，所以ax+0y=a，x=1 y=0
        return a;
    }
    LL d = exgcd(b,a%b,y,x);
    y -= (a/b)*x;
    return d;
}

int main(){
    int T;
    std::cin>>T;
    while(T--){
        LL a,b,c;
        std::cin>>a>>b>>c;
        LL x0=0, y0=0;
        LL d = exgcd(a,b,x0,y0);//d=gcd(a,b)
        if(c%d!=0){//c不是gcd(a,b)的倍数则无解
            std::cout<<"-1\n";
            continue;
        }
        LL x1 = x0*c/d, y1 = y0*c/d;//ax+by=gcd(a,b)的一组解转化为ax+by=c的一组解
        //通解的形式为x=x1+s*dx, y=y1-s*dy
        //其中s为任意整数，dx=b/d, dy = a/d;
        LL dx = b/d, dy = a/d;
        LL l = std::ceil((-x1+1.0)/dx);
        LL r = std::floor((y1-1.0)/dy);
        //x>0,y>0时，s的取值为[l,r]中的整数，若l>r，则说明不存在正整数解
        if(l>r){
            std::cout<<x1+l*dx<<" ";//所有解中x的最小正整数值
            std::cout<<y1-r*dy<<"\n";//所有解中y的最小正整数值
        }
        else{
            std::cout<<r-l+1<<" ";//正整数解的个数
            std::cout<<x1+l*dx<<" ";//正整数解中x的最小值
            std::cout<<y1-r*dy<<" ";//正整数解中y的最小值
            std::cout<<x1+r*dx<<" ";//正整数解中x的最大值
            std::cout<<y1-l*dy<<"\n";//正整数解中y的最大值
        }
        
    }
    return 0;
}
