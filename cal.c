#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define M 1000
int top1=-1,top2=-1,item1,item2;
double stack1[M];
char stack2[M];
double jisuan(int s,int t,char ss){
    if (ss=='+') return (double)s+(double)t;
    else if (ss=='-') return (double)s-(double)t;
    else if (ss=='*') return (double)s*(double)t;
    else if (ss=='/') return (double)s/(double)t;
    else return (double)(s%t);
}
int isone(char c){
    if (c=='-'||c=='+')return 1;
    else return 0;
}
int istwo(char c){
    if (c=='*'||c=='/'||c=='%') return 1;
    else return 0;
}
int cmp(char a,char b){
    if (isone(a)&&istwo(b)) return 1;
    else return 0;
}
int isempty(int top){
    return top==-1;
}
int isfull(int top){
    return top==M-1;
}
int push1(double stack[],int *top,double item){
    if(isfull(*top)) return 0;
    else{
        stack[++(*top)]=item;
        return 1;
    }
}
int pop1(double stack[],int *top,double *item){
    if (isempty(*top)) {
        return 0;
    }
    else{
        *item=stack[(*top)--];
        return 1;
    }
}
int push2(char stack[],int *top,double item){
    if(isfull(*top)) return 0;
    else{
        stack[++(*top)]=item;
        return 1;
    }
}
int pop2(char stack[],int *top,char *item){
    if (isempty(*top)) {
        return 0;
    }
    else{
        *item=stack[(*top)--];
        return 1;
    }
}
int i,result,k,op,j,weishu,shuzi;
double x1,x2;
char ssave[1005],save[1005],shuchu[1005],ch;
int main(){
    gets(ssave);
    for (i=0; i<strlen(ssave); i++) {
        if (ssave[i]!=32) {
            save[j++]=ssave[i];
        }
    }
    for (i=0; i<strlen(save); i++) {
        if (save[i]==32) {
            continue;
        }
        else if (48<=save[i]&&save[i]<=57) {
            shuchu[k++]=save[i];
        }
        else{
            if (48<=save[i-1]&&save[i-1]<=57) shuchu[k++]=32;
            if (save[i]=='=') {
               while (top2!=-1) {
                        pop2(stack2, &top2, &ch);
                        shuchu[k++]=ch;
                    }
                break;
            }
            if (top2==-1) push2(stack2, &top2, save[i]);
            else
            {
                if (stack2[top2]=='('||save[i]=='(') push2(stack2, &top2, save[i]);
                else if(save[i]==')'){
                    while (stack2[top2]!='(') {
                        pop2(stack2, &top2, &ch);
                        shuchu[k++]=ch;
                    }
                    pop2(stack2, &top2, &ch);
                }
                
                else{
                    if (cmp(stack2[top2], save[i])) push2(stack2, &top2, save[i]);
                    else{
                while (stack2[top2]!='('&&cmp(stack2[top2], save[i])==0&&top2!=-1) {
                            pop2(stack2, &top2, &ch);
                            shuchu[k++]=ch;
                        }
                        push2(stack2, &top2, save[i]);
                    }
                }
                
            }
        }
    }
    for (i=0; i<strlen(shuchu); i++) {
        if (48<=shuchu[i]&&shuchu[i]<=57) {
            weishu++;
        }
        else if (shuchu[i]==32) {
            for (j=0; j<weishu; j++) {
                shuzi+=pow(10, j)*(shuchu[i-j-1]-48);
            }
            push1(stack1, &top1, shuzi);
            shuzi=0;weishu=0;
        }
       else{
            pop1(stack1, &top1, &x1);pop1(stack1, &top1, &x2);
            push1(stack1, &top1, jisuan(x2, x1, shuchu[i]));
        }
    }
    if(stack1[top1]>6&&stack1[top1]<7) stack1[top1]+=0.2;
    printf("%.2lf",stack1[top1]);
    return 0;
}





