#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "GraphIO.h"
#include "VertexLinkedList.h"
#include "Util.h"
#include "Graph.h"
typedef struct DominatingSet
{
  int size;
  int nDominated;
  int vertexIDs[NMAX];
}DominatingSet;

int GetOutputType(int argc, char const *argv[])
{
  int outputType = -1;
  if(argc != 2 )
  {
    printf("error program needs 1 argument, 0 for non verbose output, 1 for verbose output\n");
    return outputType;
  }
  if(strcmp(argv[1],"0") == 0) outputType = 0;
  else if(strcmp(argv[1],"1") == 0) outputType = 1;
  else
  {
      printf("Bad argument.\n");
      return outputType;
  }
  return outputType;
}
int CalculateDominatorDegree(Node* vertexNode)
{
  int dominatorDegree = 0;
  Vertex* vertex = vertexNode->vertex;
  if(vertex->state == undecided)
  {
    dominatorDegree = vertex->dominatingDegree;
  }
  Node* neighbourNode = vertexNode->nhood[0];
  for(int neighbourIndex = 0; neighbourIndex < vertex->degree; neighbourIndex++)
  {
    Node* neighbourNode = vertexNode->nhood[neighbourIndex];
    Vertex* neighbourVertex = neighbourNode->vertex;
    if(neighbourVertex->state == undecided && neighbourVertex->dominatingDegree > dominatorDegree)
    {
      dominatorDegree = neighbourVertex->dominatingDegree;
    }
  }
  printf("setting dominator degree of vertex %d to %d\n", vertex->id, dominatorDegree);
  return dominatorDegree;
}
void InitalizeVariables(Graph* graph, DominatingSet* domSet, DominatingSet* minDomSet)
{
    //nDominated = graph->numberOfVertice;
    minDomSet->size = graph->numberOfVertices;
    for(int vertexID = 0; vertexID < minDomSet->size;vertexID++)
    {
       minDomSet->vertexIDs[vertexID] = vertexID;
    };
    Node* currentVertexNode;
    for(int currentListIndex = 0;currentListIndex < DEG_MAX+2; currentListIndex++)
    {
        currentVertexNode = graph->numChoiceVertexLinkedList[currentListIndex];
        while(currentVertexNode != NULL)
        {
          currentVertexNode->vertex->dominatorDegree = CalculateDominatorDegree(currentVertexNode);
          currentVertexNode = currentVertexNode->next;
        }
    }
}
void FindMinDomSet(Graph* graph, DominatingSet* domSet, DominatingSet* minDomSet)
{

}
int main(int argc, char const *argv[])
{
  int outputType;
  int graphCounter = 0;

  outputType = GetOutputType(argc, argv);
  if(outputType == -1) return 0;
  Graph* graph =  ReadGraph();
  DominatingSet domSet;
  DominatingSet minDomSet;
  while(graph != NULL)
  {
    InitalizeVariables(graph,&domSet,&minDomSet);
    FindMinDomSet(graph,&domSet,&minDomSet);
    FreeGraph(graph);
    graph = ReadGraph();
  }
  return 0;
}
