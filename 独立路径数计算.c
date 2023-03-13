#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE  512
typedef struct edge{   //�߽��ṹ
       int  eno;       //�����
       int  adjvex;    //�ڽӶ���
       int  weight;    //�ߵ�Ȩ�أ���Ϊ�����ʱ�䣩��������Ϊ1
       struct edge  *next;
}ELink;
typedef struct ver {   //����ṹ���ڽӱ��±꼴Ϊ�������
       struct edge  *link;
}VLink;
VLink G[MAXSIZE];           //���ڽӱ��ɵ�ͼ
char Visted[MAXSIZE] = {0}; //��ʶ��Ӧ�����Ƿ񱻷���
int paths[MAXSIZE];         //����·��

int N, E; //������������

void createGraph(VLink graph[]);
void travelDFS_(VLink  G[ ]);

int main(int argc, const char * argv[]) {
    
    scanf("%d %d",&N,&E); //����ͼ�Ķ�������ͱߵĸ���
    
    createGraph(G);//��������ͼ��??��Ҫ����
    
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

int Visited[MAXSIZE]={0}; //��ʶ�����Ƿ񱻷��ʹ���NΪ������

/* ������ȱ��� */

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
            Visited[v] = 1; //��ʶĳ���㱻���ʹ�
            DFS_(G, p->adjvex, level+1);
            Visited[v] = 0; //��ʶĳ���㱻���ʹ�
        }
    return;
}

void travelDFS_(VLink  G[ ])
{
    //��ʼ��
    for(int i=0; i<N; i++)
        Visited[i] = 0 ;
    Visited[0]=1;
    
    DFS_(G, 0, 0);
}


