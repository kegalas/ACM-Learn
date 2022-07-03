#include <stdio.h>
#include <time.h>

void swap(long *first, long *second)
{
    long temp = *first;
    *first = *second;
    *second = temp;
}

int partition(long *num,long left,long right){
    long i = left-1;

    long pivot = num[right];

    long j;
    for(j = left;j<right;j++){
        if(num[j]<=pivot){
            i++;
            swap(num+i,num+j);
        }
    }

    swap(num+i+1, num+right);
    return (i+1);

}

void quick_sort(long *num,long left, long right){
    if(left<right){
        long partitionIndex = partition(num, left, right);
        quick_sort(num,left,partitionIndex-1);
        quick_sort(num,partitionIndex,right);
    }


    return;
}


int main(){
    long num_count;
    long num[20000];
    scanf("%d",&num_count);
    long i;
    for(i=1;i<=num_count;i++){
        scanf("%d",&num[i]);
    }

    quick_sort(num,1,num_count);

    for(i=1;i<=num_count;i++){
        printf("%d ",num[i]);
    }


    return 0;
}