CC = gcc

minDom: VertexLinkedList.h VertexLinkedList.c GraphIO.c GraphIO.h FindMinDominatingSet.c
	$(CC) VertexLinkedList.c GraphIO.c  FindMinDominatingSet.c -o FindMinDominatingSet.exe

.PHONY: clean
clean:
	rm *.exe  *.o *.h.gch