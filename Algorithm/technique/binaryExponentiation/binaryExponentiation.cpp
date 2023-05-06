//复杂度logn
//快速幂
#include <iostream>

using namespace std;

long long binpow(long long n, long long p){
    long long res = 1;
    while(p>0){
        if(p&1){
            res = res * n;
        }
        n *= n;
        p>>=1;
    }
    return res;

}


int main(){
    long long n,p;
    cin>>n>>p;

    cout<<binpow(n,p)<<endl;

    return 0;
}

