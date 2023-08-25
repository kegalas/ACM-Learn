//复杂度nlogn
//离散化 例如将1,500,40,1000保持相对大小不变，离散化为1,3,2,4
//luogu B3694
#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> arr,assi;

void solve(){
    int n;
    std::cin>>n;
    arr.clear();
    assi.clear();
    for(int i=1;i<=n;i++){
        int a;
        std::cin>>a;
        arr.push_back(a);
        assi.push_back(a);
    }
    std::sort(assi.begin(),assi.end());
    assi.erase(std::unique(assi.begin(),assi.end()),assi.end());

    for(int i=0;i<n;i++){
        arr[i] = std::upper_bound(assi.begin(),assi.end(),arr[i])-assi.begin();
    }

    for(int i=0;i<n;i++){
        std::cout<<arr[i]<<" ";
    }
    std::cout<<"\n";
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    
    int T;
	std::cin>>T;
	while(T--){
	    solve();
	}

    return 0;
}