#include<stdio.h>
#include<ctype.h>
#include<string.h>
int main()
{
	char a[10000];
	scanf("%s",a);
	for(int i=0;i<strlen(a);i++)
	{
		if(a[i]!='-'){
			printf("%c",a[i]);
		}
		if(a[i]=='-'){
			if((a[i-1]>='a'&&a[i-1]<='z'&&a[i+1]>='a'&&a[i+1]<='z')||(a[i-1]>='A'&&a[i-1]<='Z'&&a[i+1]>='A'&&a[i+1]<='Z')||(a[i-1]>='0'&&a[i-1]<='9'&&a[i+1]>='0'&&a[i+1]<='9')){
				int x=a[i+1]-a[i-1];
				for(int j=1;j<x;j++){
					printf("%c",a[i-1]+j);
				}
			}
			else{
				printf("-");
			}
		}
	}
	return 0;
}