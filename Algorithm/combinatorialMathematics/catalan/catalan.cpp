#include <iostream>
//前几项：1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796
using namespace std;

typedef long long ll;
const int MAXN = 3005;

ll h[MAXN];

ll comb(int a,int b){
    ll ans=1;
    for(int i=1;i<=b;i++){
        ans*=a;//数字太大会爆
        a--;
    }
    for(int i=1;i<=b;i++){
        ans/=i;
    }
    return ans;
}

int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cout<<comb(2*i,i)/(i+1)<<endl;
    }
    cout<<"###"<<endl;
    //下面是递推求法，不容易爆
    h[1]=1;
    cout<<h[1]<<endl;
    for(int i=2;i<=n;i++){
        h[i] = h[i-1]*(4*i-2)/(i+1);
        cout<<h[i]<<endl;
    }

    return 0;
}

