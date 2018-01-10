CC = gcc
minDom: VertexLinkedList.h VertexLinkedList.c Graph.h Graph.c GraphIO.c GraphIO.h FindMinDominatingSet.c
	$(CC) VertexLinkedList.c GraphIO.c Graph.c FindMinDominatingSet.c -o FindMinDominatingSet.exe

.PHONY: clean
clean:
	rm *.exe  *.o *.h.gch

.PHONY: test
test:
	./FindMinDominatingSet.exe 1 < testInput.txt