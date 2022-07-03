#include <stdio.h>

void sort(long *num_point){
    long temp;
    temp = *num_point;

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
    for (i=2;i<=num_count;i++){
        long temp = 0;
        temp = num[i];
        int j;
        for (j=i-1;j>=1;j--){
            if(num[j]>temp){
                num[j+1] = num[j];
                if(j==1){
                    num[j]=temp;
                }
            }
            else{
                num[j+1]=temp;
                break;
            }
        }
    }
    for(i=1;i<=num_count;i++){
        printf("%d ",num[i]);
    }
    return 0;
}

