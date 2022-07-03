//拓扑排序
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct graph{
    int value;
    int to;
};

struct point
{
    int in_num;
    vector<graph> graph1;
}point1[100];


int main(){
    int n,m;
    cin>>n>>m;

    for(int i = 1;i<=n;i++){
        point1[i].in_num=0;
    }
    
    for (int i=1;i<=m;i++){
        int a,b,value;
        cin>>a>>b;//本次是无权图
        graph tmp;
        tmp.to=b;
        tmp.value = 0;
        point1[a].graph1.push_back(tmp);
        point1[b].in_num++;
    }
    queue<int> que;
    vector<int> ans;

    for (int i = 1; i <= n; i++)
    {
        if(point1[i].in_num == 0){
            que.push(i);
        }
    }

    while (!que.empty())
    {
        int p = que.front();
        que.pop();
        ans.push_back(p);
        for(int i = 0;i<point1[p].graph1.size();i++){
            int next = point1[p].graph1[i].to;
            point1[next].in_num--;
            if(point1[next].in_num==0){
                que.push(next);
            }
        }

    }

    if(ans.size()==n){
        for(int i = 0;i<ans.size();i++){
            cout<<ans[i]<<" ";
        }
    }
    else{
        cout<<"none";
    }
    
    
    

    return 0;
}

