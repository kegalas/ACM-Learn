//POJ 3487
#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

const int N   = 30;
const int inf = 1<<29;
const int MOD = 2007;

typedef long long ll;

int couple;
int maleLike[N][N], femaleLike[N][N];
int maleChoice[N],  femaleChoice[N];
int maleName[N],    femaleName[N];
char str[N];
queue<int>freemale;//目前单身的男人

int main(){
    int t;
    scanf("%d",&t);//数据组数
    while(t--){
        scanf("%d",&couple);//男女对数
        while(!freemale.empty()){
            freemale.pop();
        }
        for(int i=0;i<couple;i++){
            scanf("%s",str);
            maleName[i]=str[0]-'a';//题目中是以小写字母给男人名字，转化为数字
            freemale.push(maleName[i]);
        }
        sort(maleName, maleName+couple);//名字排序，便于字典序

        for(int i=0;i<couple;i++){
            scanf("%s",str);
            femaleName[i]=str[0]-'A';//女人名字是大写字母
        }
        
        for(int i=0;i<couple;i++){
            scanf("%s",str);
            for(int j=0;j<couple;j++){
                maleLike[i][j]=str[j+2]-'A';//男人喜好顺序由男人名字:女人名字列表给出;降序排列
            }
        }
        
        //女士对男士的打分，添加虚拟人物，编号couple，为女士的初始对象
        for(int i=0;i<couple;i++){
            scanf("%s",str);
            for(int j=0;j<couple;j++){
                femaleLike[i][str[j+2]-'a']=couple-j;//排名越前打分越高
            }
            femaleLike[i][couple]=0;
        }
        memset(maleChoice,0,sizeof(maleChoice));
        //一开始男士的期望都是最喜欢的女士

        for(int i=0;i<couple;i++){
            femaleChoice[i]=couple;
        }
        
        while(!freemale.empty()){
            int male=freemale.front();
            //找出未配对的男士
            int female=maleLike[male][maleChoice[male]];
            //找出心意的女士
            if(femaleLike[female][male]>femaleLike[female][femaleChoice[female]]){
            //比现男友好
                freemale.pop();
                if(femaleChoice[female]!=couple){
                //前男友再次单身，并且不能将虚拟人物加入队列
                    freemale.push(femaleChoice[female]);
                    maleChoice[femaleChoice[female]]++;
                }
                femaleChoice[female]=male;
				//更换男友
            }
            else
                maleChoice[male]++;
                //如果被拒绝，则选择下一位
        }
        for(int i=0;i<couple;i++){
            printf("%c %c\n",maleName[i]+'a', maleLike[maleName[i]][maleChoice[maleName[i]]]+'A');
        }
        if(t) puts("");

    }

    return 0;
}
