#ifndef GRAPH_H
#define GRAPH_H


typedef struct Path {

	int vexs[20];
	Path *next;
}*PathList;


struct Vex//����ṹ��
{
	int num;
	char name[20];
	char desc[1024];
};
struct Edge//�߽ṹ��
{
    int vex1;
    int vex2;
	int weight;
};

class CGraph
{
public :
	void Init();
	int InsertVex(Vex sVex);
	int InsertEdge(Edge sEdge);
	Vex GexVex(int v);
	int GetVexNum();
	int FindEdge(int v,Edge aEdge[]);
	void DFS(int nVex, bool bVisited[], int &nIndex, PathList &pList);
	void DFSTraverse(int nVex,PathList &pList);
	int  FindShortPath(int nVexStart,int nVexEnd,Edge aPath[]);
	void FindMinTree(Edge aPath[]);	

private:
	int m_nVexNum;
	Vex m_aVexs[20];
	int m_aAdjmatrix[20][20];//�ڽӾ���
};






#endif