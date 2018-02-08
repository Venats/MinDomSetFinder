Still working on this so doesn't currently do much. But eventually this should find a minimum dominating set in a sparse graph.
While it will do this is NP time I'll be trying to make this run as fast as possible

### Definitions (work in progress)
**dominating set** - A set of vertices such that all vertices in a graph are either in the dominating set or adjacent to a vertex in the dominating set

**Close neighbourhood of a vertex v** - the set of all vertices adjacent to v and v itself

**numChoice of a vertex v** - This is the number of vertices adjacent to v which are in the undecided state

**dominating degree of a vertex v** - The dominating degree of a vertex is the number of undominated vertices in the closed neighbourhood of the vertex

**dominator degree of a vertex v** - the maximum dominating degree of the undecided vertices in the close neighbourhood of v
