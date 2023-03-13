#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct dictionary_list {
    char word[30];
};

int N = 0;//查找次数

int  search(struct dictionary_list array[], int n, char s[]); //顺序查找
int  binsearch(struct dictionary_list array[], int low, int high, char s[]); //折半查找
int  indexsearch(struct dictionary_list array[], int n, char s[]); //索引查找
int  hashsearch(struct dictionary_list array[], int n, char s[]); //散列查找

int main(int argc, const char * argv[]) {
    
    FILE *fi;
    struct dictionary_list dictionary[4000];
    int i=0;
    
    if((fi=fopen("dictionary3000.txt","r"))==NULL) {
        fprintf(stderr, "dictionary3000.txt open failed!\n");
        return 1;
    }
    
    //将所有字典中单词读入至一个单词表（结构体）中,总单词个数为i,末索引为i-1
    while(fscanf(fi, "%s", dictionary[i].word)!=EOF) i++;
    
    char s[30]; int opt;
    scanf("%s",s);  //要查找的单词
    scanf("%d",&opt);  //查找方式
    
    int Pos = -1;//找到：索引 或 未找到：-1
    if(opt==1)
        Pos=search(dictionary, i, s);
    else if(opt==2)
        Pos=binsearch(dictionary, 0, i-1, s);
    else if(opt==3)
        Pos=indexsearch(dictionary, i, s);
    else if(opt==4)
        Pos=hashsearch(dictionary, i, s);;
    
    printf("%d %d\n",Pos!=-1,N);//查找结果（找到：1，否则：0） 比较次数
    
    return 0;
}


//顺序查找,n为总单词个数i+1
int  search(struct dictionary_list array[], int n, char s[])
{
    for(int i=0; i<n; i++)
    {
        N++;
        if(strcmp(s,array[i].word)==0)
            return i;
        else if(strcmp(s,array[i].word)<0)//遇到相同的或第一个比待查找的单词大的单词，就要终止查找
            return -1;
    }
    return -1;
}


//折半查找
//n    排序连续顺序文件中记录的个数
//low  当前查找范围内第一个记录在文件中的位置。 初值 low=0
//high 当前查找范围内最后那个记录在文件中的位置。 初值 high=n-1
//mid  当前查找范围内位置居中的那个记录在文件中的位置。 mid =[(low+high)/2]
int  binsearch(struct dictionary_list array[], int low, int high, char s[])
{
    int mid;
    while(low<=high){
        N++;
        mid=(low+high)/2;
        if(strcmp(s,array[mid].word)==0)
            return mid;             /*  查找成功  */
        else if(strcmp(s,array[mid].word)>0)
            low=mid+1;              /*  准备查找后半部分 */
        else
            high=mid-1;             /* 准备查找前半部分 */
    }
    return -1;                      /*   查找失败  */
}


//索引查找
struct IndexItem{
    char index;  //IndexKeyType为事先定义的索引值类型
    int start;   //子表中第一个元素所在的下标位置
    int length;  //子表的长度域
};
struct IndexItem indexlist[130];//ILMSize为事先定义的整型常量，大于等于索引项数m

int  indexsearch(struct dictionary_list array[], int n, char s[])
{
    //构建索引表：以26个英文字母为头字母的单词在字典中的起始位置和单词个数来构建索引表
    //??注意：首字母x的单词并不存在
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
            i--; //解决??，得以判断第一个单词，若不是则长度length为0
        }
    }
    indexlist[index].length=i-indexlist[index].start;
    
    //查找
    return binsearch(array, indexlist[s[0]].start, indexlist[s[0]].start+indexlist[s[0]].length-1, s);
}


//散列（Hash）查找
/* 定义散列表的结构 */
struct node {
        char data[30];
        struct node *next;
} ; //list
struct node *Hashtab[4000];

/* 定义哈希函数（为插入时计算地址），这里可以根据不同的情况更换算法 */
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

/* 散列表的创建函数 */
void insertHash(char key[])
{
    struct node *p;
    unsigned int addr = hash(key);
    
    p = (struct node *)malloc(sizeof(struct node));
    strcpy(p->data, key);
    p->next = Hashtab[addr];
    Hashtab[addr] = p;
    //当散列出现冲突时，新插入的元素放在链表的头部，这样算法简洁，效率更高
}

/* 散列表的查找函数 */
struct node *searchHash(char key[])
{
    struct node *p;
    unsigned int addr = hash(key);
    for(p=Hashtab[addr]; p!=NULL; p=p->next)
    {
        //在冲突链表中找到或未找到(遇到第一个比待查找的单词大的单词或链表结束)便结束查找。
        N++;
        if(strcmp(p->data,key)==0)
            return p;
        else if(strcmp(p->data,key)>0)
            return NULL;
    }
    return NULL;//未找到返回null
}

int  hashsearch(struct dictionary_list array[], int n, char s[])
{
    //建立散列表
    for(int i=0; i<n; i++)
        insertHash(array[i].word);
    
    //查找
    return searchHash(s)==NULL?-1:1;
}


