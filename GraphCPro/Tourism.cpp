#include<iostream>
#include"global.h"
#include"Graph.h"
#include"Tourism.h"
using namespace std;

void CTourism::CreateGraph(){

	//初始化图
	m_Graph.Init();
	//设置图的顶点
//读取VEX.txt;
	FILE *pVex = fopen(VEXPATH, "r");
	if (!pVex)
	{
		cerr << "打开文件失败";
		return;
	}
	//读取景点数目数目
	int nSpotCout = 0;
	fscanf(pVex,"%d\n",&nSpotCout);
	cout << "顶点数目："<<nSpotCout << endl;
	//读取顶点信息
	cout << "-----顶点------" << endl;
	Vex sVex;
	while (fscanf(pVex, "%d\n%s\n%s\n", &sVex.num, sVex.name, sVex.desc) != -1)
	{
		cout << sVex.num << "--" << sVex.name << endl;
		if (!m_Graph.InsertVex(sVex))
		{
			cout << "新增结点失败" << endl;
			continue;
		}
	}

		fclose(pVex);
		pVex = NULL;



		//读取边
		FILE *pEdge = fopen(EDGEPATH, "r");
		if (!pEdge)
		{
			cerr << "打开文件失败";
			return;
		}
		Edge sEdge;
		while (fscanf(pEdge,"%d\t%d\t%d\n",&sEdge.vex1,&sEdge.vex2,&sEdge.weight)!=-1)
		{
			cout << "(" << sEdge.vex1 << "," << sEdge.vex2 << ")	" << sEdge.weight<< endl;
			if (m_Graph.InsertEdge(sEdge)==0)
			{
				cout << "插入边失败！" << endl;
				continue;
			}
		}

		fclose(pEdge);
		pEdge = NULL;
	}


	

void CTourism::GetSpotInfo(){
	cout << "--------查询景点信息--------"<<endl;

	//显示景点列表
	int vexNum = m_Graph.GetVexNum();
	for (int i = 0; i < vexNum; i++)
	{
		Vex sVex = m_Graph.GexVex(i);
		cout << sVex.num << "--" << sVex.name << endl;
	}
	//查询景点
	cout << "请输入您要查询的景点编号：";
	int nVex=0;
	cin >> nVex;
	if (nVex < 0||nVex>=vexNum)
	{
		cout << "输入错误"<<endl;
		return;
	}
	Vex sVex = m_Graph.GexVex(nVex);
	cout <<sVex.name << endl;
	cout << sVex.desc << endl;

	Edge sEdge[MAX_VERTEX_NUM];
	//查询附近景点
	cout <<endl<<"-------周围景点-------"<<endl;
	int nEdgNum = m_Graph.FindEdge(nVex,sEdge);
	for (int i = 0; i < nEdgNum; i++)
	{
		Vex v1 = m_Graph.GexVex(sEdge[i].vex1);
		Vex v2 = m_Graph.GexVex(sEdge[i].vex2);
		cout << v1.name << "->" << v2.name << " " << sEdge[i].weight<<endl<<endl;
	}

	//调用FindEdge

}
//旅游景点导航

void CTourism::TravelPath() {
	cout <<"---------景区景点导航---------" <<endl<<endl;
	int vexNum = m_Graph.GetVexNum();//输出所有景点
	for (int i = 0; i < vexNum; i++)
	{
		Vex sVex = m_Graph.GexVex(i);
		cout << sVex.num << "-" << sVex.name << endl;

	}
	//输入景点编号
	int nVex;
	cout << "请输入起始顶点编号:";
	cin >> nVex;
	if (nVex < 0||nVex>9)
	{
		cout << "输入出错！" << endl;
		return;
	}
	//遍历景区景点图
	PathList pList = (PathList)malloc(sizeof(Path));
	PathList pHead = pList;
	m_Graph.DFSTraverse(nVex,pList);

	cout << "导游路线为" << endl<<endl;
	int i = 1;
	pList = pHead;
	//输入便利结果
	while (pList->next)
	{
		Vex sVex = m_Graph.GexVex(pList->vexs[0]);
		cout << "路线"<< i++<<":"<< sVex.name<< endl;
		for (int j = 0; j < vexNum; j++)
		{
			sVex = m_Graph.GexVex(pList->vexs[j]);	
			cout << "->" << sVex.name ;

		}
		cout << endl ;

		Path *tmp = pList;
		pList = pList->next;
		free(tmp);

	}
	free(pList);
	pList = NULL;
	pHead = NULL;

}
//查询最短路径
void CTourism::FindShortPath() {
	cout << "-----------搜索最短路径----------"<<endl;
	int nVexNum = m_Graph.GetVexNum();//输出所有景点
	for (int i = 0; i < nVexNum; i++)
	{
		Vex sVex = m_Graph.GexVex(i);
		cout << sVex.num << "-" << sVex.name << endl;

	}
	int nVexStart,nVexEnd;
	cout << "请输入起点编号：";
	cin >> nVexStart;
	cout << "请输入终点编号：";
	cin >> nVexEnd;
	if (nVexStart<0||nVexStart>=nVexNum||nVexEnd<0||nVexEnd>=nVexNum)
	{
		cout << "输入错误！"<< endl;
		return;
	}
	Edge aPath[MAX_VERTEX_NUM];
	int nNum = m_Graph.FindShortPath(nVexStart, nVexEnd, aPath);
	Vex sVex = m_Graph.GexVex(aPath[0].vex1);
	int nLength=0;
	cout << "最短路径为：";
	for (int i = 0; i < nNum; i++)
	{
		sVex = m_Graph.GexVex(aPath[i].vex2);
		cout << "->" << sVex.name;
		nLength += aPath[i].weight;
	}
	cout << endl;
	cout << "最短路径："<<nLength << endl;

}

//电路规划
void CTourism::DesignPath() {
	cout << "---------铺设电路规划 ----------" << endl;
		Edge aPath[MAX_VERTEX_NUM];
		m_Graph.FindMinTree(aPath);
		int nVexNum = m_Graph.GetVexNum();
		if (nVexNum==0)
		{
			cout << "请先创建图！";
			return ;
		}
		int nAllLength = 0;
		cout << "在以下两个景点铺设电路" << endl;
		for (int i = 0; i <nVexNum-1; i++)
		{
			Vex sVex1 = m_Graph.GexVex(aPath[i].vex1);
			Vex sVex2 = m_Graph.GexVex(aPath[i].vex2);
			cout << sVex1.name << "--" << sVex2.name << aPath[i].weight << endl;;
			nAllLength += aPath[i].weight;
		}
		cout <<"铺设电路总长度为：" <<nAllLength<<endl ;
}