//miller-rabin
#include <iostream>
#include <ctime>
#include <cstdio>

using namespace std;

const int test_time = 10;

int qPowMod(int a, int m, int n){
    if(m==0) return 1;
    if(m==1) return (a%n);
    long long ans = 1; //不打ll会溢出
    while(m){
        if(m&1){
            ans = ans%n*a%n;
        }
        a = (long long)a%n*a%n;//这里不打ll会溢出导致判断错误
        m>>=1;
    }
    return ans;
}

bool millerRabin(int n) {
    if (n < 3 || n % 2 == 0) return n == 2;
    int a = n - 1, b = 0;
    while (a % 2 == 0) a /= 2, ++b;
    // test_time 为测试次数,建议设为不小于 8
    // 的整数以保证正确率,但也不宜过大,否则会影响效率
    for (int i = 1, j; i <= test_time; ++i) {
        int x = rand() % (n - 2) + 2, v = qPowMod(x, a, n);
        if (v == 1) continue;
        for (j = 0; j < b; ++j) {
            if (v == n - 1) break;
            v = (long long)v * v % n;
        }
        if (j >= b) return 0;
    }
    return 1;
}

int main(){
    srand(time(NULL));
    int n;
    cin>>n;
    if(millerRabin(n)){
        cout<<"Probably a prime"<<endl;
    }
    else{
        cout<<"A composite"<<endl;
    }
    return 0;
}
