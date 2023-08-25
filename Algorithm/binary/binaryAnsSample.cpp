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

//当验证一个情况是否能满足题目的复杂度低于$O(n)$，而且这些情况具有单调性（即例如若x>y，x不能满足，则y一定不能满足）时，就可以通过二分去得到最符合题意的答案。二分这些情况的复杂度为$O(\log n)$，再乘上验证情况的复杂度得到总的复杂度。

//judge函数应该根据题意写出。

//如果是浮点数的二分，则不推荐使用EPS进行精度判断（有可能会丢精度）。而是使用计数器，一般迭代100次就能保证符合题目要求。
