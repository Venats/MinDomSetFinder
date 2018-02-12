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
  int vertexIDs[NMAX+1];
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
  //printf("setting dominator degree of vertex %d to %d\n", vertex->id, dominatorDegree);
  return dominatorDegree;
}
int CalculateDominatingDegree(Node* vertexNode)
{
  Vertex* vertex = vertexNode->vertex;
  int dominatingDegree = 0;
  if(vertex->numDominated == 0)
  {
    dominatingDegree++;
  }
  for(int i =0; i< vertex->degree; i++)
  {
    Vertex* neighbour = vertexNode->nhood[i]->vertex;
    if(vertex->numDominated == 0)
    {
      dominatingDegree++;
    }
  }
  return dominatingDegree;
}
void InitalizeVariables(Graph* graph, DominatingSet* domSet, DominatingSet* minDomSet)
{
    minDomSet->nDominated = graph->numberOfVertices;
    minDomSet->size = graph->numberOfVertices;
    domSet->size = 0;
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
    printf("Finished initialization\n");
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
  while(index < DEG_MAX+1)
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
    if(vertexNode->vertex->numChoice == 1)
    {
      return true;
    }
  }
  return false;
}
void CopyDomSet(DominatingSet* destination, DominatingSet* source)
{
  destination->size = source->size;
  destination->nDominated = source->nDominated;
  for(int i = 0; i < source->size; i++)
  {
    destination->vertexIDs[i] = source->vertexIDs[i];
  }
}
bool AssumeOutOfDom(Node* vertexNode, Graph* graph)
{
  Vertex* vertex = vertexNode->vertex;
  if(vertex->numChoice == 1 && vertex-> numDominated == 0)
  {
    return false;
  }
  if(CheckNeighbourhoodNumChoice(vertexNode))
  {
    return false;
  }
  vertex->state = outDomSet;
  vertex->numChoice--;

  Node* neighbourNode;
  Vertex* neighbour;
  //adjust numchoice for neighbour vertices
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
  //because the current vertex we are looking at no longer undecided this affects the dominator degree
  //of all vertices distance 2 away from the vertex
  Node** distanceTwoNhood = GetDistanceTwoNeighbourhood(vertexNode);
  Node* d2Neighbour;
  for(int i = 0; i < DEG_MAX*DEG_MAX; i++)
  {
    d2Neighbour = distanceTwoNhood[i];
    if(d2Neighbour == NULL)
    {
      break;
    }
    CalculateDominatorDegree(d2Neighbour);
  }
  free(distanceTwoNhood);
  return true;
}
//undoes everything AssumeOutOfDom does
void ChangeFromOutToUndecided(Node* vertexNode ,Graph* graph)
{
  Vertex* vertex = vertexNode->vertex;
  vertex->state = undecided;
  vertex->numChoice++;

  Node* neighbourNode;
  Vertex* neighbour;
  //adjust numchoice for neighbour vertices
  for(int i = 0; i< vertex->degree;i++)
  {
    neighbourNode = vertexNode->nhood[i];
    if(vertexNode == NULL)
    {
      break;
    }
    neighbour = neighbourNode->vertex;
    neighbour->numChoice++;
    if(neighbour->state == undecided)
    {
      Node** currentList = &(graph->numChoiceVertexList[(neighbour->numChoice)-1]);
      Node** destList = &(graph->numChoiceVertexList[neighbour->numChoice]);
      ChangeLists(neighbourNode,currentList,destList);
    }
  }
  Node** distanceTwoNhood = GetDistanceTwoNeighbourhood(vertexNode);
  Node* d2Neighbour;
  for(int i = 0; i < DEG_MAX*DEG_MAX; i++)
  {
    d2Neighbour = distanceTwoNhood[i];
    if(d2Neighbour == NULL)
    {
      break;
    }
    CalculateDominatorDegree(d2Neighbour);
  }
  free(distanceTwoNhood);
  return;
}
void AssumeInDom(Node* vertexNode, DominatingSet* domSet)
{
  Vertex* vertex = vertexNode->vertex;

  vertex->state = inDomSet;
  domSet->vertexIDs[domSet->size] = vertex->id;
  domSet->size++;
  vertex->numDominated++;
  if(vertex->numDominated == 1)
  {
    domSet->nDominated++;
  }
  for(int i = 0; i<vertex->degree;i++)
  {
    Vertex* neighbour = vertexNode->nhood[i]->vertex;
    neighbour->numDominated++;
    if(neighbour->numDominated == 1)
    {
      domSet->nDominated++;
    }
  }
  Node** distanceTwoNhood = GetDistanceTwoNeighbourhood(vertexNode);
  Node* d2Neighbour;
  //recalculate dominating degree
  for(int i = 0; i < DEG_MAX*DEG_MAX; i++)
  {
    d2Neighbour = distanceTwoNhood[i];
    if(d2Neighbour == NULL)
    {
      break;
    }
    d2Neighbour->vertex->dominatingDegree = CalculateDominatingDegree(d2Neighbour);
  }
  //recalculate dominator degree
  for(int i = 0; i < DEG_MAX*DEG_MAX; i++)
  {
    d2Neighbour = distanceTwoNhood[i];
    if(d2Neighbour == NULL)
    {
      break;
    }
    d2Neighbour->vertex->dominatingDegree = CalculateDominatorDegree(d2Neighbour);
  }
  free(distanceTwoNhood);
}
void ChangeFromInToUndecided(Node* vertexNode,DominatingSet* domSet)
{
  Vertex* vertex = vertexNode->vertex;

  vertex->state = undecided;
  domSet->size--;
  domSet->vertexIDs[domSet->size] = -1;
  vertex->numDominated--;
  if(vertex->numDominated == 0)
  {
    domSet->nDominated--;
  }
  for(int i = 0; i<vertex->degree;i++)
  {
    Vertex* neighbour = vertexNode->nhood[i]->vertex;
    neighbour->numDominated--;
    if(neighbour->numDominated == 0)
    {
      domSet->nDominated--;
    }
  }
  Node** distanceTwoNhood = GetDistanceTwoNeighbourhood(vertexNode);
  Node* d2Neighbour;
  //recalculate dominating degree
  for(int i = 0; i < DEG_MAX*DEG_MAX; i++)
  {
    d2Neighbour = distanceTwoNhood[i];
    if(d2Neighbour == NULL)
    {
      break;
    }
    d2Neighbour->vertex->dominatingDegree = CalculateDominatingDegree(d2Neighbour);
  }
  //recalculate dominator degree
  for(int i = 0; i < DEG_MAX*DEG_MAX; i++)
  {
    d2Neighbour = distanceTwoNhood[i];
    if(d2Neighbour == NULL)
    {
      break;
    }
    d2Neighbour->vertex->dominatingDegree = CalculateDominatorDegree(d2Neighbour);
  }
  free(distanceTwoNhood);
}
void FindMinDomSet(Graph* graph, DominatingSet* domSet, DominatingSet* minDomSet)
{
  //if we found a dominating set
  printf("ndominated = %d, numberOfVertices = %d\n",domSet->nDominated,graph->numberOfVertices);
  printf("Current dominating set is: \n");
  for(int i =0 ; i< domSet->size; i++)
    {
      printf(",%d",domSet->vertexIDs[i]);
    }
  printf("\n");
  if(domSet->nDominated == graph->numberOfVertices)
  {
    //found a new minimum dominating set
    printf("domSet found has size %d current minDomSet has size %d\n", domSet->size, minDomSet->size);
    if(domSet->size < minDomSet->size)
    {
      printf("copying new minimum dominating set\n");
      CopyDomSet(minDomSet,domSet);

      printf("min dominating set is: \n");
      for(int i =0 ; i< minDomSet->size; i++)
      {
        printf(",%d",minDomSet->vertexIDs[i]);
      }
      printf("\n");
    }
    printf("found a dominating set\n");
    return;
  }
  //get a vertex with minimum numChoice
  Node* decisionVertexNode = NULL;
  //printf("looking for next vertex\n");
  for(int i = 0; i<DEG_MAX+2;i++)
  {
    if(graph->numChoiceVertexList[i] != NULL)
    {
      decisionVertexNode = graph->numChoiceVertexList[i];
      DeleteNodeNoFree(graph->numChoiceVertexList[i],&(graph->numChoiceVertexList[i]));
      break;
    }
  }
  if(decisionVertexNode == NULL)
  {
    return;
  }
  Vertex* decisionVertex = decisionVertexNode->vertex;
  int nExtra = DominatorBound(graph);
  //printf("looking at vertex %d, nExtra = %d\n",decisionVertex->id, nExtra);
  if((domSet->size + nExtra) >= minDomSet->size )
  {
    InsertExistingNodeAtHead(decisionVertexNode, &(graph->numChoiceVertexList[decisionVertex->numChoice]));
    //printf("returning\n");
    return;
  }

  if(AssumeOutOfDom(decisionVertexNode, graph))
  {
    //printf("Assuming out of dom recurrsive call\n");
    FindMinDomSet(graph, domSet, minDomSet);
    ChangeFromOutToUndecided(decisionVertexNode,graph);
  }
  //printf("assume in domSet\n");
  AssumeInDom(decisionVertexNode, domSet);
  printf("vertex %d is now in the domset\n",decisionVertex->id);
  FindMinDomSet(graph,domSet,minDomSet);
  printf("going from in to undecided \n");
  ChangeFromInToUndecided(decisionVertexNode, domSet);

  InsertExistingNodeAtHead(decisionVertexNode,&(graph->numChoiceVertexList[decisionVertex->numChoice]));
  return;
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
    printf("min dominating set is: \n");
    for(int i =0 ; i< minDomSet.size; i++)
    {
      printf(",%d",minDomSet.vertexIDs[i]);
    }
    printf("\n");
    FreeGraph(graph);
    printf("freeing graph\n");
    graph = ReadGraph();


  }
  return 0;
}
