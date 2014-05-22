IDIR =./
CC=g++
OPT=-O1
CFLAGS= $(OPT) -I$(IDIR)

ODIR=./obj
LDIR =../lib

DEPS = BitGraph.h \
	EdgeAggregator.h \
	EdgeAnnotation.h \
	HyperEdge.h \
   HyperEdgeMultiMap.h \
	HyperGraph.h \
	HyperNode.h \
	Instantiator.h \
	Linker.h \
	Molecule.h \
	PebblerHyperEdge.h \
	PebblerHyperGraph.h \
	PebblerHyperNode.h \
	Rigid.h \
	Utilities.h

_OBJ = BitGraph.o \
	Instantiator.o \
	Linker.o\
   Main.o \
	Molecule.o \
	Rigid.o \
	Utilities.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) 

synth: $(OBJ)
	$(CC) $^ $(CFLAGS) -o $@

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core synth.exe synth.exe.stackdump $(INCDIR)/*~
