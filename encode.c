#include<stdio.h>
#include<math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
typedef struct item *ptr;
struct item{
    char c;
    struct item *next;
}iitem;
char initial[35],delete[35],key[105],save[105],hang[1000],spe;
int i,flag,j,k,mmove,sign,fl[105];
char replace(char y){
    return key[y-32];
}
int main(){
    
    gets(initial);
    for (i=0; i<strlen(initial); i++) {
        flag=0;
        for (j=0; j<i; j++) {
            if(initial[j]==initial[i])
            {
                flag=1;break;
            }
        }
        if (flag==0) {
            delete[k++]=initial[i];
        }
    }
    for (i=0; i<105; i++) {
        if (strchr(delete, 32+i)) {
            fl[i]=1;
        }
    }
    j=0;
    
    
    for (i=0; i<95; i++) {
        if (fl[i]==0) {
            save[j++]=32+i;
        }
    }
    for (i=0; i<strlen(delete); i++) {
        key[i]=delete[i];
    }
    for (j=0; j<strlen(save); j++) {
        key[j+strlen(delete)]=save[j];
    }
    
    ptr first=NULL,p,q,r;
    for (i=0; i<strlen(key); i++) {
        p=(ptr)malloc(sizeof(iitem));
        p->next=NULL;
        p->c=key[i];
        if (first==NULL) {
            first=p;
        }
        else{
            q->next=p;
        }
        q=p;
    }
    q->next=first;
    k=0;
    r=q;p=first;
    spe=key[0];
    mmove=p->c;
    sign=mmove-32;
    r->next=p->next;
    free(p);
    p=r->next;
    while (p->next!=p) {
        for (i=1; i<mmove; i++) {
            r=p;
            p=p->next;
        }
        key[sign]=p->c;
        mmove=p->c;
        sign=mmove-32;
        r->next=p->next;
        free(p);
        p=r->next;
    }
    key[(p->c)-32]=spe;
    FILE *in,*out;
    in=fopen("in.txt", "r");
    out=fopen("in_crpyt.txt", "w");
    while (fgets(hang, 1000, in)!=NULL) {
        for (i=0; i<strlen(hang); i++) {
            if (32<=hang[i]&&hang[i]<=126) {
                hang[i]=replace(hang[i]);
            }
        }
        fputs(hang, out);
    }
    fclose(in);
    fclose(out);
    return 0;
}




