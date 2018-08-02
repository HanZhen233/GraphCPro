#include<iostream>
#include"global.h"
#include"Graph.h"
#include"Tourism.h"
using namespace std;

void CTourism::CreateGraph(){

	//��ʼ��ͼ
	m_Graph.Init();
	//����ͼ�Ķ���
//��ȡVEX.txt;
	FILE *pVex = fopen(VEXPATH, "r");
	if (!pVex)
	{
		cerr << "���ļ�ʧ��";
		return;
	}
	//��ȡ������Ŀ��Ŀ
	int nSpotCout = 0;
	fscanf(pVex,"%d\n",&nSpotCout);
	cout << "������Ŀ��"<<nSpotCout << endl;
	//��ȡ������Ϣ
	cout << "-----����------" << endl;
	Vex sVex;
	while (fscanf(pVex, "%d\n%s\n%s\n", &sVex.num, sVex.name, sVex.desc) != -1)
	{
		cout << sVex.num << "--" << sVex.name << endl;
		if (!m_Graph.InsertVex(sVex))
		{
			cout << "�������ʧ��" << endl;
			continue;
		}
	}

		fclose(pVex);
		pVex = NULL;



		//��ȡ��
		FILE *pEdge = fopen(EDGEPATH, "r");
		if (!pEdge)
		{
			cerr << "���ļ�ʧ��";
			return;
		}
		Edge sEdge;
		while (fscanf(pEdge,"%d\t%d\t%d\n",&sEdge.vex1,&sEdge.vex2,&sEdge.weight)!=-1)
		{
			cout << "(" << sEdge.vex1 << "," << sEdge.vex2 << ")	" << sEdge.weight<< endl;
			if (m_Graph.InsertEdge(sEdge)==0)
			{
				cout << "�����ʧ�ܣ�" << endl;
				continue;
			}
		}

		fclose(pEdge);
		pEdge = NULL;
	}


	

void CTourism::GetSpotInfo(){
	cout << "--------��ѯ������Ϣ--------"<<endl;

	//��ʾ�����б�
	int vexNum = m_Graph.GetVexNum();
	for (int i = 0; i < vexNum; i++)
	{
		Vex sVex = m_Graph.GexVex(i);
		cout << sVex.num << "--" << sVex.name << endl;
	}
	//��ѯ����
	cout << "��������Ҫ��ѯ�ľ����ţ�";
	int nVex=0;
	cin >> nVex;
	if (nVex < 0||nVex>=vexNum)
	{
		cout << "�������"<<endl;
		return;
	}
	Vex sVex = m_Graph.GexVex(nVex);
	cout <<sVex.name << endl;
	cout << sVex.desc << endl;

	Edge sEdge[MAX_VERTEX_NUM];
	//��ѯ��������
	cout <<endl<<"-------��Χ����-------"<<endl;
	int nEdgNum = m_Graph.FindEdge(nVex,sEdge);
	for (int i = 0; i < nEdgNum; i++)
	{
		Vex v1 = m_Graph.GexVex(sEdge[i].vex1);
		Vex v2 = m_Graph.GexVex(sEdge[i].vex2);
		cout << v1.name << "->" << v2.name << " " << sEdge[i].weight<<endl<<endl;
	}

	//����FindEdge

}
//���ξ��㵼��

void CTourism::TravelPath() {
	cout <<"---------�������㵼��---------" <<endl<<endl;
	int vexNum = m_Graph.GetVexNum();//������о���
	for (int i = 0; i < vexNum; i++)
	{
		Vex sVex = m_Graph.GexVex(i);
		cout << sVex.num << "-" << sVex.name << endl;

	}
	//���뾰����
	int nVex;
	cout << "��������ʼ������:";
	cin >> nVex;
	if (nVex < 0||nVex>9)
	{
		cout << "�������" << endl;
		return;
	}
	//������������ͼ
	PathList pList = (PathList)malloc(sizeof(Path));
	PathList pHead = pList;
	m_Graph.DFSTraverse(nVex,pList);

	cout << "����·��Ϊ" << endl<<endl;
	int i = 1;
	pList = pHead;
	//����������
	while (pList->next)
	{
		Vex sVex = m_Graph.GexVex(pList->vexs[0]);
		cout << "·��"<< i++<<":"<< sVex.name<< endl;
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
//��ѯ���·��
void CTourism::FindShortPath() {
	cout << "-----------�������·��----------"<<endl;
	int nVexNum = m_Graph.GetVexNum();//������о���
	for (int i = 0; i < nVexNum; i++)
	{
		Vex sVex = m_Graph.GexVex(i);
		cout << sVex.num << "-" << sVex.name << endl;

	}
	int nVexStart,nVexEnd;
	cout << "����������ţ�";
	cin >> nVexStart;
	cout << "�������յ��ţ�";
	cin >> nVexEnd;
	if (nVexStart<0||nVexStart>=nVexNum||nVexEnd<0||nVexEnd>=nVexNum)
	{
		cout << "�������"<< endl;
		return;
	}
	Edge aPath[MAX_VERTEX_NUM];
	int nNum = m_Graph.FindShortPath(nVexStart, nVexEnd, aPath);
	Vex sVex = m_Graph.GexVex(aPath[0].vex1);
	int nLength=0;
	cout << "���·��Ϊ��";
	for (int i = 0; i < nNum; i++)
	{
		sVex = m_Graph.GexVex(aPath[i].vex2);
		cout << "->" << sVex.name;
		nLength += aPath[i].weight;
	}
	cout << endl;
	cout << "���·����"<<nLength << endl;

}

//��·�滮
void CTourism::DesignPath() {
	cout << "---------�����·�滮 ----------" << endl;
		Edge aPath[MAX_VERTEX_NUM];
		m_Graph.FindMinTree(aPath);
		int nVexNum = m_Graph.GetVexNum();
		if (nVexNum==0)
		{
			cout << "���ȴ���ͼ��";
			return ;
		}
		int nAllLength = 0;
		cout << "�������������������·" << endl;
		for (int i = 0; i <nVexNum-1; i++)
		{
			Vex sVex1 = m_Graph.GexVex(aPath[i].vex1);
			Vex sVex2 = m_Graph.GexVex(aPath[i].vex2);
			cout << sVex1.name << "--" << sVex2.name << aPath[i].weight << endl;;
			nAllLength += aPath[i].weight;
		}
		cout <<"�����·�ܳ���Ϊ��" <<nAllLength<<endl ;
}