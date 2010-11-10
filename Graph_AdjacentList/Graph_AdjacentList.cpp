// Graph_AdjacentList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;			

#define INT_MAX 10000
#define inf 9999 
#define max 20




//���������������������������������ڽӾ����塭��������������
typedef struct ArcCell
{
	int weight;//����Ȩֵ
}ArcCell,AdjMatrix[20][20];

typedef struct 
{
	char vexs[20];
	AdjMatrix arcs;
	int vexNum,arcNum;
}MGraph_L;

typedef struct node
{
	int adjvex;//�ڽӵ���
	struct node *next;//����
	int weight;
}EdgeNode;

typedef struct vnode
{
	//�������
	char vertex;//������
	EdgeNode *firstedge;//�߱�ͷָ��
}VertexNode;

typedef struct Vnode//�ڽ�������ͷ�ӵ�
{
	char vertex;//������vertex��Ŷ���vi����Ϣ
	EdgeNode *firstedge;//ָ���һ�������ý��Ļ���ָ��
}Vnode,Adjlist;

typedef struct//ͼ�Ķ���
{
	VertexNode vertices[max];
	int vexNum,arcNum;//������Ŀ������Ŀ
}Algraph;


typedef struct
{
	Adjlist adjlist;//�ڽӱ�
	int n,e;//ͼ�е�ǰ�������ͱ���
}ALGraph;//���ڼ򵥵�Ӧ�ã����붨������ͣ���ֱ��ʹ��AdjList����.


void CreatMGraph_L(MGraph_L &G,int* data,int dim)//����ͼ���ڽӾ����ʾ
{
	G.vexNum=7;
	G.arcNum=9;
	for(int i=0;i<dim;i++)
	{
		_itoa_s( i, &G.vexs[i],8,10);
		
		for(int j=0;j<dim;j++)
		{
			if(data[dim*i+j]<INT_MAX)
			{
				G.arcs[i][j].weight=data[dim*i+j];
				G.arcs[j][i].weight=data[dim*i+j];
			}
		}
	}
}

void PrintMGraph_L(MGraph_L &G)//����ͼ���ڽӾ����ʾ
{
	for(int i=0;i<G.vexNum;i++)
	{
		for(int j=0;j<G.vexNum;j++)
		{ 
			if(G.arcs[i][j].weight>0&&G.arcs[i][j].weight<INT_MAX)
			{
				cout<<i<<"->"<<j<<":"<<G.arcs[i][j].weight<<",";
			}
		}
		cout<<endl;
	}
	
}

void CreatAdj(Algraph &gra,MGraph_L G)//���ڽӱ�洢ͼ
{
	EdgeNode *arc;
	for(int i=0;i<G.vexNum;++i)
	{
		gra.vertices[i].vertex=G.vexs[i];
		gra.vertices[i].firstedge=NULL;
	}
	for(int i=0;i<G.vexNum;++i)
	{
		for(int j=0;j<G.vexNum;++j)
		{
			if(gra.vertices[i].firstedge==NULL)
			{
				if(G.arcs[i][j].weight>0&&G.arcs[i][j].weight<INT_MAX&&j<G.vexNum)
				{
					arc=new EdgeNode();
					arc->adjvex=j;
					arc->weight=G.arcs[i][j].weight;
					arc->next=NULL;
					gra.vertices[i].firstedge=arc;
				}
			}
			else
			{
				if(G.arcs[i][j].weight>0&&G.arcs[i][j].weight<INT_MAX&&j<G.vexNum)
				{
					arc=new EdgeNode();
					arc->adjvex=j;
					arc->weight=G.arcs[i][j].weight;
					arc->next=gra.vertices[i].firstedge;
					gra.vertices[i].firstedge=arc;
				}
			}
		}
	}
	gra.vexNum=G.vexNum;
	gra.arcNum=G.arcNum;
}

void PrintAdj(Algraph G)//��ӡ�ڽӾ���
{
	EdgeNode *node;
	for(int i=0;i<G.vexNum;i++)
	{
		node=G.vertices[i].firstedge;
		cout<<G.vertices[i].vertex;
		while(NULL!=node)
		{
			cout<<"->"<<node->adjvex<<":"<<node->weight				;
			node=node->next;
		}
		cout<<endl;
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	Algraph gra;
	MGraph_L G;
	int data[7][7]={{INT_MAX,28,INT_MAX,INT_MAX,INT_MAX,10,INT_MAX},
					{28,INT_MAX,16,INT_MAX,INT_MAX,INT_MAX,14},
					{INT_MAX,16,INT_MAX,12,INT_MAX,INT_MAX,INT_MAX},
					{INT_MAX,INT_MAX,12,INT_MAX,22,INT_MAX,18},
					{INT_MAX,INT_MAX,INT_MAX,22,INT_MAX,25,24},
					{10,INT_MAX,INT_MAX,INT_MAX,25,INT_MAX,INT_MAX},
					{INT_MAX,14,INT_MAX,18,24,INT_MAX,INT_MAX}};
	
	CreatMGraph_L(G,*data,7);//����ͼ���ڽӾ����ʾ
	CreatAdj(gra,G);
	cout<<"���ڿ�ʼ��ӡ�ڽӱ�:"<<endl;
	PrintAdj(gra);
	return 0;
}

