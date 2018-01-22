#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "Graph.h"
#include "VertexLinkedList.h"
Graph* NewGraph(int numberOfVertices)
{
    Graph* newGraph = (Graph*)malloc(sizeof(struct Graph));
    newGraph->numberOfVertices = numberOfVertices;
    for(int i = 0; i<DEG_MAX +2; i++)
    {
        newGraph->numChoiceVertexList[i] = NULL;
    }
}
Node* FindVertexNode(int toFind, Graph* graph)
{
    Node* currentVertexNode;
    for(int currentListIndex = 0;currentListIndex < DEG_MAX+2; currentListIndex++)
    {
        currentVertexNode = graph->numChoiceVertexList[currentListIndex];
        while(currentVertexNode != NULL)
        {
            if(currentVertexNode->vertex->id == toFind)
            {
                return currentVertexNode;
            }
            currentVertexNode = currentVertexNode->next;
        }
    }
    return NULL;
}
void InitalizeVertexNeighbourhoods(Graph* graph)
{
    for(int currentListIndex = 0;currentListIndex < DEG_MAX+2; currentListIndex++)
    {
        Node* currentVertexNode = graph->numChoiceVertexList[currentListIndex];
        while(currentVertexNode != NULL)
        {
            for(int neighbour = 0; neighbour < currentVertexNode->vertex->degree ; neighbour++)
            {
                int neighbourID = currentVertexNode->neighbourIDs[neighbour];
                Node* neighbourNode = FindVertexNode(neighbourID,graph);
                if(neighbourNode == NULL)
                {
                    printf("problem finding vertex %d\n", neighbourID);
                    exit(0);
                }
                currentVertexNode->nhood[neighbour] = neighbourNode;
            }
            currentVertexNode = currentVertexNode->next;
        }
    }
}

bool NotInList(Node** nodeList,int size,Node* nodeToCheck)
{
  Node* nodeInList;
  for(int i = 0; i < size; i++)
  {
    nodeInList = nodeList[i];
    if(nodeInList == nodeToCheck)
    {
      return false;
    }
  }
  return true;
}

Node** GetDistanceTwoNeighbourhood(Node* vertexNode)
{
  Node** distanceTwoNhood = (struct Node**)malloc(sizeof(struct Node*) * DEG_MAX * DEG_MAX);
  Vertex* vertex = vertexNode->vertex;
  int numNeighbours = vertex->degree;
  int sizeOfDistTwoNhood = 0;
  for(int neighbour = 0; neighbour < numNeighbours; neighbour++)
  {
    distanceTwoNhood[neighbour] = vertexNode->nhood[neighbour];
    sizeOfDistTwoNhood++;
  }

  for(int i = 0; i < numNeighbours; i++)
  {
    Node* adjacentNeighbour = distanceTwoNhood[i];
    Vertex* adjacentVertex = adjacentNeighbour->vertex;

    for(int distTwoNeigh = 0; distTwoNeigh < adjacentVertex->degree; distTwoNeigh++)
    {
      Node* neighbour = adjacentNeighbour->nhood[distTwoNeigh];
      if(NotInList(distanceTwoNhood,sizeOfDistTwoNhood, neighbour) && neighbour != vertexNode)
      {
        distanceTwoNhood[sizeOfDistTwoNhood] = neighbour;
        sizeOfDistTwoNhood++;
      }
    }
  }
  return distanceTwoNhood;
}

void FreeGraph(Graph* graph)
{
  for(int i = 0; i< DEG_MAX + 2; i++)
  {
    Node* currentNode = graph->numChoiceVertexList[i];
    while(currentNode != NULL)
    {
      Node* nextNode = currentNode->next;
      free(currentNode->vertex);
      free(currentNode->nhood);
      free(currentNode->neighbourIDs);
      free(currentNode);
      currentNode = nextNode;
    }
    graph->numChoiceVertexList[i] = NULL;
  }
}