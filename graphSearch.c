#include <stdio.h>
#include <stdlib.h>

//ͼ���ڽӱ���
#define MaxV 256
typedef struct edge{
    int  adj;
    int  wei;
    struct edge  *next;
} ELink;

typedef struct ver{
    ELink  *link;
} VLink;
VLink  G[MaxV];

int V, E; //����(vertex)������(edge)��

void createGraph(VLink graph[]);

void  travelDFS(VLink  G[ ], int n, int delV);
void  travelBFS(VLink  G[ ], int n, int delV);

int main(int argc, const char * argv[]) {
    
    scanf("%d %d",&V,&E); //����ͼ�Ķ���(vertex)�����ͱ�(edge)�ĸ���
    
    createGraph(G);//��������ͼ��??��Ҫ����
    
    travelDFS(G,V,-1);//-1��ʾ��ɾ������
    travelBFS(G,V,-1);
    
    int k;
    scanf("%d",&k);//����Ҫɾ���Ķ�����
    
    travelDFS(G,V,k);//ɾ��k���㣬��������ɾ��������Visted[k]=1
    travelBFS(G,V,k);
    
    return 0;
}

//ELink  *insertEdge(ELink *head, int avex)
//{
//    ELink *e,*p;
//    e =(ELink *)malloc(sizeof(ELink));
//    e->adj= avex; e->wei=1; e->next = NULL;
//    if(head == NULL)  { head=e; return head; }
//    for(p=head; p->next != NULL; p=p->next)
//        ;
//    p->next = e;
//    return head;
//}

/* ��head��һ����������������Ԫ��avex���뵽��Ӧλ���� */
ELink  *insertEdge(ELink *head, int avex)
{
    ELink *e,*p,*q = NULL;
    e =(ELink *)malloc(sizeof(ELink)); /* ����һ��������Ϊavex���½�� */
    e->adj= avex; e->wei=1; e->next = NULL;
    if(head == NULL)  /* head��һ���ձ� */
        return e;
    for(p=head; p != NULL && avex > p->adj;  q = p, p = p->next) /* �ҵ�����λ�� */
        ;
    if( p == head){  /* ��ͷ���ǰ���� */
        e->next = p;
        return e;
    }
    else {           /* �ڽ��pǰ����һ����� */
        q->next = e;
        e->next = p;
        return head;
    }
}

void createGraph(VLink graph[])
{
    for(int i=0;i<E;i++)
    {
        int v1,v2;
        scanf("%d %d",&v1,&v2);
        graph[v1].link=insertEdge(graph[v1].link, v2);
        graph[v2].link=insertEdge(graph[v2].link, v1);
    }
}


int Visited[MaxV]={0}; //��ʶ�����Ƿ񱻷��ʹ���NΪ������

/* ������ȱ��� */
void DFS(VLink  G[ ], int v)
{
    ELink  *p;
    Visited[v] = 1; //��ʶĳ���㱻���ʹ�
    printf("%d ", v);
    //VISIT(G, v); //����ĳ����
    for(p = G[v].link; p !=NULL;  p=p->next)
        if( !Visited[p->adj] )
            DFS(G, p->adj);
}

void  travelDFS(VLink  G[ ], int n, int delV)
{
    int i;
    for(i=0; i<n; i++)
        Visited[i] = 0 ;
    if(delV >= 0)  //����ɾ��
        Visited[delV] = 1;
    for(i=0; i<n; i++)
        if( !Visited[i] ) DFS(G, i);
    printf("\n");
}


/* ������ȱ��� */

//ѭ������
#define MAXSIZE     1000
int  Q[MAXSIZE];
int  Front, Rear,Count;
void  initQueue(void)
{
    Front = 0;
    Rear = MAXSIZE-1;
    Count = 0;
}
int  isEmpty(void)
{
    return Count == 0;
}
int  isFull(void)
{
    return Count == MAXSIZE;
}
void enQueue(int queue[ ], int item)
{
    if(isFull())                       /* ����������ʧ�� */
        printf("Full queue!");
    else{                              /* ��δ��������ɹ� */
        Rear = (Rear+1) % MAXSIZE;
        queue[Rear]=item;
        Count++;
    }
}
int  deQueue(int queue[ ])
{
    int e;
    if(isEmpty())                    /* �ӿգ�ɾ��ʧ�� */
        printf("Empty queue!");
    else{                            /* �ӷǿգ�ɾ���ɹ� */
        e=queue[Front];
        Count--;
        Front = (Front+1) % MAXSIZE;
        return e;
    }
    return 0;
}


void BFS(VLink  G[ ], int v)
{
    ELink  *p;
    initQueue();  //��ʼ����
    Visited[v] = 1; //��ʶĳ���������
    enQueue(Q, v);
    while( !isEmpty()){
        v = deQueue(Q);  //ȡ����ͷԪ��
        printf("%d ",v);
        //VISIT(G, v); //���ʵ�ǰ����
        for(p=G[v].link; p!=NULL; p=p->next ) //���ʸö����ÿ���ڽӶ���
            if( !Visited[p->adj] ) {
                Visited[p->adj] = 1; //��ʶĳ�������
                enQueue(Q, p->adj);
            }
    }
}

void  travelBFS(VLink  G[ ], int n, int delV)
{
    int i;
    for(i=0; i<n; i++)
        Visited[i] = 0 ;
    if(delV >= 0)  //����ɾ��
        Visited[delV] = 1;
    for(i=0; i<n; i++)
        if( !Visited[i] )
            BFS(G, i);
    printf("\n");
}

