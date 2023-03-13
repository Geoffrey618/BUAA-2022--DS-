//文件压缩-Huffman实现
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 32

struct tnode {			//Huffman树结构
	char c;		
	int weight;		//树节点权重，叶节点为字符和它的出现次数
	struct tnode *left,*right;
} ; 
int Ccount[128]={0};		//存放每个字符的出现次数，如Ccount[i]表示ASCII值为i的字符出现次数 
struct tnode *Root=NULL; 	//Huffman树的根节点
char HCode[128][MAXSIZE]={{0}}; //字符的Huffman编码，如HCode['a']为字符a的Huffman编码（字符串形式） 
int Step=0;			//实验步骤 
FILE *Src, *Obj;
	
void statCount();		//步骤1：统计文件中字符频率
void createHTree();		//步骤2：创建一个Huffman树，根节点为Root 
void makeHCode();		//步骤3：根据Huffman树生成Huffman编码
void atoHZIP(); 		//步骤4：根据Huffman编码将指定ASCII码文本文件转换成Huffman码文件

void print1();			//输出步骤1的结果
void print2(struct tnode *p);	//输出步骤2的结果 
void print3();			//输出步骤3的结果
void print4();			//输出步骤4的结果

int main()
{
        if((Src=fopen("input.txt","r"))==NULL) {
	        fprintf(stderr, "%s open failed!\n", "input.txt");
		return 1; 
	}
	if((Obj=fopen("output.txt","w"))==NULL) {
		fprintf(stderr, "%s open failed!\n", "output.txt");
		return 1;
	}
	scanf("%d",&Step);		//输入当前实验步骤 
	
	statCount();			//实验步骤1：统计文件中字符出现次数（频率）
	(Step==1)?print1():1;   	//输出实验步骤1结果	
	createHTree();			//实验步骤2：依据字符频率生成相应的Huffman树
	(Step==2)?print2(Root):2; 	//输出实验步骤2结果	
	makeHCode();		//实验步骤3：依据Root为树的根的Huffman树生成相应Huffman编码
	(Step==3)?print3():3;   	//输出实验步骤3结果
	(Step>=4)?atoHZIP(),print4():4;//实验步骤4：据Huffman编码生成压缩文件，并输出实验步骤4结果	

	fclose(Src);
	fclose(Obj);
        return 0;
} 

//【实验步骤1】开始 
void statCount()
{
//字符频率统计：
    char c;
    while( (c=fgetc(Src)) != EOF){
        Ccount[c]++;
    }
    Ccount[0]=1;	
}



//【实验步骤1】结束

//【实验步骤2】开始
void createHTree()
{
    //第一步为了生成Huffman树，首先根据字符统计结果生成一个有序链表：
    
    struct tnode *p,*F[100];
    int start=0,end=-1;
    
    for(int i=0; i<128; i++)
        if(Ccount[i]>0)
        {
            p = (struct tnode *)malloc(sizeof(struct tnode));
            p->c = i;
            p->weight = Ccount[i];
            p->left = p->right = NULL;
            //add p into F;
            F[++end]=p;
        }
    
    //对树林F中每棵树按其根结点的权值由小至大进行排序（排序时，当权值weight相同时，字符c小的排在前面），得到一个有序树林F
    struct tnode * temp;
    
    for(int i=end; i>0 ; i--){
        for(int j=0;j<i;j++)
            if(F[j]->weight>F[j+1]->weight){
                temp=F[j];
                F[j]=F[j+1];
                F[j+1]=temp;  /* 交换两个元素的位置 */
            }
    }

    
    //第二步按Huffman树生成算法，由有序表构造Huffman树：
    //while 树个数>1 in F
    //  a)   将F中T0和T1作为左、右子树合并成为一棵新的二叉树T’，并令T’->weight= T0->weight+ T1->weight
    //  b)   删除T0和T1 from F，同时将T’加入F。要求加入T’后F仍然有序。若F中有树根结点权值与T’相同，则T’应加入到其后
    
    while(start+1<end){
        p = (struct tnode *)malloc(sizeof(struct tnode));
        p ->weight = F[start]->weight + F[start+1]->weight;
        p->left = F[start];
        p->right = F[start+1];  /*将新树的根结点加入到有序结点链表中*/
        start=start+2;
        //insertSortLink(p);
        F[++end]=p;
        for(int i=end; i>0 ; i--){
            for(int j=start;j<i;j++)
                if(F[j]->weight>F[j+1]->weight){
                    temp=F[j];
                    F[j]=F[j+1];
                    F[j+1]=temp;  /* 交换两个元素的位置 */
                }
        }
    }
    
    p = (struct tnode *)malloc(sizeof(struct tnode));
    p ->weight = F[start]->weight + F[start+1]->weight;
    p->left = F[start];
    p->right = F[start+1];
    //Root = T0 （Root为Huffman树的根结点指针。循环结束时，F中只有一个T0）
    Root=p;
}



//【实验步骤2】结束

//【实验步骤3】开始
char Huffman[MAXSIZE]; //用于生成Huffman编码
void createHCode(struct tnode *p,char code, int level)
{
    if(level != 0)
        Huffman[level-1] = code;
    if(p->left == NULL && p->right == NULL){
        Huffman[level] ='\0' ;
        strcpy(HCode[p->c], Huffman);
    }
    else {
        createHCode(p->left, '0', level+1);
        createHCode(p->right, '1', level+1);
    }
}
void makeHCode()
{
    createHCode(Root, 0, 0);
}




//【实验步骤3】结束

//【实验步骤4】开始
void atoHZIP()
{
    unsigned char *pc,hc=0;//&#9888;&#65039; unsigned char 8字节，char 4字节，否则会输出 ffffff 哦。
    int c=0,i=0;
    fseek(Src,0, SEEK_SET); //从src文件头开始
    do {
        c=fgetc(Src) ;     //依次获取源文件中每个字符
        if (c == EOF) c=0;     //源文件结束
        for(pc = HCode[c]; *pc != '\0'; pc++){     //转换为huffman码
            hc = (hc << 1) | (*pc-'0'); i++;
            if(i==8){     //每满8位输出一个字节
                fputc(hc,Obj);
                printf("%x",hc);
                i = 0;
            }
        }
        if(c==0 && i!=0){ //处理文件结束时不满一个字节的情况
            while(i++<8) hc = (hc << 1);
            fputc(hc,Obj);
            printf("%x",hc);
        }
    } while (c ); //c=0时文件结束
}



//【实验步骤4】结束

void print1()
{
	int i;
	printf("NUL:1\n");
	for(i=1; i<128; i++)
		if(Ccount[i] > 0)
			printf("%c:%d\n", i, Ccount[i]);
}

void print2(struct tnode *p)
{
	if(p != NULL){
		if((p->left==NULL)&&(p->right==NULL)) 
			switch(p->c){
				case 0: printf("NUL ");break;
				case ' ':  printf("SP ");break;
				case '\t': printf("TAB ");break;
				case '\n':  printf("CR ");break;
				default: printf("%c ",p->c); break;
			}
		print2(p->left);
		print2(p->right);
	}
}

void print3()
{
	int i;
	
	for(i=0; i<128; i++){
		if(HCode[i][0] != 0){
			switch(i){
				case 0: printf("NUL:");break;
				case ' ':  printf("SP:");break;
				case '\t': printf("TAB:");break;
				case '\n':  printf("CR:");break;
				default: printf("%c:",i); break;
			}
			printf("%s\n",HCode[i]);
		}
	}
} 

void print4()
{
	long int in_size, out_size;
	
	fseek(Src,0,SEEK_END);
	fseek(Obj,0,SEEK_END);
	in_size = ftell(Src);
	out_size = ftell(Obj);
	
	printf("\n原文件大小：%ldB\n",in_size);
	printf("压缩后文件大小：%ldB\n",out_size);
	printf("压缩率：%.2f%%\n",(float)(in_size-out_size)*100/in_size);
}

