
#define BLUE (-1)
#define WHITE 0
#define RED 1

typedef enum Color {blue, white, red} Color;
typedef struct Vertex
{
    int id;
    Color color;

}Vertex;
Vertex* NewNode(int id)
{
    Vertex* newVertex = (struct Vertex*)malloc(sizeof(struct Vertex));
    newVertex->id = id;
    newVertex->color = white;
}

