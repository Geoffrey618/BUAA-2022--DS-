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
    scanf("%d",&N); //����ѧ������n
    
    FILE *fi; char filename[]="in.txt";
    if((fi = fopen(filename, "r")) == NULL){ //��һ���ļ�
            fprintf(stderr, "%s  can��t open!\n",filename);
            return -1;
        }
    
    for(int i=0; i<N; i++)
        fscanf(fi,"%d %s %d",&list[i].id,list[i].name,&list[i].seat);
    
    //�Կ�����λ���ű�T1����λ�Ŵ�С�����˳������
    sortbySeat(list, N);
    
    /* ©�� */
    int last=N-1; //���ѧ������λ
    int Q= list[last].seat < N ? list[last].seat : N; //��ǰ���а��ŵ������λ��ΪM��ȡM��N�Ľ�СֵQ
    
    //��¼��λ���������©��Ϊ0
    int seat[200]={0};
    for(int i=0; i<N; i++)
        seat[list[i].seat]++;
    
    //��1�ſ�ʼ��飬��ĳ��С�ڵ���Q����λ���û�а���ѧ�����򽫱�T2�����ѧ������λlast����Ϊ����λ��
    for(int j=1; j<=Q; j++){
        if(seat[j]==0)
            list[last--].seat=j;//�����ڶ��©����λ����ӱ�T2���������ǰ���ã���last--
            Q= list[last].seat < N ? list[last].seat : N;
            //??��Ŀ��˵��Q�Ƕ�̬�仯�ģ���Ϊ���ŵ�ʱ����ܻ��õ�ǰ���ĺ����С������Q��С  ���������������qaq
        }
            
    /* ���� */
    int m=list[last].seat; //��ǰ���а��ŵ������λ��Ϊm
    for(int i=0; i<N; i++)
        if(list[i].seat==list[i+1].seat){ //����������λ����ͬ��Ϊ����
            if(list[i+1].id>list[i].id) //ѧ�Žϴ��ѧ������λ����������Ϊm++
                list[i+1].seat=++m;
            else
                list[i].seat=++m;
        }
    
    //�������õı�T2��ѧ����С����������
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



