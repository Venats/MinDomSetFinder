#ifndef VIEWLINKEDLIST

#define VIEWLINKEDLIST
typedef enum Color {blue, white, red} Color;
typedef struct Node
{
  int vertex;
  Color color;
  struct Node** nhood;
  struct Node* next;
  struct Node* prev;
}Node;
Node* NewNode(int vertex);
void PrintList(Node** head);
void DeleteNodeNoFree(Node* toDelete,Node** headPointer);
void InsertNewNodeAtHead(int vertex, Node** head);
void InsertExistingNodeAtHead(Node* node, Node** head);
void ChangeColor(Node* node, Color color);
void ChangeLists(Node* toChange, Node** head1,Node** head2);
Node* FindVertexNode(int vertex, Node* head);
Node* GetNeighbourNode(Node* currentVertex, int neighbour, int degree);
void InitalizeVertexNeighbourhoods(Node** numChoiceVertexList,int size, int* numChoice,int* degree,int** adjacent);
void FreeVertexListPointers(Node** numChoiceVertexList,int size);

#endif
