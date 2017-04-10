//²âÊÔÎÄ¼ş
#include "GraphMtx.h"

int main()
{
	CGraphMtx<char, int> gh;
	
	gh.insertVtx('A');
	gh.insertVtx('B');
	gh.insertVtx('C');
	gh.insertVtx('D');
	gh.insertVtx('E');
	gh.insertVtx('F');

	gh.insertEdge('A', 'B', 6);
	gh.insertEdge('A', 'C', 1);
	gh.insertEdge('A', 'D', 5);
	gh.insertEdge('B', 'C', 5);
	gh.insertEdge('B', 'E', 3);
	gh.insertEdge('C', 'D', 5);
	gh.insertEdge('C', 'E', 6);	                      
	gh.insertEdge('C', 'F', 4);
	gh.insertEdge('D', 'F', 2);
	gh.insertEdge('E', 'F', 6);
	
	/*cout << gh.getFirstNeighbor('B') << endl;
	cout << gh.getNextNeighbor('D', 'A') << endl;*/

	//gh.showGraph();
	//cout << endl;
	gh.MST_Prime('A');
	//cout << endl;
	//gh.MST_Prime('E');

	gh.MST_Kruskal();
						      
	return 0;
}