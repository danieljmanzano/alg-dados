all: graph brute vertice main
	gcc -lm ./src/graph.o ./src/brute.o ./src/vertice.o ./src/main.o -o ./src/main -Wall -std=c99
	rm ./src/*.o

graph:
	gcc -c ./libs/impl/graph.c -o ./src/graph.o

brute:
	gcc -c ./libs/impl/brute.c -o ./src/brute.o

vertice:
	gcc -c ./libs/impl/vertice.c -o ./src/vertice.o

main:
	gcc -c ./src/main.c -o ./src/main.o

run:
	./src/main

clean:
	rm ./src/main

remake: clean all