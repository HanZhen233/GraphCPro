#ifndef TOURISM 
#define TOURISM 
#include "Graph.h"
class CTourism
{
public:
	void CreateGraph();
	//void CreateSpotInfo();
	void GetSpotInfo();	
	void TravelPath();
	void FindShortPath();
	void  DesignPath();
private:
	CGraph m_Graph;
};

#endif