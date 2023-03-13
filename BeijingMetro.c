#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define M 618
#define INF 0x3f3f3f3f
struct station{				//����վ��Žṹ�� 
	char stationName[30];	//վ�� 
	int IsChange;			//�ܷ񻻳� 
};
struct vertex{				//����ͼ�ṹ�� 
	int weight;				//Ȩ�� 
	int lineID;				//·����� 
};
struct station StationID_list[M];	//����վ������� 
struct vertex map[M][M];			//����ͼ 
int lineID,StationNum,lineNum,IsChange,VerNum;	//·����ţ�һ��·���е���վ������·�߸������Ƿ񻻳ˣ��ܵ���վ���� 
int prev[M],dist[M],path[M],top,pathID[M][M];	//�������飬���·����ֵ���飬dijkstra���·��������飬ջ����Floyd���·���������
char StationBegin[30],StationEnd[30];	//���վ���յ�վ 
void DrawSubwayMap(FILE *fp);		//��ͼ 
int SearchMap(char *s);				//��վ���Ƿ���ֹ� 
void dijkstra(int vs, int ve);		//dijkstra�㷨 
void PrintPath(int v1,int v2);		//��ӡ·�� 
int main()
{	
	int i,j,v1,v2,t;
	FILE *fp = fopen("bgstations.txt","r");
	scanf("%s %s",StationBegin,StationEnd);
	for(i=0;i<M;i++)			//��ʼ��ͼ 
		for(j=0;j<M;j++)
		{	
			map[i][j].weight=map[j][i].weight=INF;	//Ȩ������� 
			map[i][j].lineID=map[j][i].lineID=0;	//���Ϊ0 
		}
	DrawSubwayMap(fp);		//��ͼ 
	v1=SearchMap(StationBegin);	//�ҵ����վ��� 
	v2=SearchMap(StationEnd);	//�ҵ��յ�վ���  
	dijkstra(v1,v2);	//�����· 
	for(t=v2;t!=v1;t=prev[t])	//·��׷�� 
	{
		path[top]=t;
		top++;
	}
	PrintPath(v1,v2);	//��ӡ��� 
	return 0;
}
void DrawSubwayMap(FILE *fp)
{
	int i,j,ContainID,EdgeLast;//�������������ڵĵ���վ�ı�ţ��ߵ���� 
	char stationName[30];		//վ�� 
	fscanf(fp,"%d",&lineNum);	
	for(i=0;i<lineNum;i++)
	{
		fscanf(fp,"%d %d",&lineID,&StationNum);
		EdgeLast=-1;	//ÿһ��·��һ��ʼ���� -1 
		for(j=0;j<StationNum;j++)
		{
			fscanf(fp,"%s %d",stationName,&IsChange);
			ContainID=SearchMap(stationName);	//������û�� 
			if(ContainID == -1)		//û�� 
			{
				strcpy(StationID_list[VerNum].stationName,stationName);	//�洢 
				StationID_list[VerNum].IsChange=IsChange;				//�洢 
				if(EdgeLast != -1)		//����бߵ���� 
				{
					map[EdgeLast][VerNum].lineID=map[VerNum][EdgeLast].lineID=lineID;	//�洢 
					map[EdgeLast][VerNum].weight=map[VerNum][EdgeLast].weight=1;		//�洢 
				}
				EdgeLast=VerNum;	//�յ����� 
				VerNum++;			//���� +1 
			}
			else
			{
				if(EdgeLast != -1)	//����бߵ���� 
				{
					map[EdgeLast][ContainID].lineID=map[ContainID][EdgeLast].lineID=lineID;//�洢 
					map[EdgeLast][ContainID].weight=map[ContainID][EdgeLast].weight=1;	//�洢 
				}
				EdgeLast = ContainID;	//�յ�����
			}
		}
	}
}
int SearchMap(char *s)
{
	int i;
	for(i=0;i<VerNum;i++)
		if(strcmp(s,StationID_list[i].stationName)==0)
			return i;	//������� 
	return -1;
}
void dijkstra(int vs, int ve)
{
    int i,j,k,min,tmp;
    int flag[M];      				// flag[i]=1��ʾ"����vs"��"����i"�����·���ѳɹ���ȡ��
    for (i = 0; i < VerNum; i++)	// ��ʼ��
    {
        flag[i] = 0;              	// ����i�����·����û��ȡ����
        prev[i] = vs;             	 // ����i��ǰ������Ϊ0��
        dist[i] = map[vs][i].weight;	// ����i�����·��Ϊ"����vs"��"����i"��Ȩ��
    }
	dist[vs] = 0,flag[vs] = 1;		// ��"����vs"������г�ʼ��
    for (i = 0; i < VerNum - 1; i++)	// ����1�Σ�ÿ���ҳ�һ����������·����
    {								// Ѱ�ҵ�ǰ��С��·����������δ��ȡ���·���Ķ����У��ҵ���vs����Ķ���(k)��
        min = INF;
        for (j = 0; j < VerNum; j++)
        {
            if (flag[j]==0 && dist[j]<min)
            {
                min = dist[j];
                k = j;
            }
        }
        flag[k] = 1;				// ���"����k"Ϊ�Ѿ���ȡ�����·��
        // ������ǰ���·����ǰ������:  �����Ѿ�"����k�����·��"֮�󣬸���"δ��ȡ���·���Ķ�������·����ǰ������"��
        if(k==ve)	return;
        for (j = 0; j < VerNum; j++)
        {
            tmp = (map[k][j].weight==INF ? INF : (min + map[k][j].weight)); // ��ֹ���
            if (flag[j] == 0 && (tmp  < dist[j]) && map[k][j].lineID>0)
            {
                dist[j] = tmp;
                prev[j] = k;	//��¼ǰ�� 
            }
        }
    }
}
void PrintPath(int v1,int v2)
{		
	int i,EdgeLast=v1,pathLen=1,u=path[top-1];//i�Ǳ������ߵ���㣬���ȣ��ߵ��յ� 
	int lineId=map[EdgeLast][u].lineID;	//��ʼ·�߱�� 
	printf("%s-%d",StationID_list[v1].stationName,lineId); //��ӡ���վ�����վ��·�� 
	EdgeLast = u;
	for(i=top-2;i>=0;i--)	//����ջ������Ѱ�� 
	{
		u=path[i];	//�����յ� 
		if(lineId != map[EdgeLast][u].lineID)	//���� 
		{
			lineId = map[EdgeLast][u].lineID;
			printf("(%d)-%s-%d",pathLen,StationID_list[EdgeLast].stationName,lineId);
			pathLen=0;
		}
		pathLen++;		//���� +1 
		EdgeLast = u;	//�������
	}
	printf("(%d)-%s",pathLen,StationID_list[v2].stationName);//��ӡ�յ�վ
}


