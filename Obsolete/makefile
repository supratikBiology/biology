parse.exe: look.cpp avl.o atomType.o bondType.o moleculeType.o HyperNode.o HyperEdge.o
	g++ -g look.cpp avl.o atomType.o bondType.o moleculeType.o HyperNode.o HyperEdge.o -o parse.exe

atomType.o: atomType.c atomType.h
	g++ -g -c atomType.c -o atomType.o

bondType.o: bondType.cpp bondType.h
	g++ -g -c bondType.cpp -o bondType.o

BitGraph.o: BitGraph.cpppp BitGraph.h
	g++ -g -c Molecule.cpp -o Molecule.o
	
HyperGraph.o: HyperNode.h HyperNode.cpp HyperEdge.o Molecule.o
	g++ -g -c HyperNode.cpp -o HyperNode.o

HyperNode.o: HyperNode.h HyperNode.cpp HyperEdge.o
	g++ -g -c HyperNode.cpp HyperEdge.o -o HyperNode.o

HyperEdge.o: HyperEdge.h HyperEdge.cpp 
	g++ -g -c HyperEdge.cpp -o HyperEdge.o

Molecule.o: Molecule.cpp Molecule.h
	g++ -g -c Molecule.cpp -o Molecule.o
	

#avl.o: avl.cpp avl.h
#	g++ -g -c avl.cpp -o avl.o

