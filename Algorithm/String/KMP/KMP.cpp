//复杂度n
//kmp,luogu3375
#include <iostream>
#include <vector>
#include <string>

std::vector<int> prefixFunc(std::string const & str){
    //输入一个字符串，输出该字符串的前缀函数表
    //前缀函数pi[i]是满足s[0...x-1]==s[i-x+1...i]的最大的x
    //如果输入不是字符串而是一个数组，也可以很方便的修改为vector
    int n = str.length();
    std::vector<int> ans(n);

    for(int i=1;i<n;i++){
        //ans[0]=0，因为只看真前缀和真后缀
        int j = ans[i-1];
        while(j>0 && str[i]!=str[j]) j = ans[j-1];
        if(str[i]==str[j]) j++;
        ans[i] = j;
    }

    return ans;
}

std::vector<int> KMP(std::string const & s, std::string const & p){
    //输入主串和模式串，返回所有匹配的开始下标，下标从0开始
    std::vector<int> vec;
    std::vector<int> pf = prefixFunc(p);
    int ns = s.size(), np = p.size();
    for(int i=0, j=0;i<ns;i++){
        while(j && s[i]!=p[j]) j = pf[j-1];
        if(s[i]==p[j]) j++;
        if(j==np){
            vec.push_back(i-j+2);
            j = pf[j-1];
        }
    }
    
    return vec;
}

//我们可以通过把模式串和主串拼在一起，p+#+s，然后求这个字符串的前缀函数表（#代表不在主串、模式串字符集内的一个符号），然后pi[i]如果等于模式串的长度，那么i是匹配模式串的子串的起点。
//关于最小循环结，设字符串下标从1开始，长度为n，则如果n%(n-pf[n])==0，则有循环节，并且长度为n-pf[n]（当然长度可以为n）

int main(){
    std::string str1,str2;
    std::cin>>str1>>str2;

    for(auto x:KMP(str1,str2)){
        std::cout<<x<<"\n";
    }

    //下面不是kmp的一部分，是洛谷3375的要求
    for(auto x:prefixFunc(str2)){
        std::cout<<x<<" ";
    }
    std::cout<<"\n";

    return 0;
}

