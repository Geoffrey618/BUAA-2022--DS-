#include<stdio.h>
#include<math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define M 100
int top,item;
int stack[100];
int isempty(int top){
    return top==-1;
}
int isfull(int top){
    return top==M-1;
}
int push(int stack[],int *top,int item){
    if(isfull(*top)) return 0;
    else{
        stack[++(*top)]=item;
        return 1;
    }
}
int pop(int stack[],int *top,int *item){
    if (isempty(*top)) {
        return 0;
    }
    else{
        *item=stack[(*top)--];
        return 1;
    }
}
int get(int stack[],int *top,int *item){
    if (isempty(*top)) {
        return 0;
    }
    else{
        *item=stack[*top];
        return 1;
    }
}
int op,ele,d,pd;
int main(){
    top=-1;
    while (scanf("%d",&op)!=EOF) {
        if (op==-1) {
            break;
        }
        else if(op==1){
            scanf("%d",&ele);
            pd=push(stack, &top, ele);
            if (pd==0) {
                printf("error ");
            }
        }
        else {
            pd=pop(stack,&top,&d);
            if (pd==1) {
                printf("%d ",d);
            }
            else printf("error ");
        }
    }
    return 0;
}





