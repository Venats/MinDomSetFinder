typedef struct Node
{
  int vertex;
  struct Node** nhood;
  struct Node* next;
  struct Node* prev;
}Node;
void PrintList(Node** head);
void DeleteNodeNoFree(Node* toDelete,Node** headPointer);
void InsertNewNodeAtHead(int vertex, Node** head);
void InsertExistingNodeAtHead(Node* node, Node** head);
void ChangeLists(Node* toChange, Node** head1,Node** head2);
Node* FindVertexNode(int vertex, Node* head);
Node* GetNeighbourNode(Node* currentVertex, int neighbour, int degree);
void InitalizeVertexNeighbourhoods(Node** numChoiceVertexList,int size, int* numChoice,int* degree,int** adjacent);
void FreeVertexListPointers(Node** numChoiceVertexList,int size);
