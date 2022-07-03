#include <stdio.h>

struct num_data
{
    short if_sorted;
    long num;
};



int main(){
    int num_count;
    struct num_data num[20000];
    scanf("%d",&num_count);
    int i;
    for(i=1;i<=num_count;i++){
        scanf("%d",&num[i].num);
        num[i].if_sorted=0;
    }

    long result[20000];

    for(i=1;i<=num_count;i++){
        int point;
        int biggest_point = 0;
        short if_get_first = 0;
        long biggest_num;
        for(point=1;point<=num_count;point++){
            if(num[point].if_sorted==0&&if_get_first==0){
                biggest_num = num[point].num;
                biggest_point = point;
                if_get_first=1;
            }
            else if(num[point].if_sorted==0){
                if(num[point].num>biggest_num){
                    biggest_num = num[point].num;
                    biggest_point = point;
                }
            }
        }
        result[i]=biggest_num;
        num[biggest_point].if_sorted=1;
    }

    for(i=1;i<=num_count;i++){
        printf("%d ",result[i]);
    }

    return 0;
}