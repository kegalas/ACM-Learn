//复杂度nlogn
//离散化 例如将1,500,40,1000保持相对大小不变，离散化为1,3,2,4
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> arr,assi;

int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        int a;
        cin>>a;
        arr.push_back(a);
        assi.push_back(a);
    }
    sort(assi.begin(),assi.end());
    assi.erase(unique(assi.begin(),assi.end()),assi.end());

    for(int i=0;i<n;i++){
        arr[i] = upper_bound(assi.begin(),assi.end(),arr[i])-assi.begin();
    }

    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;

    return 0;
}