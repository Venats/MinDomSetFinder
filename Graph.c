#include <stdlib.h>
#include "Graph.h"
#include "VertexLinkedList.h"
Graph* NewGraph(int numberOfVertices)
{
    Graph* newGraph = (Graph*)malloc(sizeof(struct Graph));
    newGraph->numberOfVertices = numberOfVertices;
    for(int i = 0; i<DEG_MAX +2; i++)
    {
        newGraph->numChoiceVertexLinkedList[i] = NULL;
    }
}
Node* FindVertexNode(int toFind, Graph* graph)
{
    Node* currentVertexNode;
    for(int currentListIndex = 0;currentListIndex < DEG_MAX+2; currentListIndex++)
    {
        currentVertexNode = graph->numChoiceVertexLinkedList[currentListIndex];
        while(currentVertexNode != NULL)
        {
            if(currentVertexNode->vertex->id == toFind)
            {
                break;
            }
            currentVertexNode = currentVertexNode->next;
        }
    }
  return currentVertexNode;
}
void InitalizeVertexNeighbourhoods(Graph* graph)
{
    
    for(int currentListIndex = 0;currentListIndex < DEG_MAX+2; currentListIndex++)
    {
        Node* currentVertexNode = graph->numChoiceVertexLinkedList[currentListIndex];
        while(currentVertexNode != NULL)
        {
            for(int neighbour = 0; neighbour < currentVertexNode->vertex->degree ; neighbour++)
            {
                int neighbourID = currentVertexNode->neighbourIDs[neighbour];
                Node* neighbourNode = FindVertexNode(neighbourID,graph);
                currentVertexNode->nhood[neighbour] = neighbourNode;
            }
            currentVertexNode = currentVertexNode->next;
        }
    }
}
void FreeGraph(Graph* graph)
{
  for(int i = 0; i< DEG_MAX + 2; i++)
  {
    Node* currentNode = graph->numChoiceVertexLinkedList[i];
    while(currentNode != NULL)
    {
      Node* nextNode = currentNode->next;
      free(currentNode->vertex);
      free(currentNode->nhood);
      free(currentNode->neighbourIDs);
      free(currentNode);
      currentNode = nextNode;
    }
    graph->numChoiceVertexLinkedList[i] = NULL;
  }
}