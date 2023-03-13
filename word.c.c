#include<stdio.h>
#include<math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
int sum,k;
typedef struct Word{
    char c[55];
    int x;
}wword;
wword list[10005];
typedef struct btree{
	char string[55];
	struct btree *lc,*rc;
}tree,*ptr;
ptr create(ptr t,char st[]){
	if(t==NULL){
		t=(ptr)malloc(sizeof(tree));
		t->lc=NULL;t->rc=NULL;strcpy(t->string,st);
	}
	else if(strcmp(st,t->string)>0) t->rc=create(t->rc,st);
	else if(strcmp(st,t->string)<0) t->lc=create(t->lc,st);
	return t;
}
int search(char word[]){
	int j=0;
    for (j=0; j<sum; j++) {
        if (strcmp(word, list[j].c)==0) {
            return j;
        }
    }
    return -1;
}
void add(char word[]){
    int flag=search(word);
    if(flag==-1){
        strcpy(list[sum].c, word);
        list[sum].x=1;
        sum++;
    }
    else{
        (list[flag].x)++;
    }
}
int cmp(const void*a,const void*b){
    const wword *pa=a,*pb=b;
    return (int)(strcmp(pa->c, pb->c));
}
ptr T=NULL;
int main() {
    sum=0;
    char hang[5000],word[55],*p1,c;
    FILE *in;
    in=fopen("article.txt", "r");
    while (fgets(hang, 5000, in)!=NULL) {
        p1=hang;
        while (*p1!='\0') {
            if (isalpha(*p1)) {
                if (isupper(*p1)) {
                    c=tolower(*p1);
                }
                else c=*p1;
                word[k++]=c;
            }
            else{
                if (word[0]!='\0') {
                    add(word);
                    T=create(T,word); 
                    memset(word, '\0', sizeof(word));
                    k=0;
                }
            }
            p1++;
        }
    }
   	if(T) printf("%s",T->string);
    if(T->rc) printf(" %s",T->rc->string);
    if(T->rc->rc) printf(" %s",T->rc->rc->string);
    printf("\n");
    qsort(list, sum, sizeof(wword), cmp);
    int i=0;
    for (i=0; i<sum; i++) {
        printf("%s %d\n",list[i].c,list[i].x);
    }
    fclose(in);
    return 0;
}


