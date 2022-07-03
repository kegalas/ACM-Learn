#include <iostream>
//ax≡b (mod n)求解x
using namespace std;

int exgcd(int a, int b, int &x, int &y){
    if(!b){
        x=1;
        y=0;
        return a;
    }
    int d = exgcd(b, a%b, x, y);
    int tmp=x;
    x = y;
    y = tmp-a/b*y;
    return d;
}

int linearEquation(int a, int b, int c, int &x, int &y){
    int d = exgcd(a,b,x,y);
    if(c%d!=0) return -1;
    x = x*c/d;
    y = y*c/d;

    return d;
}



int main(){
    int a,b,c,x,y;

    cin>>a>>b;
    c=1;

    int d = linearEquation(a,b,c,x,y);

    if(d==-1){
        cout<<"None"<<endl;
    }
    else{
        //cout<<x<<" "<<y<<endl;
        //下面输出的是最小整数解
        int t = b/d;
        x = (x%t+t)%t;
        cout<<x<<endl;
    }




    return 0;
}
