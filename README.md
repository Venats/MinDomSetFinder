Still working on this currently the program does find the minimum dominating set of a graph but I'm outputing a lot of information I used to debug and the output format for the minimum dominating set isnt that nice.

While it does this is NP time I'll be trying to make this run as fast as possible

### Definitions (work in progress)
**dominating set** - A set of vertices such that all vertices in a graph are either in the dominating set or adjacent to a vertex in the dominating set

**Close neighbourhood of a vertex v** - the set of all vertices adjacent to v and v itself

**numChoice of a vertex v** - This is the number of vertices adjacent to v which are in the undecided state

**dominating degree of a vertex v** - The dominating degree of a vertex is the number of undominated vertices in the closed neighbourhood of the vertex

**dominator degree of a vertex v** - the maximum dominating degree of the undecided vertices in the close neighbourhood of v