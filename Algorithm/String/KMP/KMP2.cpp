//复杂度n
//kmp,luogu3375
#include <iostream>
#include <vector>
#include <string>

std::vector<int> prefixFunc(std::string str){
    //输入一个字符串，输出该字符串的前缀函数表
    int n = str.length();
    std::vector<int> ans(n);

    for(int i=1;i<n;i++){
        int j = ans[i-1];
        while(j>0 && str[i]!=str[j]) j = ans[j-1];
        if(str[i]==str[j]) j++;
        ans[i] = j;
    }

    return ans;
}

int main(){
    std::string str1,str2;
    std::cin>>str1>>str2;

    std::vector<int> pf = prefixFunc(str2+"#"+str1);
    //注意这个#号，代表的意思是不会在str2与str1中出现的字符，作为分隔符
    int n = str2.length();
    int m = str1.length();
    for(int i=n+1;i<n+m+1;i++){
        if(pf[i]==n){
            std::cout<<i-2*n+1<<"\n";
            //输出str2在str1中出现的位置
            //注意下标从0开始，计算在str1中出现的位置时要减去str2和分隔符
            //另外这个i是匹配到的子串的最右侧
        }
    }

    //下面不是kmp的一部分，是洛谷3375的要求
    pf = prefixFunc(str2);
    for(auto x:pf){
        std::cout<<x<<" ";
    }
    std::cout<<"\n";

    return 0;
}