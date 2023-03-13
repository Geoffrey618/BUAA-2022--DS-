#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
typedef struct custom{
    int wait;
    int order;
}cuss;
cuss cus[2000];
int window=3,i,n,zhouqi,cl,count=1,front=-1,rear=-1;
int main() {
    scanf("%d",&zhouqi);
    cuss custumer;
    for (cl=1;; cl++) {
        if(cl<=zhouqi){
            scanf("%d",&n);
        for (i=1; i<=n; i++) {
        	rear++;
            cus[rear].order=count++;cus[rear].wait=0;
        }
        }
        while ((rear-front)/window>=7&&window<5&&cl<=zhouqi) window++;
        for (i=1; i<=window&&rear!=front; i++) {
            custumer=cus[++front];
            printf("%d : %d\n",custumer.order,custumer.wait);
        }
        while ((rear-front)/window<7&&window>3) window--;
        for (i=front+1; i<=rear; i++) cus[i].wait++;
        if(cl>zhouqi&&rear==front) break;
    }
    return 0;
}


