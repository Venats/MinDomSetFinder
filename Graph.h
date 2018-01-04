
#ifndef VIEWLINKEDLIST2
#include "VertexLinkedList.h"
#define VIEWLINKEDLIST2


#define NMAX 2187
#define DEG_MAX 16

typedef enum DomState {inDomSet, undecided, outDomSet} DomState;

typedef struct Vertex
{
    DomState state;
    int id;
    int degree;

    int numDominated;
    int numChoice;
    int dominatingDegree;
    int dominatorDegree;

}Vertex;
Vertex* NewVertex(int id, int degree);
typedef struct Graph
{
    int numberOfVertices;
    Node* numChoiceVertexLinkedList[DEG_MAX + 2];

}Graph;
Graph* NewGraph(int numberOfVertices);
#endif