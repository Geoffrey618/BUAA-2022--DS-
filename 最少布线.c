#include <stdio.h>
#include <stdlib.h>
#define MAXVER  512
#define INFINITY   32767

struct edge {
    int id;
    int wei;
};
struct edge graph[MAXVER][MAXVER]; //�ڽӾ���
int edges[MAXVER]={0}; //������

void Prim(struct edge weights[][MAXVER], int n, int src, int edges[]);

int cmp (const void * a, const void * b){
    return *(int*)a - *(int*)b;
}

int main(int argc, const char * argv[]) {
    
    int N,E;
    scanf("%d %d",&N,&E); //����ͼ�Ķ���(vertex)�����ͱ�(edge)�ĸ���
    
    //��ʼ��ͼ
    for(int i=0;i<N;i++)
            for(int j=0;j<N;j++)
                graph[i][j].wei=INFINITY;
    //����ͼ
    for(int i=0;i<E;i++)
    {
        int id,v1,v2,wei;
        scanf("%d %d %d %d",&id,&v1,&v2,&wei);
        graph[v1][v2].id = id; graph[v1][v2].wei = wei;
        graph[v2][v1].id = id; graph[v2][v1].wei = wei;
    }
    
    //����С������--prim�㷨
    Prim(graph,N,0,edges);
    
    //����
    int edges_id[MAXVER]; //��Ҫ����ıߵ�id
    int edges_wei = 0;//������µ���С������
    
    for(int i=1;i<N;i++){
        edges_id[i-1]=graph[i][edges[i]].id;//��������������edges�ɵõ������������
        edges_wei+=graph[i][edges[i]].wei;//��������Ȩ����ͣ�����������
    }
    qsort(edges_id,N-1,sizeof(int),cmp);//�����idֵ������������
    
    //���
    printf("%d\n",edges_wei); //���������µ���С������
    
    for(int i=0;i<N-1;i++)
        printf("%d ",edges_id[i]); //�����Ҫ����ıߵ�id
    printf("\n");
    
    return 0;
}

void Prim(struct edge weights[][MAXVER], int n, int src, int edges[])
{ //weightsΪȨ�����顢nΪ���������srcΪ��С���ĵ�һ�����㡢edgeΪ��С��������
    int minweight [MAXVER], min;
    int i, j, k;
    for(i=0; i<n; i++){  //��ʼ���������
        minweight[i] = weights[src][i].wei;  //��src������֮�бߵ�Ȩֵ��������
        edges[i]  = src;  //��ʼʱ���ж����ǰ�򶥵���Ϊsrc��(src,i��
     }
    minweight[src]  = 0;   //����һ������src�������������
    for(i=1; i<n; i++){
        min = INFINITY;
        for(j=0, k=0;  j<n; j++)
            if(minweight[j] !=0 && minweight[j] < min) {  //������������Сֵ�����±�Ϊk
                min = minweight[j];  k = j;
            }
        minweight[k] = 0;  //�ҵ���С����һ������
        for(j=0;  j<n; j++)
             if(minweight[j] != 0 && weights[k][j].wei < minweight[j] ) {
                  minweight[j] = weights[k][j].wei;    //��С�ڵ�ǰȨֵ�ı�(k,j)Ȩֵ����������
                  edges[j] = k;   //����(j,k)��Ϣ�����������
             }
    }
}


