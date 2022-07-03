//归并排序
#include <stdio.h>

void merge(long *num,long *tmp, int left, int mid_index ,int right){
    
    int first=left, second = mid_index+1, tmp_index = left;
    while(first<mid_index+1&&second<right+1){
        if(*(num+first)<*(num+second)){
            tmp[tmp_index] = *(num+first);
            tmp_index++;
            first++;
        }
        else{
            tmp[tmp_index] = *(num+second);
            tmp_index++;
            second++;
        }
    }
    while(first<mid_index+1){
        tmp[tmp_index++] = *(num+first);
        first++;
    }
    while(second<right+1){
        tmp[tmp_index++] = *(num+second);
        second++;
    }
    int i;
    for(i=left;i<=right;i++){
        num[i]=tmp[i];
    }

    return;
}

void merge_sort(long *num,long *tmp, int left, int right){
    int mid_index;
    if(left<right){
        mid_index = left + (right-left)/2;//这样写疑似可以避免int溢出
        merge_sort(num,tmp,left,mid_index);
        merge_sort(num,tmp,mid_index+1,right);
        merge(num,tmp,left,mid_index,right);
    } 
    return;
}

int main(){
    int num_count;
    long num[20000];
    long tmp[20000];
    scanf("%d",&num_count);
    int i;
    for(i=1;i<=num_count;i++){
        scanf("%d",&num[i]);
    }

    merge_sort(num,tmp,1,num_count);
    
    for(i=1;i<=num_count;i++){
        printf("%d ",num[i]);
    }

    return 0;
}
