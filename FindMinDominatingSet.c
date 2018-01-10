#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "GraphIO.h"
#include "VertexLinkedList.h"
#include "Util.h"
#include "Graph.h"

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
int main(int argc, char const *argv[])
{
  int outputType;
  int graphCounter = 0;

  outputType = GetOutputType(argc, argv);
  if(outputType == -1) return 0;
  Graph* graph =  ReadGraph();
  while(graph != NULL)
  {
    for(int currentListIndex = 0;currentListIndex < DEG_MAX+2; currentListIndex++)
    {
        Node* currentVertexNode = graph->numChoiceVertexLinkedList[currentListIndex];
        while(currentVertexNode != NULL)
        {
            printf("read a non-null vertexNode \n");
            printf("vertex pointer is %p\n",currentVertexNode->vertex);
            printf("node %d has neighbours:\n", currentVertexNode->vertex->id);
            for(int neighbour = 0; neighbour < currentVertexNode->vertex->degree ; neighbour++)
            {
                printf(" %d",currentVertexNode->nhood[neighbour]->vertex->id);
            }
            printf("\n");
            currentVertexNode = currentVertexNode->next;
        }
    }
    FreeGraph(graph);
    graph = ReadGraph();
  }
  return 0;
}
