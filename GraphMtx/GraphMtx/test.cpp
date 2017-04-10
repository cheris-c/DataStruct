//²âÊÔÎÄ¼ş
#include "GraphMtx.h"

int main()
{
	CGraphMtx<char, int> gh;
	
	gh.insertVtx('A');
	gh.insertVtx('B');
	gh.insertVtx('C');
	gh.insertVtx('D');

	gh.insertEdge('A', 'B', 1);
	gh.insertEdge('C', 'B', 1);
	gh.insertEdge('A', 'D', 1);
	gh.insertEdge('C', 'D', 1);
	
	cout << gh.getFirstNeighbor('B') << endl;
	cout << gh.getNextNeighbor('D', 'A') << endl;

	gh.showGraph();

	return 0;
}