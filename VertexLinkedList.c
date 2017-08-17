#include <stdio.h>
#include <stdlib.h>
#include "VertexLinkedList.h"
Node* NewNode(int vertex)
{
  Node* newNode = (struct Node*)malloc(sizeof(struct Node));
  newNode->vertex = vertex;
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
  printf("vertex: %3d , ", currentVertex.vertex);
  while(currentVertex.next != NULL )
  {
    currentVertex = *currentVertex.next;
    printf("vertex: %3d ,", currentVertex.vertex);
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
void InsertNewNodeAtHead(int vertex, Node** head)
{
  Node* newNode = NewNode(vertex);
  if(*head == NULL)
  {
    *head = newNode;
    return;
  }
  (*head)->prev = newNode;
  newNode->next = *head;
  *head = newNode;
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

Node* FindVertexNode(int vertex, Node* head)
{
  Node* vertexNode = head;
  while(vertexNode !=NULL)
  {
    if(vertexNode->vertex == vertex)
    {
      break;
    }
    vertexNode = vertexNode->next;
  }
  return vertexNode;
}
Node* GetNeighbourNode(Node* currentVertex, int neighbour, int degree)
{
  Node* neighbourNode = NULL;
  for(int i = 0; i < degree; i++)
  {
    if(currentVertex->nhood[i]->vertex == neighbour)
    {
      neighbourNode = currentVertex->nhood[i];
      break;
    }
  }
  return neighbourNode;
}
void InitalizeVertexNeighbourhoods(Node** numChoiceVertexList,int size, int* numChoice,int* degree,int** adjacent)
{
  for(int i = 0; i < size; i++)
  {
    Node* currentVertexNode = numChoiceVertexList[i];
    while(currentVertexNode != NULL)
    {
      int currentVertex = currentVertexNode->vertex;
      for(int neighbour = 0; neighbour < degree[currentVertex]; neighbour++)
      {
        Node* neighbourNode = FindVertexNode(adjacent[currentVertex][neighbour], numChoiceVertexList[ numChoice[adjacent[currentVertex][neighbour]] ]);
        currentVertexNode->nhood[neighbour] = neighbourNode;
      }
      currentVertexNode = currentVertexNode->next;
    }
  }
}

void FreeVertexListPointers(Node** numChoiceVertexList,int size)
{
  for(int i = 0; i< size; i++)
  {
    Node* currentNode = numChoiceVertexList[i];
    while(currentNode != NULL)
    {
      Node* nextNode = currentNode->next;
      free(currentNode);
      currentNode = nextNode;
    }
    numChoiceVertexList[i] = NULL;
  }
}
