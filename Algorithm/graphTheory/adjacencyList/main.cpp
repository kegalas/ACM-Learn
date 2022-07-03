#include <iostream>
#include <vector>

using namespace std;

struct graph{
    int value;
    int to;
};

struct point
{
    int self;
    vector<graph> graph1;
}point1[100];



int main(){
    //有向图
    int n,m;//n个点，m条边
    cin>>n>>m;
    for (int i=1;i<=m;i++){
        int a,b,value;
        cin>>a>>b>>value;
        graph tmp;
        tmp.value = value;
        tmp.to = b;
        point1[a].graph1.push_back(tmp);
    }

    for (int i=1;i<=n;i++){
        for(int j=0;j<point1[i].graph1.size();j++){
            cout<<i<<" ";
            cout<<point1[i].graph1[j].to<<" ";
            cout<<point1[i].graph1[j].value<<endl;

        }
    }

    return 0;
}