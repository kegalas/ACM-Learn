#include <iostream>

using namespace std;

int queue[1005];

int main(){
    int n;
    cin>>n;
    if(n>1005){
        cout<<"too big"<<endl;
        return 0;
    }
    int first = 0;
    int last = 0;
    for(int i=0;i<n;i++){
        cin>>queue[last++];
    }
    last--;
    while(first<last+1){
        cout<<queue[first]<<endl;
        queue[first++]=0;
    }

    return 0;
}
