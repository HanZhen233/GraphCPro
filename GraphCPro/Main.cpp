#include<iostream>
#include"global.h"
#include"Tourism.h"
using namespace std;


int main(){

	int i=-1;
	CTourism tourism;
	while(i!=0){
    cout<<"==========������Ϣ����ϵͳ=========="<<endl;
	cout<<"1.������������ͼ"<<endl;
	cout<<"2.��ѯ������Ϣ"<<endl;
	cout<<"3.���ξ��㵼��"<<endl;
	cout<<"4.�������·��"<<endl;
	cout<<"5.�����·�滮"<<endl;
	cout<<"0.�˳�"<<endl;
	cout<<"�����������ţ�0-5����"<<endl;
	cin>>i;
	switch(i){
	case 1:
		tourism.CreateGraph();
		break;
	case 2:
		tourism.GetSpotInfo();
		break;
	case 3:
		tourism.TravelPath();
		break;
	case 4:
		tourism.FindShortPath();
		break;
	case 5:
		tourism.DesignPath();
		break;
	case 0:
		exit(0);
	}
	
	
	}
	


return 0;
}