#ifndef VIEWLINKEDLIST
#define VIEWLINKEDLIST
typedef enum DomState {inDomSet, undecided, outDomSet} DomState;
typedef struct Vertex
{
    DomState state;
    int id;
    int degree;

    int numDominated;
    int numChoice;
    int dominatingDegree;
    int dominatorDegree;

}Vertex;
typedef struct Node
{
  Vertex* vertex;
  struct Node** nhood;
  int* neighbourIDs;
  struct Node* next;
  struct Node* prev;
}Node;
Vertex* NewVertex(int id, int degree);
Node* NewNode(Vertex* vertex);
void PrintList(Node** head);
void DeleteNodeNoFree(Node* toDelete,Node** headPointer);
Node* InsertNewNodeAtHead(Vertex* vertex, Node** head);
void InsertExistingNodeAtHead(Node* node, Node** head);
void ChangeLists(Node* toChange, Node** head1,Node** head2);
Node* GetNeighbourNode(Node* currentVertex, int neighbour);


#endif
