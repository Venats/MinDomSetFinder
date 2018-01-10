
#ifndef GRAPH
#define GRAPH

#include "VertexLinkedList.h"

#define NMAX 2187
#define DEG_MAX 16


typedef struct Graph
{
    int numberOfVertices;
    Node* numChoiceVertexLinkedList[DEG_MAX + 2];

}Graph;
Graph* NewGraph(int numberOfVertices);
Node* FindVertexNode(int toFind, Graph* graph);
void InitalizeVertexNeighbourhoods(Graph* graph);
void FreeGraph(Graph* graph);
#endif