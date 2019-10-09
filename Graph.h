#include <iostream>
   using namespace std;

#define MaxVertices 50

enum Colour {
	WHITE,
	GRAY,
	BLACK
};

struct Edge {
	int child;
	int weight;
	Edge * nextEdge;
};

struct Vertex {
	string ID;
	Colour colour;
	Edge * firstEdge;
};

struct Graph {
	int numVertices;
	Vertex vertices[MaxVertices+1];
};

Graph * buildGraph (char fileName[]);
void displayGraph (Graph * graph);

void depthFirstTraversal (Graph * G, int s);


void breadthFirstTraversal (Graph * G, int s);


