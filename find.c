#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct dictionary_list {
    char word[30];
};

int N = 0;//���Ҵ���

int  search(struct dictionary_list array[], int n, char s[]); //˳�����
int  binsearch(struct dictionary_list array[], int low, int high, char s[]); //�۰����
int  indexsearch(struct dictionary_list array[], int n, char s[]); //��������
int  hashsearch(struct dictionary_list array[], int n, char s[]); //ɢ�в���

int main(int argc, const char * argv[]) {
    
    FILE *fi;
    struct dictionary_list dictionary[4000];
    int i=0;
    
    if((fi=fopen("dictionary3000.txt","r"))==NULL) {
        fprintf(stderr, "dictionary3000.txt open failed!\n");
        return 1;
    }
    
    //�������ֵ��е��ʶ�����һ�����ʱ��ṹ�壩��,�ܵ��ʸ���Ϊi,ĩ����Ϊi-1
    while(fscanf(fi, "%s", dictionary[i].word)!=EOF) i++;
    
    char s[30]; int opt;
    scanf("%s",s);  //Ҫ���ҵĵ���
    scanf("%d",&opt);  //���ҷ�ʽ
    
    int Pos = -1;//�ҵ������� �� δ�ҵ���-1
    if(opt==1)
        Pos=search(dictionary, i, s);
    else if(opt==2)
        Pos=binsearch(dictionary, 0, i-1, s);
    else if(opt==3)
        Pos=indexsearch(dictionary, i, s);
    else if(opt==4)
        Pos=hashsearch(dictionary, i, s);;
    
    printf("%d %d\n",Pos!=-1,N);//���ҽ�����ҵ���1������0�� �Ƚϴ���
    
    return 0;
}


//˳�����,nΪ�ܵ��ʸ���i+1
int  search(struct dictionary_list array[], int n, char s[])
{
    for(int i=0; i<n; i++)
    {
        N++;
        if(strcmp(s,array[i].word)==0)
            return i;
        else if(strcmp(s,array[i].word)<0)//������ͬ�Ļ��һ���ȴ����ҵĵ��ʴ�ĵ��ʣ���Ҫ��ֹ����
            return -1;
    }
    return -1;
}


//�۰����
//n    ��������˳���ļ��м�¼�ĸ���
//low  ��ǰ���ҷ�Χ�ڵ�һ����¼���ļ��е�λ�á� ��ֵ low=0
//high ��ǰ���ҷ�Χ������Ǹ���¼���ļ��е�λ�á� ��ֵ high=n-1
//mid  ��ǰ���ҷ�Χ��λ�þ��е��Ǹ���¼���ļ��е�λ�á� mid =[(low+high)/2]
int  binsearch(struct dictionary_list array[], int low, int high, char s[])
{
    int mid;
    while(low<=high){
        N++;
        mid=(low+high)/2;
        if(strcmp(s,array[mid].word)==0)
            return mid;             /*  ���ҳɹ�  */
        else if(strcmp(s,array[mid].word)>0)
            low=mid+1;              /*  ׼�����Һ�벿�� */
        else
            high=mid-1;             /* ׼������ǰ�벿�� */
    }
    return -1;                      /*   ����ʧ��  */
}


//��������
struct IndexItem{
    char index;  //IndexKeyTypeΪ���ȶ��������ֵ����
    int start;   //�ӱ��е�һ��Ԫ�����ڵ��±�λ��
    int length;  //�ӱ�ĳ�����
};
struct IndexItem indexlist[130];//ILMSizeΪ���ȶ�������ͳ��������ڵ�����������m

int  indexsearch(struct dictionary_list array[], int n, char s[])
{
    //������������26��Ӣ����ĸΪͷ��ĸ�ĵ������ֵ��е���ʼλ�ú͵��ʸ���������������
    //??ע�⣺����ĸx�ĵ��ʲ�������
    char index='a';
    indexlist[index].start=0;
    indexlist[index].index=index;
    int i;
    for(i=0; i<n; i++)
    {
        if(array[i].word[0]!=index)
        {
            indexlist[index].length=i-indexlist[index].start;
            index++;
            indexlist[index].index=index;
            indexlist[index].start=i;
            i--; //���??�������жϵ�һ�����ʣ��������򳤶�lengthΪ0
        }
    }
    indexlist[index].length=i-indexlist[index].start;
    
    //����
    return binsearch(array, indexlist[s[0]].start, indexlist[s[0]].start+indexlist[s[0]].length-1, s);
}


//ɢ�У�Hash������
/* ����ɢ�б�Ľṹ */
struct node {
        char data[30];
        struct node *next;
} ; //list
struct node *Hashtab[4000];

/* �����ϣ������Ϊ����ʱ�����ַ����������Ը��ݲ�ͬ����������㷨 */
/* compute hash value for string */
#define NHASH  3001
#define MULT  37
unsigned int hash(char *str)
{
    unsigned int h=0;
    char *p;
    for(p=str; *p!='\0'; p++)
        h = MULT*h + *p;
    return h % NHASH;
}

/* ɢ�б�Ĵ������� */
void insertHash(char key[])
{
    struct node *p;
    unsigned int addr = hash(key);
    
    p = (struct node *)malloc(sizeof(struct node));
    strcpy(p->data, key);
    p->next = Hashtab[addr];
    Hashtab[addr] = p;
    //��ɢ�г��ֳ�ͻʱ���²����Ԫ�ط��������ͷ���������㷨��࣬Ч�ʸ���
}

/* ɢ�б�Ĳ��Һ��� */
struct node *searchHash(char key[])
{
    struct node *p;
    unsigned int addr = hash(key);
    for(p=Hashtab[addr]; p!=NULL; p=p->next)
    {
        //�ڳ�ͻ�������ҵ���δ�ҵ�(������һ���ȴ����ҵĵ��ʴ�ĵ��ʻ��������)��������ҡ�
        N++;
        if(strcmp(p->data,key)==0)
            return p;
        else if(strcmp(p->data,key)>0)
            return NULL;
    }
    return NULL;//δ�ҵ�����null
}

int  hashsearch(struct dictionary_list array[], int n, char s[])
{
    //����ɢ�б�
    for(int i=0; i<n; i++)
        insertHash(array[i].word);
    
    //����
    return searchHash(s)==NULL?-1:1;
}


