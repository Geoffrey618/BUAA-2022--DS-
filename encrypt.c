#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
char get[55],key[30],ch[1005],sc[1005];
int i,j,k,flag,fl[30];
int main() {
    gets(get);
    for (i=0; i<strlen(get); i++) {
        flag=0;
        for (j=0; j<i; j++) {
            if (get[i]==get[j]) {
                flag=1;break;
            }
        }
        if (flag==0) {
            key[k++]=get[i];
        }
    }
    for (i=0; i<26; i++) {
        if (strchr(key, 'a'+i)!=NULL) {
            fl[i]=1;
        }
    }
    j=0;
    for (i=25; i>=strlen(key); i--) {
        while (fl[j]==1) {
            j++;
        }
        key[i]='a'+j;j++;
    }
    FILE *in,*out;
    in=fopen("encrypt.txt", "r");
    out=fopen("output.txt", "w");
    while (fgets(ch,1005,in)!=NULL) {
        for (i=0; i<strlen(ch); i++) {
            if ('a'<=ch[i]&&ch[i]<='z') {
                sc[i]=key[ch[i]-'a'];
            }
            else{
                sc[i]=ch[i];
            }
        }
        fputs(sc, out);
        memset(sc, '\0', 1005);
    }
    fclose(in);
    fclose(out);
    return 0;
}


