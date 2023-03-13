#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
struct item{
    int x;
    struct item*next;
};
typedef struct item *ptr;
int m,n,qq,i;
int main() {
    scanf("%d%d%d",&n,&m,&qq);
    ptr p,q,r,first=NULL;
    for (i=1; i<=n; i++) {
        p=(ptr)malloc(sizeof(struct item));
        p->next=NULL;
        p->x=i;
        if (first==NULL) {
            first=p;
        }
        else{
            q->next=p;
        }
        q=p;
    }
    q->next=first;
    r=q;p=first;
    for (i=1; i<qq; i++) {
        q=q->next;
        p=p->next;
    }
    while (p->next!=p) {
        for (i=1; i<m; i++) {
            q=q->next;
            p=p->next;
        }
        q->next=p->next;
        free(p);
        p=q->next;
    }
    printf("%d",p->x);
    return 0;
}




