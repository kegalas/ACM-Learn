#include <iostream>

using namespace std;

int main(){
    long long a,b;
    cin>>a>>b;
    if(a<b){
        a=a+b;
        b=a-b;
        a=a-b;
    }

    long long ans = b;

    while((a%b)!=0){
        long long tmp = a%b;
        a = b;
        b = tmp;
        ans = b;
    }

    cout<<ans<<endl;
    //返回最大公约数

    return 0;
}
