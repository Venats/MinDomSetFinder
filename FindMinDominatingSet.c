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

    FreeGraph(graph);
    graph = ReadGraph();
  }
  return 0;
}
