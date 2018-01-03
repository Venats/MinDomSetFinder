#include "VertexLinkedList.h"

#define NMAX 2187
#define DEG_MAX 16

#define BLUE (-1)
#define WHITE 0
#define RED 1

typedef struct Graph
{
    Node* verticesByNumChoice[DEG_MAX + 2];
    int numberOfVertices;
    int degree[DEG_MAX];
    int numChoice[DEG_MAX + 2];

}Graph;