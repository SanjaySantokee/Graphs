#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Graph.h"
#include "Queue.h"
   using namespace std;
   
Vertex newVertex (string ID) {
	
	Vertex vertex;
	
	vertex.ID = ID;
	vertex.colour = WHITE;
	vertex.firstEdge = NULL;
	
	return vertex;
}


Edge * newEdge (int child, int weight) {
	
	Edge * edge = new Edge;
	
	edge->child = child;
	edge->weight = weight;
	edge->nextEdge = NULL;
	
	return edge;
}

int findVertex (Graph * graph, string ID) {
	for (int i = 1; i <= graph->numVertices; i = i + 1) {
		if (graph->vertices[i].ID == ID)
			return i; 	// return location of vertex in array
	}
	return -1;			// -1 indicates that a vertex with the ID was not found.
}


// This function adds an edge X->Y to a graph, with a given weight.

void addEdge (Graph * graph, string X_ID, string Y_ID, int weight) {
	
	int X_Location, Y_Location;
	Edge * edge;
	
	X_Location = findVertex (graph, X_ID);
	Y_Location = findVertex (graph, Y_ID);
	
	if (X_Location == -1 || Y_Location == -1) {
		cout << "Edge does not exist: " << X_ID << "->" << Y_ID << endl;
		exit(1);
	}
	
	edge = newEdge (Y_Location, weight);
	
	Edge * firstEdge;
	Edge * previous;
	Edge * current;
	
	firstEdge = graph->vertices[X_Location].firstEdge;
	previous = current = firstEdge;
	
	while (current != NULL && Y_ID > graph->vertices[current->child].ID) {
		previous = current;
		current = current->nextEdge;
	}
	
	if (previous == current) {
		edge->nextEdge = graph->vertices[X_Location].firstEdge;
		graph->vertices[X_Location].firstEdge = edge;
	}
	else {
		edge->nextEdge = current;
		previous->nextEdge = edge;
	}
	
}

	
Graph * buildGraph (char fileName[]) {
	
	ifstream graphFile;
	
	graphFile.open (fileName);
	
	if (!graphFile.is_open()) {
		cout << "Error opening graph input file : " << fileName;
		cout << ". Aborting ..." << endl;
		return NULL;
	}
	
	Graph * newGraph = new Graph;
	
	// Read number of vertices from the first line of the file.

	int numVertices;
	
	graphFile >> numVertices;

	newGraph->numVertices = numVertices;
	
	// Read name of each vertex (vertexID) from the second line of the file
	//  and store in array of vertices.
	
	string vertexID; 
	
	for (int v = 1; v <= numVertices; v = v + 1) {
		graphFile >> vertexID;
		newGraph->vertices[v] = newVertex (vertexID);
	}
	
	// Read edges from each vertex from remaining lines of the file and
	//  store in linked list of edges connected to array location for the
	//  "parent" vertex. 
	
	int numEdges;			// number of edges from vertexID
	string adjacentID;		// ID of adjacent vertex
	int edgeWeight;			// weight of edge
	
	for (int v = 1; v <= numVertices; v = v + 1) {
		graphFile >> vertexID >> numEdges;
		for (int e = 1; e <= numEdges; e = e + 1) {
			graphFile >> adjacentID >> edgeWeight;
			addEdge (newGraph, vertexID, adjacentID, edgeWeight);
		}
	}
	
	graphFile.close();
	
	return newGraph;
	
}

void displayGraph (Graph * graph) {
	int numVertices;
	Edge * edge;
	
	numVertices = graph->numVertices;
		
	for (int v = 1; v <= numVertices; v = v + 1) {
		cout << graph->vertices[v].ID << ": ";
		edge = graph->vertices[v].firstEdge;
		while (edge != NULL) {
			cout << graph->vertices[edge->child].ID << " " << edge->weight << " ";
			edge = edge->nextEdge;
		}
		cout << endl;
	}
	
}

void dfTraverse(Graph * G, int s){
	static int time = 0; //retains its value between calls
	
	cout<< G->vertices[s].ID;
	G->vertices[s].colour = GRAY;	//currently processing
	
	Edge * edge =  G->vertices[s].firstEdge;
	
	//goes through the edges in adjecency list for that vertex and starts traversal it if it isnt processed yet (WHITE)
	while (edge!=NULL){
		if( G->vertices[ edge->child ].colour == WHITE)
			dfTraverse(G, edge->child);
		edge= edge->nextEdge;
	}
	
	G->vertices[s].colour = BLACK; //done processing
}


void depthFirstTraversal(Graph * G, int s){
	//do DF starting from s
	// start at vertex 7 ...s=7
	//color everything white
	//output id for starting vertex
	//colour everything white
	for (int h=1; h <= G->numVertices; h++)
		G->vertices[h].colour = WHITE;
	
	cout<<"DF starts from :"<< G->vertices[s].ID<<endl;
	
	dfTraverse(G,s); //starts traversal from s
	
	//check if any white remain
	for (int h=1; h <= G->numVertices; h++)
		if ( G->vertices[h].colour == WHITE )
			dfTraverse(G,h);
}


void breadthFirstTraversal (Graph * G, int s){
	
	
	for (int h=1; h <= G->numVertices; h++)
		G->vertices[h].colour = WHITE;
	
	
	G->vertices[s].colour = GRAY;	//currently processing
	Queue * q= initQueue();
	enqueue(q,s);
	cout<<"BF starts from :"<< G->vertices[s].ID<<endl;
		
	//goes through the edges in adjecency list for that vertex and starts traversal it if it isnt processed yet (WHITE)
	while (!isEmptyQueue(q)){
		
		int aParent= dequeue(q);
		cout<< G->vertices[ aParent ].ID;
		
		Edge * edge =  G->vertices[aParent].firstEdge;
		
		while( edge!= NULL){
			
			if( G->vertices[ edge->child ].colour == WHITE){
				
				G->vertices[ edge->child ].colour = GRAY;
				enqueue(q, edge->child);
				
			}
			edge= edge->nextEdge;
		}//end while edge
		
		G->vertices[aParent].colour = BLACK;
		
	}//end while !emptyQ
	cout<<endl;	
	
}









