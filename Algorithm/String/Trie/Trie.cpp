//复杂度 插入或查找一次 模板串长度
#include <iostream>
#include <cstdio>
#include <cstring>

#define MAXN 500005

using namespace std;

int nxt[MAXN][26];
int cnt;

void init(){
    memset(nxt,0,sizeof(nxt));
    cnt = 1;
}

void insert(string s){
    int cur = 1;
    for(auto c:s){
        if(!nxt[cur][c-'a']){
            nxt[cur][c-'a']=++cnt;
        }
        cur = nxt[cur][c-'a'];
    }
}

bool find_prefix(string s){
    int cur=1;
    for(auto c:s){
        if (!nxt[cur][c - 'a'])
        {
            return false;
        }            
        cur = nxt[cur][c - 'a'];
    }
    return true;
}

int main(){
    
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        string s1;
        cin>>s1;
        insert(s1);
    }
    while(1){
        string s1;
        cin>>s1;
        cout<<find_prefix(s1)<<endl;
    }


    return 0;
}

