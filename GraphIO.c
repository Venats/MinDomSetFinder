#include <stdio.h>
#include <stdlib.h>
#include "GraphIO.h"
void Output(int** adjacent,int numberOfVertices,int* degree,int verboseOutput,int graphCounter, int minSize, int* minDomSet)
{
  if(verboseOutput == 1)
  {
    printf("%d ", numberOfVertices);
    for(int i = 0; i < numberOfVertices; i++)
    {
        printf("\n%4d ",degree[i]);
      for(int j = 0; j < degree[i]; j++)
      {
          printf("%4d ",adjacent[i][j] );
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
              int** adjacent,int* numberOfVertices,
              int* degree)
{
  if(scanf("%d", numberOfVertices) != 1)
  {
    //printf("Finished Reading all graphs");
    return 0;
  }
  //TODO: Decide how what to do with constants
  /*if(*numberOfVertices > NMAX)
  {
    printf("Too many vertices in graph, need to increase NMAX and recompile.");
    return 0;
  }*/
  for(int i = 0; i < *numberOfVertices; i++)
  {
    marker[i] = -1;
    if(scanf("%d",&degree[i]) != 1)
    {
      printf("Error reading in a degree for vertex %d", i);
      return 0;
    }
    dominatingDegree[i] = degree[i]+1 ;
    for(int j = 0; j < degree[i]; j++)
    {
      if(scanf("%d", &adjacent[i][j]) != 1)
      {
        printf("Error Reading in adacency. i = %d j = %d",i,j);
        return 0;
      }
    }
  }
  return 1;
}
