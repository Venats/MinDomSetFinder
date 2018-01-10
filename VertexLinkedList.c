#include <stdio.h>
#include <stdlib.h>
#include "VertexLinkedList.h"
Vertex* NewVertex(int id, int degree)
{
    Vertex* newVertex = (struct Vertex*)malloc(sizeof(struct Vertex));
    newVertex->id = id;
    newVertex->degree = degree;
    newVertex->state = undecided;

    newVertex->numDominated = 0;
    newVertex->numChoice = degree+1;
    newVertex->dominatingDegree = degree+1;
    newVertex->dominatorDegree = 0;

    return newVertex;
}
Node* NewNode(Vertex* vertex)
{
  Node* newNode = (struct Node*)malloc(sizeof(struct Node));
  newNode->vertex = vertex;
  newNode->nhood = (struct Node**)malloc(sizeof(struct Node*) * vertex->degree);
  newNode->neighbourIDs = (int*)malloc(sizeof(int*) * vertex->degree);
  newNode->next = NULL;
  newNode->prev = NULL;
  return newNode;
}
void PrintList(Node** head)
{
  if(*head == NULL)
  {
    printf("the list is empty\n");
    return;
  }
  Node currentVertex = **head;
  printf("vertex: %3d , ", currentVertex.vertex->id);
  while(currentVertex.next != NULL )
  {
    currentVertex = *currentVertex.next;
    printf("vertex: %3d ,", currentVertex.vertex->id);
  }
  printf("\n");
}

void DeleteNodeNoFree(Node* toDelete,Node** headPointer)
{
  if(*headPointer == toDelete)
  {
    *headPointer = toDelete->next;
  }
  if(toDelete->next != NULL)
  {
    toDelete->next->prev = toDelete->prev;
  }
  if(toDelete->prev !=NULL)
  {
    toDelete->prev->next = toDelete->next;
  }
}
Node* InsertNewNodeAtHead(Vertex* vertex, Node** head)
{
  Node* newNode = NewNode(vertex);
  if(*head == NULL)
  {
    *head = newNode;
    return newNode;
  }
  (*head)->prev = newNode;
  newNode->next = *head;
  *head = newNode;
  return newNode;
}
void InsertExistingNodeAtHead(Node* node, Node** head)
{

  if(*head == NULL)
  {
    *head = node;
    node->next = NULL;
    node->prev = NULL;
    return;
  }
  (*head)->prev = node;
  node->next = *head;
  node->prev = NULL;
  *head = node;
  return;
}

//moves a vertex for the list with head1 to the list with head2
void ChangeLists(Node* toChange, Node** head1,Node** head2)
{
  DeleteNodeNoFree(toChange, head1);
  InsertExistingNodeAtHead(toChange, head2);
}


Node* GetNeighbourNode(Node* currentVertex, int neighbour)
{
  Node* neighbourNode = NULL;
  int degree = currentVertex->vertex->degree;
  for(int i = 0; i < degree; i++)
  {
    if(currentVertex->nhood[i]->vertex->id == neighbour)
    {
      neighbourNode = currentVertex->nhood[i];
      break;
    }
  }
  return neighbourNode;
}

