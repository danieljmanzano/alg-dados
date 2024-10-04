#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "libs/brute.h"
#include "libs/graph.h"

//tentativa de fazer um algoritmo "otimizado" pra solucionar o problema do caixeiro viajante (nao vai ser otimizado nao, mas é pra ser menos pior que o força bruta) 
/*tentando dar uma resumida: o distanciamin usa um algoritmo que me estima um valor minimo para a distancia entre duas cidades usando a primeira como base (só usa no começo do codigo)
o distcidades vai estimando os melhores caminhos dps da primeira cidade
o comparaiguais é pra quando ja tiver estimado tudo e eu tiver formando o caminho ja, ele me ajuda a escolher a melhor opçao entre dois caminhos de mesmo peso
o guia é a funçao "principal" que uso pra criar o caminho correto
o calculadist me fornece o tamanho do meu caminho dps de ter decidido ele todo (nao consigo calcular ele nas funçoes de guia, fica mui dificil)
o tsp só organiza o algoritmo do bagulho e chama as funçoes "em ordem" pra voltar a resposta bonitinha pra main printar*/


struct answer_ {
  int *path, minDistance;
}; //peguei do tad mermo e qui si lasque. nao tinha uma funçao pra criar resposta entao tive que fazer aq (aí precisava acessar o tipo dele)

int pa(double n){ //nao sei pra que serve mas usa na entrada, vou acreditar que funciona para algo
    return ceil((n * (n + 1)) / 2); 
}

int distanciamin(Graph *graph, int numcidades){ //aqui vou calcular a distancia minima que duas cidades podem ter pra primeira vez que mudo de cidade
    int aux = 0, soma = 0; //o auxiliar vai pegar o menor valor da linha/coluna . a soma vou usar pra achar essa distancia minima aí

    for(int i = 0; i < numcidades; i++){
        aux = getWeightEdge(graph, i, 0); //pego ja o primeiro numero da "matriz" pra comparar dps
        for(int j = 1; j < numcidades; j++){ //aq começo no 1 pq ja tenho o valor do 0 da linha de cima
            if(aux > getWeightEdge(graph, i, j) && aux != INT_MAX) aux = getWeightEdge(graph, i, j); //procuro um valor menor na linha
        } //saindo daqui eu tenho o menor valor da linha
        if((!aux) || aux == INT_MAX) break; //se o menor valor na linha é 0 nao vou fazer nenhuma alteração na frente (ou caso seja INT_MAX no bagulho), entao dá break
        soma += aux; //a soma basicamente armazena a soma dos menores valores das linhas e colunas
        for(int j = 0; j < numcidades; j++){ //percorro a mesma linha pra mexer aq
            insertEdge(graph, i, j, getWeightEdge(graph, i, j) - aux); //subtraio o menor valor da linha em geral dali
        }
    }

    for(int i = 0; i < numcidades; i++){ //mesma logica de cima, só muda que to mexendo com coluna e nao linha
        aux = getWeightEdge(graph, 0, i); 
        for(int j = 1; j < numcidades; j++){ 
            if(aux > getWeightEdge(graph, j, i) && aux != INT_MAX) aux = getWeightEdge(graph, j, i); 
        } 
        if((!aux) || aux == INT_MAX) break;
        soma += aux;
        for(int j = 0; j < numcidades; j++){ 
            insertEdge(graph, j, i, getWeightEdge(graph, j, i) - aux); 
        }
    }//dps disso tudo tenho teoricamente uma "matriz reduzida" e a soma de todos os minimos que achei no caminho
    
    return soma;
}

int distcidades(Graph *graphoriginal, int numcidades, int x, int y, int custoatual){ //calcula distancia para as proximas cidades (dps da primeira)
    Graph *graph = cloneGraph(graphoriginal); //esse "graph" na funçao é um auxiliar. como vou fazer alteraçoes nele nao posso usar o original pq nao tenho ctz se esse é realmente o caminho que vou acabar tomando
    int custocaminho = getWeightEdge(graph, x, y); //vou usar dps pra retornar o custo estimado final
    int altera = 0, aux, flag0 = 0, flagmax = 1, auxmenor; //altera vai guardar uma possivel alteraçao nova que eu faça aq, vou precisar pra estimar o custo dps; aux vai servir pra ver os valores dos vertices no geral; flag0 me diz se teve algum 0 na situaçao; flagmax me diz se teve algo diferente de INT_MAX na situaçao; auxmenor guarda o menor valor na situação 
    for(int j = 0; j < numcidades; j++){ //coloco todos os vertices dessa linha como INT_MAX
        insertEdge(graph, x, j, INT_MAX);
    }
    for(int i = 0; i < numcidades; i++){ //coloco todos os vertices dessa coluna como INT_MAX
        insertEdge(graph, i, y, INT_MAX);
    }
    insertEdge(graph, y, x, INT_MAX); //coloco o vertice de y pra x como INT_MAX tbm (teoricamente o grafo do fernando ja faz isso quando uso x pra y mas so pra garantir)

    for(int i = 0; i < numcidades; i++){
        auxmenor = getWeightEdge(graph, i, 0);
        for(int j = 1; j < numcidades; j++){
            aux = getWeightEdge(graph, i, j);
            if(auxmenor > aux) auxmenor = aux; //toda vez que acho um menor eu guardo no auxmenor
            if(aux != INT_MAX) flagmax = 0; //caso eu ache algo diferente de INT_MAX na linha eu marco a flag como 0
            if(!aux) flag0 = 1; //caso eu ache um 0 eu marco a flag (fica como menor valor do bagulho)
        }
        if(flag0 || flagmax){ //caso tenha tido um 0 na linha ou se a linha foi inteira de INT_MAX eu nao altero nada
            flag0 = 0; //só volto as flags pro valor original pra continuar as comparaçoes dps
            flagmax = 1;
            continue; 
        }else{ //caso o menor valor na linha nao tenha sido 0 && a linha nao é cheia de INT_MAX, preciso subtrair o menor valor do bagulho de todos os presentes na linha
            altera += auxmenor;
            for(int a = 0; a < numcidades; a++){
                if(getWeightEdge(graph, i, a) == INT_MAX) continue; //caso seja INT_MAX no bagulho eu nao subtraio, continua como max mesmo
                insertEdge(graph, i, a, getWeightEdge(graph, i, a) - auxmenor); //recoloco o valor desse vertice como ele menos o valor minimo que achei ali em cima
            }
        }
    }

    for(int j = 0; j < numcidades; j++){ //repito todo o processo de cima só que agora analisando em colunas 
        auxmenor = getWeightEdge(graph, 0, j);
        for(int i = 1; i < numcidades; i++){
            aux = getWeightEdge(graph, i, j);
            if(auxmenor > aux) auxmenor = aux; 
            if(aux != INT_MAX) flagmax = 0; 
            if(!aux) flag0 = 1; 
        }
        if(flag0 || flagmax){ 
            flag0 = 0; 
            flagmax = 1;
            continue; 
        }else{ 
            for(int a = 0; a < numcidades; a++){
                if(getWeightEdge(graph, a, j) == INT_MAX) continue; 
                insertEdge(graph, a, j, getWeightEdge(graph, a, j) - auxmenor); 
            }
        }
    }

    return (custoatual + custocaminho + altera); //retorno o custo que calculei logo antes + custo pra chegar nessa cidade atual + qualquer alteraçao que eu tenha feito aqui
}

void alteragrafo(Graph *graph, int numcidades, int x, int y, int custoatual){ //mesmo algoritmo do distcidades só que aq ao inves de estimar distancia eu só altero permanentemente meu grafo original pra funcionar o algoritmo mais pra frente
    int aux, flag0 = 0, flagmax = 1, auxmenor;  
    for(int j = 0; j < numcidades; j++){ 
        insertEdge(graph, x, j, INT_MAX);
    }
    for(int i = 0; i < numcidades; i++){ 
        insertEdge(graph, i, y, INT_MAX);
    }
    insertEdge(graph, y, x, INT_MAX); 

    for(int i = 0; i < numcidades; i++){
        auxmenor = getWeightEdge(graph, i, 0);
        for(int j = 1; j < numcidades; j++){
            aux = getWeightEdge(graph, i, j);
            if(auxmenor > aux) auxmenor = aux;
            if(aux != INT_MAX) flagmax = 0; 
            if(!aux) flag0 = 1; 
        }
        if(flag0 || flagmax){ 
            flag0 = 0; 
            flagmax = 1;
            continue; 
        }else{ 
            for(int a = 0; a < numcidades; a++){
                if(getWeightEdge(graph, i, a) == INT_MAX) continue; //caso seja INT_MAX no bagulho eu nao subtraio, continua como max mesmo
                insertEdge(graph, i, a, getWeightEdge(graph, i, a) - auxmenor); //recoloco o valor desse vertice como ele menos o valor minimo que achei ali em cima
            }
        }
    }

    for(int j = 0; j < numcidades; j++){ 
        auxmenor = getWeightEdge(graph, 0, j);
        for(int i = 1; i < numcidades; i++){
            aux = getWeightEdge(graph, i, j);
            if(auxmenor > aux) auxmenor = aux; 
            if(aux != INT_MAX) flagmax = 0; 
            if(!aux) flag0 = 1; 
        }
        if(flag0 || flagmax){ 
            flag0 = 0; 
            flagmax = 1;
            continue; 
        }else{ 
            for(int a = 0; a < numcidades; a++){
                if(getWeightEdge(graph, a, j) == INT_MAX) continue; 
                insertEdge(graph, a, j, getWeightEdge(graph, a, j) - auxmenor); 
            }
        }
    }

    return;
}

int comparaiguais(Graph *graph, int *resp, int *mapa, int numcidades, int comeco, int indice, int pos1, int pos2){ //faz a mesma coisa do guia so que só pra procurar a melhor opçao posterior quando temos dois caminhos de peso igual
    
    int aux1 = getWeightEdge(graph, pos1, 0);
    for(int i = 1; i <= numcidades; i++){
        if(mapa[i] == 0) continue; //caso a posição esteja marcada com 0 quer dizer que ja passei ali
        int comp = getWeightEdge(graph, pos1, i);
        if(comp == INT_MAX) continue;
        if(aux1 > comp) aux1 = comp; //pego o caminho menor
    }

    int aux2 = getWeightEdge(graph, pos2, 0);
    for(int i = 1; i <= numcidades; i++){
        if(mapa[i] == 0) continue; //caso a posição esteja marcada com 0 quer dizer que ja passei ali
        int comp = getWeightEdge(graph, pos2, i);
        if(comp == INT_MAX) continue;
        if(aux2 > comp) aux2 = comp; //pego o caminho menor
    }

    if(aux1 < aux2) return pos1; //retorno a posiçao que tem menor peso de caminhos pela frente
    else return pos2; //por padrao, se eu chegar no fim aqui e os dois aux forem iguais eu acabo retornando o pos2 (se forem iguais nao faz diferença mesmo)
}

void guia(Graph *graph, int *resp, int *mapa, int numcidades, int comeco, int indice, int distmin){ //funçao pra me guiar pelas cidades (pelo melhor caminho dps de ter feito as estimativas nas funçoes de cima)
    int aux = distcidades(graph, numcidades, 0, comeco, distmin); //pego o primeiro caminho antes de entrar no for
    int pos = -30; //esse -30 vai fazer sentido dps
    for(int i = 1; i <= numcidades; i++){
        if(mapa[i] == 0) continue; //caso a posição esteja marcada com 0 quer dizer que ja passei ali
        int comp = distcidades(graph, numcidades, i, comeco, distmin);
        if(comp == INT_MAX) continue;
        if(aux > comp){
            aux = comp; //pego o caminho menor
            pos = i; //marco a posiçao de onde peguei o menor caminho
        }else if(aux == comp && aux != INT_MAX) //caso dois caminhos tenham peso igual tenho que tentar decidir qual vai ser melhor posteriormente
            pos = comparaiguais(graph, resp, mapa, numcidades, comeco, indice, pos, i); //para isso, o comparaiguais vê os caminhos posteriores
    }

    if(pos == -30) return; //caso chegue aqui como -30 quer dizer q passei tudo direto (todas posiçoes marcadas com 0)
    mapa[pos] = 0; //marco a posiçao que passei agora como 0 no mapa
    resp[indice] = pos; //marco a cidade que to indo numa posiçao do vetor resposta
    indice++;
    distmin = aux; //o distmin aqui vai ter o tamanho do caminho que escolhi nessa iteraçao (levo ele pra proxima)
    alteragrafo(graph, numcidades, pos, comeco, distmin); //depois de estimar as distancias tenho que alterar o grafo conforme a decisao que tomei (pra qual cidade sigo)
    guia(graph, resp, mapa, numcidades, pos, indice, distmin); 
    return; //esse return é só pra garantir, teoricamente nao é pra chegar aqui
}

void diagonal(Graph *graph, int numcidades){ //so coloca a diagonal principal com o tamanho maximo
    for(int i = 0; i < numcidades; i++){
        insertEdge(graph, i, i, INT_MAX);
    }

    return;
}

int calculadist(Graph *graph, int *resp, int numcidades){ //só calcula a distancia percorrida final com base no caminho que tracei no guia
    int disttotal = 0;
    for(int i = 0; i < numcidades; i++) disttotal += getWeightEdge(graph, resp[i], resp[i+1]); //vou pegando as distancias de acordo com o melhor caminho que eu achei
    return disttotal; //ao fim do for ja vou ter a distancia total que percorri, aí retorno ela
}

Answer tsp(Graph *graph, int numcidades, int primeira){
    diagonal(graph, numcidades); //arrumo a diagonal principal pra ter um tamanho grandao (preciso disso no algoritmo)
    int distmin = distanciamin(graph, numcidades);

    int *mapa = malloc(sizeof(int) * (numcidades + 1)); //vetor pra guardar as cidades (e mexer se entro nelas)
    int *resp = malloc(sizeof(int) * (numcidades + 1));
    mapa[0] = 0; //a primeira posição eu vou usar pra marcar em quantas cidades entrei
    for(int i = 1; i <= numcidades; i++) mapa[i] = i;

    guia(graph, resp, mapa, numcidades, primeira, 0, distmin); //dps de entrar aq teoricamente eu ja vou ter o melhor caminho (os numeros vao ser a sequencia de cidades que devo tomar) dentro do *resp
    int dist = calculadist(graph, resp, numcidades);

    Answer resposta;
    resposta.minDistance = dist;
    resposta.path = resp;
    return resposta;
}

int main(void){

    int numcidades = 0, vert1 = 0, vert2 = 0, peso = 0, comeco = 0; //peguei do codigo do fernando. só pra pegar a entrada e arrumar o tad isso aq
    scanf(" %d", &numcidades);
    scanf(" %d", &comeco);
    Graph *graph = create_graph(numcidades, 0, 1);
    for(int i = 0; i < pa(numcidades - 1); i++){
        scanf(" %d %d %d", &vert1, &vert2, &peso);
        insertEdge(graph, vert1, vert2, peso);
    }

    Answer resp = tsp(graph, numcidades, comeco);
    printf("distancia minima percorrida: %d\n", resp.minDistance);
    printf("caminho percorrido:\n");
    for(int i = 0; i < numcidades; i++) printf("%d -", resp.path[i]);
    printf("%d\n", comeco);

    return 0;
}

//teoricamente ta feito, mas duvido que funciona