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

void troca(int vetor[], int x, int y){
    int aux = vetor[x];
    vetor[x] = vetor[y];
    vetor[y] = aux;
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
        troca(vetor, maior, n);
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
        troca(vetor, vetor[n], vetor[P]);
        sobe(vetor, P);
    }
}

int acessa_max(int vetor[]){
    return vetor[0];
}

int extrai_max(int vetor[], int *tam){
    int max = vetor[0];
    vetor[0] = vetor[*tam - 1];
    desce(vetor, 0, *tam - 1);
    *tam -= 1;
    return max;
}

void altera_prioridade(int vetor[], int tam, int n, int valor){
    if(vetor[n] > valor){
        vetor[n] = valor;
        desce(vetor, n, tam);
    } else if(vetor[n] < valor){
        vetor[n] = valor;
        sobe(vetor, n);
    }
}

int insere_elemento(int vetor[], int *tam, int max, int valor){
    int ret = EXIT_SUCCESS;
    if(*tam == max){
        ret = EXIT_FAILURE;
    } else{
        vetor[*tam] = valor;
        sobe(vetor, *tam);
        *tam++;
    } 
    return ret;
}

void heap_sort(int vetor[], int tam){
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

int main(void){
    int vetor[] = {9, 20, 5, 34, 63, 4, 59, 21, 10};
    int tam = 9;

    constroi_heap(vetor, tam);
    
    heap_sort(vetor, tam);

    for(int i = 0; i<tam; i++){
        printf("%d\n", vetor[i]);
    }

    return EXIT_SUCCESS;
}
