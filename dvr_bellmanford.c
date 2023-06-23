#include<stdio.h>
#include<stdlib.h>

struct node{
    int from[10];
    int d[10];
}rtab[10];

int main(){
    int costmatrix[10][10],i,j,k,n,count=0;
    printf("Enter the no of nodes = ");
    scanf("%d",&n);
    printf("Enter the cost matrix\n'We consider undirected graph case'\n");
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            scanf("%d",&costmatrix[i][j]);
            costmatrix[i][i] = 0;
            rtab[i].from[j] = j;
            rtab[i].d[j] = costmatrix[i][j];
        }
    }
    do{
        count = 0;
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                for(k=0;k<n;k++){
                    if(rtab[i].d[j] > costmatrix[i][k] + rtab[k].d[j]){
                        rtab[i].from[j] = k;
                        rtab[i].d[j] = rtab[i].d[k] + rtab[k].d[j];
                        count++;
                    }
                }
            }
        }
    }while(count != 0);

    for(i=0;i<n;i++){
        printf("\nRouting Table of %d\n------------------\nfrom | \tto | \tdt\n------------------\n",i);
        for(j=0;j<n;j++){
            printf("%d\t%d\t%d\n",i,j,rtab[i].d[j]);
        }
    }
    return 0;
}