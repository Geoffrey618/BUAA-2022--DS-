#include <stdio.h>
#include<string.h>
char ch[105],*p,*pst,*pend;
int x,i;
int main() {
    gets(ch);
    pst=ch;p=strchr(ch,'.');pend=pst+strlen(ch)-1;
    if(p==NULL){
        puts(ch);
    }
    else{
        if (p-pst>=2) {
            x=p-pst-1;
            printf("%c.",*pst);
            for(i=1;pst+i<=pend;i++){
                if(*(pst+i)!='.'){
                    printf("%c",*(pst+i));
                }
            }
            printf("e%d",x);
        }
        else if(p-pst==1&&*pst!='0'){
            printf("%se0",ch);
        }
        else{
            int j=1;
            while (*(p+j)=='0') {
                j++;
            }
            printf("%c",*(p+j));
            if(p+j!=pend){
                printf(".");
            }
            for (i=j+1; p+i<=pend; i++) {
                printf("%c",*(p+i));
            }
            printf("e%d",-j);
        }
    }
    return 0;
}