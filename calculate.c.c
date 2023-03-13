#include<stdio.h>
#include<math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define M 1000
int top1=-1,item1,top2=-1,item2,top3=-1;
int stack1[M];
char stack2[M];
int jisuan(int s,int t,char ss){
    if (ss=='+') return s+t;
    else if (ss=='-') return s-t;
    else if (ss=='*') return s*t;
    else if (ss=='/') return s/t;
    else return s%t;
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
    else if(isone(b)&&istwo(a)) return 0;
    else return 0;
}
void initial(int *top){
    (*top)=-1;
}
int isempty(int top){
    return top==-1;
}
int isfull(int top){
    return top==M-1;
}
int push1(int stack[],int *top,int item){
    if(isfull(*top)) return 0;
    else{
        stack[++(*top)]=item;
        return 1;
    }
}
int pop1(int stack[],int *top,int *item){
    if (isempty(*top)) {
        return 0;
    }
    else{
        *item=stack[(*top)--];
        return 1;
    }
}
int get1(int stack[],int *top,int *item){
    if (isempty(*top)) {
        return 0;
    }
    else{
        *item=stack[*top];
        return 1;
    }
}
int push2(char stack[],int *top,char item){
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
int get2(char stack[],int *top,char *item){
    if (isempty(*top)) {
        return 0;
    }
    else{
        *item=stack[*top];
        return 1;
    }
}
int i,result,k,op,j,weishu,shuzi,x1,x2;
char ssave[1005],save[1005],shuchu[1005],ch;
typedef struct ttree{
	int num;
	char sym;
	int fl;
	struct ttree *lc,*rc;
}tree,*ptr;
ptr stack3[M],pt1,pt2;
int push3(ptr stack[],int *top,ptr pt){
    if(isfull(*top)) return 0;
    else{
        stack[++(*top)]=pt;
        return 1;
    }
}
ptr pop3(ptr stack[],int *top){
	ptr pp=NULL;
    if (isempty(*top))  return NULL;
    else{
    	pp=(ptr)malloc(sizeof(tree));
        pp=stack[(*top)--];
        return pp;
    }
}
int main(){
    gets(ssave);
    ptr T=NULL,p=NULL,q=NULL;
    for (i=0; i<strlen(ssave); i++) {
        if (ssave[i]!=32) save[j++]=ssave[i];
    }
    for (i=0; i<strlen(save); i++) {	
        if (save[i]==32) continue;
        else if (48<=save[i]&&save[i]<=57)  shuchu[k++]=save[i];
        else{
            if (48<=save[i-1]&&save[i-1]<=57) shuchu[k++]=32;
            if (save[i]=='=') {
               while (top2!=-1) {
                        pop2(stack2, &top2, &ch);
                        shuchu[k++]=ch;
                    }break;
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
        if (48<=shuchu[i]&&shuchu[i]<=57) weishu++;
        else if (shuchu[i]==32) {
            for (j=0; j<weishu; j++) shuzi+=pow(10, j)*(shuchu[i-j-1]-48);
            p=(ptr)malloc(sizeof(tree));p->lc=NULL;p->rc=NULL;p->num=shuzi;p->fl=2;
            push3(stack3,&top3,p);
			push1(stack1, &top1, shuzi);
            shuzi=0;weishu=0;
        }
       else{
       		pt1=pop3(stack3,&top3);pt2=pop3(stack3,&top3);
			q=(ptr)malloc(sizeof(tree));q->lc=pt2;q->rc=pt1;q->sym=shuchu[i];q->fl=1;
			push3(stack3,&top3,q);
			T=q;  
            pop1(stack1, &top1, &x1);pop1(stack1, &top1, &x2);
            push1(stack1, &top1, jisuan(x2, x1, shuchu[i]));
        }
    }
    if(T){
	if(T->fl==1) printf("%c ",T->sym);else if(T->fl==2) printf("%d ",T->num);}
	if(T->lc){
    if(T->lc->fl==1) printf("%c ",T->lc->sym);else if(T->lc->fl==2) printf("%d ",T->lc->num);}
    if(T->rc){
    if(T->rc->fl==1) printf("%c",T->rc->sym);else if(T->rc->fl==2) printf("%d",T->rc->num);}
    printf("\n%d",stack1[top1]);
    return 0;
}


