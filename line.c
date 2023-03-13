#include<stdio.h>
#include<math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
typedef struct line{
    int x1,x2,y1,y2,pos,len,is;
}lline;
lline l[105];
int x,i,j,fl,n=1,sc;
void search(int m){
    int find=0;
    for (int k=1; k<=x; k++) {
        if (l[k].pos==0) {
            if (l[m].x1==l[k].x2&&l[m].y1==l[k].y2) {
                l[k].pos=1;
                l[k].len=l[m].len+1;
                find=1;
                search(k);
            }
        }
    }
    if (find==0) {
        return;
    }
}
int max(int a,int b){
    if (a>b) return a;
    else return b;
}
int main(){
    scanf("%d",&x);
    for (i=1; i<=x; i++) {
        scanf("%d%d%d%d",&l[i].x1,&l[i].y1,&l[i].x2,&l[i].y2);
        l[i].len=1;
    }
    
    for (i=1; i<=x; i++) {
        fl=0;
        for (j=1; j<=x; j++) {
            if (l[i].x2==l[j].x1&&l[i].y2==l[j].y1) {
                fl=1;break;
            }
        }
        if (fl==0) {
            l[i].is=1;
        }
    }
    
    for (i=1; i<=x; i++) {
        if (l[i].is==1) {
            search(i);
        }
    }
    for (i=1; i<=x; i++) {
        if (l[i].len>n) {
            n=l[i].len;
            sc=i;
        }
    }
    printf("%d %d %d",l[sc].len,l[sc].x1,l[sc].y1);
    return 0;
}



