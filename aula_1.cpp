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
        int aux = vetor[maior];
        vetor[maior] = vetor[n];
        vetor[n] = aux;
        desce(vetor, maior, tam);
    }
}

void constroi_heap(int vetor[], int tam){
    int n = pai(tam - 1);
    for(int i = n; i >= 0; i--){
        desce(vetor, i, tam);
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
    
    for(int i = 0; i<tam; i++){
        printf("%d\n", vetor[i]);
    }

    return EXIT_SUCCESS;
}