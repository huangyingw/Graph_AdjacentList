// Graph_AdjacentList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;			

#define INT_MAX 10000
#define inf 9999 
#define max 20




//…………………………………………邻接矩阵定义……………………
typedef struct ArcCell
{
	int weight;//弧的权值
}ArcCell,AdjMatrix[20][20];

typedef struct 
{
	char vexs[20];
	AdjMatrix arcs;
	int vexNum,arcNum;
}MGraph_L;

typedef struct node
{
	int adjvex;//邻接点域
	struct node *next;//链域
	int weight;
}EdgeNode;

typedef struct vnode
{
	//顶点表结点
	char vertex;//顶点域
	EdgeNode *firstedge;//边表头指针
}VertexNode;

typedef struct Vnode//邻接链表顶点头接点
{
	char vertex;//顶点域vertex存放顶点vi的信息
	EdgeNode *firstedge;//指向第一条依附该结点的弧的指针
}Vnode,Adjlist;

typedef struct//图的定义
{
	VertexNode vertices[max];
	int vexNum,arcNum;//顶点数目，弧数目
}Algraph;


typedef struct
{
	Adjlist adjlist;//邻接表
	int n,e;//图中当前顶点数和边数
}ALGraph;//对于简单的应用，无须定义此类型，可直接使用AdjList类型.


void CreatMGraph_L(MGraph_L &G,int* data,int dim)//创建图用邻接矩阵表示
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

void PrintMGraph_L(MGraph_L &G)//创建图用邻接矩阵表示
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

void CreatAdj(Algraph &gra,MGraph_L G)//用邻接表存储图
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

void PrintAdj(Algraph G)//打印邻接矩阵
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
	
	CreatMGraph_L(G,*data,7);//创建图用邻接矩阵表示
	CreatAdj(gra,G);
	cout<<"现在开始打印邻接表:"<<endl;
	PrintAdj(gra);
	return 0;
}

