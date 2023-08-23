//分组背包 复杂度=组数*背包容量*组内个数最大值
//luogu p1757
//有g个组，每组物品有group[i].size()个，每个物品有价值v和体积w，总共n个物品，背包体积为m。每个组最多只能拿一个物品出来，求最大价值。
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

int const MAXN = 1005;

int dp[MAXN];
std::vector<int> group[MAXN];//存储每一组的物品序号
int v[MAXN],w[MAXN];//物品价值和体积

void solve(){
    int n,m;
    std::cin>>m>>n;//背包容量;n件物品
    
    for(int i=1;i<=n;i++){
        int a,b,c;
        std::cin>>a>>b>>c;
        w[i] = a, v[i] = b,group[c].push_back(i);
    }
    
    int const g = 100;//本题中只说了有g个组，没有给出具体有多少个以及是否连续，采取遍历的方法
    for(int i=1;i<=g;i++){
        if(group[i].size()==0) continue;
        for(int j=m;j>=0;j--){
            for(auto k:group[i]){//注意这三个循环的顺序不能改变
                if(j>=w[k]) dp[j] = std::max(dp[j], dp[j-w[k]]+v[k]);
            }
        }
    }
    std::cout<<dp[m]<<"\n";
    
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

	int T;
	T=1;
	while(T--){
	    solve();
	}

    return 0;
}
