//复杂度 logn
//luogu B3736
//gcd是可重复贡献的，gcd(x,x)=x，可以用st表维护区间gcd
//x*y=gcd(x,y)*lcm(x,y)，lcm是最小公倍数
#include <iostream>

inline int gcd(int a,int b){
    return b==0 ? a : gcd(b, a%b);
}

int main(){
    int x,y,z;
    std::cin>>x>>y>>z;
    std::cout<<gcd(gcd(x,y),z)<<"\n";
    
    return 0;
}
