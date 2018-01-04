#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "GraphIO.h"
#include "VertexLinkedList.h"
#include "Util.h"
#include "Graph.h"

#define NMAX 2187
#define DEG_MAX 16

#define BLUE (-1)
#define WHITE 0
#define RED 1

Node* verticesByNumChoice[DEG_MAX + 2];
int numberOfVertices;
int degree[DEG_MAX];
int numChoice[DEG_MAX + 2];

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
  if(outputType = -1) return 0;

  //while(ReadGraph())
  //{

  //}
  return 0;
}
