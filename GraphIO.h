#include "VertexLinkedList.h"

void Output(int** adjacent,int numberOfVertices,
            int* degree, int verboseOutput,
            int graphCounter, int minSize, int* minDomSet);
int ReadGraph(int* dominatingDegree, int* marker,
              Node** verticesByNumChoice,int* numChoice,int* numberOfVertices,
              int* degree,int maxSize);
