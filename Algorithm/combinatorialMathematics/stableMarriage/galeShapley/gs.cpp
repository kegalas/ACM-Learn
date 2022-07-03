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
queue<int>freemale;

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%d",&couple);
        while(!freemale.empty()){
            freemale.pop();
        }
        for(int i=0;i<couple;i++){
            scanf("%s",str);
            maleName[i]=str[0]-'a';
            freemale.push(maleName[i]);
        }
        sort(maleName, maleName+couple);

        for(int i=0;i<couple;i++){
            scanf("%s",str);
            femaleName[i]=str[0]-'A';
        }
        
        for(int i=0;i<couple;i++){
            scanf("%s",str);
            for(int j=0;j<couple;j++){
                maleLike[i][j]=str[j+2]-'A';
            }
        }
        for(int i=0;i<couple;i++){
            scanf("%s",str);
            for(int j=0;j<couple;j++){
                femaleLike[i][str[j+2]-'a']=couple-j;
            }
            femaleLike[i][couple]=0;
        }
        memset(maleChoice,0,sizeof(maleChoice));

        for(int i=0;i<couple;i++){
            femaleChoice[i]=couple;
        }
        while(!freemale.empty()){
            int male=freemale.front();
            int female=maleLike[male][maleChoice[male]];
            if(femaleLike[female][male]>femaleLike[female][femaleChoice[female]]){
                freemale.pop();
                if(femaleChoice[female]!=couple){
                    freemale.push(femaleChoice[female]);
                    maleChoice[femaleChoice[female]]++;
                }
                femaleChoice[female]=male;
            }
            else
                maleChoice[male]++;
        }
        for(int i=0;i<couple;i++){
            printf("%c %c\n",maleName[i]+'a', maleLike[maleName[i]][maleChoice[maleName[i]]]+'A');
        }
        if(t) puts("");

    }

    return 0;
}


/*
2
3
a b c A B C
a:BAC
b:BAC
c:ACB
A:acb
B:bac
C:cab
3
a b c A B C
a:ABC
b:ABC
c:BCA
A:bac
B:acb
C:abc
*/
