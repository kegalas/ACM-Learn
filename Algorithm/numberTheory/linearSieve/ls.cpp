//复杂度 n
//欧拉筛, luogu p3383
#include <iostream>
#include <cstring>
#include <vector>

int const MAXN = 1e8+5;

std::vector<int> prime;
bool isnp[MAXN];

void sieve(int n){
    for(int i=2;i<=n;i++){
        if(!isnp[i]) prime.push_back(i);
        for(auto p:prime){
            if(i*p>n) break;
            isnp[i*p] = 1;
            if(i%p==0) break;
        }
    }
}

int main(){
    int n,q;
    std::cin>>n>>q;
    sieve(n);

    while(q--){
        int k;
        std::cin>>k;
        std::cout<<prime[k-1]<<"\n";
    }
    return 0;
}
