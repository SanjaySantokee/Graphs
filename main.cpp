#include <iostream>
#include <cstring>
#include "Graph.h"
#include "Queue.h"
   using namespace std;
   
int main() {
	
	char fileName [20];
	Graph * graph;
	
	strcpy(fileName, "graph.txt");
	
	graph = buildGraph(fileName);
	
	displayGraph(graph);
	
	depthFirstTraversal(graph, 1); //starts at vertex 1
	
	cout<<"____________________________________________"<<endl;
	
	breadthFirstTraversal(graph, 1);
	
	return 0;
}
