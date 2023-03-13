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
int search(char word[]){
    for (int j=0; j<sum; j++) {
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
                    memset(word, '\0', sizeof(word));
                    k=0;
                }
            }
            p1++;
        }
    }
    qsort(list, sum, sizeof(wword), cmp);
    for (int i=0; i<sum; i++) {
        printf("%s %d\n",list[i].c,list[i].x);
    }
    fclose(in);
    return 0;
}



