#include <stdio.h>

void bubbleSort(long *num){
    long temp = 0;
    if(*num>*(num+1)){
        temp = *num;
        *num = *(num+1);
        *(num+1) = temp;
    }
    return;
}

int main(){
    int numCount;
    long number[20000];
    scanf("%d",&numCount);
    int i;
    for(i=1;i<=numCount;i++){
        scanf("%d",&number[i]);
    }

    int last;
    int point;

    for(last=numCount;last>=2;last--){
        for(point=1;point<=last-1;point++){
            bubbleSort(number+point);
        }
    }

    for(i=1;i<=numCount;i++){
        printf("%d ",number[i]);
    }
    

    return 0;
}