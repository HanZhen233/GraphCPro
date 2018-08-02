#include<iostream>
#include"Graph.h"
#include"global.h"
using namespace std;


void CGraph::Init(){
	for(int i=0;i<20;i++)
	for(int j=0;j<20;j++)
		m_aAdjmatrix[i][j]=0;//初始化图
	m_nVexNum=0;
}

int CGraph::InsertVex(Vex sVex){
	if(m_nVexNum==MAX_VERTEX_NUM){
	return ERROR;
	}

	 m_aVexs[m_nVexNum++]=sVex;

	 return OK;
}

int CGraph::InsertEdge(Edge sEdge){
	if(sEdge.vex1<0||sEdge.vex1>m_nVexNum||sEdge.vex2<0||sEdge.vex2>m_nVexNum)
		return ERROR;
	m_aAdjmatrix[sEdge.vex1][sEdge.vex2]=sEdge.weight;
	m_aAdjmatrix[sEdge.vex2][sEdge.vex1]=sEdge.weight;

	return OK;
}



//获得顶点

Vex CGraph::GexVex(int v){

	return m_aVexs[v];

}
//获得邻近顶点个数与边
int CGraph::FindEdge(int v,Edge aEdge[])
{
	int k = 0;
	for (int i = 0; i < m_nVexNum; i++)
	{
		if (m_aAdjmatrix[v][i]!=0)
		{
			aEdge[k].vex1 = v;
			aEdge[k].vex2 = i;
			aEdge[k].weight = m_aAdjmatrix[v][i];
			k++;
		}

	}
	
	return k;
}
int CGraph::GetVexNum() {

	return m_nVexNum;
}

//深度优先搜索遍历
void CGraph::DFS(int nVex, bool bVisited[], int &nIndex, PathList &pList) {
	bVisited[nVex] = true;
	pList->vexs[nIndex++] = nVex;

	int vexNum = 0;//判断是否所有结点是否全都被访问过
	for (int i = 0; i < m_nVexNum; i++)
	{
		if (bVisited[i])
		{
			vexNum++;
		}
	}
	//如果所有结点都被访问过

	if (vexNum==m_nVexNum)
	{
		pList->next = (PathList)malloc(sizeof(Path));
		for (int i = 0; i < m_nVexNum; i++)
		{
			pList->next->vexs[i] = pList->vexs[i];
		}
		pList = pList->next;
		pList->next = NULL;
	}
	else
	{

		for (int i = 0; i < m_nVexNum; i++)
		{
			if (m_aAdjmatrix[nVex][i] != 0 && !bVisited[i])
			{
				DFS(i, bVisited, nIndex, pList);
				bVisited[i] = false;
				nIndex--;
			}
		}
	}
}

//遍历调用函数
void CGraph::DFSTraverse(int nVex, PathList & pList) {
	int nIndex = 0;
	bool bVisited[MAX_VERTEX_NUM] = { false };
	DFS(nVex, bVisited, nIndex,pList);

}

//求最短路径长度
int CGraph::FindShortPath(int nVexStart, int nVexEnd, Edge aPath[])
{
	int nShortPath[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//保存最短路径
	int nShortDistance[MAX_VERTEX_NUM];//保存最短距离
	bool aVisited[MAX_VERTEX_NUM];//判断某顶点是否已经加入到最短路径
								  //初始化
	int v;
	for (v = 0; v<m_nVexNum; v++)
	{
		aVisited[v] = false;
		if (m_aAdjmatrix[nVexStart][v] != 0)
			//初始化该顶点到其他顶点的最短距离，默认为两点间的距离
			nShortDistance[v] = m_aAdjmatrix[nVexStart][v];
		else
			//如果顶点i和nVexStart不相连，则最短距离设为最大值
			nShortDistance[v] = 0x7FFFFFFF;
		nShortPath[v][0] = nVexStart;//起始点为nVexStart
		for (int j = 1; j<m_nVexNum; j++)
		{
			nShortPath[v][j] = -1;//初始化最短路径
		}
	}
	//初始化，nVexStart顶点加入到集合中
	aVisited[nVexStart] = true;
	int min;

	for (int i = 1; i<m_nVexNum; i++)
	{
		min = 0x7FFFFFFF;
		bool bAdd = false;//判断是否还有顶点可以加入到集合中
		for (int j = 0; j<m_nVexNum; j++)
		{
			if (aVisited[j] == false)
			{
				if (nShortDistance[j]<min)
				{
					v = j;//j顶点离nVexStart顶点最近
					min = nShortDistance[j];//j到nVexStart的最短距离为min
					bAdd = true;
				}
			}
		}//如果没有顶点可以加入到集合，则跳出循环
		if (bAdd == false)
		{
			break;
		}
		aVisited[v] = true;//将顶点j加入到集合
		nShortPath[v][i] = v;//将顶点j保存到nVexStart到j的最短路径里
		for (int w = 0; w<m_nVexNum; w++)
		{
			//将w作为过度顶点计算nVexStart通过w到每个顶点的距离
			if (aVisited[w] == false && (min + m_aAdjmatrix[v][w]<nShortDistance[w]) && m_aAdjmatrix[v][w] != 0)
			{
				//更新当前最短路径及距离
				nShortDistance[w] = min + m_aAdjmatrix[v][w];
				for (int i = 0; i<m_nVexNum; i++)
				{
					//如果通过w到达顶点i的距离比较短，则将w的最短路径复制给i
					nShortPath[w][i] = nShortPath[v][i];
				}
			}
		}
	}
	int nIndex = 0;
	int nVex1 = nVexStart;
	//将最短路径保存为边的结构体数组
	for (int i = 1; i<m_nVexNum; i++)
	{
		if (nShortPath[nVexEnd][i] != -1)
		{
			aPath[nIndex].vex1 = nVex1;
			aPath[nIndex].vex2 = nShortPath[nVexEnd][i];
			aPath[nIndex].weight = m_aAdjmatrix[aPath[nIndex].vex1][aPath[nIndex].vex2];
			nVex1 = nShortPath[nVexEnd][i];
			nIndex++;
		}
	}
	return nIndex;
}

	

//生成最小生成树
void CGraph::FindMinTree(Edge aPath[])
{
	bool aVisited[MAX_VERTEX_NUM];//判断某顶点是否在最小生成树顶点集合里
	for (int i = 0; i<MAX_VERTEX_NUM; i++)
	{
		aVisited[i] = false;
	}
	aVisited[0] = true;//0顶点加入到集合中
	int min;
	int nVex1, nVex2;
	for (int k = 0; k<m_nVexNum - 1; k++)
	{
		min = 0x7FFFFFFF;
		for (int i = 0; i<m_nVexNum; i++)
		{
			if (aVisited[i])//从集合中取一个顶点
			{
				for (int j = 0; j<m_nVexNum; j++)
				{
					if (!aVisited[j])//从不在集合的顶点中取出一个顶点
					{
						if ((m_aAdjmatrix[i][j]<min) && (m_aAdjmatrix[i][j] != 0))
						{
							nVex1 = i;
							nVex2 = j;
							min = m_aAdjmatrix[i][j];//找出最短的边
						}
					}
				}
			}
		}
		//保存最短边的两个顶点
		aPath[k].vex1 = nVex1;
		aPath[k].vex2 = nVex2;
		aPath[k].weight = m_aAdjmatrix[nVex1][nVex2];
		//将两个顶点加入到集合
		aVisited[nVex1] = true;
		aVisited[nVex2] = true;
	}
}
