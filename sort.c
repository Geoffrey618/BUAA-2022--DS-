#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int keytype;

int N = 0;//元素的比较次数

void selectSort(int k[ ], int n);
void bubbleSort(keytype k[ ], int n);
void heapSort(keytype k[ ],int n);
void mergeSort(keytype k[ ],int n);
void quickSort(keytype k[],int n);

int main(int argc, const char * argv[])
{
    int n, opt, num[200];
    
    scanf("%d %d",&n,&opt);  //待排序的整数个数 排序方式
    
    for(int i=0; i<n; i++)
        scanf("%d",&num[i]);//待排序的整数

    if(opt==1)
        selectSort(num, n);
    else if(opt==2)
        bubbleSort(num, n);
    else if(opt==3)
        heapSort(num, n);
    else if(opt==4)
        mergeSort(num, n);
    else if(opt==5)
        quickSort(num, n);

    for(int i=0; i<n; i++)
        printf("%d ",num[i]);
    
    printf("\n%d\n",N);//比较次数
    
    return 0;
}


//选择排序
void  selectSort(keytype k[ ], int n)
{
    int i, j, d;
    keytype temp;
    for(i=0; i<n-1; i++){
        d=i;                  /* 假设值最小元素为未排序元素的第1个元素 */
        for(j=i+1; j<n; j++){
            N++;
            if(k[j]<k[d]) //红色语句
                d=j;          /* 寻找真正值最小元素，记录其位置d */
        }
        if(d!=i){             /* 当值最小元素非第1个元素时 */
            temp=k[d];
            k[d]=k[i];
            k[i]=temp;        /* 值最小元素与未排序的第1个元素交换位置 */
        }
    }
}


//冒泡排序
void  bubbleSort(keytype k[ ], int n)
{
    int i, j, flag=1;
    keytype temp;
    for(i=n-1; i>0 && flag==1; i--)
    {
        flag=0;                 /* 每趟排序前标志flag置0 */
        for(j=0;j<i;j++){
            N++;
            if(k[j]>k[j+1]){ //红色语句
                temp=k[j];
                k[j]=k[j+1];
                k[j+1]=temp;    /* 交换两个元素的位置 */
                flag=1;         /* 标志flag置1 */
            }
        }
    }
}


//堆排序
void adjust(keytype k[ ], int i, int n)
{
    int j;
    keytype temp;
    temp=k[i];
    j=2*i+1;                   /* j为i结点的左孩子的序号 */
    while(j<n){
        if(j<n-1 && k[j]<k[j+1])
            j++;               /* j给出i结点的左、右孩子中值最大者的序号 */
        N++;
        if(temp>=k[j]) //红色语句
            break;
        k[(j-1)/2]=k[j];
        j=2*j+1;
    }
    k[(j-1)/2]=temp;           /* 把某孩子结点上移到父结点位置 */
}

void heapSort(keytype k[ ],int n)
{
    int i;
    keytype  temp;
    for(i=n/2-1; i>=0; i--)
        adjust(k,i,n);
    for(i=n-1; i>=1; i--){
        temp=k[i];
        k[i]=k[0];
        k[0]=temp;
        adjust(k,0,i);
    }
}


//二路归并排序
void merge(keytype x[ ],keytype tmp[ ],int left,int leftend,int rightend)
{
    int i=left, j=leftend+1, q=left;
    while(i<=leftend && j<=rightend)
    {
        N++;
        if(x[i]<=x[j]) //红色语句
            tmp[q++]=x[i++];
        else
            tmp[q++]=x[j++];
    }
    while(i<=leftend)
        tmp[q++]=x[i++];
    while(j<=rightend)
        tmp[q++]=x[j++];
    for(i=left; i<=rightend; i++)
        x[i]=tmp[i];
}

void mSort(keytype k[], keytype tmp[], int left, int right)
{
    int center;
    if(left < right){
        center = (left+right)/2;
        mSort(k, tmp, left, center);
        mSort(k, tmp, center+1, right);
        merge(k, tmp, left,center, right);
    }
}

void mergeSort(keytype k[ ],int n)
{
    keytype *tmp;
    tmp = (keytype *)malloc(sizeof(keytype) * n);
    if(tmp != NULL) {
        mSort(k, tmp, 0, n-1);
        free(tmp);
    }
    else
        printf("No space for tmp array!!!\n");
}


//快速排序
//需要自己写一个swap函数，涉及指针函数知识；另外注意命名，貌似头文件已包含排序函数
void swap(keytype *i, keytype *j)
{
    keytype tmp;
    tmp = *i; *i = *j; *j=tmp;
}

void Qsort(int k[ ],int left,int right)
{
    int i, last;
    if(left<right){
        last=left;
        for(i=left+1;i<=right;i++){
            N++;
            if(k[i]<k[left]) //红色语句
                swap(&k[++last],&k[i]);
        }
        swap(&k[left],&k[last]);
        Qsort(k,left,last-1);
        Qsort(k,last+1,right);
    }
}

void quickSort(keytype k[],int n)
{
       Qsort(k,0,n-1);
}


