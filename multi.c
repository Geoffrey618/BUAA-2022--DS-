#include<stdio.h>
#include<math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
typedef struct item{
    int c,e;
    struct item *next;
}iitem;
typedef struct item* ptr;

ptr multi(ptr p1, ptr p2){
    int xs,zs;
    ptr q, t1,t2,first=NULL;
    t1=p1;t2=p2;
    while (t2) {
        xs=(t1->c)*(t2->c);
        zs=t1->e+t2->e;
        ptr p=(ptr)malloc(sizeof(iitem));
        p->next=NULL;
        p->c=xs;
        p->e=zs;
        if (first==NULL) {
            first=p;
        }
        else{
            q->next=p;
        }
        q=p;
        t2=t2->next;
    }
    t1=t1->next;
    while (t1) {
        t2=p2;
        ptr head=(ptr)malloc(sizeof(iitem));
        head->next=first;
        while (t2) {
            xs=(t1->c)*(t2->c);
            zs=t1->e+t2->e;
            ptr r=(ptr)malloc(sizeof(iitem));
            r=head;
            while (r&&r->next&&r->next->e>zs) {
                r=r->next;
            }
            if (r->next==NULL) {
                if (r->e>zs) {
                    ptr p=(ptr)malloc(sizeof(iitem));
                    p->c=xs;
                    p->e=zs;
                    p->next=NULL;
                    r->next=p;
                }
                else if(r->e==zs){
                	r->c+=xs;
				}
            }
            else{
	            if (r->next->e==zs) {
	                r->next->c+=xs;
	            }
	            else{
	                ptr p=(ptr)malloc(sizeof(iitem));
	                p->next=r->next;
	                r->next=p;
	                p->c=xs;
	                p->e=zs;
	            }
            }
            t2=t2->next;
        }
        t1=t1->next;
    }
    return first;
}
int main(){
    ptr result,p1,p2,first=NULL,pp,qq=NULL;
    
    int xs,zs;
    char ch='\0';
    while (~scanf("%d %d",&xs,&zs)&&~scanf("%c",&ch)) {
        pp=(ptr)malloc(sizeof(iitem));
        pp->next=NULL;
        pp->c=xs;
        pp->e=zs;
        if (first==NULL) {
            first=pp;
        }
        else{
            qq->next=pp;
        }
        qq=pp;
        if (ch=='\n') {
            break;
        }
    }
    p1=first;
    first=NULL;
    while (~scanf("%d %d",&xs,&zs)&&~scanf("%c",&ch)) {
        pp=(ptr)malloc(sizeof(iitem));
        pp->next=NULL;
        pp->c=xs;
        pp->e=zs;
        if (first==NULL) {
            first=pp;
        }
        else{
            qq->next=pp;
        }
        qq=pp;
        if (ch=='\n') {
            break;
        }
    }
   
    p2=first;
    result=multi(p1, p2);
    
    while (result) {
        printf("%d %d ",result->c,result->e);
        result=result->next;
    }
    return 0;
}



