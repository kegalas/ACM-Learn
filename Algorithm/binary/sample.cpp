#include <iostream>

bool judge(int mid){
    return true;
}

int main(){

    int l = 0;
    int r = 1000;
    //左右边界的取值依题而定

    while(l+1<r){
        int mid = (l+r)>>1;
        if(judge(mid)) l=mid;
        else r = mid;
    }

    if(judge(l)) std::cout<<l<<"\n";
    else std::cout<<r<<"\n";

    return 0;
}
