#include <stdio.h>
#include <stdlib.h>
#define MAXVER  512
#define INFINITY   32767

struct edge {
    int id;
    int wei;
};
struct edge graph[MAXVER][MAXVER]; //邻接矩阵
int edges[MAXVER]={0}; //生成树

void Prim(struct edge weights[][MAXVER], int n, int src, int edges[]);

int cmp (const void * a, const void * b){
    return *(int*)a - *(int*)b;
}

int main(int argc, const char * argv[]) {
    
    int N,E;
    scanf("%d %d",&N,&E); //输入图的顶点(vertex)个数和边(edge)的个数
    
    //初始化图
    for(int i=0;i<N;i++)
            for(int j=0;j<N;j++)
                graph[i][j].wei=INFINITY;
    //构造图
    for(int i=0;i<E;i++)
    {
        int id,v1,v2,wei;
        scanf("%d %d %d %d",&id,&v1,&v2,&wei);
        graph[v1][v2].id = id; graph[v1][v2].wei = wei;
        graph[v2][v1].id = id; graph[v2][v1].wei = wei;
    }
    
    //求最小生成树--prim算法
    Prim(graph,N,0,edges);
    
    //整理
    int edges_id[MAXVER]; //需要铺设的边的id
    int edges_wei = 0;//铺设光缆的最小用料数
    
    for(int i=1;i<N;i++){
        edges_id[i-1]=graph[i][edges[i]].id;//根据生成树数组edges可得到生成树边序号
        edges_wei+=graph[i][edges[i]].wei;//生成树边权重求和（即用料数）
    }
    qsort(edges_id,N-1,sizeof(int),cmp);//输出的id值按照升序排序
    
    //输出
    printf("%d\n",edges_wei); //输出铺设光缆的最小用料数
    
    for(int i=0;i<N-1;i++)
        printf("%d ",edges_id[i]); //输出需要铺设的边的id
    printf("\n");
    
    return 0;
}

void Prim(struct edge weights[][MAXVER], int n, int src, int edges[])
{ //weights为权重数组、n为顶点个数、src为最小树的第一个顶点、edge为最小生成树边
    int minweight [MAXVER], min;
    int i, j, k;
    for(i=0; i<n; i++){  //初始化相关数组
        minweight[i] = weights[src][i].wei;  //将src顶点与之有边的权值存入数组
        edges[i]  = src;  //初始时所有顶点的前序顶点设为src，(src,i）
     }
    minweight[src]  = 0;   //将第一个顶点src顶点加入生成树
    for(i=1; i<n; i++){
        min = INFINITY;
        for(j=0, k=0;  j<n; j++)
            if(minweight[j] !=0 && minweight[j] < min) {  //在数组中找最小值，其下标为k
                min = minweight[j];  k = j;
            }
        minweight[k] = 0;  //找到最小树的一个顶点
        for(j=0;  j<n; j++)
             if(minweight[j] != 0 && weights[k][j].wei < minweight[j] ) {
                  minweight[j] = weights[k][j].wei;    //将小于当前权值的边(k,j)权值加入数组中
                  edges[j] = k;   //将边(j,k)信息存入边数组中
             }
    }
}


