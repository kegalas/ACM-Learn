//kmp,luogu3375
#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

#define MAXN 1000005

int nxt[MAXN];

string s1,s2;

int getNext(){
    nxt[0]=0;
    int r = 1;
    int l = 0;
    while (r<s2.length()){
        if (s2[l] == s2[r]){
            nxt[r]=l+1;
            r++;
            l++;
        }
        else if (l){
            l = nxt[l-1];
        }
        else{
            nxt[r]=0;
            r++;
        }
    }
    
    return 0;
}

int main(){
    cin>>s1>>s2;
    //给定两个字符串
    getNext();

    int pos=0,tar=0;

    while (tar<s1.length())
    {
        if(s1[tar]==s2[pos]){
            pos++;
            tar++;
        }
        else if (pos){
            pos = nxt[pos-1];
        }
        else{
            tar++;
        }

        if (pos==s2.length()){
            cout<<tar-pos+1<<endl;
            //输出s2在s1中出现的位置
            pos = nxt[pos-1];
        }
        
    }

    for(int i=0;i<s2.length();i++){
        cout<<nxt[i]<<" ";
        //表示s2​的长度为i的前缀的最长border长度。
    }

    cout<<endl;

    return 0;
}
