//并查集

#include <iostream>
using namespace std;

const int MAXN = 1005;

int find_sets[MAXN];

int findf(int x){
    return find_sets[x]==x ? x : find_sets[x] = findf(find_sets[x]);
}

void unionSet(int x, int y){
    x = findf(x);
    y = findf(y);
    find_sets[x] = y;
}

int main(){
    int n;
    cin>>n;
    //点数
    for(int i=1;i<=n;i++){
        find_sets[i]=i;
    }
    int m;
    cin>>m;
    //边数
    for(int i=1;i<=m;i++){
        int a,b;
        cin>>a>>b;
        find_sets[b] = a;
    }
    cout<<findf(5)<<" "<<findf(8)<<endl;
    unionSet(5,8);
    cout<<findf(5)<<" "<<findf(8)<<endl;
    return 0;
}

/*
8 6
1 2
1 3
3 4
3 5
6 7
7 8
*/