#include <stdio.h>
#include <math.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
typedef struct ttree{
	int va,hi;
	struct ttree *lc,*rc;
}tree,*ptr;
void print(ptr t){
	if(t->lc==NULL&&t->rc==NULL) printf("%d %d\n",t->va,t->hi);
	return;
}
int sum,i,d;
void pre(ptr t){
	if(t!=NULL){
		print(t);
		pre(t->lc);
		pre(t->rc);
	}
	else return;
}
ptr T=NULL;
ptr create(ptr t,int x,int height){
	if(t==NULL){
		t=(ptr)malloc(sizeof(tree));
		t->va=x;t->lc=NULL;t->rc=NULL,t->hi=height+1;
	}
	else if(x<t->va) t->lc=create(t->lc,x,t->hi);
	else  t->rc=create(t->rc,x,t->hi);
	return t;
}
int main(){
	scanf("%d",&sum);
	for(i=1;i<=sum;i++){
		scanf("%d",&d);T=create(T,d,0);
	}
	pre(T);
	return 0;
} 


