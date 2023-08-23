//对数 n 进行 k 轮测试的时间复杂度是 klog^3(n)
//miller-rabin
//loj 143
//通过测试的有可能是素数，不通过的一定不是素数
#include <iostream>
#include <ctime>
#include <cstdio>
#include <cstdint>

using LL = __int128;//本题数据范围过大，防止运算中爆掉

LL const test_time = 10;

LL qPowMod(LL n, LL p, LL m){
    LL res = 1;
    while(p>0){
        if(p&1){
            res = (res * n)%m;
        }
        n = (n*n)%m;
        p>>=1;
    }
    return res;
}

bool millerRabin(LL n) {
    if (n < 3 || n % 2 == 0) return n == 2;
    LL a = n - 1, b = 0;
    while (a % 2 == 0) a /= 2, ++b;
    // test_time 为测试次数,建议设为不小于 8
    // 的整数以保证正确率,但也不宜过大,否则会影响效率
    for (LL i = 1, j; i <= test_time; ++i) {
        LL x = rand() % (n - 2) + 2;
        LL v = qPowMod(x, a, n);
        if (v == 1) continue;
        for (j = 0; j < b; ++j) {
            if (v == n - 1) break;
            v = v * v % n;
        }
        if (j == b) return 0;
    }
    return 1;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    
    srand(time(NULL));
    long long n;
    while(std::cin>>n){
        if(millerRabin(n)){
            std::cout<<"Y\n";
        }
        else{
            std::cout<<"N\n";
        }
    }
    return 0;
}
