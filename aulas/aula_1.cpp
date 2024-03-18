#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int pai(int n){
    return (n-1)/2;
}

int filho_esq(int n){
    return n*2 + 1;
}

int filho_dir(int n){
    return n*2 + 2;
}

void troca(int *x, int *y){
    int aux = *x;
    *x = *y;
    *y = aux;
}

void desce(int vetor[], int n, int tam){
    int esq = filho_esq(n);
    int dir = filho_dir(n);
    int maior = n;
    if(esq < tam && vetor[esq] > vetor[maior]){
        maior = esq;
    }
    if(dir < tam && vetor[dir] > vetor[maior]){
        maior = dir;
    }
    if(maior != n){
        troca(&vetor[maior], &vetor[n]);
        desce(vetor, maior, tam);
    }
}

void constroi_heap(int vetor[], int tam){
    int n = pai(tam - 1);
    for(int i = n; i >= 0; i--){
        desce(vetor, i, tam);
    }
}

void sobe(int vetor[], int n){
    int P = pai(n);
    if(vetor[n] > vetor[P]){
        troca(&vetor[n], &vetor[P]);
        sobe(vetor, P);
    }
}

int acessa_max(int vetor[]){
    return vetor[0];
}

int extrai_max(int vetor[], int *tam){
    int max = vetor[0];
    vetor[0] = vetor[--*tam];
    desce(vetor, 0, *tam);
    return max;
}

int altera_prioridade(int vetor[], int tam, int n, int valor){
    if(vetor[n] > valor){
        vetor[n] = valor;
        desce(vetor, n, tam);
    return EXIT_SUCCESS;
    } else if(vetor[n] < valor){
        vetor[n] = valor;
        sobe(vetor, n);
    return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

int insere_elemento(int vetor[], int *tam, int max, int valor){
    int ret = EXIT_SUCCESS;
    if(*tam == max){
        ret = EXIT_FAILURE;
    } else{
        vetor[*tam] = valor;
        sobe(vetor, *tam);
        ++*tam;
    } 
    return ret;
}

void heapsort(int vetor[], int tam){
    int novo_vetor[tam];
    int i = 0;
    while(tam > 0){
        novo_vetor[i] = extrai_max(vetor, &tam);
        i++;
    }
    for(int j = 0; j <= i; j++){
        vetor[j] = novo_vetor[i - j - 1];
    }
}

void test_pai(){
    int r;
    r = pai(6);
    assert(r == 2);

    r = pai(5);
    assert(r == 2);

    r = pai(0);
    assert(r == 0);
}

void test_filho_esq(){
    int r;
    r = filho_esq(0);
    assert(r == 1);

    r = filho_esq(1);
    assert(r == 3);

    r = filho_esq(2);
    assert(r == 5);
}

void test_filho_dir(){
    int r;
    r = filho_dir(0);
    assert(r == 2);

    r = filho_dir(1);
    assert(r == 4);

    r = filho_dir(2);
    assert(r == 6);
}

void test_desce(){
    int entrada[] = {1,5,3,4,10,2,0};
    int saida[]   = {5,10,3,4,1,2,0};
    int i;
    int max_size = sizeof(entrada)/sizeof(entrada[0]);
    
    desce(entrada,0,max_size);
    
    for (i=0; i < max_size; i++){
        assert(entrada[i] == saida[i]);
    }
}

void test_constroi_heap(){
    int entrada[] = {1,50,20,62,60,25,30};
    int saida[]   = {62,60,30,50,1,25,20};
    int i;
    int max_size = sizeof(entrada)/sizeof(entrada[0]);
    
    constroi_heap(entrada,max_size);
    
    for (i=0;i<max_size;i++){
        assert(entrada[i]==saida[i]);
    }

}

void test_sobe(){
    int entrada[] = {62, 60, 30, 50, 100, 25, 20};
    int saida[] = {100, 62, 30, 50, 60, 25, 20};
    int i;
    int max_size = sizeof(entrada)/sizeof(entrada[0]);

    sobe(entrada, 4);

    for(i = 0; i < max_size; i++){
        assert(entrada[i] == saida[i]);
    }
}

void test_acessa_max(){
    int v[] = {100,62,30,50,60,25,20};
    assert(acessa_max(v) == 100);
}

void test_extrai_max(){
    int entrada[] = {100,62,30,50,60,25,20};
    int saida1[] = {62,60,30,50,20,25};
    int saida2[] = {60,50,30,25,20};

    int i;
    int max_size = sizeof(entrada)/sizeof(entrada[0]);
    
    assert(extrai_max(entrada, &max_size) == 100);
    assert(max_size == 6);
    
    for (i = 0; i < max_size; i++){
        assert(entrada[i] == saida1[i]);
    }
    
    assert(extrai_max(entrada, &max_size) == 62);
    assert(max_size == 5);
    
    for (i = 0; i < max_size; i++){
        assert(entrada[i] == saida2[i]);
    }
}

void test_insere_elemento(){
    int max_size = 10;
    int entrada[10] = {100,62,30,50,60,25,20};
    int saida1[] = {100,70,30,62,60,25,20,50};
    int saida2[] = {150,100,30,70,60,25,20,50,62};

    int i;
    int tam = 7;
    
    assert(insere_elemento(entrada, &tam, max_size, 70) == EXIT_SUCCESS);
    assert(tam == 8);
    
    for (i = 0; i < tam; i++){
        assert(entrada[i] == saida1[i]);
    }
    
    assert(insere_elemento(entrada, &tam, max_size, 150) == EXIT_SUCCESS);
    assert(tam == 9);
    
    for (i=0;i<tam;i++){
        assert(entrada[i] == saida2[i]);
    }
}

void test_altera_prioridade(){
    /*inicializacao*/
    int max_size = 10;
    int entrada[10] = {100,62,30,50,60,25,20};
    int saida1[] = {105,100,30,50,60,25,20};
    int saida2[] = {100,60,30,50,1,25,20};
    int i;
    int tam = 7 ;

    assert(altera_prioridade(entrada, tam, 1, 105) == EXIT_SUCCESS);

    for (i=0;i<tam;i++){
        assert(entrada[i]==saida1[i]);
    }

    assert(altera_prioridade(entrada, tam, 0, 1) == EXIT_SUCCESS);

    for (i = 0; i < tam; i++){
        assert(entrada[i]==saida2[i]);
    }
}

void test_heapsort(){
    int entrada[] = {100,62,30,50,60,25,20};
    int saida[] = {20,25,30,50,60,62,100};
    int tam = sizeof(entrada)/sizeof(entrada[0]);
    int i;

    heapsort(entrada, tam);
    for (i = 0; i < tam; i++){
        assert(entrada[i] == saida[i]);
    }
}

int main(void){
    test_filho_dir();
    test_filho_esq();
    test_pai();
    test_desce();
    test_constroi_heap();
    test_sobe();
    test_acessa_max();
    test_extrai_max();
    test_insere_elemento();
    test_altera_prioridade();
    test_heapsort();
    
    return EXIT_SUCCESS;
}
