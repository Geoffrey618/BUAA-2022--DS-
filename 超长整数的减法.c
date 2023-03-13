#include<stdio.h>
#include<math.h>
#include<string.h>
#include <ctype.h>
void subtract(int m[],int n[],int len,int o){
    int j;
    for(j=len-1;j>=o;j--){
        if(m[j]>=n[j]){
            m[j]-=n[j];
        }
        else{
            m[j]=m[j]+10-n[j];
            m[j-1]--;
        }
    }
}
char a[85],b[85],*pa,*pb;
int numa[85],numb[85],i,j,x,k,*pna,*pnb;
int main(){
    gets(a);gets(b);
    pa=a;pb=b;
    while(*pa==48){
        pa++;
    }
    while(*pa!='\0'){
        numa[i++]=*(pa++)-48;
    }
    while(*pb==48){
        pb++;
    }
    while(*pb!='\0'){
        numb[j++]=*(pb++)-48;
    }
    if(i<j){
        x=j-1;
        while(x>=j-i){
            if(numb[x]>=numa[x-j+i]){
                numb[x]-=numa[x-j+i];
            }
            else{
                numb[x]=numb[x]+10-numa[x-j+i];
                numb[x-1]--;
            }
            x--;
        }
        while(numb[x]<0&&x>0){
            numb[x]+=10;numb[--x]--;
        }
        printf("-");
        if(numb[0]!=0){
            printf("%d",numb[0]);
        }
        for(k=1;k<=j-1;k++){
            printf("%d",numb[k]);
        }
        return 0;
    }
    else if(i>j){
        x=i-1;
        while(x>=i-j){
            if(numa[x]>=numb[x-i+j]){
                numa[x]-=numb[x-i+j];
            }
            else{
                numa[x]=numa[x]+10-numb[x-i+j];
                numa[x-1]--;
            }
            x--;
        }
        for(k=0;k<=i-1;k++){
            printf("%d",numa[k]);
        }
        return 0;
    }
    else{
        k=0;
        while(numa[k]==numb[k]&&k<i){
            k++;
        }
        if(k==i){
            printf("0");
        }
        else if(numa[k]>numb[k]){
            subtract(numa,numb,i,k);
            while(numa[k]==0&&k<i){
                k++;
            }
            if(k==i){
                printf("0");
            }
            else{
                while(k<i){
                    printf("%d",numa[k]);
                    k++;
                }
            }
        }
        else{
            subtract(numb, numa, i, k);
            while(numb[k]==0&&k<i){
                k++;
            }
            if(k==i){
                printf("0");
            }
            else{printf("-");
                while(k<i){
                    printf("%d",numb[k]);k++;
                }
            }
        }
        return 0;
    }
}



