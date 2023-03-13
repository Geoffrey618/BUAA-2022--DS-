#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define M 10000
int top,top2;
struct stack{
    int hhh;
    char cc;
}stack2[M];
typedef struct stack stackk;
stackk check[M];
void initial(int *top){
    (*top)=-1;
}
int isempty(int top){
    return top==-1;
}
int isfull(int top){
    return top==M-1;
}
int push(stackk stack[],int *top,int x,char fh){
    if (isfull(*top))return 0;
    else{
        (*top)++;
        stack[*top].cc=fh;
        stack[*top].hhh=x;
        return 1;
    }
}
int pop(stackk stack[],int *top,int *x,char *fh){
    if (isempty(*top)) return 0;
    else{
        *x=stack[*top].hhh;
        *fh=stack[*top].cc;
        (*top)--;
        return 1;
    }
}
char hang[300],flag,ch;
int hh,i,st,fl;
int main() {
    initial(&top);
    FILE *in;
    in=fopen("example.c", "r");
    while (fgets(hang, 300, in)!=NULL) {
        hh++;
        for (i=0; i<strlen(hang); i++) {
            if(st==0)
            {
if (hang[i]==40||hang[i]==123||hang[i]==41||hang[i]==125) push(stack2, &top, hh, hang[i]);
            else if(hang[i]=='\''||hang[i]=='\"') {st=1;flag=hang[i];}
            else if(hang[i]=='/')
            {
                if (hang[i+1]=='/') break;
                else if(hang[i+1]=='*'){ st=2;flag='*';}
            }
            else continue;
            }
            else {
                if(hang[i]==flag){
                    if (st==1) st=0;
                    else {
                        if (hang[i+1]=='/') st=0;
                    }
                }
                else continue;
            }
        }
    }
    initial(&top2);
    for (i=0; i<=top; i++) {
        if (stack2[i].cc==40) push(check, &top2, stack2[i].hhh, stack2[i].cc);
        else if(stack2[i].cc==41){
            if (check[top2].cc==40) {
                pop(check, &top2, &st, &ch);
            }
            else {
        printf("without maching '%c' at line %d\n",stack2[i].cc,stack2[i].hhh);fl=1;break;
            }
        }
        else if(stack2[i].cc==125){
            if (check[top2].cc==123) pop(check, &top2, &st, &ch);
            else {
        printf("without maching '%c' at line %d\n",stack2[i].cc,stack2[i].hhh);fl=1;break;
            }
        }
        else{
            if (check[top2].cc==40) {
    printf("without maching '%c' at line %d\n",check[top2].cc,check[top2].hhh);fl=1;break;
            }
            else push(check, &top2, stack2[i].hhh, stack2[i].cc);
        }
    }
    if (fl==0&&top2!=-1) {
        printf("without maching '%c' at line %d\n",check[top2].cc,check[top2].hhh);fl=1;
    }
    if (fl==0) {
        for (i=0; i<=top; i++) printf("%c",stack2[i].cc);
    }
    fclose(in);
    return 0;
}



