#include<stdio.h>
#include<math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
int x(int y,int z,char c){
    if (c==43) {
        return y+z;
    }
    else if(c==45){
        return y-z;
    }
    else if(c==42){
        return y*z;
    }
    else{
        return y/z;
    }
}
char ch[10086],save[10086],fh[5005],*fh1,*fh2,jj[5005];
int i,j=1,k,numfh=1,numa=1,len,a[5005],weishu,b[5005],flag=1;
int f,g;
int main() {
    gets(save);
    for (i=0; i<strlen(save); i++) {
        if(save[i]!=32){
            ch[j++]=save[i];
        }
    }
    fh1=ch;fh2=ch;
    for (i=1; i<j; i++) {
        if (!(48<=ch[i]&&ch[i]<=57)) {
            fh[numfh++]=ch[i];fh2=&ch[i];weishu=fh2-fh1-1;
            for(k=1;k<=weishu;k++){
                a[numa]+=pow(10,k-1)*(ch[i-k]-48);
            }
            numa++;fh1=&ch[i];
        }
    }
    k=0;
    for (i=1;i<numfh; i++) {
        if (fh[i]!=42&&fh[i]!=47) {
            jj[k]=fh[i];
            for(flag+=1;flag<=i;flag++){
                a[flag]=x(a[flag-1], a[flag], fh[flag-1]);
            }
            b[k]=a[flag-1];k++;}
    }
    for (i=1; i<k; i++) {
        b[i]=x(b[i-1], b[i], jj[i-1]);
    }
    printf("%d",b[k-1]);
    return 0;
}