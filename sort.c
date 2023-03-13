#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int keytype;

int N = 0;//Ԫ�صıȽϴ���

void selectSort(int k[ ], int n);
void bubbleSort(keytype k[ ], int n);
void heapSort(keytype k[ ],int n);
void mergeSort(keytype k[ ],int n);
void quickSort(keytype k[],int n);

int main(int argc, const char * argv[])
{
    int n, opt, num[200];
    
    scanf("%d %d",&n,&opt);  //��������������� ����ʽ
    
    for(int i=0; i<n; i++)
        scanf("%d",&num[i]);//�����������

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
    
    printf("\n%d\n",N);//�Ƚϴ���
    
    return 0;
}


//ѡ������
void  selectSort(keytype k[ ], int n)
{
    int i, j, d;
    keytype temp;
    for(i=0; i<n-1; i++){
        d=i;                  /* ����ֵ��СԪ��Ϊδ����Ԫ�صĵ�1��Ԫ�� */
        for(j=i+1; j<n; j++){
            N++;
            if(k[j]<k[d]) //��ɫ���
                d=j;          /* Ѱ������ֵ��СԪ�أ���¼��λ��d */
        }
        if(d!=i){             /* ��ֵ��СԪ�طǵ�1��Ԫ��ʱ */
            temp=k[d];
            k[d]=k[i];
            k[i]=temp;        /* ֵ��СԪ����δ����ĵ�1��Ԫ�ؽ���λ�� */
        }
    }
}


//ð������
void  bubbleSort(keytype k[ ], int n)
{
    int i, j, flag=1;
    keytype temp;
    for(i=n-1; i>0 && flag==1; i--)
    {
        flag=0;                 /* ÿ������ǰ��־flag��0 */
        for(j=0;j<i;j++){
            N++;
            if(k[j]>k[j+1]){ //��ɫ���
                temp=k[j];
                k[j]=k[j+1];
                k[j+1]=temp;    /* ��������Ԫ�ص�λ�� */
                flag=1;         /* ��־flag��1 */
            }
        }
    }
}


//������
void adjust(keytype k[ ], int i, int n)
{
    int j;
    keytype temp;
    temp=k[i];
    j=2*i+1;                   /* jΪi�������ӵ���� */
    while(j<n){
        if(j<n-1 && k[j]<k[j+1])
            j++;               /* j����i�������Һ�����ֵ����ߵ���� */
        N++;
        if(temp>=k[j]) //��ɫ���
            break;
        k[(j-1)/2]=k[j];
        j=2*j+1;
    }
    k[(j-1)/2]=temp;           /* ��ĳ���ӽ�����Ƶ������λ�� */
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


//��·�鲢����
void merge(keytype x[ ],keytype tmp[ ],int left,int leftend,int rightend)
{
    int i=left, j=leftend+1, q=left;
    while(i<=leftend && j<=rightend)
    {
        N++;
        if(x[i]<=x[j]) //��ɫ���
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


//��������
//��Ҫ�Լ�дһ��swap�������漰ָ�뺯��֪ʶ������ע��������ò��ͷ�ļ��Ѱ���������
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
            if(k[i]<k[left]) //��ɫ���
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


