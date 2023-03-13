#include <stdio.h>
#include <string.h>
#include <ctype.h>
char bf[105],af[105],bbff[105],ch[1005],mid[1005],shuchu[1005],*pt,*st;
int i,j,k,flag[1005];
int main() {
    gets(bf);gets(af);
    strcpy(bbff, bf);
    for (i=0; i<strlen(bbff); i++) {
        if (bbff[i]>='A'&&bbff[i]<='Z') {
            bbff[i]+=32;
        }
    }
    FILE *in,*out;
    in=fopen("filein.txt", "r");
    out=fopen("fileout.txt", "w");
    while (fgets(ch, 1005, in)!=NULL) {
        strcpy(mid, ch);
        for (i=0; i<strlen(mid); i++) {
            if ('A'<=mid[i]&&mid[i]<='Z') {
                mid[i]+=32;
            }
        }
        st=mid;pt=strstr(mid, bbff);
        while (pt!=NULL) {
            flag[pt-st]=1;
            pt+=strlen(bbff);
            pt=strstr(pt, bbff);
        }
        k=0;
        for (i=0; i<strlen(ch);) {
            if(flag[i]==0){
                shuchu[k++]=ch[i];i++;
            }
            else{
                for(j=0;j<strlen(af);j++){
                    shuchu[k+j]=af[j];
                }
                k+=strlen(af);
                i+=strlen(bf);
            }
        }
        fputs(shuchu, out);
        memset(flag, 0, sizeof(int)*1005);
        memset(shuchu, '\0', sizeof(char)*1005);
    }
    fclose(in);
    fclose(out);
    return 0;
}




