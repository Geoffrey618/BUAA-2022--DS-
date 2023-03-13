#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
void chuli(char str[],int z){
    int loc=strlen(str)-12,m;
    for (m=strlen(str)-1; m>=loc+1; m--) {
        str[m+2]=str[m];
    }
    str[loc]='_';str[loc+1]=48+z;str[loc+2]=32;
}
char get[105][40],ch[105][40],temp[40];
int x,i,j,flag,k,num[105];
int main() {
    scanf("%d\n",&x);
    for (i=1; i<=x; i++) {
        gets(get[i]);
        flag=0;
        for (j=1; j<i; j++) {
            if (strcmp(get[j], get[i])==0) {
                flag=1;break;
            }
        }
        if (flag==0) {
            strcpy(ch[k++], get[i]);
        }
    }
    for (i=0; i<k; i++) {
        for(j=i-1;j>=0;j--){
            if(strncmp(ch[i], ch[j], sizeof(char)*strlen(ch[i])-12)==0){
                num[i]=num[j]+1;break;
            }
        }
    }
    for (i=0; i<k; i++) {
        if(num[i]!=0){
            chuli(ch[i], num[i]);
        }
    }
    for(i=0;i<k-1;i++)
        {
            for(j=0;j<k-i-1;j++)
            {
     if(strcmp(ch[j], ch[j+1])>0)
     {
         strcpy(temp,ch[j]);
         strcpy(ch[j],ch[j+1]);
         strcpy(ch[j+1],temp);
     }
            }
        }
    for (i=0;i<k;i++) {
        puts(ch[i]);
    }
    return 0;
    
}


