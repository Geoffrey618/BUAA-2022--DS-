#include<stdio.h>
#include<math.h>
#include <string.h>
#include <ctype.h>
struct book{
    char name[55],zuozhe[55],she[55],date[55];
    int num;
}b[505],shuchu[505];
typedef struct book book;
char name[55],ch[55],*find;
int i,n,x,k,j;
int cmp(const void *a,const void *b){
    const book *pa=a,*pb=b;
    return (int)(strcmp(pa->name, pb->name));
}
int main(){
   
    FILE *in,*out;
    in=fopen("books.txt", "r");
    out=fopen("ordered.txt", "w");
while (~fscanf(in, "%s%s%s%s",b[n].name,b[n].zuozhe,b[n].she,b[n].date)) {b[n].num=0;n++;}
    while (~scanf("%d",&x)) {
        if (x==1) {
            scanf("%s%s%s%s",b[n].name,b[n].zuozhe,b[n].she,b[n].date);
            b[n].num=0;n++;
        }
        if (x==2){
            scanf("%s",ch);
            j=0;
            for (k=0; k<n; k++) {
                if (b[k].num!=1) {
                find=strstr(b[k].name, ch);
                if (find!=NULL) {
                    shuchu[j++]=b[k];
                }
                }
            }
            qsort(shuchu, j, sizeof(shuchu), cmp);
            for (int m=0; m<j; m++) {
                printf("-50%s-30%s-20%s-10%s\n",shuchu[m].name,shuchu[m].zuozhe,shuchu[m].she,shuchu[m].date);
            }
        }
        if(x==3){
            scanf("%s",ch);
            for (i=0; i<n; i++) {
                find=strstr(b[i].name, ch);
                if (find!=NULL) {
                    b[i].num=1;
                }
            }
        }
    }
    qsort(b, n, sizeof(book), cmp);
    for (int i=0; i<n; i++) {
        if (b[i].num==0)
    fprintf(out, "%-50s%-20s%-30s%-10s\n",b[i].name,b[i].zuozhe,b[i].she,b[i].date);
    }
    fclose(in);
    fclose(out);
    return 0;
}



