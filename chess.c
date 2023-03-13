#include<stdio.h>
char get[25][25];
int num[25][25];
int i,j,flag,x;
int pd(int a[][25],int m,int n){
    if(a[m][n]==0){
        return 0;
    }
    else{
if(a[m][n]==a[m+1][n]&&a[m][n]==a[m+2][n]&&a[m][n]==a[m+3][n]&&a[m+4][n]==0&&m<=15) {
    return 1;}else
 if(a[m][n]==a[m+1][n+1]&&a[m][n]==a[m+2][n+2]&&a[m][n]==a[m+3][n+3]&&a[m+4][n+4]==0&&m<=15&&n<=15) {
    return 1;}else    if(a[m][n]==a[m][n+1]&&a[m][n]==a[m][n+2]&&a[m][n]==a[m][n+3]&&a[m][n+4]==0&&n<=15) {return 1;}else
    if(a[m][n]==a[m+1][n-1]&&a[m][n]==a[m+2][n-2]&&a[m][n]==a[m+3][n-3]&&a[m+4][n-4]==0&&m<=15&&n>=5) {
                    return 1;}else
    if(a[m][n]==a[m-1][n+1]&&a[m][n]==a[m-2][n+2]&&a[m][n]==a[m-3][n+3]&&a[m-4][n+4]==0&&m>=5&&n<=15) {
                return 2;}else
        if(a[m][n]==a[m-1][n]&&a[m][n]==a[m-2][n]&&a[m][n]==a[m-3][n]&&a[m-4][n]==0&&m>=5) {
            return 3;}else
        if(a[m][n]==a[m-1][n-1]&&a[m][n]==a[m-2][n-2]&&a[m][n]==a[m-3][n-3]&&a[m-4][n-4]==0&&m>=5&&n>=5) {
            return 4;}else
        if(a[m][n]==a[m][n-1]&&a[m][n]==a[m][n-2]&&a[m][n]==a[m][n-3]&&a[m][n-4]==0&&n>=5) {
            return 5;}
        else{
            return 0;
        }
    }
}
int main(){
    for (i=1;i<=19; i++) {
        for (j=1; j<=19; j++) {
            scanf("%d",&num[i][j]);
        }
    }
    for (i=1; i<=19; i++) {
        for (j=1; j<=19; j++) {
            x=pd(num, i, j);
            if(x!=0){
                flag=1;
                if (x==1) {
                    printf("%d:%d,%d",num[i][j],i,j);
                }
                else if(x==2){
                    printf("%d:%d,%d",num[i][j],i-3,j+3);
                }
                else if (x==3){
                    printf("%d:%d,%d",num[i][j],i-3,j);
                }
                else if(x==4){
                    printf("%d:%d,%d",num[i][j],i-3,j-3);
                }
                else {
                    printf("%d:%d,%d",num[i][j],i,j-3);
                }
                return 0;
            }
        }
    }
    if(flag==0){
        printf("No");
    }
    return 0;
}




