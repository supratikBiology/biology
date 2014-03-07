# Define the executable
EXE = tester

# set up compiler and options
C = gcc
CC = g++

# FLAGS
#
# ansi flag gives implicit declaration warning of int fileno(...) which
# is found in stdio.h.  Action was taken to resolve this by including the
# library to resolution.
#
# The optimizations flag (-O3) could be turned off with little effect.
# Actually, -O3 gives warnings about variables which may have not been
# initialized before a use.
CFLAGS = -g -Wall -ansi #-O1

# The object files.
OFILES = Utilities.o BitGraph.o tester.o


# If there is a single scanner defined then the -lfl flag is required 
# so that yywrap is defaulted by flex, otherwise it would have to be user
# defined.  The other option (see man flex) would be to define 
# %option noyywrap in the scanner (.l) file.
$(EXE): $(OFILES)
	$(CC) $(CFLAGS) -o $(EXE) $(OFILES)
#	purify $(CC) $(CFLAGS) -o $(EXE).pure $(OFILES)

tester.o: tester.cpp BitGraph.h Utilities.h
	$(CC) $(CFLAGS) -c tester.cpp

Utilities.o: Utilities.cpp Utilities.h
	$(CC) $(CFLAGS) -c Utilities.cpp

BitGraph.o: BitGraph.cpp BitGraph.h
	$(CC) $(CFLAGS) -c BitGraph.cpp
	
clean:
	/bin/rm -f \#* core *~ *.o *.out $(EXE) \
	*.bb* *.da find_dump.txt dir_query.txt > /dev/null

clean_ast:
	/bin/rm -f \#* core *~ ada95_ast_*.o ada95_translation.o \
	*.out $(EXE) *.bb* *.da find_dump.txt dir_query.txt > /dev/null

super_clean:
	/bin/rm -f \#* core *~ *.o *.out $(EXE) \
	lex.$(EXE).c *.bb* *.da find_dump.txt dir_query.txt \
	$(EXE)_parser.* > /dev/null

e2c:
	ada95 -tp /home/calvin/ada_code/e2c/*

compiler:
	rm -f /home/calvin/ada_code/gnat/*~
	ada95 /home/calvin/ada_code/gnat/*

summarize:
	rm -f /home/calvin/ada_code/gnat/*~
	rm -f /home/calvin/ada_code/e2c/*~
	ada95 -st /home/calvin/ada_code/gnat/*
	ada95 -st /home/calvin/ada_code/e2c/*

test_all:
	ada95 -r -u /home/calvin/ada_code/*