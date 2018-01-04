#include <stdlib.h>
#include "Graph.h"
#include "VertexLinkedList.h"
Vertex* NewVertex(int id, int degree)
{
    Vertex* newVertex = (struct Vertex*)malloc(sizeof(struct Vertex));
    newVertex->id = id;
    newVertex->degree = degree;
    newVertex->state = undecided;

    newVertex->numDominated = 0;
    newVertex->numChoice = degree+1;
    newVertex->dominatingDegree = degree+1;
    newVertex->dominatorDegree = 0;

    return newVertex;
}

Graph* NewGraph(int numberOfVertices)
{
    Graph* newGraph = (Graph*)malloc(sizeof(struct Graph));
    newGraph->numberOfVertices = numberOfVertices;
    for(int i = 0; i<DEG_MAX +2; i++)
    {
        newGraph->numChoiceVertexLinkedList[i] = NULL;
    }
}
