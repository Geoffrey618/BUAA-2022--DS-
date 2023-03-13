#include <string.h>
#include <stdio.h>
#include <stdlib.h>
char juzi[1000],stack[100][1000],str[100],ssttrr[10][100],save[1000],ssave[1000];
int sum,op,pos,i,oopp[15],st[15],top=-1,len,j;
int push(char s[][1000],int *top,char sentence[1000]){
    if (*top==99) return 0;
    else{
        strcpy(s[++(*top)], sentence);
        return 1;
    }
}
int pop(char s[][1000],int *top,char sentence[1000]){
    if (*top==-1) return 0;
    else{
        strcpy(sentence, s[(*top)--]);
        return 1;
    }
}
void nichuli(char s[],int op,int pos,char str[]){
    char ss[1000];int j;
    if (op==1) {
        strncpy(ss, s, pos);
        for (j=pos; j<1000; j++) ss[j]='\0';
        j=pos;
        for(int k=pos+strlen(str); k<strlen(s); k++) {
		ss[j++]=s[k];
    }
	} 
    else{
        strncpy(ss, s, pos);
        for (j=pos; j<1000; j++) ss[j]='\0';
        for (j=0; j<strlen(str); j++) ss[j+pos]=str[j];
        j=strlen(ss);
        for (int k=pos; k<strlen(s); k++) {
            ss[j++]=s[k];
        }
    }
    strcpy(juzi, ss);
}
int main() {
    gets(juzi);
    strcpy(save, juzi);
    scanf("%d",&sum);
    for (i=1; i<=sum; i++) {
        scanf("%d %d %s",&oopp[i],&st[i],ssttrr[i]);
    }
    strcpy(stack[sum], juzi);
    for (i=sum; i>=1; i--) {
        nichuli(juzi, oopp[i], st[i], ssttrr[i]);
        strcpy(stack[i-1], juzi);
    }
    top=sum;
    while (scanf("%d",&op)!=EOF) {
        if (op==1) {
            scanf("%d %s",&pos,str);
            strncpy(ssave, save, pos);
            for (j=pos; j<1000; j++) ssave[j]='\0';
            for (int k=0; k<strlen(str); k++) ssave[pos+k]=str[k];
            j=strlen(ssave);
            for (int k=pos; k<strlen(save); k++) ssave[j++]=save[k];
            strcpy(save, ssave);
            push(stack, &top, save);
        }
        else if(op==2){
            scanf("%d %d",&pos,&len);
            if (pos-1+len>=strlen(save)) {
                strncpy(ssave, save, pos);
                for (int k=pos; k<1000; k++) ssave[k]='\0';
                strcpy(save, ssave);
                push(stack, &top, save);
            }
            else{
                strncpy(ssave, save, pos);
                int k=pos;
                for (; k<1000; k++) ssave[k]='\0';
                k=pos;
                for (int j=pos+len; j<strlen(save); j++) ssave[k++]=save[j];
                strcpy(save, ssave);
                push(stack, &top, save);
            }
        }
        else if(op==3){
            if(top!=0) {pop(stack, &top, save);
                strcpy(save, stack[top]);}
        }
        else if(op==-1) break;
    }
    puts(stack[top]);
    return 0;
}



