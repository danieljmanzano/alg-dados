all:
	gcc lista.c arvore.c main.c set.c -o teste -Wall -std=c99 -fsanitize=address
# gcc teste.c -o gerador -Wall -std=c99

run:
# ./gerador
	./teste

clean:
	rm teste test_cases.txt expected_output.txt gerador
