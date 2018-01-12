#include <stdio.h>
#include <stdlib.h>
#include "GraphIO.h"
#include "Graph.h"
/*void IntializeVertexNodes(Node** vertexList,int numberOfVertices)
{
  for(int vertexNode = 0; vertexNode < numberOfVertices; vertexNode++)
  {
    vertexList[vertexNode] = NewNode(vertexNode);
  }
  return;
}*/

/*void Output(Node** verticesByNumChoice,int numberOfVertices,int* degree,
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
}*/

Graph* ReadGraph()
{
  int numberOfVertices;
  
  if(scanf("%d", &numberOfVertices) != 1)
  {
    printf("Finished Reading all graphs\n");
    return NULL;
  }
  if(numberOfVertices > NMAX)
  {
    printf("Too many vertices in graph, need to increase NMAX and recompile.\n");
    return NULL;
  }
  Graph* graphRead = NewGraph(numberOfVertices);

  for(int vertexId = 0; vertexId < numberOfVertices; vertexId++)
  {
    int vertexDegree;
    if(scanf("%d",&vertexDegree) != 1)
    {
      printf("Error reading in a degree for vertex %d\n", vertexId);
      return NULL;
    }
    
    Vertex* vertexToAdd = NewVertex(vertexId,vertexDegree);
    Node** vertexLists = graphRead->numChoiceVertexList;
    Node* insertedNode = InsertNewNodeAtHead(vertexToAdd, &(vertexLists[vertexToAdd->numChoice]));
    for(int j = 0; j < vertexDegree; j++)
    {
      int neighbour;
      if(scanf("%d", &neighbour) != 1)
      {
        printf("Error Reading in adacency. i = %d j = %d\n",vertexId,j);
        return NULL;
      }
      insertedNode->neighbourIDs[j] = neighbour;
    }
  }
  InitalizeVertexNeighbourhoods(graphRead);
  return graphRead;
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
