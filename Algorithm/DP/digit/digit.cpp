//数位dp模板题，常用记忆化搜索实现
//hdu 2089
//本题要求，[n,m]之间的所有整数，不含4，不含62（连续的）的数字有多少个
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>

#define pb push_back

std::vector<int> digit;//用于存储getSum中x的每一位，最高位从0下标开始
int dp[8][12][2];//dp[pos][last][limit]
//pos代表搜索到第几位，如五位数，pos==0说明搜索到高位第一位，pos==4说明搜索到个位
//last代表上一位搜索的数字是多少，如果last==11，10这样的数字则代表目前在搜索pos==0。设置为11还是10还是别的什么要看题目对只有一位数时的要求
//limit代表本位数字的取值有没有限制，例如上限是12345，现在搜到了12???，要搜第三位，显然第三位只能取0,1,2,3，limit==true。又如搜到了11???，第三位就可以取0-9，limit==false。
//limit==true当且仅当上一位limit也为true且取得最大值（第一位特判）

int dfs(int pos, int last, bool limit){
    int ret = 0;
    if(pos==digit.size()) return 1;//搜索终点，由于不是非法状态所以返回1
    if(dp[pos][last][limit] != -1) return dp[pos][last][limit];
    for(int v=0;v<=(limit ? digit[pos] : 9);v++){
        if((last==6 && v==2) || v==4) continue;//非法状态
        ret += dfs(pos+1, v, limit && v==digit[pos]);
    }
    dp[pos][last][limit] = ret;
    return ret;
}

int getSum(int x){
    digit.clear();
    std::memset(dp,-1,sizeof(dp));
    while(x){//注意如果某些题0也在范围内要特判
        digit.pb(x%10);
        x/=10;
    }
    std::reverse(digit.begin(),digit.end());//高位到低位存
    return dfs(0,10,true);
}

void solve(int n, int m){
    std::cout<<getSum(m)-getSum(n-1)<<"\n";
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

	int n,m;
	while(std::cin>>n>>m){
	    if(n==0 && m==0) break;
	    solve(n,m);
	}

    return 0;
}
