#include<iostream>
#include"Graph.h"
#include"global.h"
using namespace std;


void CGraph::Init(){
	for(int i=0;i<20;i++)
	for(int j=0;j<20;j++)
		m_aAdjmatrix[i][j]=0;//��ʼ��ͼ
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



//��ö���

Vex CGraph::GexVex(int v){

	return m_aVexs[v];

}
//����ڽ�����������
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

//���������������
void CGraph::DFS(int nVex, bool bVisited[], int &nIndex, PathList &pList) {
	bVisited[nVex] = true;
	pList->vexs[nIndex++] = nVex;

	int vexNum = 0;//�ж��Ƿ����н���Ƿ�ȫ�������ʹ�
	for (int i = 0; i < m_nVexNum; i++)
	{
		if (bVisited[i])
		{
			vexNum++;
		}
	}
	//������н�㶼�����ʹ�

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

//�������ú���
void CGraph::DFSTraverse(int nVex, PathList & pList) {
	int nIndex = 0;
	bool bVisited[MAX_VERTEX_NUM] = { false };
	DFS(nVex, bVisited, nIndex,pList);

}

//�����·������
int CGraph::FindShortPath(int nVexStart, int nVexEnd, Edge aPath[])
{
	int nShortPath[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//�������·��
	int nShortDistance[MAX_VERTEX_NUM];//������̾���
	bool aVisited[MAX_VERTEX_NUM];//�ж�ĳ�����Ƿ��Ѿ����뵽���·��
								  //��ʼ��
	int v;
	for (v = 0; v<m_nVexNum; v++)
	{
		aVisited[v] = false;
		if (m_aAdjmatrix[nVexStart][v] != 0)
			//��ʼ���ö��㵽�����������̾��룬Ĭ��Ϊ�����ľ���
			nShortDistance[v] = m_aAdjmatrix[nVexStart][v];
		else
			//�������i��nVexStart������������̾�����Ϊ���ֵ
			nShortDistance[v] = 0x7FFFFFFF;
		nShortPath[v][0] = nVexStart;//��ʼ��ΪnVexStart
		for (int j = 1; j<m_nVexNum; j++)
		{
			nShortPath[v][j] = -1;//��ʼ�����·��
		}
	}
	//��ʼ����nVexStart������뵽������
	aVisited[nVexStart] = true;
	int min;

	for (int i = 1; i<m_nVexNum; i++)
	{
		min = 0x7FFFFFFF;
		bool bAdd = false;//�ж��Ƿ��ж�����Լ��뵽������
		for (int j = 0; j<m_nVexNum; j++)
		{
			if (aVisited[j] == false)
			{
				if (nShortDistance[j]<min)
				{
					v = j;//j������nVexStart�������
					min = nShortDistance[j];//j��nVexStart����̾���Ϊmin
					bAdd = true;
				}
			}
		}//���û�ж�����Լ��뵽���ϣ�������ѭ��
		if (bAdd == false)
		{
			break;
		}
		aVisited[v] = true;//������j���뵽����
		nShortPath[v][i] = v;//������j���浽nVexStart��j�����·����
		for (int w = 0; w<m_nVexNum; w++)
		{
			//��w��Ϊ���ȶ������nVexStartͨ��w��ÿ������ľ���
			if (aVisited[w] == false && (min + m_aAdjmatrix[v][w]<nShortDistance[w]) && m_aAdjmatrix[v][w] != 0)
			{
				//���µ�ǰ���·��������
				nShortDistance[w] = min + m_aAdjmatrix[v][w];
				for (int i = 0; i<m_nVexNum; i++)
				{
					//���ͨ��w���ﶥ��i�ľ���Ƚ϶̣���w�����·�����Ƹ�i
					nShortPath[w][i] = nShortPath[v][i];
				}
			}
		}
	}
	int nIndex = 0;
	int nVex1 = nVexStart;
	//�����·������Ϊ�ߵĽṹ������
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

	

//������С������
void CGraph::FindMinTree(Edge aPath[])
{
	bool aVisited[MAX_VERTEX_NUM];//�ж�ĳ�����Ƿ�����С���������㼯����
	for (int i = 0; i<MAX_VERTEX_NUM; i++)
	{
		aVisited[i] = false;
	}
	aVisited[0] = true;//0������뵽������
	int min;
	int nVex1, nVex2;
	for (int k = 0; k<m_nVexNum - 1; k++)
	{
		min = 0x7FFFFFFF;
		for (int i = 0; i<m_nVexNum; i++)
		{
			if (aVisited[i])//�Ӽ�����ȡһ������
			{
				for (int j = 0; j<m_nVexNum; j++)
				{
					if (!aVisited[j])//�Ӳ��ڼ��ϵĶ�����ȡ��һ������
					{
						if ((m_aAdjmatrix[i][j]<min) && (m_aAdjmatrix[i][j] != 0))
						{
							nVex1 = i;
							nVex2 = j;
							min = m_aAdjmatrix[i][j];//�ҳ���̵ı�
						}
					}
				}
			}
		}
		//������̱ߵ���������
		aPath[k].vex1 = nVex1;
		aPath[k].vex2 = nVex2;
		aPath[k].weight = m_aAdjmatrix[nVex1][nVex2];
		//������������뵽����
		aVisited[nVex1] = true;
		aVisited[nVex2] = true;
	}
}
