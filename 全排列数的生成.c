#include<stdio.h>
#include<math.h>
#include <string.h>
#include <ctype.h>
int q[20],flag[20];
void arrange(int m,int len){
    int j,k;
    if(m>len){
        for(j=1;j<=len;j++){
            printf("%d ",q[j]);
        }printf("\n");
    }
    else{
        for (k=1; k<=len; k++) {
            if (!flag[k]) {
                flag[k]=1;
                q[m]=k;
                arrange(m+1, len);
                flag[k]=0;
            }
        }
    }
}
int main() {
    int n;
    scanf("%d",&n);
    arrange(1, n);
    return 0;
}





