CC=gcc
FLAGS= -Wall -g
OBJECTS_MAIN=main.o
OBJECTS_GRAPH=algo.o graph.o

all: graph

graph: $(OBJECTS_MAIN) $(OBJECTS_GRAPH)
	$(CC) $(FLAGS) $(OBJECTS_MAIN) $(OBJECTS_GRAPH) -o graph
	
main.o: main.c algo.h
	$(CC) $(FLAGS) -c main.c
	
algo.o: algo.c algo.h graph.h
	$(CC) $(FLAGS) -c algo.c

graph.o: graph.c graph.h
	$(CC) $(FLAGS) -c graph.c


.PHONY: clean all

clean:
	rm -f *.o graph