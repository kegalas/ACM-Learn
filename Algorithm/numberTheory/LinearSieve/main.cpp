//复杂度 n
//欧拉筛
#include <iostream>
#include <cstring>
#define MAXN 50005


using namespace std;

int main(){
    int n, prime[MAXN], cnt=0;
    bool is_not_prime[MAXN];
    cin>>n;
    //2~n中有多少个素数
    memset(is_not_prime, 0, sizeof(prime));

    for (int i = 2;i<=n;i++){
        if(!is_not_prime[i])    prime[++cnt] = i;
        for(int j = 1;j<=cnt&&i*prime[j]<=n;j++){
            is_not_prime[i*prime[j]] = 1;
            if(i%prime[j]==0) break;
        }
    }

    for(int i = 1;i<=cnt;i++){
        cout<<prime[i]<<" ";
        //输出素数
    }
    return 0;
}
