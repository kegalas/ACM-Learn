#include <iostream>

using namespace std;

int stack[1005];

int main(){
    int n;
    cin>>n;
    int top=0;
    for(int i=1;i<=n;i++){
        cin>>stack[top++];
    }
    top--;
    while(top>-1){
        cout<<stack[top]<<endl;
        stack[top--]=0;
    }
    return 0;
}
