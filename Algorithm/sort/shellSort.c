#include <stdio.h>

void shellSort(long num[],int num_count,int increment){
    int i;
    for(i = increment+1;i<=num_count;i++){
        long temp = num[i];
        int j;
        for (j=i;j>=increment;j-=increment){
            if(temp<num[j-increment]){
                num[j]=num[j-increment];
            }
            else{
                break;
            }   
        }
        num[j] = temp;
    }
    return;
}


int main(){
    int num_count;
    long num[20000];
    scanf("%d",&num_count);
    int i;
    for(i=1;i<=num_count;i++){
        scanf("%d",&num[i]);
    }

    int increment = num_count/2;

    while (increment>=1){
        shellSort(num,num_count,increment);
        increment/=2;
    }

    for(i=1;i<=num_count;i++){
        printf("%d ",num[i]);
    }

    return 0;
}