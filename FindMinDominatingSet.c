#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
        currentVertexNode = graph->numChoiceVertexList[currentListIndex];
        while(currentVertexNode != NULL)
        {
          currentVertexNode->vertex->dominatorDegree = CalculateDominatorDegree(currentVertexNode);
          currentVertexNode = currentVertexNode->next;
        }
    }
}
//TODO: look at making more consice
int DominatorBound(Graph* graph)
{
  int nExtra = 0;
  int toRemove = 0;
  int index = 0;
  int dominator[DEG_MAX+1];
  for(int i = 0; i< DEG_MAX+1; i++)
  {
    dominator[i] = 0;
  }
  Node* vertexNode;
  for(int listIndex = 0;listIndex < DEG_MAX+2; listIndex++)
  {
    vertexNode = graph->numChoiceVertexList[listIndex];
    while(vertexNode != NULL)
    {
      Vertex* vertex = vertexNode->vertex;
      if(vertex->numDominated == 0)
      {
        dominator[vertex->dominatorDegree]++;
      }
      vertexNode= vertexNode->next;
    }
  }
  while(index < 17)
  {
    if(dominator[index] == 0)
    {
      index++;
      continue;
    }
    toRemove = index;
    nExtra = nExtra + 1;
    while(toRemove > 0 && index < 17)
    {
      if(dominator[index] >= toRemove)
      {
        dominator[index] = dominator[index] - toRemove;
        toRemove = 0;
      }
      else
      {
        toRemove = toRemove - dominator[index];
        dominator[index] = 0;
        index++;
      }
    }
  }
  return nExtra;
}
bool CheckNeighbourhoodNumChoice(Node* vertexNode)
{

  for(int i = 0; i< vertexNode->vertex->degree;i++)
  {
    vertexNode = vertexNode->nhood[i];
    if(vertexNode == NULL)
    {
      break;
    } 
    if(vertexNode->vertex->numChoice == 1 && vertexNode->vertex->numDominated == 0)
    {
      return true;
    }
  }
  return false;
}
bool AssumeOutOfDom(Node* vertexNode, Graph* graph)
{
  Vertex* vertex = vertexNode->vertex;
  if(vertex->numChoice == 1 && vertex-> numDominated == 0)
  {
    return false;
  }
  if(CheckNeighbourhoodNumChoice(vertexNode->nhood))
  {
    return false;
  }
  vertex->state = outDomSet;
  vertex->numChoice--;

  Node* neighbourNode;
  Vertex* neighbour;

  for(int i = 0; i< vertex->degree;i++)
  {
    neighbourNode = vertexNode->nhood[i];
    if(vertexNode == NULL)
    {
      break;
    }
    neighbour = neighbourNode->vertex;
    neighbour->numChoice--;
    if(neighbour->state == undecided)
    {
      Node** currentList = &(graph->numChoiceVertexList[(neighbour->numChoice)+1]);
      Node** destList = &(graph->numChoiceVertexList[neighbour->numChoice]);
      ChangeLists(neighbourNode,currentList,destList);
    }
  }

  return true;
}
void FindMinDomSet(Graph* graph, DominatingSet* domSet, DominatingSet* minDomSet)
{
  //if we found a dominating set
  if(domSet->nDominated == graph->numberOfVertices)
  {
    //found a new minimum dominating set
    if(domSet->size < minDomSet->size)
    {
      minDomSet = domSet;
    }
    return;
  }
  //get a vertex with minimum numChoice
  Node* decisionVertexNode = NULL;
  for(int i = 0; i<DEG_MAX+2;i++)
  {
    if(graph->numChoiceVertexList[i] != NULL)
    {
      decisionVertexNode = graph->numChoiceVertexList[i];
      DeleteNodeNoFree(graph->numChoiceVertexList[i],&(graph->numChoiceVertexList[i]));
      break;
    }
  }
  Vertex* decisionVertex = decisionVertexNode->vertex;
  int nExtra = DominatorBound(graph);
  printf("nExtra = %d\n",nExtra);
  if((domSet->size + nExtra) >= minDomSet->size || !AssumeOutOfDom(decisionVertexNode, graph))
  {
    InsertExistingNodeAtHead(decisionVertexNode, &(graph->numChoiceVertexList[decisionVertex->numChoice]));
    printf("returning\n");
    return;
  }

  
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
