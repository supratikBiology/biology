parse.exe: look.c avl.o atomType.o bondType.o moleculeType.o HyperNode.o HyperEdge.o
	gcc -g look.c avl.o atomType.o bondType.o moleculeType.o HyperNode.o HyperEdge.o -o parse.exe

atomType.o: atomType.c atomType.h
	gcc -g -c atomType.c -o atomType.o

bondType.o: bondType.c bondType.h
	gcc -g -c bondType.c -o bondType.o

moleculeType.o: moleculeType.c moleculeType.h
	gcc -g -c moleculeType.c -o moleculeType.o

# Hypergraph.o

HyperNode.o: HyperNode.h HyperNode.c HyperEdge.o avl.o
	gcc -g -c HyperNode.c HyperEdge.o avl.o -o HyperNode.o

HyperEdge.o: HyperEdge.h HyperEdge.c 
	gcc -g -c HyperEdge.c -o HyperEdge.o

avl.o: avl.c avl.h
	gcc -g -c avl.c -o avl.o

