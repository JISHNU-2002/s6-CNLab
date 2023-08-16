#include<stdio.h>
#include<stdlib.h>
int main(){
    int n,bsize,orate,input[50],store = 0;
    printf("Enter bucket size            = ");
    scanf("%d",&bsize);    
    printf("Enter outgoing rate          = ");
    scanf("%d",&orate);
    printf("Enter no of incoming packets = ");
    scanf("%d",&n);

    for(int i=0;i<n;i++){
        printf("\nEnter packet[%d] size  = ",i);
        scanf("%d",&input[i]);

        if(input[i] <= (bsize-store)){
            store = store + input[i];
            printf("[%d] bytes in [%d] bucket area\n",store,bsize);
        }else{
            int drop = input[i] - (bsize - store);
            printf("dropped [%d] bytes from [%d] input\nbucket area is full [%d]/[%d]\n",drop,input[i],bsize,bsize);
            store = bsize;        
        }

        if(store >= orate){
            store = store - orate;
        }else{
            store = 0;
        }
        printf("[%d] bytes left in bucket after transmition of [%d] input\n",store,input[i]);
    }
    return 0;
}
