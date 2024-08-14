all:	ponto.o circulo.o main.o 
	gcc ponto.o circulo.o main.o -o main -Wall -std=c99

ponto.o:
	gcc -c ponto.c -o ponto.o

circulo.o:
	gcc -c circulo.c -o circulo.o

main.o:
	gcc -c main.c -o main.o

run:
	./main

clean:
	rm *.o main



#~~aqui pra baixo era um makefile de exemplo que eu tinha feito, como não tem como criar dois arquivo makefile na pasta vou deixar ele todo aqui como comentário

#exemplo de como funciona o makefile
#o abobra é o arquivo que quero compilar como item ou cliente, tanto faz (ambos os casos compilam igual)
#"saida" vai ser meu executavel

#all:	abobra.o abobra1.o #abobra2.o abobra3.o ... e vai indo
#	gcc abobra.o abobra1.o -o saida -Wall -std=c99


#abobra.o:
#	gcc -c abobra.c -o abobra.o

#abobra1.o:
#	gcc -c abobra1.c -o abobra1.o
#e vai indo quantos abobra precisarls


#clean:
#	rm *.o saida
#o clean ranca tudo que eu tenha criado ali em cima

#pra compilar tudo é meteli o make que ele vai "escrever" o all (que puxa os abobra que escreve embaixo)
#aí pra usar o clean tem que escrever "make clean"