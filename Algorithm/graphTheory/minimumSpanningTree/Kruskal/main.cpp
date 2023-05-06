//复杂度 mlogm
#include <iostream>
#include <algorithm>
#define MAXN 200005

using namespace std;

int u[MAXN],v[MAXN],w[MAXN];
int r[MAXN];//临时边序号，间接排序
int find_sets[MAXN];//并查集

bool cmp(const int i, const int j){return w[i]<w[j];}

int find(int x){return find_sets[x]==x ? x : find_sets[x] = find(find_sets[x]);}

int main(){
    int n,m;//点数和边数

    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>u[i]>>v[i]>>w[i];
        //起点，终点，边权
    }

    for(int i = 1;i<=n;i++){
        find_sets[i]=i;
    }
    for(int i=1;i<=m;i++){
        r[i]=i;
    }

    sort(r+1,r+m+1,cmp);

    int ans = 0;
    //int cnt=0;

    for(int i=1;i<=m;i++){
        int tmp = r[i];
        int x = find(u[tmp]);
        int y = find(v[tmp]);

        if(x!=y){
            ans += w[tmp];
            find_sets[x] = y;
            //cnt++;
        }
    }
    //计数，如果小于n-1则不连通
    /*
    if(cnt<n-1){
        cout<<"orz"<<endl;
        return 0;
        //如果是多个样例注意这个return 0
    }
    */

    cout<<ans<<endl;

    return 0;
}
