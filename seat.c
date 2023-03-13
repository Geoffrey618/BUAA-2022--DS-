#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Info{
    int id;
    char name[30];
    int seat;
}list[200];

void sortbySeat(struct Info array[], int n);
void sortbyId(struct Info array[], int n);

int main(int argc, const char * argv[]) {
    
    int N;
    scanf("%d",&N); //读入学生人数n
    
    FILE *fi; char filename[]="in.txt";
    if((fi = fopen(filename, "r")) == NULL){ //打开一个文件
            fprintf(stderr, "%s  can’t open!\n",filename);
            return -1;
        }
    
    for(int i=0; i<N; i++)
        fscanf(fi,"%d %s %d",&list[i].id,list[i].name,&list[i].seat);
    
    //对考试座位安排表T1按座位号从小到大的顺序排序
    sortbySeat(list, N);
    
    /* 漏排 */
    int last=N-1; //最后学生的座位
    int Q= list[last].seat < N ? list[last].seat : N; //当前表中安排的最大座位号为M，取M和N的较小值Q
    
    //记录座位安排情况，漏排为0
    int seat[200]={0};
    for(int i=0; i<N; i++)
        seat[list[i].seat]++;
    
    //从1号开始检查，若某个小于等于Q的座位序号没有安排学生，则将表T2的最后学生的座位last设置为该座位号
    for(int j=1; j<=Q; j++){
        if(seat[j]==0)
            list[last--].seat=j;//若存在多个漏排座位，则从表T2最后依次向前设置，即last--
            Q= list[last].seat < N ? list[last].seat : N;
            //??题目所说的Q是动态变化的！因为补号的时候可能会让当前最大的号码减小，导致Q减小  否则第五个点过不了qaq
        }
            
    /* 重排 */
    int m=list[last].seat; //当前表中安排的最大座位号为m
    for(int i=0; i<N; i++)
        if(list[i].seat==list[i+1].seat){ //相邻两个座位号相同，为重排
            if(list[i+1].id>list[i].id) //学号较大的学生的座位号依次设置为m++
                list[i+1].seat=++m;
            else
                list[i].seat=++m;
        }
    
    //将调整好的表T2按学号由小到大序排序
    sortbyId(list, N);
    
    FILE *fp;
    fp = fopen("out.txt", "w");
    for(int i=0; i<N; i++)
        fprintf(fp,"%d %s %d\n",list[i].id,list[i].name,list[i].seat);
    
    return 0;
}

void sortbySeat(struct Info array[], int n)
{
    int i, j;
    struct Info tmp;
    for(i=0; i<n; i++)
    for(j=i; j<n; j++){
        if(array[i].seat > array[j].seat)
        {
            tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;
        }
    }
}
void sortbyId(struct Info array[], int n)
{
    int i, j;
    struct Info tmp;
    for(i=0; i<n; i++)
    for(j=i; j<n; j++){
        if(array[i].id > array[j].id)
        {
            tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;
        }
    }
}



