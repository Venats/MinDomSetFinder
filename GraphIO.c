#include <stdio.h>
#include <stdlib.h>
#include "GraphIO.h"
void IntializeVertexNodes(Node** vertexList,int numberOfVertices)
{
  for(int vertexNode = 0; vertexNode < numberOfVertices; vertexNode++)
  {
    vertexList[vertexNode] = NewNode(vertexNode);
  }
  return;
}

void Output(Node** verticesByNumChoice,int numberOfVertices,int* degree,
            int outputType,int graphCounter, int minSize, int* minDomSet,int maxDegree)
{
  if(outputType == 1)
  {
    printf("%d ", numberOfVertices);
    Node* vertexNode;
    for(int i =0; i < maxDegree +2; i++)
    {
      vertexNode = verticesByNumChoice[i];
      while(vertexNode != NULL)
      {
        printf("\n%4d ",degree[vertexNode->vertex]);
        for(int j = 0; j < degree[vertexNode->vertex]; j++)
        {
            printf("%4d ",vertexNode->nhood[j]->vertex );
        }
        vertexNode = vertexNode->next;
      }
    }
    printf("\n");
    printf("%d ", minSize);
    //printf("the minimum dominating set was size 8 and had the following vertices: ");
    for(int i = 0; i< minSize; i++)
    {
      printf("%4d ",minDomSet[i]);
    }
    printf("\n");
  }
  else
  {
    printf("%5d %3d %3d\n", graphCounter, numberOfVertices, minSize);
  }
}

int ReadGraph(int* dominatingDegree, int* marker,
              Node** verticesByNumChoice,int* numChoice,int* numberOfVertices,
              int* degree,int maxSize)
{
  if(scanf("%d", numberOfVertices) != 1)
  {
    printf("Finished Reading all graphs");
    return 0;
  }
  Node* vertexList[*numberOfVertices];
  IntializeVertexNodes(vertexList, *numberOfVertices);
  if(*numberOfVertices > maxSize)
  {
    printf("Too many vertices in graph, need to increase NMAX and recompile.");
    return 0;
  }
  for(int currentVertex = 0; currentVertex < *numberOfVertices; currentVertex++)
  {
    int currentDegree;
    marker[currentVertex] = -1;
    if(scanf("%d",&currentDegree) != 1)
    {
      printf("Error reading in a degree for vertex %d", currentVertex);
      return 0;
    }
    dominatingDegree[currentVertex] = currentDegree+1;
    numChoice[currentVertex] = currentDegree +1;
    InsertExistingNodeAtHead(vertexList[currentVertex],&verticesByNumChoice[ numChoice[currentVertex] ]);

    for(int j = 0; j < currentDegree; j++)
    {
      int neighbour;
      if(scanf("%d", &neighbour) != 1)
      {
        printf("Error Reading in adacency. i = %d j = %d",currentVertex,j);
        return 0;
      }
      vertexList[currentVertex]->nhood[j] = vertexList[neighbour];
    }
  }
  return 1;
}
/*int main(int argc, char const *argv[])
 {
  Node* vertexList[10];
  IntializeVertexNodes(vertexList, 10);
  for(int i = 0; i < 10; i++)
  {
    printf("%d\n",vertexList[i]->vertex);
  }
  return 0;
}*/
