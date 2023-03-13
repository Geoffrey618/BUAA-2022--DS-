#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE  512
typedef struct edge{   //边结点结构
       int  eno;       //边序号
       int  adjvex;    //邻接顶点
       int  weight;    //边的权重（可为距离或时间），本文中为1
       struct edge  *next;
}ELink;
typedef struct ver {   //顶点结构，邻接表下标即为顶点序号
       struct edge  *link;
}VLink;
VLink G[MAXSIZE];           //由邻接表构成的图
char Visted[MAXSIZE] = {0}; //标识相应顶点是否被访问
int paths[MAXSIZE];         //独立路径

int N, E; //顶点数，边数

void createGraph(VLink graph[]);
void travelDFS_(VLink  G[ ]);

int main(int argc, const char * argv[]) {
    
    scanf("%d %d",&N,&E); //输入图的顶点个数和边的个数
    
    createGraph(G);//建立无向图，??需要排序！
    
    travelDFS_(G);
    
    return 0;
}

ELink  *insertEdge(ELink *head, int edge, int avex)
{
    ELink *e,*p;
    e =(ELink *)malloc(sizeof(ELink));
    e->eno=edge;  e->adjvex= avex; e->weight=1; e->next = NULL;
    if(head == NULL)  { head=e; return head; }
    for(p=head; p->next != NULL; p=p->next)
        ;
    p->next = e;
    return head;
}

void createGraph(VLink graph[])
{
    for(int i=0;i<E;i++)
    {
        int e,v1,v2;
        scanf("%d %d %d",&e,&v1,&v2);
        graph[v1].link=insertEdge(graph[v1].link, e, v2);
        graph[v2].link=insertEdge(graph[v2].link, e, v1);
    }
}

int Visited[MAXSIZE]={0}; //标识顶点是否被访问过，N为顶点数

/* 深度优先遍历 */

void print_path(int n)
{
    for(int i=0;i<n;i++)
        printf("%d ", paths[i]);
    printf("\n");
}

void DFS_(VLink  G[ ], int v, int level)
{
    ELink  *p;
    
    if(v == N-1)
    {
        print_path(level);
        return;
    }
    
    for(p = G[v].link; p !=NULL;  p=p->next)
        if( !Visited[p->adjvex] ){
            paths[level]=p->eno;
            Visited[v] = 1; //标识某顶点被访问过
            DFS_(G, p->adjvex, level+1);
            Visited[v] = 0; //标识某顶点被访问过
        }
    return;
}

void travelDFS_(VLink  G[ ])
{
    //初始化
    for(int i=0; i<N; i++)
        Visited[i] = 0 ;
    Visited[0]=1;
    
    DFS_(G, 0, 0);
}


